#pragma once

#include "Entity.h"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

Quaternion EulerToQuaternion(Vector3 eulerDegrees);

struct ModelComponent
{
	Model model;
};



struct TransformComponent
{
    Vector3 position;
    Quaternion rotation = QuaternionIdentity();
    Vector3 scale;

    TransformComponent() {};

    TransformComponent(Vector3 pos, Vector3 eulerDegrees, Vector3 scl);

    void SetRotation(Vector3 eulerDegrees);
};
