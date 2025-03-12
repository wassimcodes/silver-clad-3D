#pragma once

#include "raylib/raylib.h"
#include "Renderer.h"  
class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	void Draw(Renderer& renderer);
	
};


