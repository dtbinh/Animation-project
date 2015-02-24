#include "Channel.h"
#include <iostream>
#include <math.h>
using namespace std;
Channel::Channel()
{
}

Channel::~Channel()
{
}

float Channel::evaluate(float time)
{
	if (keyframes.size() == 1)
	{
		return keyframes[0]->value;
	}
	else if (keyframes.size() > 1)
	{
		if (time < beginTime)
		{
			if (extrapIn.compare("constant") == 0)
			{
				return keyframes[0]->value;
			}
			else if (extrapIn.compare("linear") == 0)
			{
				float v, t1, p1;
				v = keyframes[0]->tanOut;
				if (v == 0)
					return keyframes[0]->value;
				else{
					t1 = keyframes[0]->time;
					p1 = keyframes[0]->value;
					return (p1 - (t1 - time) / v);
				}
			}
			else if (extrapIn.compare("cycle") == 0)
			{
				float range = lastTime - beginTime;
				if (range <= 0)
					return keyframes[0]->value;

				float t;
				t = fmodf(time - beginTime, range);
				t += range;
				t += beginTime;
				for (unsigned int i = 0; i < keyframes.size(); i++)
				{
					if (t == keyframes[i]->time)
						return keyframes[i]->value;
				}

				for (unsigned int i = 0; i < keyframes.size() - 1; i++)
				{
					float t0, t1;
					t0 = keyframes[i]->time;
					t1 = keyframes[i + 1]->time;
					if (t > t0 && t < t1)
					{
						float u, a, b, c, d;
						u = (t - t0) / (t1 - t0);
						a = keyframes[i]->a;
						b = keyframes[i]->b;
						c = keyframes[i]->c;
						d = keyframes[i]->d;
						return (d + u*(c + u*(b + u*(a))));
					}
				}			cout << "t:" << t << endl;
				cout << "beginTime:" << beginTime << endl;
				cout << "lastTime:" << lastTime << endl;
			}
			else if (extrapIn.compare("cycle_offset") == 0)
			{
				float range = lastTime - beginTime;
				if (range <= 0)
					return keyframes[0]->value;

				float t;
				t = fmodf(time - beginTime, range);
				t += beginTime;
				t += range;
				float numT;
				numT = (time - t - beginTime) / range;
				float off;
				off = numT * (lastValue - beginValue);

				for (unsigned int i = 0; i < keyframes.size(); i++)
				{
					if (t == keyframes[i]->time)
						return keyframes[i]->value + off;
				}

				for (unsigned int i = 0; i < keyframes.size() - 1; i++)
				{
					float t0, t1;
					t0 = keyframes[i]->time;
					t1 = keyframes[i + 1]->time;
					if (t > t0 && t < t1)
					{
						float u, a, b, c, d;
						u = (t - t0) / (t1 - t0);
						a = keyframes[i]->a;
						b = keyframes[i]->b;
						c = keyframes[i]->c;
						d = keyframes[i]->d;
						return ((d + u*(c + u*(b + u*(a)))) + off);
					}
				}
			}
			else if (extrapIn.compare("bounce") == 0){
				return 0;
			}



		}
		else if (time > lastTime)
		{
			if (extrapOut.compare("constant") == 0)
			{
				return keyframes[keyframes.size() - 1]->value;
			}
			else if (extrapOut.compare("linear") == 0)
			{
				float v, t0, p0;
				v = keyframes[keyframes.size() - 1]->tanIn;
				if (v == 0)
					return keyframes[keyframes.size() - 1]->value;
				else{
					t0 = keyframes[keyframes.size() - 1]->time;
					p0 = keyframes[keyframes.size() - 1]->value;
					return ((time - t0) / v + p0);
				}
			}
			else if (extrapOut.compare("cycle") == 0)
			{
				float range = lastTime - beginTime;
				if (range <= 0)
					return keyframes[keyframes.size() - 1]->value;

				float t;
				t = fmodf(time - beginTime, range);
				t += beginTime;
				for (unsigned int i = 0; i < keyframes.size(); i++)
				{
					if (t == keyframes[i]->time)
						return keyframes[i]->value;
				}

				for (unsigned int i = 0; i < keyframes.size() - 1; i++)
				{
					float t0, t1;
					t0 = keyframes[i]->time;
					t1 = keyframes[i + 1]->time;
					if (t > t0 && t < t1)
					{
						float u, a, b, c, d;
						u = (t - t0) / (t1 - t0);
						a = keyframes[i]->a;
						b = keyframes[i]->b;
						c = keyframes[i]->c;
						d = keyframes[i]->d;
						return (d + u*(c + u*(b + u*(a))));
					}
				}

			}
			else if (extrapOut.compare("cycle_offset") == 0)
			{
				float range = lastTime - beginTime;
				if (range <= 0)
					return keyframes[keyframes.size() - 1]->value;

				float t;
				t = fmodf(time - beginTime, range);
				t += beginTime;
				float numT;
				numT = (time - t - beginTime) / range;
				float off;
				off = numT * (lastValue - beginValue);

				for (unsigned int i = 0; i < keyframes.size(); i++)
				{
					if (t == keyframes[i]->time)
						return keyframes[i]->value + off;
				}

				for (unsigned int i = 0; i < keyframes.size() - 1; i++)
				{
					float t0, t1;
					t0 = keyframes[i]->time;
					t1 = keyframes[i + 1]->time;
					if (t > t0 && t < t1)
					{
						float u, a, b, c, d;
						u = (t - t0) / (t1 - t0);
						a = keyframes[i]->a;
						b = keyframes[i]->b;
						c = keyframes[i]->c;
						d = keyframes[i]->d;
						return ((d + u*(c + u*(b + u*(a)))) + off);
					}
				}

			}
			else if (extrapOut.compare("bounce") == 0){
				return 0;
			}

		}
		else
		{
			for (unsigned int i = 0; i < keyframes.size(); i++)
			{
				if (time == keyframes[i]->time)
					return keyframes[i]->value;
			}

			for (unsigned int i = 0; i < keyframes.size() - 1; i++)
			{
				float t0, t1;
				t0 = keyframes[i]->time;
				t1 = keyframes[i + 1]->time;
				if (time > t0 && time < t1)
				{
					float u,a,b,c,d;
					u = (time - t0) / (t1 - t0);
					a = keyframes[i]->a;
					b = keyframes[i]->b;
					c = keyframes[i]->c;
					d = keyframes[i]->d;
					return (d + u*(c + u*(b + u*(a))));
				}
			}

		}

	}
	return 0;
}

void Channel::precompute()
{
	if (keyframes.size() == 1)
	{
		beginTime = keyframes[0]->time;
		beginValue = keyframes[0]->value;
		lastTime = keyframes[0]->time;
		lastValue = keyframes[0]->value;
		keyframes[0]->tanIn = 0;
		keyframes[0]->tanOut = 0;
		keyframes[0]->a = 0;
		keyframes[0]->b = 0;
		keyframes[0]->c = 0;
		keyframes[0]->d = 0;
	}
	else if (keyframes.size() > 1)
	{
		beginTime = keyframes[0]->time;
		beginValue = keyframes[0]->value;
		lastTime = keyframes[keyframes.size() - 1]->time;
		lastValue = keyframes[keyframes.size() - 1]->value;

		float t0, t1, v0, v1 ,p0, p1;
		for (unsigned int i = 0; i < keyframes.size(); i++)
		{
			if (keyframes[i]->ruleIn.compare("flat") == 0)
			{
				keyframes[i]->tanIn = 0;
			}
			else if (keyframes[i]->ruleIn.compare("linear") == 0)
			{
				if (i == 0)
				{
					keyframes[i]->tanIn = 0;
				}
				else
				{
					t0 = keyframes[i - 1]->time;
					t1 = keyframes[i]->time;
					v0 = keyframes[i - 1]->value;
					v1 = keyframes[i]->value;
					keyframes[i]->tanIn = ((v1 - v0) / (t1 - t0));
				}
			}
			else if (keyframes[i]->ruleIn.compare("smooth") == 0)
			{
				if (i == 0)
				{
					keyframes[i]->tanIn = 0;
				}
				else if (i == keyframes.size() - 1)
				{
					t0 = keyframes[i - 1]->time;
					t1 = keyframes[i]->time;
					v0 = keyframes[i - 1]->value;
					v1 = keyframes[i]->value;
					keyframes[i]->tanIn = ((v1 - v0) / (t1 - t0));
				}
				else
				{
					t0 = keyframes[i - 1]->time;
					t1 = keyframes[i + 1]->time;
					v0 = keyframes[i - 1]->value;
					v1 = keyframes[i + 1]->value;
					keyframes[i]->tanIn = ((v1 - v0) / (t1 - t0));
				}
			}
			else if (keyframes[i]->ruleIn.compare("fixed") == 0)
			{
			}



			if (keyframes[i]->ruleOut.compare("flat") == 0)
			{
				keyframes[i]->tanOut = 0;
			}
			else if (keyframes[i]->ruleOut.compare("linear") == 0)
			{
				if (i == keyframes.size() - 1)
				{
					keyframes[i]->tanOut = 0;
				}
				else
				{
					t0 = keyframes[i]->time;
					t1 = keyframes[i + 1]->time;
					v0 = keyframes[i]->value;
					v1 = keyframes[i + 1]->value;
					keyframes[i]->tanOut = ((v1 - v0) / (t1 - t0));
				}
			}
			else if (keyframes[i]->ruleOut.compare("smooth") == 0)
			{
				if (i == keyframes.size() - 1)
				{
					keyframes[i]->tanOut = 0;
				}
				else if (i == 0)
				{
					t0 = keyframes[i]->time;
					t1 = keyframes[i + 1]->time;
					v0 = keyframes[i]->value;
					v1 = keyframes[i + 1]->value;
					keyframes[i]->tanOut = ((v1 - v0) / (t1 - t0));
				}
				else
				{
					t0 = keyframes[i - 1]->time;
					t1 = keyframes[i + 1]->time;
					v0 = keyframes[i - 1]->value;
					v1 = keyframes[i + 1]->value;
					keyframes[i]->tanOut = ((v1 - v0) / (t1 - t0));
				}
			}
			else if (keyframes[i]->ruleOut.compare("fixed") == 0)
			{
			}
		}

		for (unsigned int i = 0; i < keyframes.size() - 1; i++)
		{
			p0 = keyframes[i]->value;
			p1 = keyframes[i + 1]->value;
			t0 = keyframes[i]->time;
			t1 = keyframes[i + 1]->time;
			v0 = keyframes[i]->tanOut;
			v1 = keyframes[i + 1]->tanIn;
			keyframes[i]->a = 2 * p0 - 2 * p1 + (t1 - t0) * v0 + (t1 - t0) * v1;
			keyframes[i]->b = (-3) * p0 + 3 * p1 - 2 * (t1 - t0) * v0 - (t1 - t0) * v1;
			keyframes[i]->c = (t1 - t0) * v0;
			keyframes[i]->d = p0;
		}
	}
	else
	{
		return;
	}


}