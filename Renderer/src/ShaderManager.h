#pragma once

#include "raylib/raylib.h"
#include <string>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	bool LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	Shader GetShader() const;
	void SetShaderValue(int location, const void* value, int uniformType);
	int GetLocation(const std::string& uniformName) const;


	void SetupMaterialMapLocations();
	void SetupLightingParameters();
	void SetAmbientColor(const Vector3& color, float intensity);
	void SetEmissiveParameters(float intensity, const Vector4& color);

	int m_albedoMapLoc;
	int m_mraMapLoc;
	int m_normalMapLoc;
	int m_emissiveMapLoc;

private:
	Shader m_shader;
	bool m_isLoaded = false;

	int m_viewPosLoc;
	int m_ambientColorLoc;
	int m_ambientIntensityLoc;
	int m_emissiveIntensityLoc;
	int m_emissiveColorLoc;
};
