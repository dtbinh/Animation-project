#include "Skeleton.h"


Skeleton::Skeleton()
{
}


Skeleton::~Skeleton()
{
}

void Skeleton::draw()
{
	root->draw();
}

void Skeleton::update(GLUI* glui)
{
	Matrix34 i;
	i.Identity();
	root->update(i, glui);
}

bool Skeleton::load(const char *file)
{
	Tokenizer token;
	token.Open(file);
	token.FindToken("balljoint");

	// Parse tree
	root = new Joint();

	char temp[256];
	token.GetToken(temp);
	root->name = temp;

	joints.push_back(root);
	root->load(token, joints);

	// Finish
	token.Close();
	return true;
}

void Skeleton::setPose(Pose p)
{
	Vector3 rootOff(p.poseValue[0], p.poseValue[1], p.poseValue[2]);
	root->offset = rootOff;
	for (unsigned int i = 0; i < joints.size(); i++)
	{
		joints[i]->dof[0].setValue(p.poseValue[i * 3 + 3]);
		joints[i]->dof[1].setValue(p.poseValue[i * 3 + 4]);
		joints[i]->dof[2].setValue(p.poseValue[i * 3 + 5]);
	}
}
