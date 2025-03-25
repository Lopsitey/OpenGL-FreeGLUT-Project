#pragma once
#include <Windows.h>//OpenGL on windows
#include <gl/GL.h>//OpenGL itself
#include <gl/GLU.h>//OpenGL utilities
#include "GL\freeglut.h"//freeglut library
#include "GLUTCallbacks.h"
#define frameMS 16

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display();
	void DrawPolygon();
	void DrawTriangle();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void DrawCube();
private:
	float rotation;
	float triangleRotation;
	Camera* camera;
};

