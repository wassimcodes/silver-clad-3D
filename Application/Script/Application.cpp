#include <iostream>

#include "WindowManager.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include "Entity.h"
#include "Components.h"

int main()
{

	Window window(1280, 720, "Silver Clad");
	Renderer renderer;

	ShaderManager shaderManager;
	if (!shaderManager.LoadShader("D:/Cpp/SilverClad/Renderer/shaders/pbr.vs", "D:/Cpp/SilverClad/Renderer/shaders/pbr.fs"))
	{
		std::cerr << "Failed to load shader!" << std::endl;
		return -1;
	}

	LightManager lightManager(shaderManager);

	renderer.SetShader(shaderManager);

	lightManager.AddLight(lightManager.LIGHT_POINT, Vector3{ 8.0f, 3.0f, 5.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, BLUE, 100.0f);
	lightManager.AddLight(lightManager.LIGHT_POINT, Vector3{ -5.0f, 10.0f, 5.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, GREEN, 100.0f);
	lightManager.AddLight(lightManager.LIGHT_POINT, Vector3{ 0.0f, 10.0f, -10.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, YELLOW, 100.0f);


	Entity carEntity(1);
	renderer.LoadModel("Assets/models/glb/old_car_new.glb", carEntity, { { 3, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } });


	renderer.LoadTexture(carEntity, MATERIAL_MAP_ALBEDO, "Assets/textures/oldcar/old_car_d.png");
	renderer.LoadTexture(carEntity, MATERIAL_MAP_EMISSION, "Assets/textures/oldcar/old_car_e.png");
	renderer.LoadTexture(carEntity, MATERIAL_MAP_METALNESS, "Assets/textures/oldcar/old_car_mra.png");
	renderer.LoadTexture(carEntity, MATERIAL_MAP_NORMAL, "Assets/textures/oldcar/old_car_n.png");
	
	Entity cubeEntity(2);
	renderer.LoadModel("Assets/models/glb/cube.glb", cubeEntity, { { 10, -2,5 }, { 0, 0, 0 }, { 5, 2, 5} });

	renderer.LoadTexture(cubeEntity, MATERIAL_MAP_ALBEDO, "Assets/textures/oldcar/metal_d.jpg");
	renderer.LoadTexture(cubeEntity, MATERIAL_MAP_METALNESS, "Assets/textures/oldcar/metal_mra.jpg");
	renderer.LoadTexture(cubeEntity, MATERIAL_MAP_NORMAL, "Assets/textures/oldcar/metal_n.png");


	while (!WindowShouldClose())
	{
		window.Draw(renderer, lightManager);
	}

	return 0;
}