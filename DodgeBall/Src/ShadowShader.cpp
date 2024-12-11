#include <glad/glad.h>

#include "Assertion.h"
#include "Light.h"
#include "StaticMesh.h"
#include "ShadowShader.h"

ShadowShader::~ShadowShader() {}

void ShadowShader::SetLight(const Light* light)
{
	SetUniform("lightView", light->GetViewMatrix());
	SetUniform("lightProjection", light->GetProjectionMatrix());
}

void ShadowShader::DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh)
{
	SetUniform("world", world);

	GL_ASSERT(glBindVertexArray(mesh->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
	GL_ASSERT(glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");
}