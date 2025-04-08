#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube(void);

	void Draw();
	void Update();
private:
	//static Vertex indexedVertices[];
	//static Color indexedColors[];
	//static GLushort indices[];
	Vector3 _position;
	GLfloat _rotation;
};

