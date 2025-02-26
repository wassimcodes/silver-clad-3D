#pragma once

#include "raylib/raylib.h"
#include <unordered_map>
#include <string>
#include <vector>

struct ModelComponent
{
	Model model;
};

class Entity
{
public:
	Entity(int id) : m_id(id) {}
	int GetID() const { return m_id; }

private:
	int m_id;
};

class RenderSystem
{
public:
	void AddEntity(Entity entity, ModelComponent modelComponent);
	void Render();
	const std::unordered_map<int, ModelComponent>& GetEntities() const;

private:
	std::unordered_map<int, ModelComponent> m_entities;
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	void LoadModel(const std::string& path, Entity entity);
	void LoadTexture(const std::string& path, Entity entity);
	void Render();
private:
	RenderSystem m_renderSystem;
	std::vector<Entity> m_entities;
	int m_nextEntityID;
};