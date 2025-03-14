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

private:
	Shader m_shader;
	bool m_isLoaded = false;
};
