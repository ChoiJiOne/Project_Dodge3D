#include <glad/glad.h>
#include <stb_image.h>

#include "Assertion.h"
#include "Skybox.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "TextureUtils.h"

Skybox::~Skybox()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Skybox::Initialize(const std::wstring& rightPath, const std::wstring& leftPath, const std::wstring& topPath, const std::wstring& bottomPath, const std::wstring& frontPath, const std::wstring& backPath)
{
	ASSERT(!bIsInitialized_, "already initialize cube map texture resource...");

	std::vector<std::wstring> resourcePaths = {
		rightPath,
		leftPath,
		topPath,
		bottomPath,
		frontPath,
		backPath,
	};

	std::wstring extension = GetCubemapExtension(resourcePaths);
	if (extension == L"astc")
	{
		cubeMapID_ = CreateAstcCompressionCubemap(resourcePaths);
	}
	else if (extension == L"dds")
	{
		cubeMapID_ = CreateDxtCompressionCubemap(resourcePaths);
	}
	else
	{
		cubeMapID_ = CreateNonCompressionCubemap(resourcePaths);
	}
	
	CreateSkyboxVertexObject();

	bIsInitialized_ = true;
}

void Skybox::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteTextures(1, &cubeMapID_), "failed to delete cube map texture object...");
	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete skybox vertex buffer object...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete skybox vertex array object...");

	bIsInitialized_ = false;
}

void Skybox::Active(uint32_t unit) const
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + unit), "failed to active %d texture unit...", (GL_TEXTURE0 + unit));
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID_), "failed to bind cube map texture...");
}

std::wstring Skybox::GetCubemapExtension(const std::vector<std::wstring>& resourcePaths)
{
	std::wstring expectExtension = StringUtils::ToLower(FileUtils::GetFileExtension(resourcePaths.front()));
	std::wstring extension;

	for (const auto& resourcePath : resourcePaths)
	{
		extension = StringUtils::ToLower(FileUtils::GetFileExtension(resourcePath));

		if (expectExtension != extension)
		{
			return L"";
		}
	}

	return expectExtension;
}

uint32_t Skybox::CreateNonCompressionCubemap(const std::vector<std::wstring>& resourcePaths)
{
	uint32_t cubeMapID;
	GL_ASSERT(glGenTextures(1, &cubeMapID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID), "failed to bind texture object...");

	for (std::size_t index = 0; index < resourcePaths.size(); ++index)
	{
		int32_t width = 0;
		int32_t height = 0;
		int32_t channels = 0;
		std::vector<uint8_t> buffer;
		TextureUtils::LoadImageFromFile(resourcePaths[index], width, height, channels, buffer);

		GLenum target = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);
		GLenum format = TextureUtils::FindTextureFormatFromChannel(channels);
		ASSERT(format != 0xFFFF, "%d is not support image channel...", channels);

		GL_ASSERT(glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer.data()), "failed to allows elements of an image array to be read by shaders...");
	}

	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE), "failed to set texture object warp r...");

	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, 0), "failed to unbind texture object...");

	return cubeMapID;
}

uint32_t Skybox::CreateAstcCompressionCubemap(const std::vector<std::wstring>& resourcePaths)
{
	uint32_t cubeMapID;
	GL_ASSERT(glGenTextures(1, &cubeMapID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID), "failed to bind texture object...");

	for (std::size_t index = 0; index < resourcePaths.size(); ++index)
	{
		std::vector<uint8_t> astcData;
		EAstcBlockSize blockSize = EAstcBlockSize::None;
		TextureUtils::LoadAstcFromFile(resourcePaths[index], astcData, blockSize);

		AstcFileHeader* astcDataPtr = reinterpret_cast<AstcFileHeader*>(astcData.data());

		int32_t xsize = astcDataPtr->xsize[0] + (astcDataPtr->xsize[1] << 8) + (astcDataPtr->xsize[2] << 16);
		int32_t ysize = astcDataPtr->ysize[0] + (astcDataPtr->ysize[1] << 8) + (astcDataPtr->ysize[2] << 16);
		int32_t zsize = astcDataPtr->zsize[0] + (astcDataPtr->zsize[1] << 8) + (astcDataPtr->zsize[2] << 16);
		int32_t xblocks = (xsize + astcDataPtr->blockdimX - 1) / astcDataPtr->blockdimX;
		int32_t yblocks = (ysize + astcDataPtr->blockdimY - 1) / astcDataPtr->blockdimY;
		int32_t zblocks = (zsize + astcDataPtr->blockdimZ - 1) / astcDataPtr->blockdimZ;
		GLenum compressionFormat = static_cast<GLenum>(blockSize);

		uint32_t byteToRead = (xblocks * yblocks * zblocks) << 4;

		GLenum target = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);
		GL_ASSERT(glCompressedTexImage2D(target, 0, compressionFormat, xsize, ysize, 0, byteToRead, reinterpret_cast<const void*>(&astcDataPtr[1])), "failed to compress texture...");
	}

	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE), "failed to set texture object warp r...");

	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, 0), "failed to unbind texture object...");

	return cubeMapID;
}

uint32_t Skybox::CreateDxtCompressionCubemap(const std::vector<std::wstring>& resourcePaths)
{
	uint32_t cubeMapID;
	GL_ASSERT(glGenTextures(1, &cubeMapID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID), "failed to bind texture object...");

	for (std::size_t index = 0; index < resourcePaths.size(); ++index)
	{
		std::vector<uint8_t> dxtData;
		GLenum format;
		uint32_t blockSize;
		TextureUtils::LoadDxtFromFile(resourcePaths[index], dxtData, format, blockSize);

		DDSFileHeader* dxtDataPtr = reinterpret_cast<DDSFileHeader*>(dxtData.data());
		uint32_t width = dxtDataPtr->dwWidth;
		uint32_t height = dxtDataPtr->dwHeight;
		uint32_t linearSize = dxtDataPtr->dwPitchOrLinearSize;
		uint32_t mipMapCount = dxtDataPtr->dwMipMapCount;
		uint32_t bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		uint8_t* bufferPtr = reinterpret_cast<uint8_t*>(&dxtDataPtr[1]);

		GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), "failed to set pixel storage modes...");

		GLenum target = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);
		for (uint32_t level = 0, offset = 0; level < mipMapCount; ++level)
		{
			if (width == 0 || height == 0)
			{
				mipMapCount--;
				continue;
			}

			uint32_t size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
			GL_ASSERT(glCompressedTexImage2D(target, level, format, width, height, 0, size, bufferPtr + offset), "failed to compression texture...");

			offset += size;
			width /= 2;
			height /= 2;
		}
	}

	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, 0), "failed to unbind texture object...");

	return cubeMapID;
}

void Skybox::CreateSkyboxVertexObject()
{
	std::vector<float> vertices = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	vertexCount_ = static_cast<uint32_t>(vertices.size());

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate skybox vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate skybox vertex buffer...");
	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind skybox vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind skybox vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * static_cast<uint32_t>(vertices.size()), vertices.data(), GL_STATIC_DRAW), "failed to create a new data store for a skybox vertex buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0)), "failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind skybox vertex array...");
}