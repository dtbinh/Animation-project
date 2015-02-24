#ifndef MORPH_H
#define MORPH_H

#include "vector3.h"
#include "matrix34.h"
#include "DOF.h"
#include "token.h"
#include "Joint.h"
#include "skeleton.h"
#include <vector>
#include "vertex.h"


class Morph
{
private:



public:
	int total;
	Morph();
	~Morph();
	bool load(const char*filename, std::vector<Vertex*> &ver);
};

#endif
