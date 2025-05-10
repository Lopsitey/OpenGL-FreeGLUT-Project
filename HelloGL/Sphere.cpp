#include "Sphere.h"

Sphere::Sphere(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
    : SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.0f)
{
    //0 friction coefficient so the terrain doesn't move
    _scale = {3, 3, 3}; //3x as big
}


Sphere::~Sphere(void)
{
}

void Sphere::Update()
{
    _rotationSpeed += 0.8f;
}
