#pragma once

#include "raylib/raylib.h"
#include "Renderer.h"  
class Window
{
public:
	Window(int width, int height, const char* title);
	void Draw(Renderer& renderer);
	~Window();
};


