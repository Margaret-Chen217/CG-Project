#include "windows.h"
#include <gl.h>			
#include <glu.h>			
#include <glut.h>		
#include <math.h>

#define PI  3.141591653
#define log2 1.41421356
#define MAP 20 //地面网格数20*20
int view_angle=1;//view_angle控制视角的变化，默认值为视角1
int r=0;//控制雷达的旋转角度
float x,y,z;//飞机的位置坐标

void init (void)
{
	glClearColor (0.0f, 0.0f, 1.0f, 1.0f);  //背景颜色为淡蓝色
	glMatrixMode (GL_PROJECTION);       // Set projection parameters.
	glOrtho (-100,100,-100,100,-100,100);

}

void ReSize(int width, int height)		// 窗口大小调整并且重新初始化窗口
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

//--------------绘制长方体，width×height×depth-------------
void DrawBox(float width,float height,float depth)
{
	glPushMatrix();
	glScalef(width,height,depth);
	glutSolidCube(1);
	glPopMatrix();

}

//-------绘制地面----------------------------------
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

//------------绘制场景中的物体，包括雷达，飞机等------------------------
void DrawObjects ()
{
	//------------雷达支柱-----------------------
	glPushMatrix();
	glTranslatef(0.0f,0.5f,0.0f);
	glColor3f(0,1,0);
	glutSolidCube(1);
	glTranslatef(0.0f,0.8f,0.0f);
	glScalef(0.2f,1.3f,0.2f);
	glColor3f(0.0f,0.0f,1.0f);	
	glutSolidCube(1);		
	glPopMatrix();

	//------------雷达--------------------
	glPushMatrix();
	glTranslatef(0,2.5f,0);		
	glRotatef(r,0.0,1.0,0.0);//雷达旋转
	glColor3f(1.0f,1.0f,1.0f);		
	glRotatef(45, 1.0, 0.0, 0.0);//盘的角度调整，仰30度
	glutWireCone(1.5,0.8f,15,10);			
	glRotatef(180, 1.0, 0.0, 0.0);//杆的角度调整,反方向转
	glTranslatef(0.0f,0.0f,-0.7f); //杆的位置调整
	glutWireCone(0.2f,2.0f,10,10);	//园锥杆
	glColor3f(1,0,0);			    
	glTranslatef(0.0f,0.0f,2.0f);
	glutSolidSphere(0.1f,20,20);
	glPopMatrix();

	//--------飞机----------------------------
	glPushMatrix();
	glTranslatef(-x,y,-z);//飞机的定位
	glRotatef(r,0,1,0);//飞机随雷达旋转
	glColor3f(1,1,1);
	DrawBox(1,0.2,0.2);//机身

	//机头和机尾---------------------------
	glPushMatrix();
	glTranslatef(-0.5,0,0);
	glScalef(2,1,1);
	glutSolidSphere(0.13,20,20);
	glTranslatef(0.5,0,0);
	glScalef(2,1,1);
	glutSolidSphere(0.13,20,20);
	glPopMatrix();

	//机翼---------------------------------
	glPushMatrix();
	glTranslatef(0.1,0,0.3);
	glRotatef(30,0,1,0);
	DrawBox(0.2,0.1,0.6);
	glRotatef(-60,0,1,0);
	glTranslatef(-0.2,0,-0.6);
	DrawBox(0.2,0.1,0.6);
	glPopMatrix();

	//螺旋桨，黄色-----------------------------
	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(-0.8,0,0);
	glRotatef(-r*20,1,0,0);//螺旋桨自转
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

	//飞机的位置设定
	x=5*sin(r*PI/180);
	y=8;
	z=5*cos(r*PI/180);

	if(view_angle==1)//视角1
	{
		//glTranslatef(0,-5,-15);
		gluLookAt(0,10,15,0,5,0,0,1,0);
	}
	if(view_angle==2)//视角2
	{
		gluLookAt(x,y,z,0,0,0,0,1,0);
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


void Keyboard (unsigned char key, int x, int y)//通过键盘的数字键1和2来切换场景的视角
{
	switch(key) {
	case 49://数字键1，选择视角1
		view_angle=1;
		break;	
	case 50://数字键2，选择视角2
		view_angle=2;
		break;
	}
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);                         // 初始化 GLUT.
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);   // 设置显示模式
	glutInitWindowPosition (0, 0);   //窗口位置
	glutInitWindowSize (720,560);      // 窗口大小为720*560.
	glutCreateWindow ("雷达飞机动画——使用数字键1和2切换视角"); // 创建显示窗口

	init ( );                            // 执行初始化程序
	glutDisplayFunc (Display);         // 窗口显示绘制的图像.
	glutIdleFunc(Idel);
	glutKeyboardFunc(Keyboard);  //键盘事件处理函数
	glutReshapeFunc(ReSize);    //注册当前窗口的形状变化回调函数ReSizeGLScene
	glutMainLoop ( );           // 显示窗口内容并进入GLUT事件处理循环
}