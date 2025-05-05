#pragma once
#include "Structures.h"
#include <ft2build.h>//freetype
#include FT_FREETYPE_H//a macro to include the other header files

class Texture2D
{
public:
    Texture2D();
    ~Texture2D(void);

    bool Load(const char* path, int width, int height);
    bool LoadFreeType(const FT_Bitmap& bitmap);

    GLuint GetID() const { return _ID; }
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }

private:
    GLuint _ID; //Texture ID
    int _width, _height; //Width and height of the texture
    char* tempTextureData; //Temporary texture data array
};
