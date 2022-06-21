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

	if (view_angle == 1)//�ӽ�1
	{
		//glTranslatef(0,-5,-15);
		gluLookAt(-15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
	if (view_angle == 2)//�ӽ�2
	{
		gluLookAt(2.0f, 2.3f, -posz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
	
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
		Sleep(2000);
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

	if (view_angle == 1)//�ӽ�1
	{
		//glTranslatef(0,-5,-15);
		gluLookAt(-15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
	if (view_angle == 2)//�ӽ�2
	{
		gluLookAt(2.0f, 2.3f, -posz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
}

void KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 49://���ּ�1��ѡ���ӽ�1
		view_angle = 1;
		break;
	case 50://���ּ�2��ѡ���ӽ�2
		view_angle = 2;
		break;
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
	glutDisplayFunc(display); //���Ƴ���
	glutIdleFunc(idle);       //�ػ泡�������ƶ����Ĳ���
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}