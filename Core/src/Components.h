#pragma once

#include "Entity.h"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

class Component
{
public:
	virtual ~Component() = default;
};

Quaternion EulerToQuaternion(Vector3 eulerDegrees);

struct ModelComponent
{
	Model model;
	Texture2D textures;
};



struct TransformComponent
{
    Vector3 position;
    Quaternion rotation = QuaternionIdentity();
    Vector3 scale;

    TransformComponent() = default;

    TransformComponent(Vector3 pos, Vector3 eulerDegrees, Vector3 scl);

    void SetRotation(Vector3 eulerDegrees);
};
