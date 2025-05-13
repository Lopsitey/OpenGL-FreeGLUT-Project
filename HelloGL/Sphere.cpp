#include "Sphere.h"

Sphere::Sphere(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
    : SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.89f)
{
    //0.89 friction coefficient because the earth is slow and massive
    _scale = {3, 3, 3}; //3x as big
}


Sphere::~Sphere(void)
{
}

void Sphere::Update()
{
    _rotationSpeed += 0.8f;
    _velocity *= _frictionCoefficient;
    _position += _velocity;
}
