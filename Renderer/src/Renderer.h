#pragma once

#include "raylib/raylib.h"
#include "Entity.h"
#include "Components.h"
#include "RenderSystem.h"

#include <vector>
#include "string"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void LoadModel(const std::string& path, Entity entity, TransformComponent transform);
	void LoadTexture(const std::string& path, Entity entity);
	void Render();
private:
	RenderSystem m_renderSystem;
	std::vector<Entity> m_entities;
	int m_nextEntityID;
};