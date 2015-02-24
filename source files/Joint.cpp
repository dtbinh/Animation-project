#include "Joint.h"
#include <iostream>
using namespace std;

static int counter = 0;
Joint::Joint()
{
	offset.Set(0, 0, 0);
	pose.Set(0, 0, 0);
	local.Identity();
	world.Identity();
	initial = true;
}

Joint::~Joint()
{
}

bool Joint::load(Tokenizer &t, std::vector<Joint*> &joints)
{
	while (1) {
		char temp[256];
		t.GetToken(temp);
		if (strcmp(temp, "offset") == 0) {
			offset.x = t.GetFloat();
			offset.y = t.GetFloat();
			offset.z = t.GetFloat();
		}
		else if (strcmp(temp, "boxmin") == 0){
			boxMin.x = t.GetFloat();
			boxMin.y = t.GetFloat();
			boxMin.z = t.GetFloat();
		}
		else if (strcmp(temp, "boxmax") == 0){
			boxMax.x = t.GetFloat();
			boxMax.y = t.GetFloat();
			boxMax.z = t.GetFloat();
		}
		else if (strcmp(temp, "pose") == 0){
			pose.x = t.GetFloat();
			pose.y = t.GetFloat();
			pose.z = t.GetFloat();
			dof[0].setValue(pose.x);
			dof[1].setValue(pose.y);
			dof[2].setValue(pose.z);
		}
		else if (strcmp(temp, "rotxlimit") == 0){
			float min = t.GetFloat();
			float max = t.GetFloat();
			dof[0].setMinMax(min, max);
		}
		else if (strcmp(temp, "rotylimit") == 0){
			float min = t.GetFloat();
			float max = t.GetFloat();
			dof[1].setMinMax(min, max);
		}
		else if (strcmp(temp, "rotzlimit") == 0){
			float min = t.GetFloat();
			float max = t.GetFloat();
			dof[2].setMinMax(min, max);
		}// Check for other tokens
		else if (strcmp(temp, "balljoint") == 0) {
			Joint *jnt = new Joint;
			char temp2[256];
			t.GetToken(temp2);
			jnt->name = temp2;
			joints.push_back(jnt);
			jnt->load(t, joints);
			addChild(jnt);
		}
		else if (strcmp(temp, "}") == 0) return true;
		else t.SkipLine(); // Unrecognized token
	}
}

void Joint::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(world);
	drawWireBox(boxMin.x, boxMin.y, boxMin.z, boxMax.x, boxMax.y, boxMax.z);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children.at(i)->draw();
	}
}

void Joint::update(Matrix34 &p, GLUI* glui)
{
	if (initial){

		GLUI_Rollout* r = glui->add_rollout(this->name.c_str(), true);
		//new GLUI_StaticText(glui, this->name.c_str());
		//r->close();
		(new GLUI_Spinner(r, "rotateX:", &this->dof[0].value))
			->set_float_limits(this->dof[0].min, this->dof[0].max);
		(new GLUI_Spinner(r, "rotateY:", &this->dof[1].value))
			->set_float_limits(this->dof[1].min, this->dof[1].max);
		(new GLUI_Spinner(r, "rotateZ:", &this->dof[2].value))
			->set_float_limits(this->dof[2].min, this->dof[2].max);
		initial = false;

		counter++;
		if (counter == 5)
			glui->add_column();
		counter = counter % 5;
		
	}

	Matrix34 rotX, rotY, rotZ, off;
	rotX.MakeRotateX(dof[0].getValue());
	rotY.MakeRotateY(dof[1].getValue());
	rotZ.MakeRotateZ(dof[2].getValue());
	off.MakeTranslate(offset.x, offset.y, offset.z);

	Matrix34 temp;
	temp.Dot(rotY, rotX);
	temp.Dot(rotZ, temp);
	temp.Dot(off, temp);
	local = temp;

	world.Dot(p, local);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children.at(i)->update(world, glui);
	}
}

void Joint::addChild(Joint* c)
{
	children.push_back(c);
	c->parent = this;
}

Matrix34 Joint::getWorld()
{
	return world;
}