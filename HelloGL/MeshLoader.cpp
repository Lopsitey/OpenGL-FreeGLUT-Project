#include "MeshLoader.h"
#include <fstream>//included in the cpp and not the header since other classes accessing the header don't need it
#include <iostream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColors(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadCoords(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)//file and mesh references
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColors(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.ColorCount;
		if (mesh.ColorCount > 0)
		{
			mesh.Colors = new Color[mesh.ColorCount];
			for (int i = 0; i < mesh.ColorCount; ++i)
			{
				inFile >> mesh.Colors[i].r;
				inFile >> mesh.Colors[i].g;
				inFile >> mesh.Colors[i].b;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;
		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; ++i)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	void LoadCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TextCoordinateCount;
		if (mesh.TextCoordinateCount > 0)
		{
			mesh.TexCoords = new TextCoordinate[mesh.TextCoordinateCount];
			for (int i = 0; i < mesh.TextCoordinateCount; ++i)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	Mesh* MeshLoader::Load(const char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;
		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadColors(inFile, *mesh);
		if (path != "pyramid.txt")//this file has no textures at the moment
			LoadCoords(inFile, *mesh);//Swapping these lets the pyramids load in because they're untextured at the moment
		LoadIndices(inFile, *mesh);//The coords then aren't loaded into the cube so it gets no texture and is rendered empty
		

		cout << path << " LOADED" << endl;

		inFile.close();

		return mesh;
	}
}