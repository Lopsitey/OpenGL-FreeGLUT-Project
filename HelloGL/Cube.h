#pragma once
#include <Windows.h>//OpenGL on windows
#include <gl/GL.h>//OpenGL itself
#include <gl/GLU.h>//OpenGL utilities
#include "GL\freeglut.h"//freeglut library
#include "Structures.h"
#include "MeshLoader.h"

class Cube
{
public:
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube(void);

	void Draw();
	void Update();
	void DrawIndexedCubeAlt();
private:
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
	GLfloat _rotation;
	Vector3 _position;
	Mesh* _mesh;
};

