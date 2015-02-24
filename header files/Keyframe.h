#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "vector3.h"
#include "matrix34.h"
#include "token.h"
#include <vector>
#include <string>
using namespace std;

class Keyframe
{
private:

public:
	Keyframe();
	~Keyframe();
	float time;
	float value;
	float tanIn, tanOut;
	float a, b, c, d;
	string ruleIn, ruleOut;
};

#endif