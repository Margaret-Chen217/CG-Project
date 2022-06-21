
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <glut.h>		// Header File For The OpenGL32 tools Library
#include <math.h>
//#include <glew.h>
#define MAP 40
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

int view=1;
GLdouble	g_eye[3];
GLdouble	g_look[3];
float		rad_xz;	
float		g_Angle;
float		g_elev;	
UINT g_cactus[28];
GLUquadricObj *g_text; 
GLfloat r=0;
GLint sky=1;
BOOL DisplayScene()
{ 
	if(view==0)
	{
		gluLookAt(MAP+10+28*cos(float(-3.13149*r/180.0f)),15,-MAP-28*sin(float(-3.13149*r/180.0f)),MAP+10,0.5,-MAP,0.0,1.0,0.0);
		return true;
	}
	float speed=0.1f;	
	if (KEY_DOWN(VK_SHIFT))  speed   =speed*4;
	if (KEY_DOWN(VK_LEFT))   g_Angle-=speed*2;
	if (KEY_DOWN(VK_RIGHT))  g_Angle+=speed*2;
	rad_xz = float (3.13149* g_Angle/180.0f);
	if (KEY_DOWN('3')) g_elev +=1.0f;//pgUp
	if (KEY_DOWN('4')) g_elev -=1.0f;//pgDn
	if (g_elev<-100)	g_elev  =-100;
	if (g_elev> 100)	g_elev  = 100;
	if (KEY_DOWN(VK_UP))
	{ g_eye[2]+=sin(rad_xz)*speed;
	g_eye[0]+=cos(rad_xz)*speed;
	}
	if (KEY_DOWN(VK_DOWN))
	{ g_eye[2]-=sin(rad_xz)*speed;
	g_eye[0]-=cos(rad_xz)*speed;
	}
	if (g_eye[0]<-(MAP*2-20))	g_eye[0]= -(MAP*2-20);
	if (g_eye[0]> (MAP*2-20))	g_eye[0]=  (MAP*2-20);
	if (g_eye[2]<-(MAP*2-20))	g_eye[2]= -(MAP*2-20);
	if (g_eye[2]> (MAP*2-20))	g_eye[2]=  (MAP*2-20);
	g_eye[1] =2.8;

	g_look[0] = float(g_eye[0] + 100*cos(rad_xz));
	g_look[2] = float(g_eye[2] + 100*sin(rad_xz));
	g_look[1] = g_eye[1];

	gluLookAt(g_eye[0],g_eye[1],g_eye[2],g_look[0],g_look[1]+g_elev,g_look[2],0.0,1.0,0.0);
	return TRUE;
}

GLvoid DrawSky(float scale)
{
	glPushMatrix();
	glTranslatef(0.0,scale-1,0.0);
	glScalef(scale,scale,scale);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[3+(sky-1)*5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//������ˣ�����������ӳ�������
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);// ǰ
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[4+(sky-1)*5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[5+(sky-1)*5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[6+(sky-1)*5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[7+(sky-1)*5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);// ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[2]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

GLvoid DrawGround()
{ 
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);
	glTranslatef(0,0.0f,0);
	int size0=(int)(MAP*2);
	glBegin(GL_LINES);
	for (int x = -size0; x < size0;x+=4)
	{
		glVertex3i(x, 0, -size0); 
		glVertex3i(x, 0,  size0);
	}
	for (int z = -size0; z < size0;z+=4)
	{
		glVertex3i(-size0, 0, z);
		glVertex3i( size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();
}

void Box(float x,float y,float z)
{ 
	glPushMatrix();
	glScalef(x,y,z);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);// ǰ
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);// ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void picter(float x,float y,float z)//�����״�
{
	glPushAttrib(GL_CURRENT_BIT);//ѹ�����Զ�ջ
	glPushMatrix();
	GLfloat mat_diffuse[]={0.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);//���ò���
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat light_position[] = {0,0,-4,1,0};
	GLfloat light_color[]={1,1,0,1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//ָ��0�Ź�Դλ��
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);//���ù���Ϊ������
	//glEnable(GL_LIGHTING);//�򿪹���
	glEnable(GL_LIGHT0);
	glTranslatef(x,y+0.5f,z);//������λ
	glColor3f(1.0f,1.0f,0.0f);
	//auxSolidCube(1);
	glTranslatef(0.0f,0.8f,0.0f);//֧�ܶ�λ
	glColor3f(1.0f,0.0f,0.0f);
	//auxSolidBox(.2f,1.3f,.2f);
	glPopMatrix();
	glPushMatrix();//�״�
	glTranslatef(x,y+2.5f,z);
	glRotatef(r-90,0.0,1.0,0.0);
	glColor3f(1.0f,1.0f,1.0f);
	glRotatef(45, 1.0, 0.0, 0.0);
	//auxWireCone(1.5,0.6f);	
	//=======================================
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,0.0f,-0.7f);
	//auxWireCone(0.2f,2.0f);	
	glColor3f(FRAND,0,0);//�����ɫ
	glTranslatef(0.0f,0.0f,2.0f);
	//auxSolidSphere(0.1f);
	glPopMatrix();
	glPopAttrib();//�ָ�����
	r+=0.08f;if(r>360) r=0;

}
void airplane(float x,float y,float z)//�����ɻ�
{ 
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(-r, 0.0, 1.0, 0.0);
	glTranslatef(30,0,0);
	glRotatef(30, 0.0, 0.0, 1.0);//�ɻ���б
	//=============================================
	glPushMatrix();//
	glRotatef(-r*30, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	Box(1.0f,0.1f,0.02f);//������
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);//������
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);//������������ͼ
	glTranslatef(0.0f,0.0f,-0.5f);//����
	gluSphere(g_text, 0.4f, 8, 8);//�ɻ�ͷ��
	//=============================================
	glTranslatef(0.0f,-0.0f,-2);//λ�õ���,���ͷ�Խ�
	gluCylinder(g_text,0.4,0.4,2.0,8,4);//����,԰��(�뾶����)
	//=====================================================
	glRotatef(-180, 1.0, 0.0, 0.0);//�Ƕȵ���
	glTranslatef(0.0f,-0.0f,0.0f);//λ�õ���,����һ��		
	gluCylinder(g_text,0.4,0.1,1.5,8,4);//��β,԰׶(�װ뾶����)
	//======================================================
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);//
	glTranslatef(0.0f,-0.8f,1.2f);//λ�õ���
	Box(1.0,0.05f,0.3f);//����
	glTranslatef(0.0f,0.1f,0.0f);//λ�õ���
	Box(0.05f,0.6f,0.30f);//����
	//======================================================
	glTranslatef(0.0f,0.7f,-1.9f);//λ�õ���
	Box(3,0.05f,0.5f);//ǰ��
	//======================================================
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

AUX_RGBImageRec* DIBImageLoad(char* Filename)
{
	AUX_RGBImageRec* pAuxRGB=new AUX_RGBImageRec ;
	pAuxRGB->sizeX = 0;
	pAuxRGB->sizeY = 0;
	pAuxRGB->data = NULL;

	FILE* img = NULL;
	img = fopen(Filename,"r");

	DWORD size = 0;    

	DWORD off=0;

	fseek(img,10,SEEK_SET);
	fread(&off,4,1,img);

	fseek(img,0,SEEK_SET);

	fseek(img,18,SEEK_SET);
	fread(&(pAuxRGB->sizeX),4,1,img);
	fread(&(pAuxRGB->sizeY),4,1,img);
	fseek(img,0,SEEK_END);
	size = ftell(img) - off;

	pAuxRGB->data= (unsigned char*)malloc(size);

	fseek(img,off,SEEK_SET);    // image data
	fread(pAuxRGB->data,size,1,img);

	fclose(img);

	return pAuxRGB;
}

bool LoadT8(char *filename, GLuint &texture)
{	
	AUX_RGBImageRec *pImage = NULL;
	pImage = DIBImageLoad(filename);//װ����ͼ
	if(pImage == NULL)		
		return false;
	glGenTextures(1, &texture);	//��������
	glBindTexture    (GL_TEXTURE_2D,texture);//��������
	gluBuild2DMipmaps(GL_TEXTURE_2D,4, pImage->sizeX, 
	pImage->sizeY,GL_RGB, GL_UNSIGNED_BYTE,pImage->data);
	free(pImage->data);//�ͷ�λͼռ�ݵ��ڴ���Դ
	free(pImage);	
	return true;
}


void init (void)
{
	g_eye[0]= MAP;//
	g_eye[2]=-MAP;//
	g_Angle=0;//���ÿ�ʼ������ת�Ƕ�Ϊ0
	g_elev=0;//���ÿ�ʼ������ת�Ƕ�Ϊ0
	g_text = gluNewQuadric();

	LoadT8("textures/aa.BMP",g_cactus[0]);
	LoadT8("textures/bb.BMP",g_cactus[1]);
	LoadT8("textures/GROUND.BMP",g_cactus[2]);

	LoadT8("textures/0FRONT.BMP",g_cactus[3]);
	LoadT8("textures/0LEFT.BMP",g_cactus[4]);
	LoadT8("textures/0RIGHT.BMP",g_cactus[5]);
	LoadT8("textures/0RBACK.BMP",g_cactus[6]);
	LoadT8("textures/0TOP.BMP",g_cactus[7]);

	LoadT8("textures/1FRONT.BMP",g_cactus[8]);
	LoadT8("textures/1LEFT.BMP",g_cactus[9]);
	LoadT8("textures/1RIGHT.BMP",g_cactus[10]);
	LoadT8("textures/1RBACK.BMP",g_cactus[11]);
	LoadT8("textures/1TOP.BMP",g_cactus[12]);

	LoadT8("textures/2FRONT.BMP",g_cactus[13]);
	LoadT8("textures/2LEFT.BMP",g_cactus[14]);
	LoadT8("textures/2RIGHT.BMP",g_cactus[15]);
	LoadT8("textures/2RBACK.BMP",g_cactus[16]);
	LoadT8("textures/2TOP.BMP",g_cactus[17]);

	LoadT8("textures/3FRONT.BMP",g_cactus[18]);
	LoadT8("textures/3LEFT.BMP",g_cactus[19]);
	LoadT8("textures/3RIGHT.BMP",g_cactus[20]);
	LoadT8("textures/3RBACK.BMP",g_cactus[21]);
	LoadT8("textures/3TOP.BMP",g_cactus[22]);

	LoadT8("textures/4FRONT.BMP",g_cactus[23]);
	LoadT8("textures/4LEFT.BMP",g_cactus[24]);
	LoadT8("textures/4RIGHT.BMP",g_cactus[25]);
	LoadT8("textures/4RBACK.BMP",g_cactus[26]);
	LoadT8("textures/4TOP.BMP",g_cactus[27]);

}

void animation (void)
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();								 // ���õ�ǰ��ģ�͹۲����
	DisplayScene();
	glPushMatrix();
	glTranslatef(g_eye[0],g_eye[1],g_eye[2]);
	DrawSky(200);
	glPopMatrix();
	DrawGround();
	picter(MAP+10,0,-MAP);
	airplane(MAP+10,15,-MAP);

	glutSwapBuffers();	//����������
	glutPostRedisplay();
}
void reshape(int w ,int h)
{
	glViewport(0,0,w,h);			// ����OpenGL�ӿڴ�С��	
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();			
	gluPerspective( 45.0f,(GLfloat)w/(GLfloat)h,0.1f,3000.0f);//����͸�ӽǶ�Ϊ45�ȣ����ó���ȣ�������Ұ����0.1f��Զ��3000.0f
	glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
	glLoadIdentity();					// ���õ�ǰָ���ľ���Ϊ��λ����
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key){
	case '1':view=1;
		break;
	case '2':view=0;
		break;
	case '5':sky=1;
		break;
	case '6':sky=2;
		break;
	case '7':sky=3;
		break;
	case '8':sky=4;
		break;
	case '9':sky=5;
		break;
	case 'q':exit(0);
		break;
	default:break;
	}
}

void light0()//�ƹ�
{	//GLfloat light_position[] = {1.0,10.0,-51.0,10.0};
	GLfloat light_position[] = {0,0,-4,1,0};
	GLfloat light_color[]={1,1,0,1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//ָ��0�Ź�Դλ��
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);//���ù���Ϊ������
	glEnable(GL_LIGHTING);//�򿪹���
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glEnable(GL_COLOR_MATERIAL);//������ɫ����
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // Set display mode.
	glutInitWindowPosition (50, 100);   // Set top-left display-window position.
	glutInitWindowSize (800, 600);      // Set display-window width and height.���ô���Ϊ640*480
	glutCreateWindow ("Project06"); // Create display window.
	init ( );                            // Execute initialization procedure.
	glutDisplayFunc (animation);       // Send graphics to display window.
	glutReshapeFunc(reshape);         //ע�ᵱǰ���ڵ���״�仯�ص�����changesize
	glutKeyboardFunc(keyboard);
	printf("input 5-9 to change sky");
	glutMainLoop ( );                    // Display everything and wait.
}
