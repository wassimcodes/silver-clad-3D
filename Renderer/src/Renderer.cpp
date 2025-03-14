#include "Renderer.h"
#include "iostream"


Renderer::Renderer() :
	m_nextEntityID(0), m_shaderManager(nullptr) 
{
}

Renderer::~Renderer()
{
	for (auto& entity : m_entities)
	{
		UnloadModel(m_renderSystem.GetEntities().at(entity.GetID()).model);
	}
}

void Renderer::LoadModel(const std::string& modelPath, Entity entity, TransformComponent transform)
{
	Model model = ::LoadModel(modelPath.c_str());
	ModelComponent modelComponent = { model };
	m_renderSystem.AddEntity(entity, modelComponent, transform);
	m_entities.push_back(entity);
}

void Renderer::LoadTexture(Entity entity, int mapType, const std::string& texturePath) {
    auto& entities = m_renderSystem.GetEntities();
    if (entities.find(entity.GetID()) != entities.end())
    {
        Model& model = entities.at(entity.GetID()).model;
        if (mapType >= 0 && mapType < MATERIAL_MAP_BRDF) {
            model.materials[0].maps[mapType].texture = ::LoadTexture(texturePath.c_str());
        }
    }
}

void Renderer::SetShader(ShaderManager& shaderManager)
{
    m_shaderManager = &shaderManager;

    // Ensure the shader is loaded
    Shader shader = m_shaderManager->GetShader();
    if (shader.id == 0) {
        std::cerr << "Shader is not loaded!" << std::endl;
        return;
    }
}

void Renderer::Render()
{
    Shader pbrShader = m_shaderManager->GetShader();

    for (const auto& entity : m_renderSystem.GetEntities())
    {

        const TransformComponent& transform = m_renderSystem.GetTransforms().at(entity.first);

        Model model = entity.second.model;
        model.materials[0].shader = pbrShader;

        float angle;
        Vector3 axis;
        QuaternionToAxisAngle(transform.rotation, &axis, &angle);

        ::DrawModelEx(entity.second.model, transform.position, axis, angle * RAD2DEG, transform.scale, WHITE);
    }
}

