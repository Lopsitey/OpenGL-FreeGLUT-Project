#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh,
                         TGALoader* texture,
                         Vector3 position,
                         Vector3 rotationAxis,
                         float frictionCoefficient)
    : _mesh(mesh),
      _texture(texture),
      _position(position),
      _rotationAxis(rotationAxis),
      _frictionCoefficient(frictionCoefficient)
//default member initialisation - better than writing it in the constructor manually e.g. _position = position
{
    //No initialization needed here
}


SceneObject::~SceneObject(void)
{
    delete _mesh;
    delete _texture;
}

void SceneObject::Update()
{
    // Update logic for the scene object
}

void SceneObject::Draw()
{
    // Draw logic for the scene object
}

void SceneObject::SetVelocity(const Vector3& velocity, const float& frictionCoefficient)
{
    //Allows the velocity of objects to be changed dynamically
    _velocity = velocity;
    _frictionCoefficient = frictionCoefficient;
}
