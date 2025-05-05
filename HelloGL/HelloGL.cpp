#include "HelloGL.h"
#include "GLUTCallbacks.h"//not actually used in the header so can be included in the cpp instead
#include "MeshLoader.h"
#include <cstdlib>//for rand, srand
#include <ctime>
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	displayText = "Hello World!";//Text to be displayed on the screen
	rotation = 0.0f;
	GLUTCallbacks::Init(this);
	InitGL(argc, argv); //initialises the OpenGL settings
	InitObjects();
	InitLighting();
	InitFonts();
	glutMainLoop();
	FT_Done_Face(fontFace);
	FT_Done_FreeType(fontLib);
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
	_lightPos = new Vector4();
	_lightPos->x = 0.0;
	_lightPos->y = 0.0;
	_lightPos->z = 1.0;
	_lightPos->w = 0.0;

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

void HelloGL::Display() //can be marked const because it doesn't change any values
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the scene

    for (int i = 0; i < maxObjects; ++i)
    {
        objects[i]->Draw();
    }

	glDisable(GL_DEPTH_TEST);//DOES THIS NEED TO BE HERE?

	Vector3 v = { 10.0f, 750.0f, 0.0f };//Top left with a slight gap
	Color c = { 1.0f, 1.0f, 1.0f };
	DrawString(displayText, &v, &c);

	glEnable(GL_DEPTH_TEST);

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
    glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPos->x));
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	displayText += key;//Add the key pressed to the display text
	/*
	if (key == '+')
	{
		rotation += 0.5f;
		//camera->center.x += 0.1f; - pans the camera right
		//camera->center.y += 0.1f; - pans the camera up
		//camera->up.x -= 0.1f;
	}
	if (key == '-')
	{
		rotation -= 0.5f;
		//camera->center.x -= 0.1f; - pans the camera left
		//camera->center.y -= 0.1f; - pans the camera down
		//camera->up.x += 0.1f;
	}
	*/
	if (key == '+')
	{
		camera->eye.z += 0.1f;
	}
	if (key == '-')
	{
		camera->eye.z -= 0.1f;
	}
	/*if (rotation >= 360.0f)
	    rotation = 0.0f;*/
}

bool HelloGL::InitFonts()
{
	FT_Error error = FT_Init_FreeType(&fontLib);
	if (error)//where 0 is success
	{
		std::cerr << "An error occurred during FreeType library initialization: " << error << std::endl;
		exit(1);
	}
	
	error = FT_New_Face(fontLib, fontPath, 0, &fontFace);
	if (error)
	{
		std::cerr << "An error occurred during FreeType face initialization: " << error << std::endl;
		exit(1);
	}
	else if (error)
	{
		std::cerr << "An error occurred, the font file could be opened or read, or it is broken... " << error << std::endl;
		exit(1);
	}

	FT_Set_Pixel_Sizes(fontFace, 0, 40);//Sets the font size to 40px
}

void HelloGL::DrawString(std::string &text, Vector3* pos, Color* color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);//Sets the window dimensions
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Alpha blending

	glColor3f(color->r, color->g, color->b);
	float startX = pos->x;
	float startY = pos->y;

	for (char c : text)
	{
		if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
		{
			std::cerr << "Could not load character" << std::endl;
			continue;
		}

		FT_GlyphSlot glyph = fontFace->glyph;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		Texture2D fontTex;
		fontTex.LoadFreeType(glyph->bitmap);//Create the texture for this character using the Texture2D class
		
		//Set the position for this character
		float x = startX + glyph->bitmap_left;
		float y = startY - (glyph->bitmap.rows - glyph->bitmap_top);//Align to the baseline 
		//Get the character width and height
		float texWidth = glyph->bitmap.width;
		float texHeight = glyph->bitmap.rows;

		//Draw the character as a textured quad
		glBindTexture(GL_TEXTURE_2D, fontTex.GetID());
		glBegin(GL_QUADS);//Have to render BL to TR because FreeType's origin is BL

		glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);//Bottom-left
		glTexCoord2f(1.0f, 1.0f); glVertex2f(x + texWidth, y);//Bottom-right
		glTexCoord2f(1.0f, 0.0f); glVertex2f(x + texWidth, y + texHeight);//Top-right
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + texHeight);//Top-left

		glEnd();

		// Advance the position for the next character
		startX += glyph->advance.x >> 6;//Advance in pixels (note: FT_Advance is in 1/64th of a pixel)
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}