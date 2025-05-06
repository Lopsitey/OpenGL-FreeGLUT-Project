#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, TGALoader* texture)
{
    _mesh = mesh;
    _texture = texture;
}

SceneObject::~SceneObject(void)
{
    delete _mesh;
}

void SceneObject::Update()
{
    // Update logic for the scene object
}

void SceneObject::Draw()
{
    // Draw logic for the scene object
}

void SceneObject::SetVelocity(const Vector3& velocity, const float& frictionCoefficient)
{
    // Allows the velocity of objects to be changed dynamically
}
