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
private:
    //static Vertex indexedVertices[];
    //static Color indexedColors[];
    //static GLushort indices[];
    Vector3 _position;
    GLfloat _rotationSpeed;
    Vector3 _rotationAxis;
    Material* _material;
};
