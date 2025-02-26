#include "CameraManager.h"

CameraManager::CameraManager()
{
    m_camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
    m_camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void CameraManager::Update()
{
    UpdateCamera(&m_camera, CAMERA_FREE);
}

Camera CameraManager::GetCamera() const
{
    return m_camera;
}