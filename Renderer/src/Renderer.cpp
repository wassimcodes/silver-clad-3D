#include "Renderer.h"
#include "iostream"


Renderer::Renderer() : m_nextEntityID(0) {}

Renderer::~Renderer()
{
	for (auto& entity : m_entities)
	{
		UnloadModel(m_renderSystem.GetEntities().at(entity.GetID()).model);
	}
}

void Renderer::LoadModel(const std::string& path, Entity entity, TransformComponent transform)
{
	Model model = ::LoadModel(path.c_str());
	ModelComponent modelComponent = { model };
	m_renderSystem.AddEntity(entity, modelComponent, transform);
	m_entities.push_back(entity);
}

void Renderer::Render()
{
    for (const auto& entity : m_renderSystem.GetEntities())
    {
        std::cout << "Rendering entity ID: " << entity.first << std::endl;
        std::cout << "Mesh count: " << entity.second.model.meshCount << std::endl;
        std::cout << "Material count: " << entity.second.model.materialCount << std::endl;

        const TransformComponent& transform = m_renderSystem.GetTransforms().at(entity.first);

        float angle;
        Vector3 axis;
        QuaternionToAxisAngle(transform.rotation, &axis, &angle);

        std::cout << "Entity ID: " << entity.first << std::endl;

        ::DrawModelEx(entity.second.model, transform.position, axis, angle * RAD2DEG, transform.scale, WHITE);
    }
}






