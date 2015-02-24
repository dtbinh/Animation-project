#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3.h"
#include "matrix34.h"
#include "DOF.h"
#include "token.h"
#include "Joint.h"
#include "skeleton.h"
#include "vertex.h"

class Triangle
{
private:


public:
	Vertex* ver[3];
	Triangle();
	~Triangle();
	void draw();
};

#endif
