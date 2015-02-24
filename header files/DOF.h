#ifndef DOF_H
#define DOF_H

#include "vector3.h"
#include "matrix34.h"

class DOF {
public:
	DOF();
	~DOF();
	void setValue(float v);
	float getValue();
	void setMinMax(float m, float n);
	float value;
	float min, max;
private:


};

#endif