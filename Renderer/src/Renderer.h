#pragma once

#include "raylib/raylib.h"
#include "Entity.h"
#include "Components.h"
#include "EntityManager.h"
#include "ShaderManager.h"

#include <vector>
#include "string"

class CameraManager;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void LoadModel(const std::string& modelPath, ModelComponent& modelComponent);
	void LoadTexture(const std::string& texturePath, ModelComponent& modelComponent, int mapType);
	void SetShader(ShaderManager& shaderManager);

	void Render(EntityManager& entityManager, CameraManager* iCameraManager);
	
private:
	EntityManager m_renderSystem;
	std::vector<Entity> m_entities;
	int m_nextEntityID;
	ShaderManager* m_shaderManager;
};