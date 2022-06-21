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

GLuint	texture[1];	 //纹理索引号数组

// 读取位图函数
AUX_RGBImageRec* DIBImageLoad(char* Filename)
{
	AUX_RGBImageRec* pAuxRGB = new AUX_RGBImageRec; // AUX_RGBImageRec是GLAUX中的一个类，在opengl中用于读取和操作位图
	pAuxRGB->sizeX = 0;  // 位图的宽度
	pAuxRGB->sizeY = 0;  // 位图的高度
	pAuxRGB->data = NULL; // 位图的RGB数据

	FILE* img = NULL;
	img = fopen(Filename,"rb");

	DWORD size = 0;    

	fseek(img,18,SEEK_SET);  // 从文件头偏移18个字节，跳过位图的部分头部信息（包括类型、大小、保留字等等） 
	fread(&(pAuxRGB->sizeX), 4, 1, img); // 读取宽度，4个字节
	fread(&(pAuxRGB->sizeY), 4, 1, img); // 读取长度，4个字节
	fseek(img,0,SEEK_END);
	size = ftell(img) - 54;  // 计算RGB数据的大小

	pAuxRGB->data= (unsigned char*)malloc(size);

	fseek(img, 54, SEEK_SET);    // 从文件头偏移54个字节，达到RGB数据开始的位置
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

int LoadGLTextures()									// 导入位图并转为纹理数据
{
	int Status = FALSE;									

	AUX_RGBImageRec *TextureImage[1];				
	memset(TextureImage,0,sizeof(void *)*1);           

	if (TextureImage[0] = LoadBMP("Data/NeHe.bmp"))     // 读入位图
	{
		Status = TRUE;							

		glGenTextures(1, &texture[0]);					// 创建纹理，返回纹理的索引号

		glBindTexture(GL_TEXTURE_2D, texture[0]);       // 绑定纹理，告诉opengl在后面所有和纹理相关调用中，
		                                                // 我们所操作的是这个绑定的纹理对象，直到有新的纹理对象被绑定。

		glTexImage2D(GL_TEXTURE_2D, 0, 4, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 
			0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TextureImage[0]->data); // 设置纹理的类型、长、宽等参数，将位图中的RGB数据拷贝到纹理中

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置2D纹理的属性，当纹理缩小（GL_TEXTURE_MIN_FILTER）时，采用双线性插值
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置2D纹理的属性，当纹理放大（GL_TEXTURE_MAG_FILTER）时，采用双线性插值
	}

	// 释放位图
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

	glEnable(GL_TEXTURE_2D);							// 开启纹理贴图（纹理映射）
	glShadeModel(GL_SMOOTH);							// 开启smooth绘制模式
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// 指定清空颜色缓冲区时，所用的颜色值
	glClearDepth(1.0f);									// 指定清空深度缓冲区时，所用的深度值
	glEnable(GL_DEPTH_TEST);							// 开启深度测试
	glDepthFunc(GL_LEQUAL);								// 指定深度缓冲区的比较函数
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 
	return TRUE;	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清空颜色和深度缓冲区，分别使用glClearColor和glClearDepth设定的值
	glLoadIdentity();									
	glTranslatef(0.0f,0.0f,-5.0f);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	// 背面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	// 上面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	// 下面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	// 左面
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
