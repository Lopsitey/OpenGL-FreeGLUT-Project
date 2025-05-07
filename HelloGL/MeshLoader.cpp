#include "MeshLoader.h"
#include <fstream>//included in the cpp and not the header since other classes accessing the header don't need it
#include <iostream>
#include <sstream>

using namespace std;

namespace MeshLoader
{
    void LoadSubMesh(ifstream& inFile, SubMesh& sub)
    {
        string currentLine; //holds the current line in the file
        while (getline(inFile, currentLine)) //actively reading the file
        {
            istringstream ss(currentLine); //for parsing data in the line
            string tag;
            ss >> tag; //extracts the first word in the line

            if (tag == "SECTION") //for checking for further submeshes within the main mesh
            {
                //push back to caller to handle next section
                inFile.seekg(-(currentLine.length() + 1), ios::cur); //TODO 
                break;
            }

            if (tag == "VERTICES")
            {
                int count;
                ss >> count;
                sub.Vertices.resize(count);

                for (int i = 0; i < count; ++i)
                    inFile >> sub.Vertices[i].x >> sub.Vertices[i].y >> sub.Vertices[i].z;
            }
            else if (tag == "TEXCOORDS")
            {
                int count;
                ss >> count;
                sub.TexCoords.resize(count);

                for (int i = 0; i < count; ++i)
                    inFile >> sub.TexCoords[i].u >> sub.TexCoords[i].v;
            }
            else if (tag == "NORMALS")
            {
                int count;
                ss >> count;
                sub.Normals.resize(count);

                for (int i = 0; i < count; ++i)
                    inFile >> sub.Normals[i].x >> sub.Normals[i].y >> sub.Normals[i].z;
            }
            else if (tag == "INDICES")
            {
                int count;
                ss >> count;
                sub.Indices.resize(count * 3);

                for (int i = 0; i < count * 3; i += 3)
                    inFile >> sub.Indices[i] >> sub.Indices[i + 1] >> sub.Indices[i + 2];
            }
        }
    }

    Mesh* Load(const char* path)
    {
        auto mesh = new Mesh(); //set to auto because type is obvious
        ifstream inFile(path);

        if (!inFile) //error checking
        {
            cerr << "Failed to open file: " << path << '\n'; //couldn't open
            delete mesh;
            return nullptr;
        }

        string line;
        while (getline(inFile, line))
        {
            if (line.rfind("SECTION", 0) == 0) //for the initial mesh
            {
                SubMesh sub;
                LoadSubMesh(inFile, sub);
                mesh->SubMeshes.push_back(sub);
            }
        }

        inFile.close();
        cout << path << " loaded successfully with " << mesh->SubMeshes.size() << " sections.\n";
        return mesh;
    }
}
