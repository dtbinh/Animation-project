#include "morph.h"

Morph::Morph()
{
}


Morph::~Morph()
{
}

bool Morph::load(const char*filename, std::vector<Vertex*> &ver)
{
	Tokenizer token;
	token.Open(filename);
	while (1) {
		char temp[256];
		token.GetToken(temp);
		if (strcmp(temp, "positions") == 0) {
			total = token.GetInt();
			token.FindToken("{");
			float index, px, py, pz;
			for (int i = 0; i < total; i++)
			{
				index = token.GetInt();
				px = token.GetFloat();
				py = token.GetFloat();
				pz = token.GetFloat();
				Vector3 temp = Vector3(px, py, pz);
				ver[index]->localPosition = temp;
			}
			token.FindToken("}");
		}
		else if (strcmp(temp, "normals") == 0){
			total = token.GetInt();
			token.FindToken("{");
			float index, nx, ny, nz;
			for (int i = 0; i < total; i++)
			{
				index = token.GetInt();
				nx = token.GetFloat();
				ny = token.GetFloat();
				nz = token.GetFloat();
				Vector3 temp = Vector3(nx, ny, nz);
				ver[index]->localNormal = temp;
				ver[index]->localNormal.Normalize();
			}
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