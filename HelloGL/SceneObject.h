#pragma once
#include "Structures.h"
#include "Texture2D.h";
#include "TGALoader.h";

class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
	
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject(void);

	virtual void Update();//only needs to be declared virtual in the base class
	virtual void Draw();//any derived class can then override it, even children of children
};

