#include "Cube.h"

Cube::Cube(Mesh* mesh, float x, float y, float z)
{
	_mesh = mesh;
	_rotation = 0.0f;
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Cube::~Cube(void)
{

}

void Cube::Draw()
{
	DrawIndexedCubeAlt();
}

void Cube::Update()
{
	_rotation += 0.1f;
}

void Cube::DrawIndexedCubeAlt()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
	//instead of retyping every vertex and colour manually in one big long array we can use an array of colours and an array of vertices
	//these can then be reused by applying them with the relevant indicies
	//its like accessing a colour pallete and size chart and then choosing what side to apply what colour and length too
	//the indices in this case are being used to access the colours in a specific order whilst they are applied to the sides in a linear order using the pointer to access them
	//therefore, if you wanted to change the colour of the third side you would have to change the third value in the indices array to access a different colour
	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);//draw mode, side count, indices type, indices
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}