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

//--------------ʹ�õĿ��Ʊ���----------------------
static int shoulder = 0, elbow = 0, thumb=0, littlethumb=0;//�����ֱ۵���ת
bool Picked=false;//�������Ƿ񱻼���

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

//------���Ƴ�����display����(�����������ֱۺ���)-----------------
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	
	//����һ����ֹ����
	if(!Picked)
	{
		glPushMatrix();
		glTranslatef(2.0f,-2.0f,0.0f);
		glutSolidSphere(0.25,20,16);
		glPopMatrix();	
	}
	
	glPushMatrix();

	//�ƶ����ϱ�λ�ã���ʼ�����ֱۣ������ϱۡ�ǰ�ۺ�5����ָ��
	glTranslatef (-1.2, 1.6, 0.0);
	glRotatef ((GLfloat)shoulder, 0.0, 0.0, 1.0);		
	glTranslatef (0.6, -0.8, 0.0);

	//�����ϱ�
	glPushMatrix();
	glScalef (2.0, 1.0, 0.4);
	glutWireCube (1.0);
	glPopMatrix();

	//�ƶ���ǰ��λ��
	glTranslatef (1.0, 0.0, 0.0);
	glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
	glTranslatef (1.0, 0.0, 0.0);

	//����ǰ��
	glPushMatrix();
	glScalef (2.0, 1.0, 0.4);
	glutWireCube (1.0);
	glPopMatrix();

	//���Ƶ�һ����ָ��ÿ����ָ��������
	{
		glPushMatrix();

		//�ƶ�����1����ָ��λ��
		glTranslatef(0.0,0.5,0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,.0);
		glTranslatef(0.3,0.0,0.0);
		
		//���Ƶ�1����ָ
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//�ƶ�����2����ָ��λ��
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//���Ƶ�2����ָ
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}

		
	//���Ƶڶ�����ָ��ÿ����ָ��������
	{
		glPushMatrix();

		//�ƶ�����1����ָ��λ��
		glTranslatef(0.0,-0.5,0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//���Ƶ�1����ָ
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//�ƶ�����2����ָ��λ��
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//���Ƶ�2����ָ
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}
		
	//���Ƶ�������ָ��ÿ����ָ��������
	{
		glPushMatrix();

		//�ƶ�����1����ָ��λ��
		glTranslatef(0.0,0.2, 0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//���Ƶ�1����ָ
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//�ƶ�����2����ָ��λ��
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//���Ƶ�2����ָ
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}
	
	//���Ƶ��ĸ���ָ��ÿ����ָ��������
	{
		glPushMatrix();

		//�ƶ�����1����ָ��λ��
		glTranslatef(0.0,-0.2,0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//���Ƶ�1����ָ
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		//�ƶ�����2����ָ��λ��
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//���Ƶ�2����ָ
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);
		glPopMatrix();

		glPopMatrix();
	}

	//���Ƶ������ָ��ÿ����ָ��������
	{
		glPushMatrix();

		//�ƶ�����1����ָ��λ��
		glTranslatef(0.0,0.4,-0.2);
		glTranslatef(1.0,0.0,0.0);
		glRotatef((GLfloat)thumb,-1.0,0.0,0.0);
		glTranslatef(0.3,0.0,0.0);

		//���Ƶ�1����ָ����
		glPushMatrix();
		glScalef(0.6,0.2,0.1);
		glutWireCube(1);
		if(Picked){//�����򣬻����ֱ��˶�����
			glPushMatrix();
			glScalef(1.67,10,5);
			glutSolidSphere(0.25,20,16);
			testposition();
			glPopMatrix();
		}
		glPopMatrix();	

		//�ƶ�����2����ָ��λ��
		glTranslatef(0.3,0.0,0.0);
		glRotatef((GLfloat)littlethumb,0.0,0.0,1.0);
		glTranslatef(0.2,0.0,0.0);

		//���Ƶ�2����ָ
		glPushMatrix();
		glScalef(0.4,0.2,0.1);
		glutWireCube(1);	
		glPopMatrix();

		glPopMatrix();
	}
	
	
	glPopMatrix();

	glutSwapBuffers();
}


//�¼�ѭ�����ڿ��е�ʱ����õĺ��������ƶ����Ĳ���
void idle(void)
{
	//����ǰ�ֱ۵Ķ�������
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
	
	//���ֱ۵����ض�λ��ʱ��Picked��Ϊtrue����ʾ����Ա�����
	if(shoulder==-5 && elbow==-45 && thumb==-55 && littlethumb==-50)
		Picked=true;

	//��������ֱ۵Ķ�������
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

	//���ƶ�����ѭ������
	if(shoulder==0 && elbow==0)
	{
		Picked=false;
        thumb=0;
		littlethumb=0;
		Sleep(2000);//2����ظ����Ŷ���
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
	glutCreateWindow ("�������ֱ۶�����ÿ��2sѭ�����²���");
	init();
	glutDisplayFunc(display); //���Ƴ���
	glutIdleFunc(idle);       //�ػ泡�������ƶ����Ĳ���
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}


