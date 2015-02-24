#include "triangle.h"

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::draw()
{

	Vector3 P1 = ver[0]->worldPosition;
	Vector3 P2 = ver[1]->worldPosition;
	Vector3 P3 = ver[2]->worldPosition;

	Vector3 N1 = ver[0]->worldNormal;
	Vector3 N2 = ver[1]->worldNormal;
	Vector3 N3 = ver[2]->worldNormal;

	float T1U = ver[0]->textureU;
	float T1V = ver[0]->textureV;
	float T2U = ver[1]->textureU;
	float T2V = ver[1]->textureV;
	float T3U = ver[2]->textureU;
	float T3V = ver[2]->textureV;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

	glNormal3f(N1.x, N1.y, N1.z);
	glTexCoord2f(T1U, T1V);
	glVertex3f(P1.x, P1.y, P1.z);

	glNormal3f(N2.x, N2.y, N2.z);
	glTexCoord2f(T2U, T2V);
	glVertex3f(P2.x, P2.y, P2.z);

	glNormal3f(N3.x, N3.y, N3.z);
	glTexCoord2f(T3U, T3V);
	glVertex3f(P3.x, P3.y, P3.z);

	glEnd();

}