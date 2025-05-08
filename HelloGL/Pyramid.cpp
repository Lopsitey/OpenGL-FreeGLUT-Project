#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis)
	: SceneObject(mesh, texture, Vector3{x, y, z}, rotationAxis, frictionCoefficient = 0.99f)
{
	//0.99f slows the pyramid down over time (more friction than the cube)
	_rotationSpeed = 0;
}

Pyramid::~Pyramid(void)
{
    delete _mesh; //delete the mesh
}

void Pyramid::Draw()
{
	if (_mesh == nullptr)
		return;

	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	for (const auto& subMesh : _mesh->SubMeshes)
	{
		glNormalPointer(GL_FLOAT, 0, subMesh.Normals.data());
		glVertexPointer(3, GL_FLOAT, 0, subMesh.Vertices.data());
		glTexCoordPointer(2, GL_FLOAT, 0, subMesh.TexCoords.data());
	}
	InitMaterials();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotationSpeed, _rotationAxis.x, _rotationAxis.y, _rotationAxis.z);
	for (const auto& subMesh : _mesh->SubMeshes)
	{
		glDrawElements(GL_TRIANGLES, subMesh.Indices.size(), GL_UNSIGNED_SHORT, subMesh.Indices.data());
	}
	glPopMatrix();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
