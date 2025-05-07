#include "Renderer.h"
#include "iostream"

#include "CameraManager.h"


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

void Renderer::LoadModel(const std::string& modelPath, ModelComponent& modelComponent)
{
	modelComponent.model = ::LoadModel(modelPath.c_str());
}

void Renderer::LoadTexture(const std::string& texturePath, ModelComponent& modelComponent, int mapType) 
{
	Texture2D texture = ::LoadTexture(texturePath.c_str());
	modelComponent.model.materials[0].maps[mapType].texture = texture;
	modelComponent.textures.push_back(texture);
}

void Renderer::SetShader(ShaderManager& shaderManager)
{
    m_shaderManager = &shaderManager;

    Shader shader = m_shaderManager->GetShader();
    if (shader.id == 0) 
    {
        std::cerr << "Shader is not loaded!" << std::endl;
        return;
    }
}

void Renderer::Render(EntityManager& entityManager, CameraManager* cameraManager) {
    Shader pbrShader = m_shaderManager->GetShader();

    std::unordered_map<int, ModelComponent>& entities = entityManager.GetEntities();
    for (std::pair<const int, ModelComponent>& entityPair : entities) {
        int entityID = entityPair.first;
        ModelComponent& modelComponent = entityPair.second;

        // Access the corresponding TransformComponent
        const std::unordered_map<int, TransformComponent>& transforms = entityManager.GetTransforms();
        std::unordered_map<int, TransformComponent>::const_iterator transformIt = transforms.find(entityID);
        if (transformIt == transforms.end()) {
            std::cerr << "TransformComponent not found for entity ID: " << entityID << std::endl;
            continue;
        }

        const TransformComponent& transformComponent = transformIt->second;

        // Assign the shader to all materials
        for (int i = 0; i < modelComponent.model.materialCount; i++) 
        {
            modelComponent.model.materials[i].shader = pbrShader;
        }

        float angle;
        Vector3 axis;
        QuaternionToAxisAngle(transformComponent.rotation, &axis, &angle);
        Vector3 cameraPos = cameraManager->GetCamera().position;
        m_shaderManager->SetShaderValue(m_shaderManager->GetLocation("viewPos"), &cameraPos, SHADER_UNIFORM_VEC3);

        // Render the model
        ::DrawModelEx(modelComponent.model, transformComponent.position, axis, angle * RAD2DEG, transformComponent.scale, WHITE);

    }
}