#include "RenderSystem.h"
#include "iostream"

void RenderSystem::AddEntity(Entity entity, ModelComponent modelComponent, TransformComponent transformComponent)
{
	m_entities[entity.GetID()] = modelComponent;
	m_transforms[entity.GetID()] = transformComponent;

}

std::unordered_map<int, ModelComponent>& RenderSystem::GetEntities()
{
	return m_entities;
}

const std::unordered_map<int, TransformComponent>& RenderSystem::GetTransforms() const
{
	return m_transforms;
}
