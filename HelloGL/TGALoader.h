#pragma once
#include "Structures.h"

class TGALoader
{
public:
	TGALoader();
	~TGALoader(void);

	bool Load(const char* path);

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

private:
	GLuint _ID;//Texture ID
	int _width, _height;//Width and height of the texture
	char* tempHeaderData = new char[18]; //18 Bytes is TGA Header Size
	char* tempTextureData;//Temporary texture data array
};

