#include "WindowManager.h"
#include "printer.h"
#include "Renderer.h"

int main()
{
	Window window(1920, 1080, "SilverClad");
    Renderer renderer;

	Entity entity1 = 1;
	renderer.LoadModel("D:/Cpp/SilverClad/Assets/3D_Assets/cottageHouse.obj", entity1);

    while (!WindowShouldClose()) 
    {
		window.Draw(renderer);
    }
}