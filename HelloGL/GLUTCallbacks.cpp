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
		int updateTime = glutGet(GLUT_ELAPSED_TIME);//how long it took to process since glutInit
		helloGL->Update();//no if statement needed because timer will always be called after display so the null check will have already been performed
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;//How long it took to process the update frame
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}
	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
		//Code here
	}
}