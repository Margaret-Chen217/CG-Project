#include <math.h>
#include "windows.h"
#include <glut.h>

static int shoulder = -30, elbow = 60,
	finger1 = 65,finger2 = -55,finger3 = -50,finger4 = -45,finger5 = -40,
	finger11 = -50,finger21 = 45,finger31 = 45,finger41 = 45,finger51 = 45;

static float angle = 0.0;
static bool bSphere = false;

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

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   glLoadIdentity ();    

   GLfloat x = 6.0*sin(angle);
   GLfloat z = 6.0*cos(angle);

   gluLookAt (x, 6.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   

   glPushMatrix();

   //移动到上臂位置
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   testposition(); // 肩关节位置
   glTranslatef (1.0, 0.0, 0.0);
   testposition(); // 上臂中心位置

   //绘制上臂
   glPushMatrix();
   glScalef (2.0, 1.0, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //移动到前臂位置
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   testposition(); // 肘关节位置
   glTranslatef (1.0, 0.0, 0.0);
   testposition(); // 前臂中心位置

   //绘制前臂
   glPushMatrix();
   glScalef (2.0, 1.0, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   //画第一根手指 
   glPushMatrix();
   glTranslatef (1.0, 0.4, -0.2);
   glRotatef ((GLfloat) finger1, 0.0, 0.0, 1.0); // 指跟位置
   testposition(); //
   glTranslatef (0.25, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.25, 0.0, 0.0);
   glRotatef ((GLfloat) finger11, 0.0, 0.0, 1.0); // 二节指跟位置
   testposition(); //
   glTranslatef (0.25, 0.0, 0.0);
   testposition(); //
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();
   
   
   //画第二根指 
   glPushMatrix();
   glTranslatef (1.0, -0.4, 0.3);
   glRotatef ((GLfloat) finger2, 0.0, 0.0, 1.0);// 指跟位置
   testposition(); //
   glTranslatef (0.25, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.25, 0.0, 0.0);
   glRotatef ((GLfloat) finger21, 0.0, 0.0, 1.0);// 二节指跟位置
   testposition(); //
   glTranslatef (0.25, 0.0, 0.0);
   testposition(); //
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();

   //画第三根指
   glPushMatrix();
   glTranslatef (1.0, -0.4, 0.1);
   glRotatef ((GLfloat) finger3, 0.0, 0.0, 1.0);// 指跟位置
   testposition(); //
   glTranslatef (0.25, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.25, 0.0, 0.0);
   glRotatef ((GLfloat) finger31, 0.0, 0.0, 1.0);// 二节指跟位置
   testposition(); //
   glTranslatef (0.25, 0.0, 0.0);
   testposition(); //
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();

   //画第四根指 
   glPushMatrix();
   glTranslatef (1.0, -0.4, -0.1);
   glRotatef ((GLfloat) finger4, 0.0, 0.0, 1.0);// 指跟位置
   testposition();//
   glTranslatef (0.25, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.25, 0.0, 0.0);
   glRotatef ((GLfloat) finger41, 0.0, 0.0, 1.0);// 二节指跟位置
   testposition();//
   glTranslatef (0.25, 0.0, 0.0);
   testposition();//
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();

   //画第五根指
   glPushMatrix();
   glTranslatef (1.0, -0.4, -0.3);
   glRotatef ((GLfloat) finger5, 0.0, 0.0, 1.0);// 指跟位置
   testposition();//
   glTranslatef (0.25, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.25, 0.0, 0.0);
   glRotatef ((GLfloat) finger51, 0.0, 0.0, 1.0);// 二节指跟位置
   testposition();//
   glTranslatef (0.25, 0.0, 0.0);
   testposition();//
   glPushMatrix();
   glScalef (0.5, 0.2, 0.2);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();
   //

   //画圆柱
   if(bSphere)
   {
		glTranslatef(1.3,0.0,0.0);
		glutWireSphere(0.7,20,20);
   }

   glPopMatrix();

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);    
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();
//   glTranslatef (0.0, 0.0, -5.0);
}

#define judge(n);  if(n> 90) n = 90;
#define judgeN(n); if(n<-90) n = -90;
#define judge2(n);  if(n> 0) n = 0;
#define judgeE(n);  if(n> 180) n = 180;
#define judgeNE(n); if(n< 0) n = 0;

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':   // 肩关节转动
         shoulder = (shoulder + 5) % 360;
		 judge(shoulder); 
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
		 judgeN(shoulder);
         glutPostRedisplay();
         break;
      case 'e':  // 肘关节转动
         elbow = (elbow + 5) % 360;
		 judgeE(elbow);
         glutPostRedisplay();
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
		 judgeNE(elbow);
         glutPostRedisplay();
         break;
	  case 'f':  
         finger1 = (finger1 + 5) % 360;
		 judge(finger1);
         glutPostRedisplay();
         break;
      case 'F':
         finger1 = (finger1 - 5) % 360;
		 judgeN(finger1);
         glutPostRedisplay();
         break;

	  case 'g':  
         finger11 = (finger11 + 5) % 360;
		 judge2(finger11);
         glutPostRedisplay();
         break;
      case 'G':
         finger11 = (finger11 - 5) % 360;
		 judgeN(finger11);
         glutPostRedisplay();
         break;

     case 'v':  // 转动视角
         angle=(((int)(angle*57.3+5.0))%360)*0.01745;
		 glutPostRedisplay();
         break;
      case 'V':
		 angle=(((int)(angle*57.3-5.0))%360)*0.01745;
         glutPostRedisplay();
         break;

	 case 'h':  
         finger2 = (finger2 + 5) % 360;
		 judge(finger2);
         glutPostRedisplay();
         break;
      case 'H':
         finger2 = (finger2 - 5) % 360;
		 judgeN(finger2);
         glutPostRedisplay();
         break;
	  
	  case 'j': 
         finger21 = (finger21 + 5) % 360;
		 judgeE(finger21);
         glutPostRedisplay();
         break;
      case 'J':
         finger21 = (finger21 - 5) % 360;
		 judgeNE(finger21);
         glutPostRedisplay();
         break;

	  case 'k':  /*  e key rotates at elbow  */
         finger3 = (finger3 + 5) % 360;
		 judge(finger3);
         glutPostRedisplay();
         break;
      case 'K':
         finger3 = (finger3 - 5) % 360;
		 judgeN(finger3);
         glutPostRedisplay();
         break;

	  case 'l':  /*  e key rotates at elbow  */
         finger31 = (finger31 + 5) % 360;
		 judgeE(finger31);
         glutPostRedisplay();
         break;
      case 'L':
         finger31 = (finger31 - 5) % 360;
		 judgeNE(finger31);
         glutPostRedisplay();
         break;

	  case 'o':  /*  e key rotates at elbow  */
         finger4 = (finger4 + 5) % 360;
		 judge(finger4);
         glutPostRedisplay();
         break;
      case 'O':
         finger4 = (finger4 - 5) % 360;
		 judgeN(finger4);
         glutPostRedisplay();
         break;

	  case 'i':  /*  e key rotates at elbow  */
         finger41 = (finger41 + 5) % 360;
		 judgeE(finger41);
         glutPostRedisplay();
         break;
      case 'I':
         finger41 = (finger41 - 5) % 360;
		 judgeNE(finger41);
         glutPostRedisplay();
         break;

	  case 'u':  /*  e key rotates at elbow  */
         finger5 = (finger5 + 5) % 360;
		 judge(finger5);
         glutPostRedisplay();
         break;
      case 'U':
         finger5 = (finger5 - 5) % 360;
		 judgeN(finger5);
         glutPostRedisplay();
         break;

	  case 'y':  /*  e key rotates at elbow  */
         finger51 = (finger51 + 5) % 360;
		 judgeE(finger51);
         glutPostRedisplay();
         break;
      case 'Y':
         finger51 = (finger51 - 5) % 360;
		 judgeNE(finger51);
         glutPostRedisplay();
         break;
	   case 'q':
         bSphere = !bSphere;
         glutPostRedisplay();
         break;
	  case 'r':
         shoulder = 0;
		 elbow = 0;
		 finger1 =0;
		 finger2=0;
		 finger3=0;
		 finger4=0;
		 finger5=0;
		 finger11=0;
		 finger21=0;
		 finger31=0;
		 finger41=0;
		 finger51=0;
		 angle = 0.0;
         glutPostRedisplay();//标记当前窗口需要重新绘制
         break;
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
   glutMainLoop();
   return 0;
}
