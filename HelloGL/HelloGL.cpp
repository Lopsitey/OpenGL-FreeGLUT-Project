#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGl Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);//clears the scene
	DrawPolygon();//draws the square
	DrawTriangle();//draws the triangle
	glFlush();
}

void HelloGL::DrawPolygon() 
{
	glBegin(GL_POLYGON);//begins the draw (with polygon chosen)
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);//sets the entire colour to red
		glVertex2f(-1, 1);//vertex 1 (top left)
		glVertex2f(1, 1);//vertex 2 (top right)
		glColor4f(0.0, 1.0, 0.0, 1.0);//sets the colour to green (bottom half)
		glVertex2f(1, -1);//vertex 3 (bottom right)
		glVertex2f(-1, -1);//vertex 4 (bottom left)
		glEnd();//ends the drawing
	}
}

void HelloGL::DrawTriangle()
{
	glBegin(GL_TRIANGLES);//begins the draw (with triangle chosen)
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex2f(0.0, 0.75);//vertex (top)
		glColor4f(0.0, 1.0, 0.0, 1.0);//sets the colour to green
		glVertex2f(0.75, -0.75);//vertex (bottom right)
		glColor4f(0.0, 0.0, 1.0, 1.0);//sets the colour to blue
		glVertex2f(-0.75, -0.75);//vertex (bottom left)
		glEnd();
	}
}

HelloGL::~HelloGL(void)
{
}
