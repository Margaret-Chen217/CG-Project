#include "H.h"
//机器人材质系数设置
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient_color[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.5 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
//灯塔金属材质系数设置
GLfloat Bmat_ambient[] = { 0.247250, 0.224500, 0.064500, 1.000000 };
GLfloat Bmat_diffuse[] = { 0.346150, 0.314300, 0.090300, 1.000000 };
GLfloat Bmat_specular[] = { 0.797357, 0.723991, 0.208006, 1.000000 };
GLfloat Bmat_shininess[] = { 83.199997 }; //材质RGBA镜面指数，数值在0～128范围内
//光照设置
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat position[] = { -4, 7, 10 ,1.0};
GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat local_view[] = { 0.0 };

bool blend = false;  //是否混合

int init(void)
{
	/*
	if (!LoadGLTextures())  //Jump To Texture Loading Routine
	{
	return FALSE;  //If Texture Didn't Load Return FALSE
	}*/
	//加载纹理图片
	LoadT8("Data/Ground.bmp", g_cactus[0]);
	LoadT8("Data/Cloud.bmp", g_cactus[1]);
	LoadT8("Data/Fire.bmp", g_cactus[2]);
	LoadT8("Data/Metal.bmp", g_cactus[3]);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);  //开启光照计算
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);//开启颜色跟踪!!
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);  //启用阴影平滑
	glClearColor(0.3, 0.4, 0.5, 0.0);
	glClearDepth(1.0f);  //Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);  //所做深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //真正精细的透视修正
	/*
	void glHint(GLenum target,GLenum mode);指定特定于实现的提示；
	target——指示要控制行为的符号常量，以下的符号常量与建议语义一起被接受：
	GL_FOG_HINT—指示雾计算的准确性，若OpenGL实现不有效地支持每像素雾计算，提示GL_DONT_CARE或GL_FASTEST会导致每个顶点雾化效果计算；
	GL_LINE_SMOOTH_HINT—指示是锯消除行的采样质量，若应用了一个较大的筛选器函数，则将提示GL_NICEST可能会导致生成过程中栅格化，更多像素碎片；
	GL_PERSPECTIVE_CORRECTION_HINT—表示颜色和纹理坐标插补的质量，若角度更正参数插值不有效地支持由OpenGL实现，提示GL_DONT_CARE或GL_FASTEST可以导致简单线性插值的颜色和/或纹理坐标；
	GL_POINT_SMOOTH_HINT—表示是锯消除点采样的质量，若应用了一个较大的筛选器函数，则将提示GL_NICEST可能会导致生成过程中栅格化，更多像素碎片；
	GL_POLYGON_SMOOTH_HINT—指示是锯消除多边形的采样质量，若应用了一个较大的筛选器函数，则将提示GL_NICEST可能会导致生成过程中栅格化，更多像素碎片。
	mode——符号常量指示所需的行为，接受以下符号常量：
	GL_FASTEST—应选择最有效的选项；
	GL_NICEST—应选择最正确或最高质量的选项；
	GL_DONT_CARE—客户端没有一个首选项。
	返回以下错误代码和其条件：
	GL_INVALID_ENUM，目标或模式不被接受的值；
	GL_INVALID_OPERATION，不能在调用glBegin和glEnd的相应调用之间被调用该函数。
	*/

	glMatrixMode(GL_PROJECTION);  //Set projection parameters.
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);		//基于源象素alpha通道值的半透明混合函数

	return TRUE;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  //Reset The View
	if (sight)  //视角1
	{
		gluLookAt(ex, ey, ez, cx, cy, cz, 0, 1, 0);
		if (blend)
		{
			glColor4f(1, 0, 0,0.2);
			glBegin(GL_POLYGON);
			glVertex2f(-100, 100);
			glVertex2f(-100, -100);
			glVertex2f(100, -100);
			glVertex2f(100, 100);
			glEnd();
		}
		else
			glColor4f(1, 1, 1,0);
	}
	if (!sight)  //视角2
		gluLookAt(3, 20, 0, -5, 3, 0, 0, 1, 0);
	//光照
	glPushMatrix();
	glRotatef(Ror, 0, -1, 0);  //代表灯罩的锥形旋转
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(-2.4, 0, -1);
	glRotatef(90, 0, 1, 0);
	DrawRobot();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(2.4, 0, 1);
	glRotatef(90, 0, -1, 0);
	DrawRobot();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, Bmat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Bmat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Bmat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, Bmat_shininess);
	DrawBeacon();
	glPopMatrix();
	
	DrawGround();

	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case '1':  //数字键1，选择视角1
		sight = true;
		break;
	case '2':  //数字键2，选择视角2
		sight = false;
		break;

	case 'b':
	{
				blend = !blend;  //切换混合选项的 TRUE / FALSE
				if (blend)
					glEnable(GL_BLEND);  //打开混合
				else
					glDisable(GL_BLEND);  //关闭混合
	}break;
	default:
		break;
	}
}

void SpecialKey(int key, int x, int y)
{
	float disEye2Center = sqrt((ex - cx)*(ex - cx) + (ey - cy)*(ey - cy) + (ez - cz)*(ez - cz));
	if (key == GLUT_KEY_LEFT)
	{
		angleS -= 2.0;

	}
	if (key == GLUT_KEY_RIGHT)
	{
		angleS += 2.0;

	}
	rad = float(PI*angleS / 180.0f);
	if (key == GLUT_KEY_UP)
	{

		ez += 0.2*sin(rad);
		ex += 0.2*cos(rad);
	}
	if (key == GLUT_KEY_DOWN)
	{
		ez -= 0.2*sin(rad);
		ex -= 0.2*cos(rad);
	}

	if (key == GLUT_KEY_PAGE_UP)
	{
		yo += 1.0f;
	}
	if (key == GLUT_KEY_PAGE_DOWN)
	{
		yo -= 1.0f;
	}
	cx = float(ex + disEye2Center*cos(rad));
	cy = ey + yo;
	cz = float(ez + disEye2Center*sin(rad));
}

int main(int argc, char** argv)
{
	printf("数字键1、2，切换视角\n");
	printf("在第三方视角1下，上下左右键控制视角漫游\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);  //窗口大小为720*560.
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Whatever");  //创建显示窗口
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(Idel);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKey);
	glutTimerFunc(33, timerFunc, 1);  //设置定时器回调函数
	glutMainLoop();
	return 0;
}