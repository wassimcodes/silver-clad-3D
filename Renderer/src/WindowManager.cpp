#include "WindowManager.h"
#include "CameraManager.h"

Window::Window(int width, int height, const char* title)
{
	InitWindow(width, height, title);
}

void Window::Draw(Renderer& renderer) // Accept a Renderer object
{
    static CameraManager cameraManager;
    cameraManager.Update();
    BeginDrawing();
    ClearBackground(RED);
    BeginMode3D(cameraManager.GetCamera());
    DrawGrid(10, 5.0f);
    renderer.Render(); // Use the passed Renderer object
    HideCursor();
    EndMode3D();
    EndDrawing();
}
Window::~Window()
{
	CloseWindow();
}

