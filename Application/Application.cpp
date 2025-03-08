#include "WindowManager.h"
#include "Renderer.h"
#include "Entity.h"
#include "Components.h"

int main()
{
	Window window(1920, 1080, "SilverClad");
    Renderer renderer;
	 
	Entity entity1 = 1;
	renderer.LoadModel("D:/Cpp/SilverClad/Assets/3D_Assets/cottageHouse.obj", entity1, { { 0, 0, 0 }, { 0, 0,0 }, { 1, 1, 1 } });

    while (!WindowShouldClose()) 
    {
		window.Draw(renderer);
    }
}