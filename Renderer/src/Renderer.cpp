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
	m_renderSystem.Render();
}






