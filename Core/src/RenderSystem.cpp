#include "RenderSystem.h"
#include "iostream"

void RenderSystem::AddEntity(Entity entity, ModelComponent modelComponent, TransformComponent transformComponent)
{
	m_entities[entity.GetID()] = modelComponent;
	m_transforms[entity.GetID()] = transformComponent;
}

void RenderSystem::SetTransform(Entity entity, const TransformComponent& transform)
{
	m_transforms[entity.GetID()] = transform;
}

void RenderSystem::Render()
{
	for (const auto& entity : m_entities)
	{
		std::cout << "Rendering entity ID: " << entity.first << std::endl;
		std::cout << "Mesh count: " << entity.second.model.meshCount << std::endl;
		std::cout << "Material count: " << entity.second.model.materialCount << std::endl;
		const TransformComponent& transform = m_transforms.at(entity.first);


		float angle;
		Vector3 axis;
		QuaternionToAxisAngle(transform.rotation, &axis, &angle);
		std::cout << "Entity ID: " << entity.first << std::endl;
        std::cout << "Rotation Axis: (" << axis.x << ", " << axis.y << ", " << axis.z << ")" << std::endl;
        std::cout << "Rotation Angle: " << angle * RAD2DEG << " degrees" << std::endl;

		::DrawModelEx(entity.second.model, transform.position, axis, angle * RAD2DEG, transform.scale, WHITE);
	}
}

const std::unordered_map<int, ModelComponent>& RenderSystem::GetEntities() const
{
	return m_entities;
}
