#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
    Cube(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis);
    ~Cube(void) override;

    void Draw() override;
    void Update() override;
    void InitMaterials();
    float GetFrictionCoefficient() const override { return frictionCoefficient; }
private:
    GLfloat _rotationSpeed;
    Material* _material;
    float frictionCoefficient;
};
