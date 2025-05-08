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
    delete _material; //Because it's a pointer which has dynamically allocated objects using new
    //For example, in the MeshLoader: Mesh* mesh = new Mesh();
}

void SceneObject::Update()
{
    // Update logic for the scene object
}

void SceneObject::Draw()
{
	if (_mesh == nullptr)
		return; //exits if the mesh hasn't been loaded correctly

	glBindTexture(GL_TEXTURE_2D, _texture->GetID()); //binds the texture to the cube so it can be drawn with it
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //enables the texture to be drawn
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	for (const auto& subMesh : _mesh->SubMeshes)
	{
		//.data() returns a pointer to the first element of the array which is all the function needs to read the entire array
		glNormalPointer(GL_FLOAT, 0, subMesh.Normals.data());
		glVertexPointer(3, GL_FLOAT, 0, subMesh.Vertices.data());
		glTexCoordPointer(2, GL_FLOAT, 0, subMesh.TexCoords.data()); //binds the texture coordinates to the cube
	}
	InitMaterials(); //polyymorphism - calls the derived class InitMaterials function
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

	for (const auto& subMesh : _mesh->SubMeshes)
	{
		glDrawElements(GL_TRIANGLES, subMesh.Indices.size(), GL_UNSIGNED_SHORT, subMesh.Indices.data());
		//draw mode, side count, indices type, indices
	}
	glPopMatrix();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //disables the texture coordinates
}

void SceneObject::SetVelocity(const Vector3& velocity, const float& frictionCoefficient)
{
    //Allows the velocity of objects to be changed dynamically
    _velocity = velocity;
    _frictionCoefficient = frictionCoefficient;
}
