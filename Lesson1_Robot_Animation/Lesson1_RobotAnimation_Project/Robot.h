#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
<<<<<<< HEAD
#include "math.h"
=======
#include <math.h>
>>>>>>> 6632e56339526b26857c1992cf82243b3efa2845
#define MAP 20 //����������20*20
#define PI  3.141591653

const  GLfloat posz = 3.5;

void DrawRobot1(int angle) {
	//DrawCap
	glPushMatrix();
	glColor3f(1.0f, 0.75294f, 0.79608f);//Pink
	glTranslatef(0.0f, 5.0f, -posz);
	glScalef(2.6f, 0.8f, 2.6f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawHead
	glPushMatrix();
	glColor3f(0.99039f, 0.92157f, 0.94314f);//AntiqueWhite
	glTranslatef(0.0f, 4.0f, -posz);
	glScalef(2.0f, 2.0f, 2.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawBody
	glPushMatrix();
	glColor3f(0.98039f, 0.50196f, 0.44706f);//Salmon
	glTranslatef(0.0f, 0.5f, -posz);
	glScalef(3.0f, 4.0f, 2.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawLeftHand
	glPushMatrix();
	glColor3f(1.0f, 0.62745f, 0.47843f);//LightSalmon
	glTranslatef(-2.0f, 0.5f, -posz);
	glScalef(0.8f, 5.0f, 0.8f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawRightHand
	glPushMatrix();
	glColor3f(1.0f, 0.62745f, 0.47843f);//LightSalmon
	//Rotate Animation
	glTranslatef(2.0f, 2.3f, -posz);
	glRotatef((GLfloat)angle, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -1.8f, 0.0f);
	glScalef(0.8f, 5.0f, 0.8f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawLeftLeg
	glPushMatrix();
	glColor3f(0.91373f, 0.58824f, 0.47843f);//DarkSalmon
	glTranslatef(-0.7f, -4.0f, -posz);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawRightLeg
	glPushMatrix();
	glColor3f(0.91373f, 0.58824f, 0.47843f);//DarkSalmon
	glTranslatef(0.7f, -4.0f, -posz);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();
}

void DrawRobot2(int angle) {
	//DrawCap
	glPushMatrix();
	glColor3f(1.0f, 0.75294f, 0.79608f);//Pink
	glTranslatef(0.0f, 5.0f, posz);
	glScalef(2.6f, 0.8f, 2.6f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawHead
	glPushMatrix();
	glColor3f(0.99039f, 0.92157f, 0.94314f);//AntiqueWhite
	glTranslatef(0.0f, 4.0f, posz);
	glScalef(2.0f, 2.0f, 2.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawBody
	glPushMatrix();
	glColor3f(0.98039f, 0.50196f, 0.44706f);//Salmon
	glTranslatef(0.0f, 0.5f, posz);
	glScalef(3.0f, 4.0f, 2.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawLeftHand
	glPushMatrix();
	glColor3f(1.0f, 0.62745f, 0.47843f);//LightSalmon
	glTranslatef(2.0f, 0.5f, posz);
	glScalef(0.8f, 5.0f, 0.8f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawRightHand
	glPushMatrix();
	glColor3f(1.0f, 0.62745f, 0.47843f);//LightSalmon
	//Rotate Animation
	glTranslatef(-2.0f, 2.3f, posz);
	angle = 0 - angle;
	glRotatef((GLfloat)angle, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -1.8f, 0.0f);
	glScalef(0.8f, 5.0f, 0.8f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawLeftLeg
	glPushMatrix();
	glColor3f(0.91373f, 0.58824f, 0.47843f);//DarkSalmon
	glTranslatef(-0.7f, -4.0f, posz);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//DrawRightLeg
	glPushMatrix();
	glColor3f(0.91373f, 0.58824f, 0.47843f);//DarkSalmon
	glTranslatef(0.7f, -4.0f, posz);
	glScalef(1.0f, 4.0f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();
}

void DrawGround()
{
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);
<<<<<<< HEAD
	glTranslatef(0, -6.0f, 0);
=======
	glTranslatef(0, -6.0f, 0.0f);
>>>>>>> 6632e56339526b26857c1992cf82243b3efa2845
	int size0 = (int)(MAP * 2);
	glBegin(GL_LINES);
	for (int x = -size0; x < size0; x += 1)
	{
		glVertex3i(x, 0, -size0); glVertex3i(x, 0, size0);
	}
	for (int z = -size0; z < size0; z += 1)
	{
		glVertex3i(-size0, 0, z); glVertex3i(size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();
}