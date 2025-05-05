#pragma once
#include "Cube.h"
#include "Pyramid.h"
#include <ft2build.h>//freetype
#include FT_FREETYPE_H//a macro to include the other header files
#include <string>
#define frameMS 16

class HelloGL
{
public:
    HelloGL(int argc, char* argv[]);
    ~HelloGL(void);
    void Display();
    void Update();
    void Keyboard(unsigned char key, int x, int y);
    static void InitGL(int argc, char* argv[]);
    void InitObjects();
    void InitLighting();

    bool InitFonts();
    void DrawString(std::string &text, Vector3* pos, Color* color);
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
    SceneObject* objects[maxObjects]; //An array of all the objects to be drawn to the screen
    float randFloatRange(float min, float max);
    Vector4* _lightPos;
    Lighting* _lightData;
    FT_Library fontLib;//font library initialisation
    FT_Face fontFace;//font face initialisation
    std::string displayText;
    const char* fontPath = "C:/Windows/Fonts/jokerman.ttf";
    /*
    static Vertex vertices[];
    static Color colors[];
    static Vertex indexedVertices[];
    static Color indexedColors[];
    static GLushort indices[];
    */
};
