#pragma once
#include "Structures.h"

class Texture2D
{
public:
	Texture2D();
	~Texture2D(void);
	
	bool Load(char* path, int width, int height);

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

private:
	GLuint _ID;//Texture ID
	int _width, _height;//Width and height of the texture
	char* tempTextureData;//Temporary texture data array
};

