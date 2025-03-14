#pragma once
#include "raylib/raylib.h"
#include "CameraManager.h"
#include "ShaderManager.h"
#include <vector>

#define MAX_LIGHTS 4


class LightManager
{
public:

    typedef enum {
        LIGHT_DIRECTIONAL = 0,
        LIGHT_POINT,
        LIGHT_SPOT
    } LightType;

    typedef struct {
        int type;
        int enabled;
        Vector3 position;
        Vector3 target;
        float color[4];
        float intensity;

        // Shader light parameters locations
        int typeLoc;
        int enabledLoc;
        int positionLoc;
        int targetLoc;
        int colorLoc;
        int intensityLoc;
    } Light;

    LightManager(ShaderManager& shaderManager);
    ~LightManager();

    void AddLight(int type, Vector3 position, Vector3 target, Color color, float intensity);
	void UpdateLight(int index);
    void updateAllLights();
    void ToggleLight(int index);
    void RenderPointLights(CameraManager& cameraManager);

    const std::vector<Light>& GetLights() const;

private:
    // add m_shader from shader manager
	ShaderManager& m_shaderManager;
	std::vector<Light> m_lights;
    int m_lightCount;

};