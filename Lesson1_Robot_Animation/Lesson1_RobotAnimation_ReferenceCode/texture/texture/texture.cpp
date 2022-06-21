#include <math.h>
#include <stdio.h>
#include "windows.h"
#include <glut.h>
#include <glaux.h>	

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

#define testposition1();    glColor3f(0.0,1.0,0.0);\
	glBegin(GL_LINES);\
	glVertex3f(0.0,0.0,-0.2);\
	glVertex3f(0.0,0.0,0.2);\
	glEnd();\
	glBegin(GL_LINES);\
	glVertex3f(-0.2,0.0,0.0);\
	glVertex3f(0.2,0.0,0.0);\
	glEnd();\
	glColor3f(1.0,1.0,1.0);


GLfloat	xrot;				
GLfloat	yrot;				
GLfloat	zrot;			

GLuint	texture[1];	 //��������������

// ��ȡλͼ����
AUX_RGBImageRec* DIBImageLoad(char* Filename)
{
	AUX_RGBImageRec* pAuxRGB = new AUX_RGBImageRec; // AUX_RGBImageRec��GLAUX�е�һ���࣬��opengl�����ڶ�ȡ�Ͳ���λͼ
	pAuxRGB->sizeX = 0;  // λͼ�Ŀ��
	pAuxRGB->sizeY = 0;  // λͼ�ĸ߶�
	pAuxRGB->data = NULL; // λͼ��RGB����

	FILE* img = NULL;
	img = fopen(Filename,"rb");

	DWORD size = 0;    

	fseek(img,18,SEEK_SET);  // ���ļ�ͷƫ��18���ֽڣ�����λͼ�Ĳ���ͷ����Ϣ���������͡���С�������ֵȵȣ� 
	fread(&(pAuxRGB->sizeX), 4, 1, img); // ��ȡ��ȣ�4���ֽ�
	fread(&(pAuxRGB->sizeY), 4, 1, img); // ��ȡ���ȣ�4���ֽ�
	fseek(img,0,SEEK_END);
	size = ftell(img) - 54;  // ����RGB���ݵĴ�С

	pAuxRGB->data= (unsigned char*)malloc(size);

	fseek(img, 54, SEEK_SET);    // ���ļ�ͷƫ��54���ֽڣ��ﵽRGB���ݿ�ʼ��λ��
	fread(pAuxRGB->data, size, 1, img);

	fclose(img);

	return pAuxRGB;
}

AUX_RGBImageRec *LoadBMP(char *Filename)				
{
	FILE *File=NULL;									

	if (!Filename)										
	{
		return NULL;									
	}

	File=fopen(Filename,"r");							

	if (File)											
	{
		fclose(File);									
		return DIBImageLoad(Filename);				
	}

	return NULL;							
}

int LoadGLTextures()									// ����λͼ��תΪ��������
{
	int Status = FALSE;									

	AUX_RGBImageRec *TextureImage[1];				
	memset(TextureImage,0,sizeof(void *)*1);           

	if (TextureImage[0] = LoadBMP("Data/NeHe.bmp"))     // ����λͼ
	{
		Status = TRUE;							

		glGenTextures(1, &texture[0]);					// �����������������������

		glBindTexture(GL_TEXTURE_2D, texture[0]);       // ����������opengl�ں������к�������ص����У�
		                                                // ������������������󶨵��������ֱ�����µ�������󱻰󶨡�

		glTexImage2D(GL_TEXTURE_2D, 0, 4, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 
			0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TextureImage[0]->data); // ������������͡�������Ȳ�������λͼ�е�RGB���ݿ�����������

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ����2D��������ԣ���������С��GL_TEXTURE_MIN_FILTER��ʱ������˫���Բ�ֵ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ����2D��������ԣ�������Ŵ�GL_TEXTURE_MAG_FILTER��ʱ������˫���Բ�ֵ
	}

	// �ͷ�λͼ
	if (TextureImage[0])									
	{
		if (TextureImage[0]->data)							
		{
			free(TextureImage[0]->data);					
		}

		free(TextureImage[0]);								
	}

	return Status;										
}


int init(void) 
{
	if (!LoadGLTextures())								
	{
		return FALSE;									
	}

	glEnable(GL_TEXTURE_2D);							// ����������ͼ������ӳ�䣩
	glShadeModel(GL_SMOOTH);							// ����smooth����ģʽ
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// ָ�������ɫ������ʱ�����õ���ɫֵ
	glClearDepth(1.0f);									// ָ�������Ȼ�����ʱ�����õ����ֵ
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glDepthFunc(GL_LEQUAL);								// ָ����Ȼ������ıȽϺ���
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 
	return TRUE;	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����ɫ����Ȼ��������ֱ�ʹ��glClearColor��glClearDepth�趨��ֵ
	glLoadIdentity();									
	glTranslatef(0.0f,0.0f,-5.0f);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
	// ǰ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	// ����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	// ����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	// ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	// ����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();


	glutSwapBuffers();

	//	xrot+=0.6f;
	yrot+=0.04f;
	//	zrot+=0.8f;										

	glutPostRedisplay();

}

void reshape (int width, int height)
{
	if (height==0)										
	{
		height=1;										
	}

	glViewport(0,0,width,height);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();									

}


void keyboard (unsigned char key, int x, int y)
{
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
