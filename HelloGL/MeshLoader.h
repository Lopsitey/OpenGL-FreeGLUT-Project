#pragma once
#include "Structures.h"
#include <fstream>
#include <iostream>
#include <gl/GLU.h>//OpenGL utilities

namespace MeshLoader
{
	Mesh* Load(char* path);
};

