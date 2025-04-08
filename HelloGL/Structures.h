#pragma once
#include <Windows.h>//OpenGL on windows
#include <gl/GL.h>//OpenGL itself
#include <gl/GLU.h>//OpenGL utilities
#include "GL\freeglut.h"//freeglut library

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

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TextCoordinate
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	TextCoordinate* TexCoords;
	int TextCoordinateCount;
	int VertexCount, ColorCount, IndexCount;
};