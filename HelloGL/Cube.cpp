#include "Cube.h"
Cube::Cube(Mesh* mesh, TGALoader* texture, float x, float y, float z, Vector3 rotationAxis) : SceneObject(mesh, texture)
{
	_mesh = mesh;
	_texture = texture;
	_rotationSpeed = 0.0f;
	_rotationAxis = rotationAxis;
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Cube::~Cube(void)
{
	delete _mesh; //Because it's a pointer which has dynamically allocated objects using new
	//For example, in the MeshLoader: Mesh* mesh = new Mesh();
}

void Cube::Draw()
{
	if (_mesh == nullptr)
		return; //exits if the mesh hasn't been loaded correctly

	glBindTexture(GL_TEXTURE_2D, _texture->GetID()); //binds the texture to the cube so it can be drawn with it
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //enables the texture to be drawn
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	//glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords); //binds the texture coordinates to the cube
	InitMaterials();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);

	//instead of retyping every vertex and colour manually in one big long array we can use an array of colours and an array of vertices
	//these can then be reused by applying them with the relevant indicies
	//its like accessing a colour pallete and size chart and then choosing what side to apply what colour and length to
	//the indices in this case are being used to access the colours in a specific order whilst they are applied to the sides in a linear order using the pointer to access them
	//therefore, if you wanted to change the colour of the third side you would have to change the third value in the indices array to access a different colour

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotationSpeed, _rotationAxis.x, _rotationAxis.y, _rotationAxis.z);
	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	//draw mode, side count, indices type, indices
	glPopMatrix();

	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //disables the texture coordinates
}

void Cube::Update()
{
	_rotationSpeed += 0.8f;
	_velocity *= _frictionCoefficient;
	_position += _velocity; //adds the vectors directly
}

void Cube::InitMaterials()
{
	_material = new Material();
	_material->ambient.x = 0.8f;
	_material->ambient.y = 0.05f;
	_material->ambient.z = 0.05f;
	_material->ambient.w = 1.0f;
	_material->diffuse.x = 0.8f;
	_material->diffuse.y = 0.05f;
	_material->diffuse.z = 0.05f;
	_material->diffuse.w = 1.0f;
	_material->specular.x = 1.0f;
	_material->specular.y = 1.0f;
	_material->specular.z = 1.0f;
	_material->specular.w = 1.0f;
	_material->shininess = 100.0f;
}

void Cube::SetVelocity(const Vector3& velocity, const float& frictionCoefficient)
{
	_velocity = velocity;
	_frictionCoefficient = frictionCoefficient;
}
