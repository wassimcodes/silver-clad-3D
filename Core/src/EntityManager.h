#pragma once

#include "Components.h"
#include "Entity.h"
#include <unordered_map>

class EntityManager
{
public:
	void AddEntity(Entity entity, ModelComponent modelComponent, TransformComponent transformComponent);
	std::unordered_map<int, ModelComponent>& GetEntities();
	const std::unordered_map<int, TransformComponent>& GetTransforms() const;

private:
	std::unordered_map<int, ModelComponent> m_entities;
	std::unordered_map<int, TransformComponent> m_transforms;
};