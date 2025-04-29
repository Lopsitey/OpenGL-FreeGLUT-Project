#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)      
{
	_mesh = mesh;
	_position.x = x;	
	_position.y = y;
	_position.z = z;
	_rotation = 0;
}

Pyramid::~Pyramid(void)
{
	delete _mesh;//delete the mesh
}

void Pyramid::Draw()
{
	if (_mesh == nullptr)
		return;//exits if the mesh hasn't been loaded correctly

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);//draw mode, side count, indices type, indices
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Pyramid::Update()
{
	_rotation += 0.5f;
}
