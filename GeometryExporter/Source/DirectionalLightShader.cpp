#include "DirectionalLightShader.h"

#include "Camera3D.h"
#include "GLAssertion.h"
#include "Material.h"
#include "MathUtils.h"
#include "StaticMesh.h"
#include "StringUtils.h"

DirectionalLightShader::~DirectionalLightShader() {}

void DirectionalLightShader::SetCamera(const Camera3D* camera)
{
	SetUniform("viewPosition", camera->GetEyePosition());
	SetUniform("view", camera->GetViewMatrix());
	SetUniform("projection", camera->GetProjectionMatrix());
}

void DirectionalLightShader::SetMaterial(const Material* material)
{
	SetUniform("material.ambientRGB", material->GetAmbientRGB());
	SetUniform("material.diffuseRGB", material->GetDiffuseRGB());
	SetUniform("material.specularRGB", material->GetSpecularRGB());
	SetUniform("material.shininess", material->GetShininess());
}

void DirectionalLightShader::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	SetUniform("light.direction", directionalLight.GetDirection());
	SetUniform("light.ambientRGB", directionalLight.GetAmbientRGB());
	SetUniform("light.diffuseRGB", directionalLight.GetDiffuseRGB());
	SetUniform("light.specularRGB", directionalLight.GetSpecularRGB());
}

void DirectionalLightShader::DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh)
{
	SetUniform("world", world);

	GL_ASSERT(glBindVertexArray(mesh->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
	GL_ASSERT(glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");
}