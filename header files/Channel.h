#ifndef CHANNEL_H
#define CHANNEL_H

#include "Keyframe.h"
using namespace std;

class Channel
{
private:

public:
	Channel();
	~Channel();
	int totalKeyframe;
	float beginTime, lastTime;
	float beginValue, lastValue;
	vector<Keyframe*> keyframes;
	string extrapIn, extrapOut;
	float evaluate(float time);
	void precompute();
};

#endif