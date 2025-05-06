#pragma once
#include "Structures.h"
#include "TGALoader.h"
#include "Texture2D.h"

class SceneObject
{
protected:
    Mesh* _mesh;
    TGALoader* _texture;

public:
    SceneObject(Mesh* mesh, TGALoader* texture);
    virtual ~SceneObject(void);

    virtual void Update(); //only needs to be declared virtual in the base class
    virtual void Draw(); //any derived class can then override it, even children of children
    virtual void SetVelocity(const Vector3& velocity, const float& frictionCoefficient);
};
