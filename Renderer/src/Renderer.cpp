#include "Renderer.h"
#include <iostream>

// Renderer Class
Renderer::Renderer()
	: m_nextEntityID(0)
{
}

Renderer::~Renderer()
{
	for (auto& entity : m_entities)
	{
		UnloadModel(m_renderSystem.GetEntities().at(entity.GetID()).model);
	}
}

void Renderer::LoadModel(const std::string& path, Entity entity)
{
	Model model = ::LoadModel(path.c_str());
	ModelComponent modelComponent = { model };
	m_renderSystem.AddEntity(entity, modelComponent);
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

void RenderSystem::AddEntity(Entity entity, ModelComponent modelComponent)
{
	m_entities[entity.GetID()] = modelComponent;
}
void RenderSystem::Render()
{
	for (const auto& entity : m_entities)
	{
		std::cout << "Rendering entity ID: " << entity.first << std::endl;
		std::cout << "Mesh count: " << entity.second.model.meshCount << std::endl;
		std::cout << "Material count: " << entity.second.model.materialCount << std::endl;

		// Draw the model
		::DrawModel(entity.second.model, { 0, 0, 0 }, 1.0f, WHITE);

	}
	// Draw a cube for debugging
	//::DrawCube({ 0, 0, 0 }, 2.0f, 2.0f, 2.0f, BLUE);
}


const std::unordered_map<int, ModelComponent>& RenderSystem::GetEntities() const
{
	return m_entities;
}