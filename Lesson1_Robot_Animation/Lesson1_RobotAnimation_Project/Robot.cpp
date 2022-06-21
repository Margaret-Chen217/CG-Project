//Author:MargaretChen
//Date:June,21,2022
//MyGithub:https://github.com/Margaret-Chen217
/*Reference:*/
/*DrawRobot-------------- RobotDemo.cpp and https://blog.csdn.net/qq_29721419/article/details/676320648 */
/*ArmAngleShakeAnimation----- RobotDemo.cpp */
/*Color------------------ https://wenku.baidu.com/view/d1906026f41fb7360b4c2e3f5727a5e9846a277b.html */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include "Robot.h"

/*ControlRotateAngle*/
static int ArmAngle = 0;
int view_angle = 1;
float ex = 0.0, ey = 0.0, ez = 0.0;		//视点变化
float cx = 0.0, cy = 0.0, cz = 0.0;					//视线变化
float s_angle = -90.0;
float rad = 0.0;
float yo = 0.0;


void init(void)
{
	glClearColor(1.0f, 0.97255f, 0.86275f, 1.0f);  /*BackGround Color: Cornsilk*/
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}

/*DrawRobot*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float cameraLookAtY = -0.8 * cos(ArmAngle * PI / 180);
	float cameraLookAtZ = -0.8 * sin(ArmAngle * PI / 180);

	if (view_angle == 1)//视角1
	{
		//glTranslatef(0,-5,-15);
		gluLookAt(-15.0 + ex, ey,ez, cx, cy,cz, 0.0f, 1.0f, 0.0f);
	}
	if (view_angle == 2)//视角2
	{
		gluLookAt(2.0f, 2.3f, -posz+2, 0.0f, cameraLookAtY, cameraLookAtZ, 0.0f, 1.0f, 0.0f);
	}
	
	DrawGround();
	DrawRobot1(ArmAngle);
	DrawRobot2(ArmAngle);
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
		//Sleep(2000);
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
	gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 49://数字键1，选择视角1
		view_angle = 1;
		break;
	case 50://数字键2，选择视角2
		view_angle = 2;
		break;
	}
}

void KeySight(int key, int x, int y)
{
	float disEye2Center = sqrt((ex - cx) * (ex - cx) + (ey - cy) * (ey - cy) + (ez - cz) * (ez - cz));
	if (key == GLUT_KEY_LEFT)
	{
		s_angle -= 2.0;

	}
	if (key == GLUT_KEY_RIGHT)
	{
		s_angle += 2.0;

	}
	rad = float(PI * s_angle / 180.0f);
	if (key == GLUT_KEY_UP)
	{

		ey -= 0.2 * sin(rad);    
		ex -= 0.2 * cos(rad);
	}
	if (key == GLUT_KEY_DOWN)
	{
		ey += 0.2 * sin(rad);
		ex = 0.2 * cos(rad);
	}

	if (key == GLUT_KEY_PAGE_UP)
	{
		cy += 1.0f;
		ey += 1.0f;
	}
	if (key == GLUT_KEY_PAGE_DOWN)
	{
		cy -= 1.0f;
		ey -= 1.0f;
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
	glutDisplayFunc(display); //绘制场景
	glutIdleFunc(idle);       //重绘场景，控制动画的播放
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(KeySight);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}