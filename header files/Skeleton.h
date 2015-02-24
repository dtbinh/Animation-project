#ifndef SKELETON_H
#define SKELETON_H

#include "vector3.h"
#include "matrix34.h"
#include "DOF.h"
#include "token.h"
#include "Joint.h"
#include "AnimationPlayer.h"
#include <vector>

class Skeleton
{
private:
	Joint* root;

public:
	Skeleton();
	~Skeleton();
	std::vector<Joint*> joints;
	void update(GLUI* glui);
	void draw();
	bool load(const char *file);
	void setPose(Pose p);
};

#endif
