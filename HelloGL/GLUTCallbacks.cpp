#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks 
{
	namespace
	{
		//Initialises as null before any action
		HelloGL* helloGL = nullptr;
	}
	void Init(HelloGL* gl) 
	{
		helloGL = gl;
	}
	void Display() 
	{
		if (helloGL != nullptr) 
		{
			helloGL->Display();//lambda
		}
	}
}