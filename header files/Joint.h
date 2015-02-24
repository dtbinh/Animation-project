#ifndef JOINT_H
#define JOINT_H

#include "vector3.h"
#include "matrix34.h"
#include "DOF.h"
#include "token.h"
#include <vector>
#include "core.h"

class Joint
{

public:
	Joint();
	~Joint();
	void update(Matrix34 &p, GLUI* glui);
	void draw();
	bool load(Tokenizer &t, std::vector<Joint*> &joints);
	void addChild(Joint* c);
	Matrix34 getWorld();
	std::string name;

	Matrix34 local;
	Matrix34 world;
	DOF dof[3];
	Joint* parent;
	Vector3 offset;
	Vector3 boxMin;
	Vector3 boxMax;
	Vector3 pose;
	std::vector<Joint*> children;
	bool initial;

private:


};

#endif
