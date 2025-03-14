#include <iostream>
#include "ShaderManager.h"
#include "LightManager.h"

LightManager::LightManager(ShaderManager& shaderManager)
	: m_shaderManager(shaderManager), m_lightCount(0) {}

LightManager::~LightManager(){}

void LightManager::AddLight(int type, Vector3 position, Vector3 target, Color color, float intensity)
{
	if (m_lightCount >= MAX_LIGHTS)
	{
		std::cerr << "You have reached the maximum number of lights!" << std::endl;
		return;
	}

    Light light;
	light.type = type;
	light.enabled = true;
	light.position = position;
	light.target = target;
	light.color[0] = (float)color.r / 255.0f;
	light.color[1] = (float)color.g / 255.0f;
	light.color[2] = (float)color.b / 255.0f;
	light.color[3] = (float)color.a / 255.0f;
	light.intensity = intensity;

	// Set shader locations for light properties
	light.enabledLoc = m_shaderManager.GetLocation(TextFormat("lights[%i].enabled", m_lightCount));
	light.typeLoc = m_shaderManager.GetLocation(TextFormat("lights[%i].type", m_lightCount));
	light.positionLoc = m_shaderManager.GetLocation(TextFormat("lights[%i].position", m_lightCount));
	light.targetLoc = m_shaderManager.GetLocation(TextFormat("lights[%i].target", m_lightCount));
	light.colorLoc = m_shaderManager.GetLocation(TextFormat("lights[%i].color", m_lightCount));
	light.intensityLoc = m_shaderManager.GetLocation(TextFormat("lights[%i].intensity", m_lightCount));

	m_lights.push_back(light);
	m_lightCount++;
	UpdateLight(m_lightCount - 1);

	std::cout << "Light added: " << m_lightCount << std::endl;

}

void LightManager::UpdateLight(int index)
{
	if (index < 0 || index >= m_lights.size())
	{
		std::cerr << "Invalid light index!" << std::endl;
		return;
	}

	Light& light = m_lights[index];
	m_shaderManager.SetShaderValue(light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
	m_shaderManager.SetShaderValue(light.typeLoc, &light.type, SHADER_UNIFORM_INT);

	float position[3] = { light.position.x, light.position.y, light.position.z };
	m_shaderManager.SetShaderValue(light.positionLoc, position, SHADER_UNIFORM_VEC3);

	float target[3] = { light.target.x, light.target.y, light.target.z };
	m_shaderManager.SetShaderValue(light.targetLoc, target, SHADER_UNIFORM_VEC3);

	float color[4] = { light.color[0], light.color[1], light.color[2], light.color[3] };
	m_shaderManager.SetShaderValue(light.colorLoc, color, SHADER_UNIFORM_VEC4);
	m_shaderManager.SetShaderValue(light.intensityLoc, &light.intensity, SHADER_UNIFORM_FLOAT);

	std::cout << "Light " << m_lightCount << " Uniform Locations:" << std::endl;
	std::cout << "  enabledLoc: " << light.enabledLoc << std::endl;
	std::cout << "  typeLoc: " << light.typeLoc << std::endl;
	std::cout << "  positionLoc: " << light.positionLoc << std::endl;
	std::cout << "  targetLoc: " << light.targetLoc << std::endl;
	std::cout << "  colorLoc: " << light.colorLoc << std::endl;
	std::cout << "  intensityLoc: " << light.intensityLoc << std::endl;

}

void LightManager::updateAllLights()
{
	for (size_t i = 0; i < m_lights.size(); i++)
	{
		UpdateLight(i);
	}
}

void LightManager::ToggleLight(int index)
{
	if (index < 0 || index >= m_lights.size())
	{
		std::cerr << "Invalid light index!" << std::endl;
		return;
	}

	m_lights[index].enabled = !m_lights[index].enabled;
	UpdateLight(index);
}

void LightManager::RenderPointLights(CameraManager& cameraManager)
{
	Camera camera = cameraManager.GetCamera();
	for (const auto& light : m_lights)
	{
		Color lightColor = {(unsigned char)(light.color[0] * 255.0f),
			                (unsigned char)(light.color[1] * 255.0f), 
			                (unsigned char)(light.color[2] * 255.0f), 
			                (unsigned char)(light.color[3] * 255.0f)};

		if (light.enabled)
		{
			DrawSphereEx(light.position,3.f, 16, 16, lightColor);
		}
		else
		{
			DrawSphereWires(light.position, 0.2f, 8, 8, ColorAlpha(lightColor, 0.3f));
		}

	}
}

const std::vector<LightManager::Light>& LightManager::GetLights() const
{
	return m_lights;
}






