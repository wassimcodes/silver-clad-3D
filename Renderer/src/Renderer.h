#pragma once

#include "raylib/raylib.h"
#include <unordered_map>
#include <string>
#include <vector>

struct ModelComponent
{
	Model model;
};

struct TransformComponent
{
	Vector3 position;
	Vector3 Rotation;
	Vector3 Scale;
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
	void AddEntity(Entity entity, ModelComponent modelComponent, TransformComponent transformComponent);
	void SetTransform(Entity entity, const TransformComponent& transform);
	void Render();
	const std::unordered_map<int, ModelComponent>& GetEntities() const;

private:
	std::unordered_map<int, ModelComponent> m_entities;
	std::unordered_map<int, TransformComponent> m_transforms;
};

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