#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "matrix34.h"
#include "DOF.h"
#include "token.h"
#include "Joint.h"
#include "skeleton.h"
#include <vector>


class Vertex
{
private:



public:
	Vector3 localPosition;
	Vector3 localNormal;
	Vector3 worldPosition;
	Vector3 worldNormal;
	float textureU;
	float textureV;
	int totalBindings;
	std::vector<int> bindingIndex;
	std::vector<float> bindingWeight;
	Vertex();
	~Vertex();
	void update(std::vector<Matrix34> bindingMatrixs, std::vector<Joint*> joints);

};

#endif
