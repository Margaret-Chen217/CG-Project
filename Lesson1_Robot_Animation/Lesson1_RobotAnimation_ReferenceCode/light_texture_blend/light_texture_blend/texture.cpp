#include <math.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include "windows.h"
#include <glut.h>
#include <glaux.h>		// Header File For The Glaux Library


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


bool	keys[256];			
bool	active=TRUE;		
bool	fullscreen=TRUE;	
bool	light = true;				
bool	lp = true;					
bool	fp;					

bool    blend;					// 是否混合
bool	bp;						// B键是否按下



GLfloat	xrot;				
GLfloat	yrot;				
GLfloat xspeed;				
GLfloat yspeed;				
GLfloat	z=-5.0f;		

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

GLuint	filter;				
GLuint	texture[3];			// 存储3个纹理的索引号


AUX_RGBImageRec* DIBImageLoad(char* Filename)
{
	AUX_RGBImageRec* pAuxRGB=new AUX_RGBImageRec ;
	pAuxRGB->sizeX = 0;
	pAuxRGB->sizeY = 0;
	pAuxRGB->data = NULL;

	FILE* img = NULL;
	img = fopen(Filename,"rb");

	DWORD size = 0;    

	fseek(img,18,SEEK_SET);
	fread(&(pAuxRGB->sizeX),4,1,img);
	fread(&(pAuxRGB->sizeY),4,1,img);
	fseek(img,0,SEEK_END);
	size = ftell(img) - 54;

	pAuxRGB->data= (unsigned char*)malloc(size);

	fseek(img,54,SEEK_SET);    // image data
	fread(pAuxRGB->data,size,1,img);

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

int LoadGLTextures()									
{
	int Status=FALSE;									

	AUX_RGBImageRec *TextureImage[1];					

	memset(TextureImage,0,sizeof(void *)*1);           

	if (TextureImage[0]=LoadBMP("Data/Glass.bmp"))
	{
		Status=TRUE;									

		glGenTextures(3, &texture[0]);					

		// 放大和缩小时，使用最近邻插值
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// 放大和缩小时，使用双线性邻插值
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// 放大使用双线性插值，缩小时使用双线性插值和最近邻相结合
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

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

	glEnable(GL_TEXTURE_2D);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	
	//glEnable(GL_LIGHT1);	

	glColor4f(1.0f,1.0f,1.0f,0.5f);			// 全亮度，50% Alpha 混合
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);		// 基于源象素alpha通道值的半透明混合函数

	// Enable Light One
	return TRUE;		
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();									
	glTranslatef(0.0f,0.0f,z);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[filter]);

	glBegin(GL_QUADS);
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	xrot+=xspeed;
	yrot+=yspeed;
	glutSwapBuffers();

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

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();	
}


void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':   /*  s key rotates at shoulder  */

		if (key=='l')
		{
			light=!light;
			if (!light)
			{
				glDisable(GL_LIGHTING);
			}
			else
			{
				glEnable(GL_LIGHTING);
			}
		}

		break;
	case 'f':

		if (key=='f' && !fp)
		{
			fp=TRUE;
			filter+=1;
			if (filter>2)
			{
				filter=0;
			}
		}
		fp=!fp;
		break;
	case 'b':

		if (key=='b' && !bp)				
		{
			bp = !bp;				
			blend = !blend;				
			if(blend)				
			{
				glEnable(GL_BLEND);		
				glDisable(GL_DEPTH_TEST);	
			}
			else					
			{
				glDisable(GL_BLEND);		
				glEnable(GL_DEPTH_TEST);	
			}
			bp = !bp;
		}

	default:
		break;
	}
}

void KeySight(int key, int x, int y)
{
	switch(key){
	case GLUT_KEY_PAGE_UP: 
		z-=0.02f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		z+=0.02f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP: 
		xspeed-=0.01f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		xspeed+=0.01f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT: 
		yspeed+=0.01f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		yspeed-=0.01f;
		glutPostRedisplay();
		break;
		glutPostRedisplay();
	default:
		break;
	}
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
	glutSpecialFunc(KeySight);
	glutMainLoop();
	return 0;
}
