#pragma once
#include "Cube.h"
#include "Pyramid.h"
#define frameMS 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitGL(int argc, char* argv[]);
	void InitObjects();
	/*
	void DrawPolygon();
	void DrawTriangle();
	void DrawCube();
	void DrawCubeArray();
	void DrawIndexedCube();
	void DrawCubeArrayAlt();
	*/
private:
	float rotation = 0.0f;
	Camera* camera;
	SceneObject* objects[400];
	/*
	static Vertex vertices[];
	static Color colors[];
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
	*/
};

