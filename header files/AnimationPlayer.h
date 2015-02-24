#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include "Animation.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class AnimationPlayer
{
private:

public:
	AnimationPlayer();
	~AnimationPlayer();
	float time;
	Animation *animation;
	Pose p;
	void setClip(Animation &clip);
	const Pose &getPose();
	void update();
};

#endif