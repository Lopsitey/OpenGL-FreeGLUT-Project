#pragma once
#include <Windows.h>//OpenGL on windows
#include <gl/GL.h>//OpenGL itself
#include <gl/GLU.h>//OpenGL utilities
#include "GL/freeglut.h"//freeglut library

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

/*
struct Color
{
	GLfloat r, g, b;
};
*/
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
    Vector3* Normals;
    GLushort* Indices;
    TextCoordinate* TexCoords;
    int TextCoordinateCount;
    int VertexCount, NormalCount, IndexCount;
};

struct Vector4
{
    float x, y, z, w;
};

struct Lighting
{
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
};

struct Material
{
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    GLfloat shininess;
};
