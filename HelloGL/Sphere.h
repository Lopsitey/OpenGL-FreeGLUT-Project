#pragma once
#include "SceneObject.h"

class Sphere : public SceneObject
{
public:
    Sphere(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis);
    ~Sphere(void) override;
    void Update() override;
    float GetFrictionCoefficient() const override { return frictionCoefficient; }

private:
    float frictionCoefficient;
};
