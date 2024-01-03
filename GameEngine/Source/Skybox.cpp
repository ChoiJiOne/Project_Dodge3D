#include "Skybox.h"

#include "Assertion.h"
#include "FileManager.h"
#include "GLAssertion.h"
#include "StringUtils.h"

#include <glad/glad.h>
#include <stb_image.h>

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

	std::vector<std::string> resourcePaths = {
		StringUtils::Convert(rightPath),
		StringUtils::Convert(leftPath),
		StringUtils::Convert(topPath),
		StringUtils::Convert(bottomPath),
		StringUtils::Convert(frontPath),
		StringUtils::Convert(backPath),
	};

	GL_ASSERT(glGenTextures(1, &cubeMapID_), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID_), "failed to bind texture object...");

	for (std::size_t index = 0; index < resourcePaths.size(); ++index)
	{
		int32_t width = 0;
		int32_t height = 0;
		int32_t channels = 0;
		uint8_t* bufferPtr = stbi_load(resourcePaths[index].c_str(), &width, &height, &channels, 0);
		ASSERT(bufferPtr != nullptr, "failed to load %s cube map texture...", resourcePaths[index].c_str());

		GLenum target = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);
		GLenum format = 0;
		switch (channels)
		{
		case 1:
			format = static_cast<GLenum>(GL_RED);
			break;

		case 3:
			format = static_cast<GLenum>(GL_RGB);
			break;

		case 4:
			format = static_cast<GLenum>(GL_RGBA);
			break;

		default:
			ASSERT(false, "%d is not support image channel...", channels);
		}

		GL_ASSERT(glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bufferPtr), "failed to allows elements of an image array to be read by shaders...");

		stbi_image_free(bufferPtr);
		bufferPtr = nullptr;
	}

	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE), "failed to set texture object warp r...");

	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, 0), "failed to unbind texture object...");

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