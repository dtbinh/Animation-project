#include "Animation.h"
#include <iostream>
#include <math.h>
using namespace std;

Animation::Animation()
{}

Animation::~Animation()
{}

void Animation::evaluate(float t, Pose &p)
{
	for (int i = 0; i < totalChannel; i++)
	{
		p.poseValue[i] = channels[i]->evaluate(t);
	}
}

void Animation::precompute()
{
	for (int i = 0; i < totalChannel; i++)
	{
		channels[i]->precompute();
	}
}

bool Animation::load(const char*file)
{
	Tokenizer token;
	token.Open(file);
	while (1) {
		char temp[256];
		token.GetToken(temp);
		if (strcmp(temp, "animation") == 0) {
			token.FindToken("{");
		}
		else if (strcmp(temp, "range") == 0) {
			range[0] = token.GetFloat();
			range[1] = token.GetFloat();
		}
		else if (strcmp(temp, "numchannels") == 0){
			totalChannel = token.GetInt();
		}
		else if (strcmp(temp, "channel") == 0){
			token.FindToken("{");
			token.FindToken("extrapolate");
			Channel *channel = new Channel();
			token.GetToken(temp);
			channel->extrapIn = temp;
			token.GetToken(temp);
			channel->extrapOut = temp;

			token.FindToken("keys");
			int totalKey;
			totalKey = token.GetInt();
			channel->totalKeyframe = totalKey;
			token.FindToken("{");
			for (int j = 0; j < totalKey; j++){
				Keyframe *keyframe = new Keyframe();
				keyframe->time = token.GetFloat();
				keyframe->value = token.GetFloat();
				token.GetToken(temp);
				keyframe->ruleIn = temp;
				token.GetToken(temp);
				keyframe->ruleOut = temp;
				channel->keyframes.push_back(keyframe);
			}
			channels.push_back(channel);

			token.FindToken("}");
			token.FindToken("}");
		}
		else
		{
			token.Close();
			return true;
		} // Unrecognized token
	}
	return true;

}

void Animation::draw(int index)
{
	glColor3f(1, 0, 1);
	glPushMatrix();
	glLoadIdentity();
	glLineWidth(2);
	glBegin(GL_LINES);

	//draw curve
	for (float j = -4; j <= 4; j += 0.01)
	{
		glVertex3f(j, channels[index]->evaluate(j), 0);
		glVertex3f((j + 0.01), channels[index]->evaluate(j + 0.01), 0);
	}
	glEnd();
	glPopMatrix();
	
	for (unsigned int i = 0; i < channels[index]->keyframes.size(); i++)
	{
		//draw keyframe point
		glColor3f(1, 0, 0);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(channels[index]->keyframes[i]->time, channels[index]->keyframes[i]->value, 0);
		glutSolidSphere(0.03, 100, 100);

		
		glLineWidth(4);
		glBegin(GL_LINES);
		//tanOut
		glColor3f(1, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0.1, channels[index]->keyframes[i]->tanOut*0.1, 0);

		//tanIn
		glColor3f(0, 1, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(-0.1, channels[index]->keyframes[i]->tanIn*(-0.1), 0);
		glEnd();

		glPopMatrix();
	}
	glColor3f(1, 1, 1);
}