#pragma once
#include "Structures.h"
#include "TGALoader.h"
#include "Texture2D.h"

class SceneObject
{
protected:
    Mesh* _mesh;
    TGALoader* _texture;
    Material* _material;
    Vector3 _position{0.0f, 0.0f, 0.0f};
    Vector3 _rotationAxis{0.0f, 0.0f, 0.0f};
    Vector3 _velocity{0.0f, 0.0f, 0.0f};
    float _frictionCoefficient{0.99f}; //default friction coefficient where 1 is no friction
    GLfloat _rotationSpeed = 0.0f;

public:
    SceneObject(Mesh* mesh, TGALoader* texture, Vector3 position, Vector3 rotationAxis, float frictionCoefficient);
    virtual ~SceneObject(void);

    virtual void Update(); //only needs to be declared virtual in the base class
    virtual void Draw(); //any derived class can then override it, even children of children
    virtual void SetVelocity(const Vector3& velocity, const float& frictionCoefficient);
    //all objects have a velocity and friction
    virtual float GetFrictionCoefficient() const { return _frictionCoefficient; } //returns the friction coefficient
    virtual void InitMaterials() 
    {
        //Default material initialization
        _material->ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
        _material->diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
        _material->specular = { 0.2f, 0.2f, 0.2f, 1.0f };
        _material->shininess = 32.0f;
    };
};
