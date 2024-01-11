#include "MultiLightsShader.h"

#include "Camera3D.h"
#include "GLAssertion.h"
#include "Material.h"
#include "MathUtils.h"
#include "StaticMesh.h"
#include "StringUtils.h"

MultiLightsShader::~MultiLightsShader() {}

void MultiLightsShader::SetCamera(const Camera3D* camera)
{
	SetUniform("viewPosition", camera->GetEyePosition());
	SetUniform("view", camera->GetViewMatrix());
	SetUniform("projection", camera->GetProjectionMatrix());
}

void MultiLightsShader::SetMaterial(const Material* material)
{
	SetUniform("material.ambientRGB", material->GetAmbientRGB());
	SetUniform("material.diffuseRGB", material->GetDiffuseRGB());
	SetUniform("material.specularRGB", material->GetSpecularRGB());
	SetUniform("material.shininess", material->GetShininess());
}

void MultiLightsShader::SetDirectionalLights(const std::vector<DirectionalLight>& directionalLights)
{
	ASSERT(directionalLights.size() <= MAX_LIGHTS, "%d light count is overflow max lights", directionalLights.size());

	for (std::size_t index = 0; index < directionalLights.size(); ++index)
	{
		SetUniform(StringUtils::PrintF("directionalLights[%d].direction",   index), directionalLights[index].GetDirection());
		SetUniform(StringUtils::PrintF("directionalLights[%d].ambientRGB",  index), directionalLights[index].GetAmbientRGB());
		SetUniform(StringUtils::PrintF("directionalLights[%d].diffuseRGB",  index), directionalLights[index].GetDiffuseRGB());
		SetUniform(StringUtils::PrintF("directionalLights[%d].specularRGB", index), directionalLights[index].GetSpecularRGB());
	}
}

void MultiLightsShader::SetPointLights(const std::vector<PointLight>& pointLights)
{
	ASSERT(pointLights.size() <= MAX_LIGHTS, "%d light count is overflow max lights", pointLights.size());

	for (std::size_t index = 0; index < pointLights.size(); ++index)
	{
		SetUniform(StringUtils::PrintF("pointLights[%d].position",    index), pointLights[index].GetPosition());
		SetUniform(StringUtils::PrintF("pointLights[%d].ambientRGB",  index), pointLights[index].GetAmbientRGB());
		SetUniform(StringUtils::PrintF("pointLights[%d].diffuseRGB",  index), pointLights[index].GetDiffuseRGB());
		SetUniform(StringUtils::PrintF("pointLights[%d].specularRGB", index), pointLights[index].GetSpecularRGB());
		SetUniform(StringUtils::PrintF("pointLights[%d].constant",    index), pointLights[index].GetConstant());
		SetUniform(StringUtils::PrintF("pointLights[%d].linear",      index), pointLights[index].GetLinear());
		SetUniform(StringUtils::PrintF("pointLights[%d].quadratic",   index), pointLights[index].GetQuadratic());
	}
}

void MultiLightsShader::SetSpotLights(const std::vector<SpotLight> spotLights)
{
	ASSERT(spotLights.size() <= MAX_LIGHTS, "%d light count is overflow max lights", spotLights.size());

	for (std::size_t index = 0; index < spotLights.size(); ++index)
	{
		SetUniform(StringUtils::PrintF("spotLights[%d].position",    index), spotLights[index].GetPosition());
		SetUniform(StringUtils::PrintF("spotLights[%d].direction",   index), spotLights[index].GetDirection());
		SetUniform(StringUtils::PrintF("spotLights[%d].cutOff",      index), spotLights[index].GetCutOff());
		SetUniform(StringUtils::PrintF("spotLights[%d].outerCutOff", index), spotLights[index].GetOuterCutOff());
		SetUniform(StringUtils::PrintF("spotLights[%d].ambientRGB",  index), spotLights[index].GetAmbientRGB());
		SetUniform(StringUtils::PrintF("spotLights[%d].diffuseRGB",  index), spotLights[index].GetDiffuseRGB());
		SetUniform(StringUtils::PrintF("spotLights[%d].specularRGB", index), spotLights[index].GetSpecularRGB());
		SetUniform(StringUtils::PrintF("spotLights[%d].constant",    index), spotLights[index].GetConstant());
		SetUniform(StringUtils::PrintF("spotLights[%d].linear",      index), spotLights[index].GetLinear());
		SetUniform(StringUtils::PrintF("spotLights[%d].quadratic",   index), spotLights[index].GetQuadratic());
	}
}

void MultiLightsShader::DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh)
{
	SetUniform("world", world);

	GL_ASSERT(glBindVertexArray(mesh->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
	GL_ASSERT(glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");
}