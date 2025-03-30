#include "CameraManager.h"

CameraManager::CameraManager()
{
    m_camera.position = Vector3{ 0.0f, 5.0f, 10.0f };
    m_camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 90.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();

}

void CameraManager::Update()
{
    UpdateCamera(&m_camera, CAMERA_FREE);
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
}

Camera CameraManager::GetCamera() const
{
    return m_camera;
}