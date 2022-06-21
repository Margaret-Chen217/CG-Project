#include <glut.h>
#include <GLAUX.H>
#include <stdio.h>
#include <windows.h>
#include <math.h>

const float windowWidth = 800.0f, windowHeight = 800.0f;  //屏幕宽度，高度
#define PI  3.141591653
#define MAP 20	//地面网格数

bool sight = true;	//视角设定，默认true为第三方视角，false为第一方视角
float ex = 0.0, ey = 5.0, ez = 50.0;  //视点变化
float cx = 0.0, cy = 5.0, cz = 0.0;  //视线变化
float angleS = -90.0;
float rad = 0.0, yo = 0.0;

bool done = false;  //判断是否握手成功，默认为未握手成功
int step = 2;  //移动步长
static int shoulder = 0, elbow = 0, thumb = 0, littlethumb = 0;  //控制手臂关节的旋转
int Ror=0, Rstep = 10;

GLuint	texture[3];			// Storage For 3 Textures
GLuint g_cactus[28];


void reshape(int width, int height)
{
	if (height == 0)  //Prevent A Divide By Zero By
	{
		height = 1;  //Making Height Equal One
	}

	glViewport(0, 0, width, height);  //Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);  //Select The Projection Matrix
	glLoadIdentity();  //Reset The Projection Matrix

	//Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);  //Select The Modelview Matrix
	glLoadIdentity();  //Reset The Modelview Matrix
}

void Idel()
{
	//捡球前手臂的动画控制
	if (!done)
	{
		if (shoulder > -20)
			shoulder -= step;
		else if (elbow > -50)
			elbow -= step;
		else if (thumb > -30)
			thumb -= step;
		else if (littlethumb > -30)
			littlethumb -= step;
	}

	//当手臂到达特定位置时，Picked设为true，表示球可以被捡起
	if (shoulder <= -20 && elbow <= -50 && thumb <= -30 && littlethumb <= -30)
		done = true;

	//捡起球后手臂的动画控制
	if (done)
	{
		if (shoulder < 0)
			shoulder += step;
		if (elbow < 0)
			elbow += step;
		if (thumb < 0)
			thumb++;
		if (littlethumb < 0)
			littlethumb++;
	}

	//控制动画的循环播放
	if (shoulder == 0 && elbow == 0)
	{
		done = false;
		thumb = 0;
		littlethumb = 0;
		Sleep(2000);//2秒后重复播放动画
	}

	Sleep(100);
	glutPostRedisplay();
}

void FireTexture(void)  //火焰纹理贴图
{
	//纹理贴图
	glEnable(GL_TEXTURE_2D);  //启用纹理映射
	glBindTexture(GL_TEXTURE_2D, g_cactus[2]); 
	glBegin(GL_QUADS);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
	// 后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	// 顶面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	// 底面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawRobot()  //绘制机器手臂
{
	//头————————————————————
	glPushMatrix();
	glTranslatef(0, 10, 0);
	glutSolidSphere(1, 200, 500);
	glTranslatef(0, 0.4, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.5, 1.8, 200, 500);
	glPopMatrix();

	//身————————————————————
	glPushMatrix();
	glTranslatef(0, 7, 0);
	glScalef(0.5, 1, 0.4);
	//glutSolidCube(4);
	//纹理贴图
	glEnable(GL_TEXTURE_2D);  //启用纹理映射
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]); 
	glBegin(GL_QUADS);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f); // 纹理和四边形的左上
	// 后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f, 2.0f, -2.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -2.0f, -2.0f); // 纹理和四边形的左下
	// 顶面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 2.0f, 2.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, 2.0f, 2.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, -2.0f); // 纹理和四边形的右上
	// 底面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f, -2.0f, -2.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f); // 纹理和四边形的右下
	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, -2.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, -2.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f); // 纹理和四边形的左下
	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f); // 纹理和四边形的左上
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//左腿————————————————————
	glPushMatrix();
	glTranslatef(-0.6, 4, 0);
	glScalef(0.4, 1, 0.5);
	//glutSolidCube(2);  //大腿
	FireTexture();
	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.5, 0);
	glutSolidSphere(0.4, 200, 500);  //关节
	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.5, 0);
	//glutSolidCube(2);  //小腿
	FireTexture();
	glPopMatrix();

	//右腿————————————————————
	glPushMatrix();
	glTranslatef(0.6, 4, 0);
	glScalef(0.4, 1, 0.5);
	//glutSolidCube(2);  //大腿
	FireTexture();
	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.5, 0);
	glutSolidSphere(0.4, 200, 500);  //关节
	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.5, 0);
	//glutSolidCube(2);  //小腿
	FireTexture();
	glPopMatrix();

	//左臂————————————————————
	glPushMatrix();
	glTranslatef(1.5, 8.2, 0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //上臂
	FireTexture();
	glPopMatrix();

	glTranslatef(0, -1.2, 0);
	glutSolidSphere(0.4, 200, 500);  //关节

	glTranslatef(0, -1.2, 0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //下臂
	FireTexture();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -1, 0.4);
	glScalef(0.2, 0.4, 0.2);
	glutSolidCube(1);  //1指
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.9, 0.4);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2指根
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2指尖
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.9, 0.1);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3指根
	glPopMatrix();

	glTranslatef(0.0, -0.5, -0.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3指尖
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.9, -0.2);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4指根
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4指尖
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	//右臂————————————————————
	glPushMatrix();
	glTranslatef(-1.5, 8.2, 0);
	glRotatef((GLfloat)shoulder, 1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //上臂
	FireTexture();
	glPopMatrix();

	glTranslatef(0, -1.2, 0);
	glutSolidSphere(0.4, 200, 500);  //关节

	glRotatef((GLfloat)elbow, 1.0, -1.0, 0.0);
	glTranslatef(0, -1.2, 0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //下臂
	FireTexture();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -1, 0.4);
	glScalef(0.2, 0.4, 0.2);
	glutSolidCube(1);  //指1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.9, 0.4);
	glRotatef((GLfloat)thumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2指根
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef((GLfloat)littlethumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2指尖
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.9, 0.1);
	glRotatef((GLfloat)thumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3指根
	glPopMatrix();

	glTranslatef(0.0, -0.5, -0.0);
	glRotatef((GLfloat)littlethumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3指尖
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.9, -0.2);
	glRotatef((GLfloat)thumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4指根
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef((GLfloat)littlethumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4指尖
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void DrawGround()  //绘制地面
{
	glPushAttrib(GL_CURRENT_BIT);
	//设定地面纹理
	glEnable(GL_TEXTURE_2D);  //启用纹理映射
	float scale = 100;  //贴图缩放
	glTranslatef(0, -1, 0);
	glScalef(scale, 1, scale);
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//网格线
	glEnable(GL_BLEND);
	glColor3f(0.5f, 0.7f, 1.0f);
	glTranslatef(0, 0.0f, 0);
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
	glDisable(GL_BLEND);
	glPopAttrib();
}

void DrawBeacon()
{
	glPushMatrix();
	glTranslatef(-4, 7, 10);
	glutSolidSphere(0.5, 200, 500);
	glRotatef(Ror, 0, 1, 0);  //代表灯罩的锥形旋转
	glutSolidCone(1, 1, 200, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, 3, 10);
	glScalef(1, 3, 1);
	//glutSolidCube(20);  
	//纹理贴图
	glEnable(GL_TEXTURE_2D);  //启用纹理映射
	glBindTexture(GL_TEXTURE_2D, g_cactus[3]); 
	glBegin(GL_QUADS);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
	// 后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	// 顶面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	// 底面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void timerFunc(int value)
{
	Ror += Rstep;
	if (Ror > 360)
		Ror %= 360;
	glutPostRedisplay();  //标记当前窗口需要重新绘制
	glutTimerFunc(33, timerFunc, 1);  //创建定时器回调函数
}


AUX_RGBImageRec* DIBImageLoad(char* Filename)  //载入位图图像
{
	AUX_RGBImageRec* pAuxRGB = new AUX_RGBImageRec;
	pAuxRGB->sizeX = 0;
	pAuxRGB->sizeY = 0;
	pAuxRGB->data = NULL;

	FILE* img = NULL;  //文件句柄
	//img = fopen(Filename, "r");
	fopen_s(&img, Filename, "r");

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

bool LoadT8(char *filename, GLuint &texture)
{
	AUX_RGBImageRec *pImage = NULL;
	pImage = DIBImageLoad(filename);//装入贴图
	if (pImage == NULL)		return false;
	glGenTextures(1, &texture);	//生成纹理
	glBindTexture(GL_TEXTURE_2D, texture);//捆绑纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
		pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	free(pImage->data);//释放位图占据的内存资源
	free(pImage);
	return true;
}