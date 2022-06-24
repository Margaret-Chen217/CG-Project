//Author:MargaretChen
//Date:June,21,2022
//MyGithub:https://github.com/Margaret-Chen217
/*Reference:*/
/*DrawRobot-------------- RobotDemo.cpp and https://blog.csdn.net/qq_29721419/article/details/676320648 */
/*ShakeAnimation--------- RobotDemo.cpp */
/*Color------------------ https://wenku.baidu.com/view/d1906026f41fb7360b4c2e3f5727a5e9846a277b.html */
/*Text------------------- https://blog.csdn.net/qq_35040828/article/details/51758258 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif
#include "stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include <string>
#include "Robot.h"

#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*ControlRotateAngle*/
static int ArmAngle = 0;
int view_angle = 1;

int view = 1;
GLdouble	g_eye[3];
GLdouble	g_look[3];
float		rad_xz;
float		g_Angle;
float		g_elev;
GLfloat r = 0;

GLuint filter;						// 使用哪一个纹理过滤器
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };		// 雾气的模式
GLuint fogfilter = 0;					// 使用哪一种雾气
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };		// 雾的颜色设为白色

float ex = -15.0, ey = 0, ez = 0, cx = 0, cy = 0, cz = 0;
float s_angle = -90.0;
float rad = 0.0;

GLfloat LightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 1.0f, 1.0f, 1.0f, 1.0f };
bool light = true;
bool glass = false;
bool fog = false;

UINT g_cactus[10];
UINT texture[10];

void init(void)
{
	//glClearColor(1.0f, 0.97255f, 0.86275f, 1.0f);  /*BackGround Color: Cornsilk*/
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	/*glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);*/

	char str1[] = "textures/4LEFT.BMP";
	LoadT8(str1, g_cactus[0]);
	char str2[] = "textures/4LEFT.BMP";
	LoadT8(str2, g_cactus[1]);
	char str3[] = "textures/4LEFT.BMP";
	LoadT8(str3, g_cactus[2]);
	char str4[] = "textures/4LEFT.BMP";
	LoadT8(str4, g_cactus[3]);
	char str5[] = "textures/4LEFT.BMP";
	LoadT8(str5, g_cactus[4]);
	char str6[] = "textures/GROUND.BMP";
	LoadT8(str6, g_cactus[5]);
	char str7[] = "textures/Glass/Glass_Pink.BMP";
	LoadT8(str7, texture[0]);
	//char str6[] = "textures/GROUND.BMP";
	//LoadT8(str6, g_cactus[5]);
	//char str6[] = "textures/GROUND.BMP";
	//LoadT8(str6, g_cactus[5]);
	//char str6[] = "textures/GROUND.BMP";
	//LoadT8(str6, g_cactus[5]);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);			// 设置背景的颜色为雾气的颜色

	glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// 设置雾气的模式
	glFogfv(GL_FOG_COLOR, fogColor);			// 设置雾的颜色
	glFogf(GL_FOG_DENSITY, 0.1f);			// 设置雾的密度
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// 设置系统如何计算雾气
	glFogf(GL_FOG_START, 2.0f);				// 雾气的开始位置
	glFogf(GL_FOG_END, 5.0f);				// 雾气的结束位置


	//glEnable(GL_LIGHT1);	
}

GLvoid DrawSky(float scale)
{
	glPushMatrix();
	glTranslatef(0.0, scale - 1, 0.0);
	glScalef(scale, scale, scale);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//纹理过滤，把纹理像素映射成像素
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);// 前
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);// 左
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[2]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 右
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[3]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 后
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[4]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);// 上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 下
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}



/*DrawRobot*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float cameraLookAtY = -0.8 * cos(ArmAngle * PI / 180);
	float cameraLookAtZ = -0.8 * sin(ArmAngle * PI / 180);

	if (view_angle == 1)
	{
		//glTranslatef(0,-5,-15);
		gluLookAt(ex, ey, ez, cx, cy, cz, 0.0f, 1.0f, 0.0f);
	}
	if (view_angle == 2)
	{
		gluLookAt(2.0f, 2.3f, -posz + 2, 0.0f, cameraLookAtY, cameraLookAtZ, 0.0f, 1.0f, 0.0f);
	}
	DrawGround();

	glPushMatrix();
	glTranslatef(0.0, -6.1, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	DrawSky(200);
	glPopMatrix();
	DrawRobot1(ArmAngle);
	DrawRobot2(ArmAngle, texture);

	if (glass) {
		DrawGlassWall();
	}


	glutSwapBuffers();
}

/*ControlAnimation*/
void idle(void)
{

	if (ArmAngle > -60) {
		ArmAngle--;
	}

	if (ArmAngle == -60)
	{
		/*Replay After 2s*/
		Sleep(200);
		ArmAngle = 0;
	}
	Sleep(100);
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, (GLfloat)w / (GLfloat)h, 0.1f, 3000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void KeySight(int key, int x, int y)
{
	float disEye2Center = sqrt((ex - cx) * (ex - cx) + (ey - cy) * (ey - cy) + (ez - cz) * (ez - cz));

	if (key == GLUT_KEY_LEFT)
	{
		s_angle -= 4.0;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		s_angle += 4.0;
	}
	rad = float(PI * s_angle / 180.0f);
	if (key == GLUT_KEY_UP)
	{
		ez += 0.4 * sin(rad);
		ex += 0.4 * cos(rad);
	}

	if (key == GLUT_KEY_DOWN)
	{
		ez -= 0.4 * sin(rad);
		ex -= 0.4 * cos(rad);
	}

	if (key == GLUT_KEY_PAGE_DOWN)
	{
		cy -= 2.0;
		ey -= 2.0;
	}

	if (key == GLUT_KEY_PAGE_UP)
	{
		cy += 1.0;
		ey += 1.0;
	}

	cx = float(ex + disEye2Center * cos(rad));
	cy = ey;
	cz = float(ez + disEye2Center * sin(rad));
}

void KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		view_angle = 1;
		break;
	case '2':
		view_angle = 2;
		break;
	case 'l':   /*  s key rotates at shoulder  */
		if (!light && !glass)
		{
			glEnable(GL_LIGHTING);
			light = true;
		}
		else if(light)
		{
			glDisable(GL_LIGHTING);
			light = false;
		}
		

		break;
	case 'g':
		if (glass) {
			glass = false;
		}
		else {
			glass = true;
		}
		break;
	case 'f':
		if (fog) {
			fog = false;
			glDisable(GL_FOG);
		}		// 使用雾气
		else {
			fog = true;
			glEnable(GL_FOG);
		}
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("RoborAnimation");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(KeySight);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}