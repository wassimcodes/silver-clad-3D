#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
	: m_isLoaded(false)
{
	std::cout << "ShaderManager created" << std::endl;
}

ShaderManager::~ShaderManager()
{
	if (m_isLoaded)
	{
		UnloadShader(m_shader);
	}
		
}

bool ShaderManager::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	m_shader = ::LoadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	if (m_shader.id == 0)
	{
		std::cout << "Failed to load shader" << std::endl;
		return false;
	}
	std::cout<<"shader loaded successfully"<<std::endl;
	m_isLoaded = true;
	return true;
}

Shader ShaderManager::GetShader() const
{
	return m_shader;
}

void ShaderManager::SetShaderValue(int location, const void* value, int uniformType)
{
	::SetShaderValue(m_shader, location, value, uniformType);
}

int ShaderManager::GetLocation(const std::string& uniformName) const
{
	return ::GetShaderLocation(m_shader, uniformName.c_str());
}


