#include "Grenade.h"

Grenade::Grenade(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
    : SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.0f)
{
    //0 friction coefficient so the terrain doesn't move
    _scale = {2, 2, 2}; //twice as big
}


Grenade::~Grenade(void)
{
}

void Grenade::Update()
{
    _rotationSpeed += 0.8f;
}
