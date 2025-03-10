#pragma once
#include "raylib/raylib.h"

class CameraManager
{
public:
	CameraManager();

	void Update();
	Camera GetCamera() const;

private:
	Camera m_camera; 
};
