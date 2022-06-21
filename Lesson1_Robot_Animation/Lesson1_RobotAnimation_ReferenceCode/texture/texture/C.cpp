#include "H.h"
//�����˲���ϵ������
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient_color[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.5 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
//������������ϵ������
GLfloat Bmat_ambient[] = { 0.247250, 0.224500, 0.064500, 1.000000 };
GLfloat Bmat_diffuse[] = { 0.346150, 0.314300, 0.090300, 1.000000 };
GLfloat Bmat_specular[] = { 0.797357, 0.723991, 0.208006, 1.000000 };
GLfloat Bmat_shininess[] = { 83.199997 }; //����RGBA����ָ������ֵ��0��128��Χ��
//��������
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat position[] = { -4, 7, 10 ,1.0};
GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat local_view[] = { 0.0 };

bool blend = false;  //�Ƿ���

int init(void)
{
	/*
	if (!LoadGLTextures())  //Jump To Texture Loading Routine
	{
	return FALSE;  //If Texture Didn't Load Return FALSE
	}*/
	//��������ͼƬ
	LoadT8("Data/Ground.bmp", g_cactus[0]);
	LoadT8("Data/Cloud.bmp", g_cactus[1]);
	LoadT8("Data/Fire.bmp", g_cactus[2]);
	LoadT8("Data/Metal.bmp", g_cactus[3]);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);  //�������ռ���
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);//������ɫ����!!
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);  //������Ӱƽ��
	glClearColor(0.3, 0.4, 0.5, 0.0);
	glClearDepth(1.0f);  //Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);  //������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //������ϸ��͸������
	/*
	void glHint(GLenum target,GLenum mode);ָ���ض���ʵ�ֵ���ʾ��
	target����ָʾҪ������Ϊ�ķ��ų��������µķ��ų����뽨������һ�𱻽��ܣ�
	GL_FOG_HINT��ָʾ������׼ȷ�ԣ���OpenGLʵ�ֲ���Ч��֧��ÿ��������㣬��ʾGL_DONT_CARE��GL_FASTEST�ᵼ��ÿ��������Ч�����㣻
	GL_LINE_SMOOTH_HINT��ָʾ�Ǿ������еĲ�����������Ӧ����һ���ϴ��ɸѡ������������ʾGL_NICEST���ܻᵼ�����ɹ�����դ�񻯣�����������Ƭ��
	GL_PERSPECTIVE_CORRECTION_HINT����ʾ��ɫ����������岹�����������Ƕȸ���������ֵ����Ч��֧����OpenGLʵ�֣���ʾGL_DONT_CARE��GL_FASTEST���Ե��¼����Բ�ֵ����ɫ��/���������ꣻ
	GL_POINT_SMOOTH_HINT����ʾ�Ǿ��������������������Ӧ����һ���ϴ��ɸѡ������������ʾGL_NICEST���ܻᵼ�����ɹ�����դ�񻯣�����������Ƭ��
	GL_POLYGON_SMOOTH_HINT��ָʾ�Ǿ���������εĲ�����������Ӧ����һ���ϴ��ɸѡ������������ʾGL_NICEST���ܻᵼ�����ɹ�����դ�񻯣�����������Ƭ��
	mode�������ų���ָʾ�������Ϊ���������·��ų�����
	GL_FASTEST��Ӧѡ������Ч��ѡ�
	GL_NICEST��Ӧѡ������ȷ�����������ѡ�
	GL_DONT_CARE���ͻ���û��һ����ѡ�
	�������´���������������
	GL_INVALID_ENUM��Ŀ���ģʽ�������ܵ�ֵ��
	GL_INVALID_OPERATION�������ڵ���glBegin��glEnd����Ӧ����֮�䱻���øú�����
	*/

	glMatrixMode(GL_PROJECTION);  //Set projection parameters.
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);		//����Դ����alphaͨ��ֵ�İ�͸����Ϻ���

	return TRUE;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();  //Reset The View
	if (sight)  //�ӽ�1
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
	if (!sight)  //�ӽ�2
		gluLookAt(3, 20, 0, -5, 3, 0, 0, 1, 0);
	//����
	glPushMatrix();
	glRotatef(Ror, 0, -1, 0);  //������ֵ�׶����ת
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
	case '1':  //���ּ�1��ѡ���ӽ�1
		sight = true;
		break;
	case '2':  //���ּ�2��ѡ���ӽ�2
		sight = false;
		break;

	case 'b':
	{
				blend = !blend;  //�л����ѡ��� TRUE / FALSE
				if (blend)
					glEnable(GL_BLEND);  //�򿪻��
				else
					glDisable(GL_BLEND);  //�رջ��
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
	printf("���ּ�1��2���л��ӽ�\n");
	printf("�ڵ������ӽ�1�£��������Ҽ������ӽ�����\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);  //���ڴ�СΪ720*560.
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Whatever");  //������ʾ����
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(Idel);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKey);
	glutTimerFunc(33, timerFunc, 1);  //���ö�ʱ���ص�����
	glutMainLoop();
	return 0;
}