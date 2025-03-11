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
	void Timer(int preferredRefresh)
	{
		helloGL->Update();//no if statement needed because timer will always be called after display so the null check will have already been performed
		glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
	}
}