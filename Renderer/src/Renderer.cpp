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

void Renderer::LoadModel(const std::string& modelPath, Entity entity, TransformComponent transform)
{
	Model model = ::LoadModel(modelPath.c_str());
	ModelComponent modelComponent = { model };
	m_renderSystem.AddEntity(entity, modelComponent, transform);
	m_entities.push_back(entity);
}

void Renderer::LoadTexture(Entity entity, int mapType, const std::string& texturePath) {
    auto& entities = m_renderSystem.GetEntities();
    if (entities.find(entity.GetID()) != entities.end()) {
        Model& model = entities.at(entity.GetID()).model;

        if (mapType >= 0 && mapType < MATERIAL_MAP_BRDF)
        {
            Texture2D texture = ::LoadTexture(texturePath.c_str());
            model.materials[0].maps[mapType].texture = texture;
        }
        else {
            std::cerr << "Entity not found: " << entity.GetID() << std::endl;
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

void Renderer::Render(CameraManager* iCameraManager) {
    Shader pbrShader = m_shaderManager->GetShader();

    // Set ambient color and intensity
    Vector3 ambientColor = { 26.0f / 255.0f, 32.0f / 255.0f, 135.0f / 255.0f };
    float ambientIntensity = 0.02f;
    m_shaderManager->SetAmbientColor(ambientColor, ambientIntensity);

    // Set emissive parameters
    float emissiveIntensity = 1.0f;
    Vector4 emissiveColor = { 1.0f, 1.0f, 1.0f, 1.0f }; // White emission
    m_shaderManager->SetEmissiveParameters(emissiveIntensity, emissiveColor);

    for (const auto& entity : m_renderSystem.GetEntities()) {
        const TransformComponent& transform = m_renderSystem.GetTransforms().at(entity.first);

        Model model = entity.second.model;
        model.materials[0].shader = pbrShader;

        float angle;
        Vector3 axis;
        QuaternionToAxisAngle(transform.rotation, &axis, &angle);
        Vector3 CameraPos = iCameraManager->GetCamera().position;
        m_shaderManager->SetShaderValue(m_shaderManager->GetLocation("viewPos"), &CameraPos, SHADER_UNIFORM_VEC3);

        ::DrawModelEx(model, transform.position, axis, angle * RAD2DEG, transform.scale, WHITE);
    }
}

