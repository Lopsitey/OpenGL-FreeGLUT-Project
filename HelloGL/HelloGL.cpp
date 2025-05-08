#include "HelloGL.h"
#include "GLUTCallbacks.h"//not actually used in the header so can be included in the cpp instead
#include <cstdlib>//for rand, srand
#include <ctime>
#include <iostream>
#define GLfloat(x) static_cast<GLfloat>(x)//Casts input to a GLfloat

HelloGL* HelloGL::instance = nullptr; //because it's a static variable
HelloGL::HelloGL(int argc, char* argv[])
{
	instance = this; //sets the instance for any free functions
	displayText = "Right Click To Access Menu!"; //Text to be displayed on the screen
	rotation = 0.0f;
	GLUTCallbacks::Init(instance);
	InitGL(argc, argv); //initialises the OpenGL settings
	InitObjects();
	InitLighting();
	InitFonts();
	InitMenu();
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
	auto cubeTexTGA = new TGALoader(); //TGA loader
	auto pyramidTexTGA = new TGALoader();
	auto texture = new Texture2D(); //For any 2D textures or RAW images
	texture->Load("penguins.raw", 512, 512);
	cubeTexTGA->Load("fern.tga"); //Loads the texture from the file
	pyramidTexTGA->Load("earth.tga");

	//Only need to seed the numbers once
	constexpr int seed = 1746533803; //Other good seeds: 1746533825 || 1746533853
	srand(seed); //Generates random numbers each time: srand(static_cast<unsigned int>(time(nullptr)));
	//Outputs random seed: std::cout<<"Seed: "<<static_cast<unsigned int>(time(nullptr))<<'\n';
	
	for (int i = 0; i < maxObjects; ++i)
	{
		//Random x, y and z position for each object
		GLfloat randX = randFloatRange(-20.0f, 19.9f);
		GLfloat randY = randFloatRange(-10.0f, 9.9f);
		GLfloat randZ = -randFloatRange(0.0f, 99.9f);

		Vector3 randRotAxis = {
			randFloatRange(1.0f, 10.0f),
			randFloatRange(1.0f, 10.0f),
			randFloatRange(1.0f, 10.0f)
		}; //Rotation axis

		if (i < maxObjects - 50) //instantiating a child of the parent class SceneObject
			objects[i] = new Cube(cubeMesh, cubeTexTGA, randX, randY, randZ, randRotAxis);
		else
			objects[i] = new Pyramid(triangleMesh, pyramidTexTGA, randX, randY, randZ, randRotAxis);
	}

	rotation = 0.0f; //default rotation
	camera = new Camera(); //Deleted in the destructor
	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;
	//ReSharper disable once GrammarMistakeInComment
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
	_lightPos = new Vector4{0, 0, 1, 0}; //Light position

	_lightData = new Lighting();
	_lightData->ambient.x = 0.2f; //red
	_lightData->ambient.y = 0.2f; //green
	_lightData->ambient.z = 0.2f; //blue
	_lightData->ambient.w = 1.0f; //alpha value
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

	if (showObjects)
	{
		for (int i = 0; i < maxObjects; ++i)
		{
			objects[i]->Draw();
		}
	}

	Color c = {1.0f, 1.0f, 1.0f}; //White
	DrawString(displayText, &textLoc, &c);
    glFlush();
    glutSwapBuffers();
}

//Generates a random float in the range [min, max]
GLfloat HelloGL::randFloatRange(float min, float max)
{
	return (GLfloat(rand()) / RAND_MAX) * (max - min) + min;
}

void HelloGL::Update()
{
	if (showObjects)
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
	else
	{
		glutPostRedisplay(); //keeps the text updating if no objects are shown
	}
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (initiatedTyping)
	{
		if (key == '\b')
		{
			if (displayText.length() > 0) //if there is any text to erase
				displayText.erase(displayText.size() - 1); //removes the last character if backspace is pressed
		}
		else
		{
			displayText += static_cast<char>(key); //Add the key pressed to the display text
		}
	}
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
		std::cerr << "An error occurred during FreeType library initialization: " << error << '\n';
		exit(1);
	}
	std::string fontPath = "C:/Windows/Fonts/" + fontType + ".ttf"; //sets the font path to the font type
	error = FT_New_Face(fontLib, fontPath.c_str(), 0, &fontFace); //c_str passes the string in as a constant
	if (error)
	{
		std::cerr << "An error occurred during FreeType face initialization: " << error << '\n';
		exit(1);
	}
	else if (error)
	{
		std::cerr << "An error occurred, the font file could be opened or read, or it is broken... " << error << '\n';
		exit(1);
	}
	FT_Set_Pixel_Sizes(fontFace, 0, 40);//Sets the font size to 40px
	return true;
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
	GLfloat startX = pos->x;
	GLfloat startY = pos->y;

	for (char c : text)
	{
		if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
		{
			std::cerr << "Could not load character" << '\n';
			continue;
		}

		FT_GlyphSlot glyph = fontFace->glyph;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		Texture2D fontTex;
		fontTex.LoadFreeType(glyph->bitmap);//Create the texture for this character using the Texture2D class
		
		//Set the position for this character
		GLfloat x = startX + GLfloat(glyph->bitmap_left);
		GLfloat y = startY - GLfloat((glyph->bitmap.rows - glyph->bitmap_top)); //Align to the baseline 
		//Get the character width and height
		GLfloat texWidth = GLfloat(glyph->bitmap.width);
		GLfloat texHeight = GLfloat(glyph->bitmap.rows);

		//Draw the character as a textured quad
		glBindTexture(GL_TEXTURE_2D, fontTex.GetID());
		glBegin(GL_QUADS);//Have to render BL to TR because FreeType's origin is BL

		glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);//Bottom-left
		glTexCoord2f(1.0f, 1.0f); glVertex2f(x + texWidth, y);//Bottom-right
		glTexCoord2f(1.0f, 0.0f); glVertex2f(x + texWidth, y + texHeight);//Top-right
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + texHeight);//Top-left

		glEnd();

		// Advance the position for the next character
		startX += GLfloat(glyph->advance.x >> 6); //Advance in pixels (note: FT_Advance is in 1/64th of a pixel)
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

void HelloGL::InitMenu()
{
	int subMenu = glutCreateMenu(MenuCallback);
	glutAddMenuEntry("Jokerman", 4); //Add an entry to the submenu
	glutAddMenuEntry("Colonna MT Regular", 5); //Add an entry to the submenu
	glutAddMenuEntry("Bauhaus 93 Regular", 6); //Add an entry to the submenu

	glutCreateMenu(MenuCallback); //Main menu
	//Add menu options:
	glutAddMenuEntry("Show Objects", 1);
	glutAddMenuEntry("Hide Objects", 2);
	glutAddMenuEntry("Move on X Axis", 7);
	glutAddMenuEntry("Move on Y Axis", 8);
	glutAddMenuEntry("Move on Z Axis", 9);
	glutAddMenuEntry("Stop All", 10);
	glutAddMenuEntry("Toggle Friction", 11);
	glutAddMenuEntry("Toggle Typing Mode", 3);

	glutAddSubMenu("Font", subMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON); //Attaches the menu to right mouse button
}

void HelloGL::MenuCallback(int option)
{
	if (instance)
		instance->Menu(option); //Calls the non-static function
}

void HelloGL::Menu(int option)
{
	menuOption = option; //Ensures that you stay in typing mode when changing the font
	static Vector3 velocity = {0.0f, 0.0f, 0.0f}; //static ensures that the velocity is not reset each time
	static bool toggleFriction = false;
	switch (option)
	{
	case 1:
		std::cout << "Showing Objects!" << '\n';
		showObjects = true;
		break;
	case 2:
		std::cout << "Hiding Objects!" << '\n';
		showObjects = false;
		break;
	case 3:
		std::cout << "Typing Mode!" << '\n';
		displayText = "";
		initiatedTyping = !initiatedTyping;
		break;
	case 4:
		std::cout << "Selected Jokerman Font!" << '\n';
		fontType = "jokerman";
		textLoc.x = 120.0f;
		InitFonts();
		break;
	case 5:
		std::cout << "Selected Colonna MT Regular Font!" << '\n';
		fontType = "COLONNA";
		textLoc.x = 160.0f;
		InitFonts();
		break;
	case 6:
		std::cout << "Selected Bauhaus 93 Regular Font!" << '\n';
		fontType = "BAUHS93";
		textLoc.x = 150.0f;
		InitFonts();
		break;
	case 7:
		std::cout << "Pushing along the X Axis!" << '\n';
		velocity.x = 0.1f;
		UpdateVelocity(velocity, toggleFriction);
		break;
	case 8:
		std::cout << "Pushing along the Y Axis!" << '\n';
		velocity.y = 0.1f;
		UpdateVelocity(velocity, toggleFriction);
		break;
	case 9:
		std::cout << "Pushing along the Z Axis!" << '\n';
		velocity.z = -0.1f;
		UpdateVelocity(velocity, toggleFriction);
		break;
	case 10:
		std::cout << "Stopped All" << '\n';
		velocity = Vector3{0, 0, 0};
		UpdateVelocity(velocity, toggleFriction);
		break;
	case 11:
		std::cout << "Friction is now " << (!toggleFriction == 1 ? "on!" : "off!") << '\n';
		toggleFriction = !toggleFriction;
		UpdateVelocity(velocity, toggleFriction);
		velocity = Vector3{0, 0, 0}; //Resets the velocity so toggling doesn't use the old velocity
		break;
	default:
		std::cout << "ERROR Unsupported Option!" << '\n';
		break;
	}
}

void HelloGL::UpdateVelocity(const Vector3& velocity, const bool& toggleFriction)
{
	for (int i = 0; i < maxObjects; ++i)
	{
		objects[i]->SetVelocity(velocity, toggleFriction ? objects[i]->GetFrictionCoefficient() : 1.0f);
		//sets the velocity and the friction coefficient for each object
	}
}
