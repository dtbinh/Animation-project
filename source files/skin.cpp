#include "skin.h"
#include <iostream>

using namespace std;

Skin::Skin()
{
}


Skin::~Skin()
{
}

void Skin::update(std::vector<Joint*> joints)
{
	for (int i = 0; i < totalVertex; i++)
	{
		ver[i]->update(bindingMat, joints);
	}
}

void Skin::draw()
{
	for (int i = 0; i < totalTriangle; i++)
	{
		tri[i]->draw();
	}
}

bool Skin::load(const char* file)
{
	Tokenizer token;
	token.Open(file);
	while (1) {
		char temp[256];
		token.GetToken(temp);
		if (strcmp(temp, "positions") == 0) {
			totalVertex = token.GetInt();
			token.FindToken("{");
			float px, py, pz;
			for (int i = 0; i < totalVertex; i++)
			{
				Vertex* v = new Vertex();
				px = token.GetFloat();
				py = token.GetFloat();
				pz = token.GetFloat();
				v->localPosition = Vector3(px, py, pz);
				ver.push_back(v);
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "normals") == 0){
			totalVertex = token.GetInt();
			token.FindToken("{");
			float nx, ny, nz;
			for (int i = 0; i < totalVertex; i++)
			{
				Vertex* v = new Vertex();
				nx = token.GetFloat();
				ny = token.GetFloat();
				nz = token.GetFloat();
				ver[i]->localNormal = Vector3(nx, ny, nz);
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "skinweights") == 0){
			totalVertex = token.GetInt();
			token.FindToken("{");
			int index;
			float weight;
			for (int i = 0; i < totalVertex; i++)
			{
				int tBinding;
				tBinding = token.GetInt();
				ver[i]->totalBindings = tBinding;

				for (int j = 0; j < tBinding; j++)
				{
					index = token.GetInt();
					weight = token.GetFloat();
					ver[i]->bindingIndex.push_back(index);
					ver[i]->bindingWeight.push_back(weight);
				}
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "triangles") == 0){
			totalTriangle = token.GetInt();
			token.FindToken("{");
			int tx, ty, tz;
			for (int i = 0; i < totalTriangle; i++)
			{
				Triangle* t = new Triangle();
				tx = token.GetInt();
				ty = token.GetInt();
				tz = token.GetInt();
				t->ver[0] = ver[tx];
				t->ver[1] = ver[ty];
				t->ver[2] = ver[tz];
				tri.push_back(t);
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "bindings") == 0){
			totalBindings = token.GetInt();
			token.FindToken("{");
			float x, y, z;
			for (int i = 0; i < totalBindings; i++)
			{
				token.FindToken("matrix");
				token.FindToken("{");
				x = token.GetFloat();
				y = token.GetFloat();
				z = token.GetFloat();
				Vector3 a(x, y, z);
				x = token.GetFloat();
				y = token.GetFloat();
				z = token.GetFloat();
				Vector3 b(x, y, z);
				x = token.GetFloat();
				y = token.GetFloat();
				z = token.GetFloat();
				Vector3 c(x, y, z);
				x = token.GetFloat();
				y = token.GetFloat();
				z = token.GetFloat();
				Vector3 d(x, y, z);
				Matrix34 tempMat;
				tempMat.a = a;
				tempMat.b = b;
				tempMat.c = c;
				tempMat.d = d;
				tempMat.Inverse();

				bindingMat.push_back(tempMat);
				token.FindToken("}");
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "texcoords") == 0){
			totalVertex = token.GetInt();
			token.FindToken("{");
			float tu, tv;
			for (int i = 0; i < totalVertex; i++)
			{
				tu = token.GetFloat();
				tv = token.GetFloat();
				ver[i]->textureU = tu;
				ver[i]->textureV = tv;
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "material") == 0){
			char temp1[256];
			token.GetToken(temp1);
			token.FindToken("{");
			char temp2[256];
			token.GetToken(temp2);
			char temp3[256];
			token.GetToken(temp3);
			LoadGLTextures();
			token.FindToken("}");
		}
		else
		{
			token.Close();
			return true;
		} // Unrecognized token
	}
	return true;
}

void Skin::LoadGLTextures()
{
	// Load Texture
	BMPImage image1;

	if (!image1.load("head.bmp"))
		exit(1);

	// Create Texture
	
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// note that BMP images store their data in BRG order, not RGB
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1.sizeX, image1.sizeY, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, image1.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

};

bool Skin::reset(const char*filename)
{
	Tokenizer token;
	token.Open(filename);
	while (1) {
		char temp[256];
		token.GetToken(temp);
		if (strcmp(temp, "positions") == 0) {
			totalVertex = token.GetInt();
			token.FindToken("{");
			float px, py, pz;
			for (int i = 0; i < totalVertex; i++)
			{
				px = token.GetFloat();
				py = token.GetFloat();
				pz = token.GetFloat();
				ver[i]->localPosition = Vector3(px, py, pz);

			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "normals") == 0){
			totalVertex = token.GetInt();
			token.FindToken("{");
			float nx, ny, nz;
			for (int i = 0; i < totalVertex; i++)
			{
				nx = token.GetFloat();
				ny = token.GetFloat();
				nz = token.GetFloat();
				ver[i]->localNormal = Vector3(nx, ny, nz);
			}
			token.FindToken("}");
		}
		else
		{
			token.Close();
			return true;
		}
	}
	return true;
}