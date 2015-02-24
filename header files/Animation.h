#ifndef ANIMATION_H
#define ANIMATION_H

#include "Channel.h"
#include "Pose.h"
#include <iostream>
#include <math.h>
using namespace std;

class Animation
{
private:

public:
	Animation();
	~Animation();
	float range[2];
	int totalChannel;
	vector<Channel*> channels;
	void evaluate(float time, Pose &p);
	bool load(const char*filename);

	void precompute();
	void draw(int index);
};

#endif