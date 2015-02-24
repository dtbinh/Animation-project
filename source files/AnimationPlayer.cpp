#include "AnimationPlayer.h"
#include <iostream>
#include <math.h>
using namespace std;

AnimationPlayer::AnimationPlayer()
{
	time = 0;
}

AnimationPlayer::~AnimationPlayer()
{}

void AnimationPlayer::setClip(Animation &clip){
	animation = &clip;
}

const Pose& AnimationPlayer::getPose(){
	return p;
}

void AnimationPlayer::update(){
	animation->evaluate(time, p);
	time += 0.01;
	if (time > animation->range[1]){
		time = animation->range[0];
	}
}