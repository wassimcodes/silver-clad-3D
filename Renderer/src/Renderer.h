#pragma once

#include "raylib/raylib.h"
#include "Entity.h"
#include "Components.h"
#include "RenderSystem.h"
#include "ShaderManager.h"

#include <vector>
#include "string"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void LoadModel(const std::string& modelPath, Entity entity, TransformComponent transform);
	void LoadTexture(Entity entity, int mapType, const std::string& texturePath);
	void SetShader(ShaderManager& shaderManager);

	void Render();
	
private:
	RenderSystem m_renderSystem;
	std::vector<Entity> m_entities;
	int m_nextEntityID;
	ShaderManager* m_shaderManager;
};