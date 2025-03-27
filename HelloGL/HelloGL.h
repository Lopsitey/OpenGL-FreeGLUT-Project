#pragma once
#include <Windows.h>//OpenGL on windows
#include <gl/GL.h>//OpenGL itself
#include <gl/GLU.h>//OpenGL utilities
#include "GL\freeglut.h"//freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#define frameMS 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	/*
	void DrawPolygon();
	void DrawTriangle();
	void DrawCube();
	void DrawCubeArray();
	void DrawIndexedCube();
	void DrawCubeArrayAlt();
	*/
private:
	float rotation;
	float triangleRotation;
	Camera* camera;
	Cube* cube[200];
	/*
	static Vertex vertices[];
	static Color colors[];
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
	*/
};

