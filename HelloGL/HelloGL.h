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
    void DrawString(std::string& text, Vector3* pos, Color* color);
    
    static void InitGL(int argc, char* argv[]);
    void InitObjects();
    void InitLighting();
    bool InitFonts();
    //Needs to be static because for usage i static functions
    static HelloGL* instance; //Static pointer to the instance so free functions can be referenced in static functions
    void InitMenu();
    static void MenuCallback(int option);
    void Menu(int option);
    
private:
    static constexpr int maxObjects = 250;
    float rotation;
    Camera* camera;
    SceneObject* objects[maxObjects]; //An array of all the objects to be drawn to the screen
    static GLfloat randFloatRange(float min, float max);
    Vector4* _lightPos;
    Lighting* _lightData;
    FT_Library fontLib;//font library initialisation
    FT_Face fontFace;//font face initialisation
    std::string displayText;
    std::string fontType = "jokerman";
    Vector3 textLoc = {120.0f, 500.0f, 0.0f}; //Centered by default
    int menuOption = 0;
    bool initiatedTyping = false;
    bool showObjects = false;
    void UpdateVelocity(const Vector3& velocity, const float& frictionCoefficient);
};
