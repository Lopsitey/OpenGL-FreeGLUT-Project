#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
    Cube(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis);
    ~Cube(void) override;

    void Update() override;
    void InitMaterials() override;
    float GetFrictionCoefficient() const override { return frictionCoefficient; }
private:
    Material* material;
    float frictionCoefficient;
};
