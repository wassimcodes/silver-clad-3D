#include "WindowManager.h"
#include "CameraManager.h"

Window::Window(int width, int height, const char* title)
{
	InitWindow(width, height, title);
}

void Window::Draw(Renderer& renderer, LightManager& lightManager)
{
    static CameraManager cameraManager;
    cameraManager.Update();
    BeginDrawing();
    ClearBackground(RED);
    BeginMode3D(cameraManager.GetCamera());
    //DrawGrid(30, 5.0f);
    renderer.Render(&cameraManager);
	lightManager.RenderPointLights(cameraManager);
    
    EndMode3D();
    EndDrawing();
}
Window::~Window()
{
	CloseWindow();
}

