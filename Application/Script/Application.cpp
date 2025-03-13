#include "WindowManager.h"
#include "Renderer.h"
#include "Entity.h"
#include "Components.h"

int main()
{
	Window window(1280, 720, "Silver Clad");
	Renderer renderer;
	// Importing OBJ
	Entity entity1(1);
	Entity entity2(2);
	renderer.LoadModel("Assets/3D_Assets/cottageHouse.obj", entity1, { { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } });
	renderer.LoadModel("Assets/3D_Assets/Floor.obj", entity2, { { 0, 0, 0 }, { 0, 0, 0 }, { 3, 3, 3 } });

	while (!WindowShouldClose())
	{
		window.Draw(renderer);
	}
}