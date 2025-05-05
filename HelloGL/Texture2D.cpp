#include "Texture2D.h"
#include <fstream>
#include <iostream>

using namespace std;

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D(void)
{
    glDeleteTextures(1, &_ID); //Delete the texture after use
    delete[] tempTextureData; //Delete the temporary texture data array which stored the contents of the file
}

bool Texture2D::Load(const char* path, int width, int height)
{
    int fileSize;
    ifstream inFile;
    _width = width;
    _height = height;

    inFile.open(path, ios::binary); //Open the file in binary mode
    if (!inFile.good())
    {
        cerr << "Error: Texture file not found" << endl;
        return false;
    }

    inFile.seekg(0, ios::end); //Seek to the end of the file
    fileSize = static_cast<int>(inFile.tellg()); //Gets the size of the file

    tempTextureData = new char[fileSize]; //Creates an array ready to hold the entire file

    inFile.seekg(0, ios::beg); //Go back to the start of the file
    inFile.read(tempTextureData, fileSize); //Read the file into the array
    inFile.close(); //Close the file

    cout << path << " LOADED\n SIZE: " << fileSize << endl;

    glGenTextures(1, &_ID);
    //Generate a texture ID, which is used to reference and manipulate the texture throughout the program
    glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture ID
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);//Create the texture with the given parameters
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
    //Build the mipmaps for the texture
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return true;
}

bool Texture2D::LoadFreeType(const FT_Bitmap& bitmap)
{
    //Use reeType's bitmap data to generate an OpenGL texture
    _width = bitmap.width;
    _height = bitmap.rows;

    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Sets texture wrapping to GL_CLAMP
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    //Generate the texture from the FreeType bitmap buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _width, _height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);

    return true;
}
