#include "vertex.h"
#include <iostream>

using namespace std;
Vertex::Vertex()
{
}


Vertex::~Vertex()
{
}

void Vertex::update(std::vector<Matrix34> bindingMatrixs, std::vector<Joint*> joints)
{
	worldPosition.Set(0, 0, 0);
	worldNormal.Set(0, 0, 0);

	for (int i = 0; i < totalBindings; i++)
	{
		//cout << "shuaige" << endl;
		Vector3 tempP;
		Matrix34 world, bind;
		world = joints[bindingIndex[i]]->getWorld();
		bind = bindingMatrixs[bindingIndex[i]];
		world.Dot(world, bind);

		world.Transform(localPosition, tempP);
		tempP = tempP * bindingWeight[i];
		worldPosition = worldPosition + tempP;
	}

	for (int i = 0; i < totalBindings; i++)
	{
		//cout << "shuaige" << endl;
		Vector3 tempN;
		Matrix34 world, bind;
		world = joints[bindingIndex[i]]->getWorld();
		bind = bindingMatrixs[bindingIndex[i]];
		world.Dot(world, bind);

		world.Transform3x3(localNormal, tempN);
		tempN = tempN * bindingWeight[i];
		worldNormal = worldNormal + tempN;
	}

	worldNormal.Normalize();
}