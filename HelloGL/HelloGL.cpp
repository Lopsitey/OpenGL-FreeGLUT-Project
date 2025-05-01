#include "HelloGL.h"
#include "GLUTCallbacks.h"//not actually used in the header so can be included in the cpp instead
#include "MeshLoader.h"
#include <cstdlib>//for rand, srand
#include <ctime>
/*
Vertex HelloGL::vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
				-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
				1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
				-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

				-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
				-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

				-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
				1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

				1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
				-1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

Color HelloGL::colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
				1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
				0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
				0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

				1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
				0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

				0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
				1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

				0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
				0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4
*/

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	GLUTCallbacks::Init(this);
	InitGL(argc, argv); //initialises the OpenGL settings
	InitObjects();
	InitLighting();
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera; //Clean up the dynamically allocated Camera object
	delete*objects; //for deleting an array
}

void HelloGL::InitGL(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(550, 100); //Centered in HD
	glutCreateWindow("Simple OpenGl Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(frameMS, GLUTCallbacks::Timer, frameMS);
	//16 milliseconds to a frame - 1000ms in a second 1000/16 = 60 - for 60fps
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION); //the matrix that deals with the camera
	glLoadIdentity();
	glViewport(0, 0, 800, 800); //sets the viewport to the entire window
	gluPerspective(45, 1, 0.5f, 1000); //45 fov, 1 aspect ratio, 0.5 near clipping plane, 1000 far clipping plane
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D); //enables 2D texturing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); //removes the back faces of the polygons
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
}

void HelloGL::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::Load("cube.txt"); //Load the mesh from the file
	Mesh* triangleMesh = MeshLoader::Load("pyramid.txt"); //Load the mesh from the file
	auto textureTGA = new TGALoader();
	auto texture = new Texture2D();
	texture->Load("penguins.raw", 512, 512);
	textureTGA->Load("fern.tga"); //Load the texture from the file
	//constexpr int cubeAmount = maxObjects - 100;

	srand(static_cast<unsigned int>(time(nullptr))); //Only need to seed the numbers once
	for (int i = 0; i < maxObjects; ++i)
	{
		//Random x y and z position for each cube
		float randX = randFloatRange(-20.0f, 19.9f);
		float randY = randFloatRange(-10.0f, 9.9f);
		float randZ = -randFloatRange(0.0f, 99.9f);

		Vector3 randRotAxis = {
			randFloatRange(1.0f, 10.0f), randFloatRange(1.0f, 10.0f), randFloatRange(1.0f, 10.0f)
		}; //Rotation axis

		objects[i] = new Cube(cubeMesh, textureTGA, randX, randY, randZ, randRotAxis);
		//instantiating a child of the parent class SceneObject
	}
	/* Deprecated because the pyramids file became outdated as the project progressed
	for (int i = cubeAmount; i < maxObjects; ++i)
	{
	    objects[i] = new Pyramid(triangleMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	*/
	rotation = 0.0f; //default rotation
	camera = new Camera(); //Deleted in the destructor
	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;
	//moves the camera further away than the prior line
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;//the position of the camera in the world
	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f; //the point the camera is focussed on 
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->ambient.x = 0.2f;
	_lightData->ambient.y = 0.2f;
	_lightData->ambient.z = 0.2f;
	_lightData->ambient.w = 1.0f;
	_lightData->diffuse.x = 0.8f;
	_lightData->diffuse.y = 0.8f;
	_lightData->diffuse.z = 0.8f;
	_lightData->diffuse.w = 1.0f;
	_lightData->specular.x = 0.2f;
	_lightData->specular.y = 0.2f;
	_lightData->specular.z = 0.6f; //changed from 0.2 to make random objects shiny
	_lightData->specular.w = 1.0f;
}

void HelloGL::Display() const //can be marked const because it doesn't change any values
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the scene
	//DrawPolygon();//draws the square
	//DrawTriangle();//draws the triangle
	/*glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);//moves the camera back 5 units
	glRotatef(rotation, rotation, 0.0f, rotation);//-1 rotates it right 1 rotates it left
	glColor4f(0.0, 1.0, 0.0, 1.0);//sets the colour to green
	glutWireTeapot(0.5);
	glPopMatrix();*/
	//DrawCubeArray();
	//DrawIndexedCube();
	//DrawCubeArrayAlt();
	//for (auto& object : objects)
    for (int i = 0; i < maxObjects; ++i)
    {
        objects[i]->Draw();
    }
    glFlush();
    glutSwapBuffers();
}

//Generates a random float in the range [min, max]
float HelloGL::randFloatRange(float min, float max)
{
	float num = (max - min) + min;
	return (static_cast<float>(rand()) / RAND_MAX) * (max - min) + min;
}


void HelloGL::Update()
{
    for (int i = 0; i < maxObjects; ++i)
    {
        objects[i]->Update();
    }
    glLoadIdentity();
    gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z,
              camera->up.x, camera->up.y, camera->up.z);
    glutPostRedisplay();
    glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x));
    glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x));
    glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		rotation += 0.5f;
		//camera->center.x += 0.1f; - pans the camera right
		//camera->center.y += 0.1f; - pans the camera up
		//camera->up.x -= 0.1f;
	}
	if (key == 'a')
	{
		rotation -= 0.5f;
		//camera->center.x -= 0.1f; - pans the camera left
		//camera->center.y -= 0.1f; - pans the camera down
		//camera->up.x += 0.1f;
	}
	if (key == 'w')
	{
		camera->eye.z += 0.1f;
	}
	if (key == 's')
	{
		camera->eye.z -= 0.1f;
	}
	/*if (rotation >= 360.0f)
	    rotation = 0.0f;*/
}


/*
void HelloGL::DrawPolygon()
{
	glPushMatrix();//isolates the matrix so the calculations don't interfere with the vertices
	glTranslatef(0.0f, 0.0f, -5.0f);//moves the camera back 5 units
	glRotatef(rotation, rotation, 0.0f, rotation);//-1 rotates it right 1 rotates it left
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
	glRotatef(rotation, 0.0f, 0.0f, 0);
	glRotatef(rotation, rotation, 0.0f, rotation);
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

void HelloGL::DrawCube()
{
	glRotatef(rotation, 0.0f, rotation, 0.0f);//rotates the object's y axis but makes it spin left and right
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

void HelloGL::DrawCubeArray() 
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, rotation, 0.0f);//rotates the object's y axis but makes it spin left and right
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; ++i) 
	{
		
		//this works because the data in the array is contiguous
		//glColor3f(colors[i].r,colors[i].g,colors[i].b);//accessing an array filled with data structures works like this, every three values is a new vector 3 essentially
		//glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		
		glColor3fv(&colors[i].r);
		glVertex3fv(&vertices[i].x);
	}
	glEnd();
	glPopMatrix();
}

void HelloGL::DrawIndexedCube() 
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, rotation, 0.0f);//rotates the object's y axis but makes it spin left and right
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; ++i)
	{
		//instead of retyping every vertex and colour manually in one big long array we can use an array of colours and an array of vertices
		//these can then be reused by applying them with the relevant indices
		//its like accessing a colour palette and size chart and then choosing what side to apply what colour and length too
		//the indices in this case are being used to access the colours in a specific order whilst they are applied to the sides in a linear order using i to iterate
		//therefore, if you wanted to change the colour of the third side you would have to change the third value in the indices array to access a different colour
		glColor3fv(&indexedColors[indices[i]].r);//this function uses a pointer to pull all three values from the colour struct, not just the r value
		glVertex3fv(&indexedVertices[indices[i]].x);
	}
	glEnd();
	glPopMatrix();
}

void HelloGL::DrawCubeArrayAlt() 
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glPushMatrix();
	glRotatef(rotation, 0.0f, rotation, 0.0f);//rotates the object's y axis but makes it spin left and right
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
*/
