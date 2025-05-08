#include "Cube.h"

Cube::Cube(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
	: SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.995f)
{
	//0.999f slows the cube down over time (less friction than the pyramid)
}


Cube::~Cube(void)
{
	
}

void Cube::Update()
{
	_rotationSpeed += 0.8f;
	_velocity *= _frictionCoefficient; //applies friction to the velocity
	_position += _velocity; //adds the vectors directly
}

void Cube::InitMaterials()
{
	_material = new Material();
	_material->ambient = {0.8f, 0.05f, 0.05f, 1.0f}; //red
	_material->diffuse = {0.8f, 0.05f, 0.05f, 1.0f}; //red
	_material->specular = {1.0f, 1.0f, 1.0f, 1.0f}; //bright white - higher value = brighter
	_material->shininess = 100.0f;
}