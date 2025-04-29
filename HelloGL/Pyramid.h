#pragma once
#include "SceneObject.h"
class Pyramid : public SceneObject
{
public:
	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid(void);

	void Draw();
	void Update();
private:
	Vector3 _position;
	GLfloat _rotation;
};

