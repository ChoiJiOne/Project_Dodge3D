#include <glad/glad.h>

#include "Assertion.h"
#include "StaticMesh.h"

StaticMesh::~StaticMesh()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void StaticMesh::Initialize(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
	ASSERT(!bIsInitialized_, "already initialize static mesh resource...");

	indexCount_ = static_cast<uint32_t>(indices.size());

	const void* vertexBufferPtr = reinterpret_cast<const void*>(vertices.data());
	uint32_t vertexBufferSize = static_cast<uint32_t>(vertices.size()) * Vertex::GetStride();

	const void* indexBufferPtr = reinterpret_cast<const void*>(indices.data());
	uint32_t indexBufferSize = static_cast<uint32_t>(indices.size()) * sizeof(uint32_t);
	
	SetupMesh(vertexBufferPtr, vertexBufferSize, indexBufferPtr, indexBufferSize);

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, position))), "failed to define an array of generic vertex attribute data");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable a generic vertex attribute array");

	GL_ASSERT(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, normal))), "failed to define an array of generic vertex attribute data");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable a generic vertex attribute array");

	GL_ASSERT(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Vertex::GetStride(), (void*)(offsetof(Vertex, texture))), "failed to define an array of generic vertex attribute data");
	GL_ASSERT(glEnableVertexAttribArray(2), "failed to enable a generic vertex attribute array");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array object...");

	bIsInitialized_ = true;
}

void StaticMesh::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteBuffers(1, &indexBufferObject_), "failed to delete static mesh index buffer...");
	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete static mesh vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete static mesh vertex array object...");

	bIsInitialized_ = false;
}

void StaticMesh::SetupMesh(const void* vertexBufferPtr, uint32_t vertexBufferSize, const void* indexBufferPtr, uint32_t indexBufferSize)
{
	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate static mesh vertex array object...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate static mesh vertex buffer...");
	GL_ASSERT(glGenBuffers(1, &indexBufferObject_), "failed to generate static mesh index buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind static mesh vertex array object...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind static mesh vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexBufferPtr, GL_STATIC_DRAW), "failed to initialize static mesh vertex buffer...");
	GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject_), "failed to bind static mesh index buffer...");
	GL_ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferPtr, GL_STATIC_DRAW), "failed to initialize static mesh index buffer...");
}