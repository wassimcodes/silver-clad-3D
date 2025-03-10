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

void Renderer::LoadTexture(const std::string& path, Entity entity)
{
	Texture2D texture = ::LoadTexture(path.c_str());
	ModelComponent& modelComponent = const_cast<ModelComponent&>(m_renderSystem.GetEntities().at(entity.GetID()));
	for (int i = 0; i < modelComponent.model.materialCount; i++)
	{
		modelComponent.model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
	}
}

void Renderer::Render()
{
    for (const auto& entity : m_renderSystem.GetEntities())
    {
        // Log the entity ID, mesh count, and material count
        std::cout << "Rendering entity ID: " << entity.first << std::endl;
        std::cout << "Mesh count: " << entity.second.model.meshCount << std::endl;
        std::cout << "Material count: " << entity.second.model.materialCount << std::endl;

        // Get the corresponding TransformComponent for the entity
        const TransformComponent& transform = m_renderSystem.GetTransforms().at(entity.first);

        // Convert the quaternion rotation to an axis-angle representation
        float angle;
        Vector3 axis;
        QuaternionToAxisAngle(transform.rotation, &axis, &angle);

        // Log rotation information
        std::cout << "Entity ID: " << entity.first << std::endl;
        std::cout << "Rotation Axis: (" << axis.x << ", " << axis.y << ", " << axis.z << ")" << std::endl;
        std::cout << "Rotation Angle: " << angle * RAD2DEG << " degrees" << std::endl;

        // Draw the model with the transform properties
        ::DrawModelEx(entity.second.model, transform.position, axis, angle * RAD2DEG, transform.scale, WHITE);
    }
}






