#include "Terrain.h"

Terrain::Terrain(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
    : SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.0f)
{
    //0 friction coefficient so the terrain doesn't move
    _scale = {10, 2, 10}; //very long and wide scale
}


Terrain::~Terrain(void)
{
    
}