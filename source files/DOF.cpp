#include "DOF.h"
#include <iostream>    

DOF::DOF()
{
	value = 0;
	min = -3.14;
	max = 3.14;
}

void DOF::setValue(float v)
{
	if (v > max)
		value = max;
	else if (v < min)
		value = min;
	else
		value = v;
}

float DOF::getValue()
{
	return value;
}

void DOF::setMinMax(float m, float n)
{
	min = m;
	max = n;
	//cout << "min" << m << endl;
	//cout << "max" << n << endl;
}

DOF::~DOF()
{}