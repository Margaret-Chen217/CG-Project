#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

#define testposition();    glColor3f(1.0,0.0,0.0);\
   glBegin(GL_LINES);\
   glVertex3f(0.0,0.0,-0.2);\
   glVertex3f(0.0,0.0,0.2);\
   glEnd();\
   glBegin(GL_LINES);\
   glVertex3f(-0.2,0.0,0.0);\
   glVertex3f(0.2,0.0,0.0);\
   glEnd();\
   glColor3f(1.0,1.0,1.0);

//--------------使用的控制变量----------------------
static int shoulder = 0, elbow = 0, thumb=0, littlethumb=0;//控制手臂的旋转
bool Picked=false;//控制球是否被捡起

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

//------绘制场景的display函数(包括机器人手臂和球)-----------------
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	
	//绘制一个静止的球
	if(!Picked)
	{
		glPushMatrix();
		glTranslatef(2.0f,-2.0f,0.0f);
		glutSolidSphere(0.25,20,16);
		glPopMatrix();	
	}
	
	glPushMatrix();

	//移动到上臂位置，开始绘制手臂（包括上臂、前臂和5根手指）
	glTranslatef (-1.2, 1.6, 0.0);
	glRotatef ((GLfloat)shoulder, 0.0, 0.0, 1.0);		
	glTranslatef (0.6, -0.8, 0.0);

	//绘制上臂
	glPushMatrix();
	glScalef (2.0, 1.0, 0.4);
	glutWireCube (1.0);
	glPopMatrix();

	//移动到前臂位置
	glTranslatef (1.0, 0.0, 0.0);
	glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
	glTranslatef (1.0, 0.0, 0.0);

	//绘制前臂
	glPushMatrix();
	glScalef (2.0, 1.0, 0.4);
	glutWireCube (1.0);
	glPopMatrix();

	//绘制第一根手指，每根手指包括两段
	{
		glPushMatrix();

		//移动到第1段手指的位置
		glTranslatef(0.0,0.5,0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,.0);
		glTranslatef(0.3,0.0,0.0);
		
		//绘制第1段手指
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//移动到第2段手指的位置
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//绘制第2段手指
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}

		
	//绘制第二根手指，每根手指包括两段
	{
		glPushMatrix();

		//移动到第1段手指的位置
		glTranslatef(0.0,-0.5,0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//绘制第1段手指
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//移动到第2段手指的位置
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//绘制第2段手指
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}
		
	//绘制第三根手指，每根手指包括两段
	{
		glPushMatrix();

		//移动到第1段手指的位置
		glTranslatef(0.0,0.2, 0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//绘制第1段手指
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//移动到第2段手指的位置
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//绘制第2段手指
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}
	
	//绘制第四根手指，每根手指包括两段
	{
		glPushMatrix();

		//移动到第1段手指的位置
		glTranslatef(0.0,-0.2,0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//绘制第1段手指
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//移动到第2段手指的位置
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//绘制第2段手指
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}

	//绘制第五根手指，每根手指包括两段
	{
		glPushMatrix();

		//移动到第1段手指的位置
		glTranslatef(0.0,0.4,-0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,-1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//绘制第1段手指和球
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		if(Picked){//绘制球，会随手臂运动的球
			glPushMatrix();
			glScalef(1.67,10,5);
			glutSolidSphere(0.25,20,16);
			testposition();
			glPopMatrix();
		}
		glPopMatrix();	

		//移动到第2段手指的位置
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//绘制第2段手指
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);	
		glPopMatrix();

		glPopMatrix();
	}
	
	
	glPopMatrix();

	glutSwapBuffers();
}


//事件循环处于空闲的时候调用的函数，控制动画的播放
void idle(void)
{
	//捡球前手臂的动画控制
	if(!Picked)
	{
		if(shoulder>-5)
			shoulder--;
		else if(elbow>-45)
			elbow--;
		else if(thumb>-55)
			thumb--;
		else if(littlethumb>-50)
			littlethumb--;
	}
	
	//当手臂到达特定位置时，Picked设为true，表示球可以被捡起
	if(shoulder==-5 && elbow==-45 && thumb==-55 && littlethumb==-50)
		Picked=true;

	//捡起球后手臂的动画控制
	if(Picked)
	{
		if(shoulder<0)
			shoulder++;
		else if(elbow<0)
			elbow++;
 		//else if(thumb<0)
 		//	thumb++;
 		//else if(littlethumb<0)
 		//	littlethumb++;
	}

	//控制动画的循环播放
	if(shoulder==0 && elbow==0)
	{
		Picked=false;
        thumb=0;
		littlethumb=0;
		Sleep(2000);//2秒后重复播放动画
	}

	Sleep(100);
	glutPostRedisplay();		
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (800, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("机器人手臂动画，每隔2s循环重新播放");
	init();
	glutDisplayFunc(display); //绘制场景
	glutIdleFunc(idle);       //重绘场景，控制动画的播放
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}


