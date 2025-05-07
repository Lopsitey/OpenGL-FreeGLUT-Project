#pragma once
#include <Windows.h>//OpenGL on windows
#include <gl/GL.h>//OpenGL itself
#include <gl/GLU.h>//OpenGL utilities
#include "GL/freeglut.h"//freeglut library
#include <string>
#include <vector>

struct Vector3
{
    float x, y, z;

    Vector3& operator+=(const Vector3& other) //overloaded the operator to allow direct addition with other vectors
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& operator*=(const float& other) //for multiplication
    {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    Vector3& operator=(const Vector3& other) = default; //allows you to directly set the vector 3

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

struct SubMesh
{
    std::vector<Vertex> Vertices; //a vector of Vector3s (verticies)
    std::vector<Vector3> Normals;
    std::vector<GLushort> Indices;
    std::vector<TextCoordinate> TexCoords;
};

struct Mesh
{
    std::vector<SubMesh> SubMeshes;
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
struct Glyph {
    GLuint textureID;
    int width, height;
    int bearingX, bearingY;
    int advance;
};