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

	EntityManager entityManager;

	Entity carEntity(1);
	ModelComponent carModel;
	renderer.LoadModel("Assets/models/glb/old_car_new.glb", carModel);
	renderer.LoadTexture("Assets/textures/oldcar/old_car_d.png", carModel, MATERIAL_MAP_ALBEDO);
	renderer.LoadTexture("Assets/textures/oldcar/old_car_e.png", carModel, MATERIAL_MAP_EMISSION);
	renderer.LoadTexture("Assets/textures/oldcar/old_car_mra.png", carModel, MATERIAL_MAP_METALNESS);
	renderer.LoadTexture("Assets/textures/oldcar/old_car_n.png", carModel, MATERIAL_MAP_NORMAL);
	TransformComponent carTransform = { {3, 0, 0},{1,1,1}, {1, 1, 1}};
	entityManager.AddEntity(carEntity, carModel, carTransform);
	
	Entity cubeEntity(2);
	ModelComponent cubeModel;
	renderer.LoadModel("Assets/models/glb/cube.glb", cubeModel);
	renderer.LoadTexture("Assets/textures/oldcar/metal_d.jpg", cubeModel, MATERIAL_MAP_ALBEDO);
	renderer.LoadTexture("Assets/textures/oldcar/metal_mra.jpg", cubeModel, MATERIAL_MAP_METALNESS);
	renderer.LoadTexture("Assets/textures/oldcar/metal_n.png", cubeModel, MATERIAL_MAP_NORMAL);
	TransformComponent cubeTransform = { {10, 0, 5}, {1,1,1}, {5, 2, 5} };
	entityManager.AddEntity(cubeEntity, cubeModel, cubeTransform);


	while (!WindowShouldClose())
	{
		window.Draw(renderer, lightManager);
	}

	return 0;
}