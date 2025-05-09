#pragma once
#include "SceneObject.h"

class Grenade : public SceneObject
{
public:
    Grenade(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis);
    ~Grenade(void) override;
    void Update() override;
    float GetFrictionCoefficient() const override { return frictionCoefficient; }

private:
    float frictionCoefficient;
};
