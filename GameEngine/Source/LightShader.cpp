#include <glad/glad.h>

#include "Assertion.h"
#include "Camera3D.h"
#include "Light.h"
#include "LightShader.h"
#include "Material.h"
#include "StaticMesh.h"
#include "ShadowMap.h"

LightShader::~LightShader() {}

void LightShader::SetMaterial(const Material* material)
{
	SetUniform("material.ambientRGB", material->GetAmbientRGB());
	SetUniform("material.diffuseRGB", material->GetDiffuseRGB());
	SetUniform("material.specularRGB", material->GetSpecularRGB());
	SetUniform("material.shininess", material->GetShininess());
}

void LightShader::SetLight(const Light* light)
{
	SetUniform("lightView", light->GetViewMatrix());
	SetUniform("lightProjection", light->GetProjectionMatrix());
	SetUniform("light.position", light->GetPosition());
	SetUniform("light.direction", light->GetDirection());
	SetUniform("light.ambientRGB", light->GetAmbientRGB());
	SetUniform("light.diffuseRGB", light->GetDiffuseRGB());
	SetUniform("light.specularRGB", light->GetSpecularRGB());
}

void LightShader::SetCamera(const Camera3D* camera)
{
	SetUniform("viewPosition", camera->GetEyePosition());
	SetUniform("view", camera->GetViewMatrix());
	SetUniform("projection", camera->GetProjectionMatrix());
}

void LightShader::DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh, const ShadowMap* shadowMap)
{
	shadowMap->Active(0);

	SetUniform("world", world);

	GL_ASSERT(glBindVertexArray(mesh->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
	GL_ASSERT(glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");
}