#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	triangleRotation = 0.0f;
	camera = new Camera();//Deleted in the destructor
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
    camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
    camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(550, 100);//Centered in HD
	glutCreateWindow("Simple OpenGl Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(frameMS, GLUTCallbacks::Timer, frameMS);//16 milliseconds to a frame - 1000ms in a second 1000/16 = 60 - for 60fps
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_MODELVIEW);//GL_PROJECTION is the matrix that deals with the camera
    glLoadIdentity();
    glViewport(0, 0, 800, 800);//sets the viewport to the entire window
    gluPerspective(45, 1, 0.5f, 1000);//45 fov, 1 aspect ratio, 0.5 near clipping plane, 1000 far clipping plane
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);//clears the scene
	DrawPolygon();//draws the square
	DrawTriangle();//draws the triangle
	//DrawCube();
	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update() 
{
    glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
}

void HelloGL::DrawPolygon() 
{
    glPushMatrix();//isolates the matrix so the calculations don't interfere with the verticies
    glTranslatef(0.0f, 0.0f, -5.0f);//moves the camera back 5 units
	glRotatef(rotation, 0.0f, 0.0f, 0.0f);//-1 rotates it right 1 rotates it left
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
	glPopMatrix();//if I don't pop the matrix here it stacks the rotations with anything called afterwards
}

void HelloGL::DrawTriangle()
{
	glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);//moves the camera back 5 units
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
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
	//glPopMatrix();
}

HelloGL::~HelloGL(void)
{
    delete camera;//Clean up the dynamically allocated Camera object
}

void HelloGL::Keyboard(unsigned char key, int x, int y) 
{
	if (key == 'd') 
	{
		rotation += 0.5f;
	}
	if (key == 'a')
	{
		rotation -= 0.5f;
	}
	/*if (rotation >= 360.0f)
		rotation = 0.0f;*/
}

void HelloGL::DrawCube()
{
    glBegin(GL_TRIANGLES);
    // face v0-v1-v2
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    glColor3f(1, 1, 0);
    glVertex3f(-1, 1, 1);
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    // face v2-v3-v0
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    // face v0-v3-v4
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    glColor3f(0, 0, 1);
    glVertex3f(1, -1, -1);
    // face v4-v5-v0
    glColor3f(0, 0, 1);
    glVertex3f(1, -1, -1);
    glColor3f(0, 1, 1);
    glVertex3f(1, 1, -1);
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);

    // face v0-v5-v6
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    glColor3f(0, 1, 1);
    glVertex3f(1, 1, -1);
    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    // face v6-v1-v0
    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    glColor3f(1, 1, 0);
    glVertex3f(-1, 1, 1);
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);

    // face  v1-v6-v7
    glColor3f(1, 1, 0);
    glVertex3f(-1, 1, 1);
    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);
    // face v7-v2-v1
    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glColor3f(1, 1, 0);
    glVertex3f(-1, 1, 1);

    // face v7-v4-v3
    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1);
    glVertex3f(1, -1, -1);
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    // face v3-v2-v7
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);

    // face v4-v7-v6
    glColor3f(0, 0, 1);
    glVertex3f(1, -1, -1);
    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);
    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    // face v6-v5-v4
    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    glColor3f(0, 1, 1);
    glVertex3f(1, 1, -1);
    glColor3f(0, 0, 1);
    glVertex3f(1, -1, -1);

    glEnd();
}