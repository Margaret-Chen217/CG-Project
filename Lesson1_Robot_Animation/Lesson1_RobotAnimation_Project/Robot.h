#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>       
#endif

#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include "glaux.h"
#include <math.h>
#define MAX_CHAR 128
#define MAP 40 
#define PI  3.141591653

const  GLfloat posz = 3.5;
GLint sky = 1;
const static GLfloat white_color[] = { 1.0f, 1.0f, 1.0f, 0.3333f };

void setMaterial_glass(const GLfloat mat_diffuse[4], GLfloat mat_shininess);
void setLight(void);

void DrawRobot1(int angle)
{
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

void DrawRobot2(int angle, UINT texture[]) {
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

	//GLfloat mat_shininess[] = { 76.800003 }; //??????RGBA????????????????????????0???128?????????

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidCube(1.0);

	glPopMatrix();

	//DrawBody
	//glPushMatrix();

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	////glColor3f(0.98039f, 0.50196f, 0.44706f);//Salmon
	//glTranslatef(0.0f, 0.5f, posz);
	//glScalef(3.0f, 4.0f, 2.0f);
	//glutSolidCube(1.0);

	//glDisable(GL_TEXTURE_2D);

	//glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	// ??????
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, -1.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, 2.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 2.5f, 4.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, -1.5f, 4.5f);
	// ??????
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 2.5f, 2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 2.5f, 4.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 4.5f);
	// ??????
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, 2.5f, 2.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, 2.5f, 4.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, 2.5f, 4.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 2.5f, 2.5f);
	// ??????
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, -1.5f, 2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, -1.5f, 4.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 4.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 2.5f);
	// ??????
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 4.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 2.5f, 4.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, 2.5f, 4.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, -1.5f, 4.5f);
	// ??????
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, 2.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 2.5f, 2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, -1.5f, 2.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
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

void DrawGlassWall()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setLight();
	glDepthMask(GL_FALSE);
	setMaterial_glass(white_color, 100.0);
	glPushMatrix();
	glTranslatef(-10, 0, 0);
	glScalef(1.0, 10.0, 10.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glDepthMask(GL_TRUE);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

AUX_RGBImageRec* DIBImageLoad(char* Filename)
{
	AUX_RGBImageRec* pAuxRGB = new AUX_RGBImageRec; // AUX_RGBImageRec???GLAUX?????????????????????opengl??????????????????????????????
	pAuxRGB->sizeX = 0;  // ???????????????
	pAuxRGB->sizeY = 0;  // ???????????????
	pAuxRGB->data = NULL; // ?????????RGB??????

	FILE* img = NULL;
	img = fopen(Filename, "rb");

	DWORD size = 0;

	fseek(img, 18, SEEK_SET);  // ??????????????????18?????????????????????????????????????????????????????????????????????????????????????????? 
	fread(&(pAuxRGB->sizeX), 4, 1, img); // ???????????????4?????????
	fread(&(pAuxRGB->sizeY), 4, 1, img); // ???????????????4?????????
	fseek(img, 0, SEEK_END);
	size = ftell(img) - 54;  // ??????RGB???????????????

	pAuxRGB->data = (unsigned char*)malloc(size);

	fseek(img, 54, SEEK_SET);    // ??????????????????54??????????????????RGB?????????????????????
	fread(pAuxRGB->data, size, 1, img);

	fclose(img);

	return pAuxRGB;
}

bool LoadT8(char* filename, GLuint& texture)
{
	AUX_RGBImageRec* pImage[1];
	pImage[0] = DIBImageLoad(filename);//????????????
	if (pImage == NULL)
		return false;
	glGenTextures(1, &texture);	//????????????
	glBindTexture(GL_TEXTURE_2D, texture);//????????????

	glTexImage2D(GL_TEXTURE_2D, 0, 4, pImage[0]->sizeX, pImage[0]->sizeY,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pImage[0]->data); // ????????????????????????????????????????????????????????????RGB????????????????????????

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ??????2D????????????????????????????????????GL_TEXTURE_MIN_FILTER??????????????????????????????
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ??????2D????????????????????????????????????GL_TEXTURE_MAG_FILTER??????????????????????????????

	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
	//pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	//????????????????????????RGB???BGR???????????????????????????
	free(pImage[0]->data);//?????????????????????????????????
	free(pImage[0]);
	return true;
}

void setMaterial_glass(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
{
	static const GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat mat_emission1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void setLight(void)
{
	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void drawString(const  char* str) {
	static  int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ??????????????????????????????????????????
						// ????????????ASCII??????????????????????????????
		isFirstCall = 0;

		// ??????MAX_CHAR??????????????????????????????
		lists = glGenLists(MAX_CHAR);

		// ???????????????????????????????????????????????????????????????
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ????????????????????????????????????????????????????????????
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

GLvoid DrawSky(float scale, UINT* g_cactus)
{
	glPushMatrix();
	glTranslatef(0.0, scale - 50, 0.0);
	glScalef(scale, scale, scale);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);// ???
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);// ???
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ???
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ???
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);// ???
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -0.8f, -1.0f);// ???
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -0.8f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -0.8f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.8f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}
