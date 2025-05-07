#include "EntityManager.h"
#include "iostream"

void EntityManager::AddEntity(Entity entity, ModelComponent modelComponent, TransformComponent transformComponent)
{
	m_entities[entity.GetID()] = modelComponent;
	m_transforms[entity.GetID()] = transformComponent;

}

std::unordered_map<int, ModelComponent>& EntityManager::GetEntities()
{
	return m_entities;
}

const std::unordered_map<int, TransformComponent>& EntityManager::GetTransforms() const
{
	return m_transforms;
}
