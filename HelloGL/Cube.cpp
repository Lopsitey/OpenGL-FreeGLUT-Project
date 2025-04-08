#include "Cube.h"/*
Vertex Cube::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
				-1,-1, 1,   1,-1, 1,   // v2,v3
				1,-1,-1,   1, 1,-1,    // v4,v5
				-1, 1,-1,   -1,-1,-1 }; // v6,v7

Color Cube::indexedColors[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
				1, 0, 0,   1, 0, 1,   // v2,v3
				0, 0, 1,   0, 1, 1,   // v4,v5
				0, 1, 0,   0, 0, 0 }; //v6,v7

GLushort Cube::indices[] = { 0, 1, 2,  2, 3, 0,      // front
				0, 3, 4,  4, 5, 0,      // right
				0, 5, 6,  6, 1, 0,      // top
				1, 6, 7,  7, 2, 1,      // left
				7, 4, 3,  3, 2, 7,      // bottom
				4, 7, 6,  6, 5, 4 };    // back
				*/
Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_mesh = mesh;
	_texture = texture;
	_rotation = 0.0f;
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Cube::~Cube(void)
{
	delete _mesh;//Because it's a pointer which has dynamically allocated objects using new
	//For example, in the MeshLoader: Mesh* mesh = new Mesh();
}

void Cube::Draw()
{
	if (_mesh == nullptr)
		return;//exits if the mesh hasn't been loaded correctly

	glBindTexture(GL_TEXTURE_2D, _texture->GetID());//binds the texture to the cube so it can be drawn with it
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);//enables the texture to be drawn
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);//binds the texture coordinates to the cube

	//instead of retyping every vertex and colour manually in one big long array we can use an array of colours and an array of vertices
	//these can then be reused by applying them with the relevant indicies
	//its like accessing a colour pallete and size chart and then choosing what side to apply what colour and length too
	//the indices in this case are being used to access the colours in a specific order whilst they are applied to the sides in a linear order using the pointer to access them
	//therefore, if you wanted to change the colour of the third side you would have to change the third value in the indices array to access a different colour

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);//draw mode, side count, indices type, indices
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);//disables the texture coordinates
}

void Cube::Update()
{
	_rotation += 0.1f;
}