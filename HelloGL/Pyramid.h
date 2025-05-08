#pragma once
#include "SceneObject.h"

class Pyramid : public SceneObject
{
public:
    Pyramid(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis);
    ~Pyramid(void) override;

    void Draw() override;
    void Update() override;
    void InitMaterials();
    float GetFrictionCoefficient() const override { return frictionCoefficient; }
private:
    GLfloat _rotationSpeed;
    Material* _material;
    float frictionCoefficient;
};
