#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
	: m_isLoaded(false), m_albedoMapLoc(-1), m_mraMapLoc(-1), m_normalMapLoc(-1), m_emissiveMapLoc(-1),
	m_viewPosLoc(-1), m_ambientColorLoc(-1), m_ambientIntensityLoc(-1),
	m_emissiveIntensityLoc(-1), m_emissiveColorLoc(-1) {
	std::cout << "ShaderManager created" << std::endl;
}

ShaderManager::~ShaderManager() {
	if (m_isLoaded) {
		UnloadShader(m_shader);
	}
}

bool ShaderManager::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    m_shader = ::LoadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    if (m_shader.id == 0) {
        std::cerr << "Failed to load shader!" << std::endl;
        return false;
    }

    // Set up shader locations for material maps and lighting
    SetupMaterialMapLocations();
    SetupLightingParameters();

    std::cout << "Shader loaded successfully" << std::endl;
    m_isLoaded = true;
    return true;
}

Shader ShaderManager::GetShader() const {
    return m_shader;
}

void ShaderManager::SetShaderValue(int location, const void* value, int uniformType) {
    ::SetShaderValue(m_shader, location, value, uniformType);
}

int ShaderManager::GetLocation(const std::string& uniformName) const {
    return ::GetShaderLocation(m_shader, uniformName.c_str());
}

void ShaderManager::SetupMaterialMapLocations() {
    m_shader.locs[SHADER_LOC_MAP_ALBEDO] = GetLocation("albedoMap");
    m_shader.locs[SHADER_LOC_MAP_METALNESS] = GetLocation("mraMap");
    m_shader.locs[SHADER_LOC_MAP_NORMAL] = GetLocation("normalMap");
    m_shader.locs[SHADER_LOC_MAP_EMISSION] = GetLocation("emissiveMap");
    m_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetLocation("viewPos");


    std::cout << "Shader material map locations:" << std::endl;
    std::cout << "  Albedo Map: " << m_albedoMapLoc << std::endl;
    std::cout << "  MRA Map: " << m_mraMapLoc << std::endl;
    std::cout << "  Normal Map: " << m_normalMapLoc << std::endl;
    std::cout << "  Emissive Map: " << m_emissiveMapLoc << std::endl;
}

void ShaderManager::SetupLightingParameters() {
    m_viewPosLoc = GetLocation("viewPos");
    m_ambientColorLoc = GetLocation("ambientColor");
    m_ambientIntensityLoc = GetLocation("ambient");
    m_emissiveIntensityLoc = GetLocation("emissivePower");
    m_emissiveColorLoc = GetLocation("emissiveColor");

    std::cout << "Shader lighting parameter locations:" << std::endl;
    std::cout << "  View Position: " << m_viewPosLoc << std::endl;
    std::cout << "  Ambient Color: " << m_ambientColorLoc << std::endl;
    std::cout << "  Ambient Intensity: " << m_ambientIntensityLoc << std::endl;
    std::cout << "  Emissive Intensity: " << m_emissiveIntensityLoc << std::endl;
    std::cout << "  Emissive Color: " << m_emissiveColorLoc << std::endl;
}

void ShaderManager::SetAmbientColor(const Vector3& color, float intensity) {
    SetShaderValue(m_ambientColorLoc, &color, SHADER_UNIFORM_VEC3);
    SetShaderValue(m_ambientIntensityLoc, &intensity, SHADER_UNIFORM_FLOAT);
}

void ShaderManager::SetEmissiveParameters(float intensity, const Vector4& color) {
    SetShaderValue(m_emissiveIntensityLoc, &intensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(m_emissiveColorLoc, &color, SHADER_UNIFORM_VEC4);
}


