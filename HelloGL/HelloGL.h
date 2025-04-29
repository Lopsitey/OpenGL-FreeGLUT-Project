#pragma once
#include "Cube.h"
#include "Pyramid.h"
#define frameMS 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display() const;
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	static void InitGL(int argc, char* argv[]);
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
	static constexpr int maxObjects = 250;
	float rotation;
	Camera* camera;
	SceneObject* objects[maxObjects];//An array of all the objects to be drawn to the screen
	/*
	static Vertex vertices[];
	static Color colors[];
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
	*/
};

