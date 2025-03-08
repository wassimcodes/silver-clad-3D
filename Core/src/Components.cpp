#include "Components.h"
#include "iostream"

TransformComponent::TransformComponent(Vector3 pos, Vector3 eulerDegrees, Vector3 scl)
    : position(pos), scale(scl)
{
    SetRotation(eulerDegrees);
}

static Quaternion EulerToQuaternion(Vector3 eulerDegrees)
{
    Vector3 eulerRadians = {
        DEG2RAD * eulerDegrees.x,
        DEG2RAD * eulerDegrees.y,
        DEG2RAD * eulerDegrees.z
    };
    return QuaternionFromEuler(eulerRadians.x, eulerRadians.y, eulerRadians.z);
}

void TransformComponent::SetRotation(Vector3 eulerDegrees)
{
    rotation = EulerToQuaternion(eulerDegrees);
    std::cout << "Quaternion: (" << rotation.x << ", " << rotation.y << ", " << rotation.z << ", " << rotation.w << ")" << std::endl;
}