#include "windows.h"
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glut.h>		// Header File For The OpenGL32 tools Library
#include <math.h>

#define PI  3.141591653
#define MAP 20 //����������20*20
int view_angle=1;//view_angle�����ӽǵı仯��Ĭ��ֵΪ�ӽ�1
int r=0;//�����״����ת�Ƕ�
float x,y,z;//�ɻ���λ������

//float angle = 0, air = 0, flat = 0;					//��ת����
//bool sight = true;									//�ӽǱ���
//float eyeX = 0.0, eyeY = 2.2, eyeZ = 13.0;			//�ӵ�λ��
//float centerX = 0.0, centerY = 2.0, centerZ = -10.0;//����λ��
//float upX = 0.0, upY = 1.0, upZ = 0.0;				//���߷���
//float planeX = 5.0, planeY = 5.0, planeZ = 0.0;		//�ɻ����״�ĳ�ʼx,y,z����
float ex = 0.0, ey = 5.0, ez = 15.0;					//�ӵ�仯
float cx = 0.0, cy = 5.0, cz = 0.0;					//���߱仯
float s_angle = -90.0;
float rad = 0.0;
float yo = 0.0;


void init (void)
{
	glClearColor (0.0, 0.0, 0.5, 1.0f);  //������ɫΪ����ɫ
	glMatrixMode (GL_PROJECTION);       // Set projection parameters.
	glOrtho (-100,100,-100,100,-100,100);

}

void ReSize(int width, int height)		// ���ڴ�С�����������³�ʼ������
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

//--------------���Ƴ����壬width��height��depth-------------
void DrawBox(float width,float height,float depth)
{
	glPushMatrix();
	glScalef(width,height,depth);
	glutSolidCube(1);
	glPopMatrix();

}

//-------���Ƶ���----------------------------------
void DrawGround()
{ 
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);
	glTranslatef(0,0.0f,0);
	int size0=(int)(MAP*2);
	glBegin(GL_LINES);
	for (int x = -size0; x < size0;x+=1)
	{
		glVertex3i(x, 0, -size0); glVertex3i(x, 0,  size0);
	}
	for (int z = -size0; z < size0;z+=1)
	{
		glVertex3i(-size0, 0, z); glVertex3i( size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();
}

//------------���Ƴ����е����壬�����״�ɻ���------------------------
void DrawObjects ()
{
	//------------�״�֧��-----------------------
	glPushMatrix();
	glTranslatef(0.0f,0.5f,0.0f);
	glColor3f(0,1,0);
	glutSolidCube(1);
	glTranslatef(0.0f,0.8f,0.0f);
	glScalef(0.2f,1.3f,0.2f);
	glColor3f(0.0f,0.0f,1.0f);	
	glutSolidCube(1);		
	glPopMatrix();

	//------------�״�--------------------
	glPushMatrix();
	glTranslatef(0,2.5f,0);		
	glRotatef(r,0.0,1.0,0.0);//�״���ת
	glColor3f(1.0f,1.0f,1.0f);		
	glRotatef(45, 1.0, 0.0, 0.0);//�̵ĽǶȵ�������30��
	glutWireCone(1.5,0.8f,15,10);			
	glRotatef(180, 1.0, 0.0, 0.0);//�˵ĽǶȵ���,������ת
	glTranslatef(0.0f,0.0f,-0.7f); //�˵�λ�õ���
	glutWireCone(0.2f,2.0f,10,10);	//԰׶��
	glColor3f(1,0,0);			    
	glTranslatef(0.0f,0.0f,2.0f);
	glutSolidSphere(0.1f,20,20);
	glPopMatrix();

	//--------�ɻ�----------------------------
	glPushMatrix();
	glTranslatef(-x,y,-z);//�ɻ��Ķ�λ
	glRotatef(r,0,1,0);//�ɻ����״���ת
	glColor3f(1,1,1);
	DrawBox(1,0.2,0.2);//����

	//��ͷ�ͻ�β---------------------------
	glPushMatrix();
	glTranslatef(-0.5,0,0);
	glScalef(2,1,1);
	glutSolidSphere(0.13,20,20);
	glTranslatef(0.5,0,0);
	glScalef(2,1,1);
	glutSolidSphere(0.13,20,20);
	glPopMatrix();

	//����---------------------------------
	glPushMatrix();
	glTranslatef(0.1,0,0.3);
	glRotatef(30,0,1,0);
	DrawBox(0.2,0.1,0.6);
	glRotatef(-60,0,1,0);
	glTranslatef(-0.2,0,-0.6);
	DrawBox(0.2,0.1,0.6);
	glPopMatrix();

	//����������ɫ-----------------------------
	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(-0.8,0,0);
	glRotatef(-r*20,1,0,0);//��������ת
	DrawBox(0.01,0.5,0.1);
	glPopMatrix();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear display window.

	glLoadIdentity();

	//�ɻ���λ���趨
	x=5*sin(r*PI/180);
	y=5;
	z=5*cos(r*PI/180);

	if(view_angle==1)//�ӽ�1
	{
		//glTranslatef(0,-5,-15);
		//gluLookAt(0,10,15,0,5,0,0,1,0);
		gluLookAt(ex,ey,ez,cx,cy,cz,0,1,0);
	}
	if(view_angle==2)//�ӽ�2
	{
		gluLookAt(x,y,z,0,2,0,0,1,0);
	}

	DrawGround();
	DrawObjects();  
}


void Idel()
{
	r=(r+1)%360;
	Sleep(10);
	glutPostRedisplay();   
}


void Keyboard (unsigned char key, int x, int y)//ͨ�����̵����ּ�1��2���л��������ӽ�
{
	switch(key) {
	case 49://���ּ�1��ѡ���ӽ�1
		view_angle=1;
		break;	
	case 50://���ּ�2��ѡ���ӽ�2
		view_angle=2;
		break;
	}
}
void KeySight(int key, int x, int y)
{
	float disEye2Center=sqrt((ex-cx)*(ex-cx)+(ey-cy)*(ey-cy)+(ez-cz)*(ez-cz));
	if(key == GLUT_KEY_LEFT)
	{
		s_angle -= 2.0;	

	}
	if(key == GLUT_KEY_RIGHT)
	{
		s_angle += 2.0;

	}
	rad = float(PI*s_angle/180.0f);
	if(key == GLUT_KEY_UP)
	{

		ez += 0.2*sin(rad);
		ex += 0.2*cos(rad);
	}
	if(key == GLUT_KEY_DOWN)
	{
		ez -= 0.2*sin(rad);
		ex -= 0.2*cos(rad);
	}

	if(key == GLUT_KEY_PAGE_UP)
	{
		yo +=1.0f;
	}
	if(key == GLUT_KEY_PAGE_DOWN)
	{
		yo-=1.0f;
	}
	cx = float(ex+disEye2Center*cos(rad));
	cy = ey+yo;
	cz = float(ez+disEye2Center*sin(rad));
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);                         // ��ʼ�� GLUT.
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);   // ������ʾģʽ
	glutInitWindowPosition (0, 0);   //����λ��
	glutInitWindowSize (720,560);      // ���ڴ�СΪ720*560.
	glutCreateWindow ("�״�ɻ���������ʹ�����ּ�1��2�л��ӽ��Լ���������"); // ������ʾ����

	init ( );                            // ִ�г�ʼ������
	glutDisplayFunc (Display);         // ������ʾ���Ƶ�ͼ��.
	glutIdleFunc(Idel);
	glutKeyboardFunc(Keyboard);  //�����¼�������
	glutSpecialFunc(KeySight);//�Լ����������4�����򰴼�����Ӧ����
	glutReshapeFunc(ReSize);    //ע�ᵱǰ���ڵ���״�仯�ص�����ReSizeGLScene
	glutMainLoop ( );           // ��ʾ�������ݲ�����GLUT�¼�����ѭ��
}