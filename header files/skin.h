#ifndef SKIN_H
#define SKIN_H

#include "vector3.h"
#include "matrix34.h"
#include "DOF.h"
#include "token.h"
#include "Joint.h"
#include "skeleton.h"
#include "vertex.h"
#include "triangle.h"
#include <vector>
#include "BMPImage.h"

class Skin
{
private:


public:
	GLuint texture[1];
	int totalVertex;
	int totalTriangle;
	int totalBindings;
	std::vector<Vertex*> ver;
	std::vector<Triangle*> tri;
	std::vector<Matrix34> bindingMat;

	Skin();
	~Skin();
	bool load(const char*filename);
	void draw();
	void update(std::vector<Joint*> joints);
	void LoadGLTextures();
	bool reset(const char*filename);
};

#endif
