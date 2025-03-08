#pragma once

#include "Components.h"
#include "Entity.h"
#include <unordered_map>

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