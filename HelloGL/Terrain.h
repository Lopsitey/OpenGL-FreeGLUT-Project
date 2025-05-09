#pragma once
#include "SceneObject.h"

class Terrain : public SceneObject
{
public:
    Terrain(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis);
    ~Terrain(void) override;
    float GetFrictionCoefficient() const override { return frictionCoefficient; }
    
private:
    float frictionCoefficient;
};
