#include <glut.h>
#include <GLAUX.H>
#include <stdio.h>
#include <windows.h>
#include <math.h>

const float windowWidth = 800.0f, windowHeight = 800.0f;  //��Ļ��ȣ��߶�
#define PI  3.141591653
#define MAP 20	//����������

bool sight = true;	//�ӽ��趨��Ĭ��trueΪ�������ӽǣ�falseΪ��һ���ӽ�
float ex = 0.0, ey = 5.0, ez = 50.0;  //�ӵ�仯
float cx = 0.0, cy = 5.0, cz = 0.0;  //���߱仯
float angleS = -90.0;
float rad = 0.0, yo = 0.0;

bool done = false;  //�ж��Ƿ����ֳɹ���Ĭ��Ϊδ���ֳɹ�
int step = 2;  //�ƶ�����
static int shoulder = 0, elbow = 0, thumb = 0, littlethumb = 0;  //�����ֱ۹ؽڵ���ת
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
	//����ǰ�ֱ۵Ķ�������
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

	//���ֱ۵����ض�λ��ʱ��Picked��Ϊtrue����ʾ����Ա�����
	if (shoulder <= -20 && elbow <= -50 && thumb <= -30 && littlethumb <= -30)
		done = true;

	//��������ֱ۵Ķ�������
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

	//���ƶ�����ѭ������
	if (shoulder == 0 && elbow == 0)
	{
		done = false;
		thumb = 0;
		littlethumb = 0;
		Sleep(2000);//2����ظ����Ŷ���
	}

	Sleep(100);
	glutPostRedisplay();
}

void FireTexture(void)  //����������ͼ
{
	//������ͼ
	glEnable(GL_TEXTURE_2D);  //��������ӳ��
	glBindTexture(GL_TEXTURE_2D, g_cactus[2]); 
	glBegin(GL_QUADS);
	// ǰ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawRobot()  //���ƻ����ֱ�
{
	//ͷ����������������������������������������
	glPushMatrix();
	glTranslatef(0, 10, 0);
	glutSolidSphere(1, 200, 500);
	glTranslatef(0, 0.4, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.5, 1.8, 200, 500);
	glPopMatrix();

	//����������������������������������������
	glPushMatrix();
	glTranslatef(0, 7, 0);
	glScalef(0.5, 1, 0.4);
	//glutSolidCube(4);
	//������ͼ
	glEnable(GL_TEXTURE_2D);  //��������ӳ��
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]); 
	glBegin(GL_QUADS);
	// ǰ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f, 2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -2.0f, -2.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, 2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, -2.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f, -2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f); // ������ı��ε�����
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//���ȡ���������������������������������������
	glPushMatrix();
	glTranslatef(-0.6, 4, 0);
	glScalef(0.4, 1, 0.5);
	//glutSolidCube(2);  //����
	FireTexture();
	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.5, 0);
	glutSolidSphere(0.4, 200, 500);  //�ؽ�
	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.5, 0);
	//glutSolidCube(2);  //С��
	FireTexture();
	glPopMatrix();

	//���ȡ���������������������������������������
	glPushMatrix();
	glTranslatef(0.6, 4, 0);
	glScalef(0.4, 1, 0.5);
	//glutSolidCube(2);  //����
	FireTexture();
	glScalef(1 / 0.4, 1 / 1, 1 / 0.5);
	glTranslatef(0, -1.5, 0);
	glutSolidSphere(0.4, 200, 500);  //�ؽ�
	glScalef(0.4, 1, 0.5);
	glTranslatef(0, -1.5, 0);
	//glutSolidCube(2);  //С��
	FireTexture();
	glPopMatrix();

	//��ۡ���������������������������������������
	glPushMatrix();
	glTranslatef(1.5, 8.2, 0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //�ϱ�
	FireTexture();
	glPopMatrix();

	glTranslatef(0, -1.2, 0);
	glutSolidSphere(0.4, 200, 500);  //�ؽ�

	glTranslatef(0, -1.2, 0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //�±�
	FireTexture();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -1, 0.4);
	glScalef(0.2, 0.4, 0.2);
	glutSolidCube(1);  //1ָ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.9, 0.4);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2ָ��
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2ָ��
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.9, 0.1);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3ָ��
	glPopMatrix();

	glTranslatef(0.0, -0.5, -0.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3ָ��
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.9, -0.2);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4ָ��
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4ָ��
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	//�ұۡ���������������������������������������
	glPushMatrix();
	glTranslatef(-1.5, 8.2, 0);
	glRotatef((GLfloat)shoulder, 1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //�ϱ�
	FireTexture();
	glPopMatrix();

	glTranslatef(0, -1.2, 0);
	glutSolidSphere(0.4, 200, 500);  //�ؽ�

	glRotatef((GLfloat)elbow, 1.0, -1.0, 0.0);
	glTranslatef(0, -1.2, 0);
	glPushMatrix();
	glScalef(0.4, 0.8, 0.5);
	//glutSolidCube(2);  //�±�
	FireTexture();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -1, 0.4);
	glScalef(0.2, 0.4, 0.2);
	glutSolidCube(1);  //ָ1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.9, 0.4);
	glRotatef((GLfloat)thumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2ָ��
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef((GLfloat)littlethumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //2ָ��
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.9, 0.1);
	glRotatef((GLfloat)thumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3ָ��
	glPopMatrix();

	glTranslatef(0.0, -0.5, -0.0);
	glRotatef((GLfloat)littlethumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //3ָ��
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.9, -0.2);
	glRotatef((GLfloat)thumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4ָ��
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef((GLfloat)littlethumb, 0.0, 0.0, -1.0);
	glPushMatrix();
	glScalef(0.2, 0.5, 0.2);
	glutSolidCube(1);  //4ָ��
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void DrawGround()  //���Ƶ���
{
	glPushAttrib(GL_CURRENT_BIT);
	//�趨��������
	glEnable(GL_TEXTURE_2D);  //��������ӳ��
	float scale = 100;  //��ͼ����
	glTranslatef(0, -1, 0);
	glScalef(scale, 1, scale);
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//������
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
	glRotatef(Ror, 0, 1, 0);  //������ֵ�׶����ת
	glutSolidCone(1, 1, 200, 500);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, 3, 10);
	glScalef(1, 3, 1);
	//glutSolidCube(20);  
	//������ͼ
	glEnable(GL_TEXTURE_2D);  //��������ӳ��
	glBindTexture(GL_TEXTURE_2D, g_cactus[3]); 
	glBegin(GL_QUADS);
	// ǰ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	// ����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void timerFunc(int value)
{
	Ror += Rstep;
	if (Ror > 360)
		Ror %= 360;
	glutPostRedisplay();  //��ǵ�ǰ������Ҫ���»���
	glutTimerFunc(33, timerFunc, 1);  //������ʱ���ص�����
}


AUX_RGBImageRec* DIBImageLoad(char* Filename)  //����λͼͼ��
{
	AUX_RGBImageRec* pAuxRGB = new AUX_RGBImageRec;
	pAuxRGB->sizeX = 0;
	pAuxRGB->sizeY = 0;
	pAuxRGB->data = NULL;

	FILE* img = NULL;  //�ļ����
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
	pImage = DIBImageLoad(filename);//װ����ͼ
	if (pImage == NULL)		return false;
	glGenTextures(1, &texture);	//��������
	glBindTexture(GL_TEXTURE_2D, texture);//��������
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
		pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	free(pImage->data);//�ͷ�λͼռ�ݵ��ڴ���Դ
	free(pImage);
	return true;
}