#include "TGALoader.h"
#include <fstream>
#include <iostream>
//Casts to an unsigned char using the new method
#define ucharCast(c) static_cast<unsigned char>(c)
//#define length(x) (sizeof(x)/sizeof(x[0]))
using namespace std;

TGALoader::TGALoader()
{
	_ID = 0;//Zero by default
	_width = 0;
	_height = 0;
    tempHeaderData = new char[headerSize];
	tempTextureData = nullptr;
}
TGALoader::~TGALoader(void)
{
    delete[] tempHeaderData; //We don't need the header memory anymore
    delete[] tempTextureData; //Clear up the data - We don't need this anymore
	glDeleteTextures(1, &_ID); //Delete the texture after use
}

bool TGALoader::Load(const char* path)
{
    int fileSize, width = _width, height = _height;
    char type, pixelDepth, mode;

    ifstream inFile;

    inFile.open(path, ios::binary);
    if (!inFile.good())
    {
        cerr << "Can't open TGA texture file " << path << endl;
        return false;
    }

    inFile.seekg(0, ios::beg);//Seek back to beginning of file
    inFile.read(tempHeaderData, headerSize);//Read in all of the header data (the first 18 bytes)

    inFile.seekg(0, ios::end);//Seek to end of file
    fileSize = (int)inFile.tellg() - headerSize;//Get currents position in file which gives us total file size, so we take the header size off

    tempTextureData = new char[fileSize]; //Create a new array to store data
    inFile.seekg(headerSize, ios::beg); //Seek back to beginning of file + 18
    inFile.read(tempTextureData, fileSize); //Read in all the data in one go
    inFile.close(); //Close the file

    type = tempHeaderData[2];//Get TGA Type out of Header - Must be RGB for this to work
    width = (ucharCast(tempHeaderData[13]) << 8u) + ucharCast(tempHeaderData[12]);//Find the width (Combines two bytes into a short)
    height = (ucharCast(tempHeaderData[15]) << 8u) + ucharCast(tempHeaderData[14]);//Find the height
    //The u is used to explicitly state that the shift taking place is unsigned

    bool flipped = false;
    if ((int)((tempHeaderData[11] << 8) + tempHeaderData[10]) == 0)
        flipped = true;

    if (type == 2)//Type 2 is RGB
    {
        cout << path << " TGA LOADED\n SIZE: " << fileSize << endl;

        glGenTextures(1, &_ID);//Get next Texture ID
        glBindTexture(GL_TEXTURE_2D, _ID);//Bind the texture to the ID

        pixelDepth = tempHeaderData[16];//Find the pixel depth (24/32bpp)
        mode = pixelDepth / 8;//Get the mode (1 byte = 8 bits = 1 channel, 2 bytes = 16 bits = 2 channels, etc.)
        //Dividing it by 8 converts it to bytes which is the same as the number of colour channels

        //Note that TGA files are stored as BGR(A) - So we need to specify the format as GL_BGR(A)_EXT
        if (mode == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempTextureData);
            
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);//Build the mipmaps for the texture
        }
       // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);//Create the texture with the given parameters
    }

    return _ID > 0;
}
