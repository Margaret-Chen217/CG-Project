#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include "glaux.h"
#include <math.h>
#define MAP 40 //����������20*20
#define PI  3.141591653

const  GLfloat posz = 3.5;
UINT g_cactus[28];
GLint sky = 1;

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

	//GLfloat mat_ambient[] = { 0.021500, 0.174500, 0.021500, 0.550000 };

	//GLfloat mat_diffuse[] = { 0.075680, 0.614240, 0.075680, 0.550000 };

	//GLfloat mat_specular[] = { 0.633000, 0.727811, 0.633000, 0.550000 };

	//GLfloat mat_shininess[] = { 76.800003 }; //材质RGBA镜面指数，数值在0～128范围内

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

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
	glTranslatef(0, -6.0f, 0);

	int size0 = (int)(MAP * 2);
	glBegin(GL_LINES);
	for (int x = -size0; x < size0; x += 3)
	{
		glVertex3i(x, 0, -size0); glVertex3i(x, 0, size0);
	}
	for (int z = -size0; z < size0; z += 3)
	{
		glVertex3i(-size0, 0, z); glVertex3i(size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();
}



AUX_RGBImageRec* DIBImageLoad(char* Filename)
{
	AUX_RGBImageRec* pAuxRGB = new AUX_RGBImageRec;
	pAuxRGB->sizeX = 0;
	pAuxRGB->sizeY = 0;
	pAuxRGB->data = NULL;

	FILE* img = NULL;
	img = fopen(Filename, "r");

	DWORD size = 0;

	DWORD off = 0;

	fseek(img, 10, SEEK_SET);
	fread(&off, 4, 1, img);

	fseek(img, 0, SEEK_SET);

	fseek(img, 18, SEEK_SET);
	fread(&(pAuxRGB->sizeX), 4, 1, img);
	fread(&(pAuxRGB->sizeY), 4, 1, img);
	fseek(img, 0, SEEK_END);
	size = ftell(img) - off;

	pAuxRGB->data = (unsigned char*)malloc(size);

	fseek(img, off, SEEK_SET);    // image data
	fread(pAuxRGB->data, size, 1, img);

	fclose(img);

	return pAuxRGB;
}

bool LoadT8(char* filename, GLuint& texture)
{
	AUX_RGBImageRec* pImage = NULL;
	pImage = DIBImageLoad(filename);//装入贴图
	if (pImage == NULL)
		return false;
	glGenTextures(1, &texture);	//生成纹理
	glBindTexture(GL_TEXTURE_2D, texture);//捆绑纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
		pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	free(pImage->data);//释放位图占据的内存资源
	free(pImage);
	return true;
}

