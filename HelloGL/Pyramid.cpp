#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
	: SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.99f)
{
	//0.99f slows the pyramid down over time (more friction than the cube)
}

Pyramid::~Pyramid(void)
{
	
}

void Pyramid::Update()
{
	_rotationSpeed += 0.5f; //rotates slower than the cube
	_velocity *= _frictionCoefficient;
	_position += _velocity;
}

void Pyramid::InitMaterials()
{
	_material = new Material();
	_material->ambient = {0.5f, 1, 1, 1.0f}; //eggshell blue ambient light (lighter blue-green)
	_material->diffuse = {0.5f, 0.8f, 0.8f, 1.0f}; //eggshell blue shine / direct reflection
	_material->specular = {0.3f, 0.6f, 0.6f, 1.0f}; //greenish/blueish specular (soft shine)
	_material->shininess = 32.0f; //lower shininess for a more matte finish;
}
