#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ======== Windows ======
#include <GL/glut.h>
// ====== Mac OS X =======
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
// =======================
#define PI (3.14159)
#define PI2 (PI/2)
#define dt  (10/(double)10000) // interval of time
#define X (50)
#define Y (250)
#define L (1)
#define Z (0.5) //height of object

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };
enum COLOR { WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY, BLACK };
GLfloat color[][4] = {
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 1.0, 1.0 },
		{ 0.0, 1.0, 1.0, 1.0 },
		{ 0.7, 0.7, 0.7, 1.0 },
		{ 0.0, 0.0, 0.0, 1.0 }
	};
double xjiki = 0, yjiki = 0; // position of tank
double xteki = X, yteki = Y;
double l = 0.3; // length
double jiki_angle = PI2; // angle of direction
double xjiki_check = 0, yjiki_check = 0; // variables for checking collision and range of tanc's position
double xpro = 0, ypro = 0;// position of projectile
double xpro_check = 0, ypro_check = 0; // variables for checking collision and range of projectile's position
int flagpro = 0;  // this flag decides whether to draw a projectile
int flagproend = 1; //this flag decides whether to end projfunc
double tpro = 0; // angle of projectile
int mySpecialValue = 0;
double kabeList[][3] = {
		{ 0.0, 2.0, 0.0 },
		{ 4.0, 4.0, 0.0 },
		{ 2.0, 6.0, 0.0 },
		{ 0.0, 10.0, 0.0 },
		{ 4.0, 13.0, 0.0 },
		{ 3.0, 14.0, 0.0 },
		{ 2.0, 15.0, 0.0 },
		{ 1.0, 16.0, 0.0 },
		{ 3.0, 19.0, 0.0 },
		{ 2.0, 20.0, 0.0 },
		{ 1.0, 21.0, 0.0 },
		{ 0.0, 22.0, 0.0 } };
int kabeIndex = 12;
double v = 0;

void calcNormal(GLdouble v0[3], GLdouble v1[3], GLdouble v2[3], GLdouble n[3])
{
	GLdouble v2v[2][3];
	GLdouble vt[3];
	double abs;
	int i;
	for (i = 0; i < 3; i++)
	{
		v2v[0][i] = v1[i] - v0[i];
		v2v[1][i] = v2[i] - v0[i];
	}
	vt[0] = v2v[0][1] * v2v[1][2] - v2v[0][2] * v2v[1][1];
	vt[1] = v2v[0][2] * v2v[1][0] - v2v[0][0] * v2v[1][2];
	vt[2] = v2v[0][0] * v2v[1][1] - v2v[0][1] * v2v[1][0];
	abs = sqrt(vt[0] * vt[0] + vt[1] * vt[1] + vt[2] * vt[2]);
	for (i = 0; i < 3; i++)
		n[i] = vt[i] / abs;
}
/* drawXXX
------------------------------------*/
void drawGround()
{
	int i, j;
	GLdouble normal[3] = { 0.0, 0.0, 1.0 };

	glPushMatrix();

	glNormal3dv(normal);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[YELLOW]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glBegin(GL_QUADS);
	glVertex3d(-0.5*L, -0.5*L, 0.0); // start
	glVertex3d((X - 0.5)*L, -0.5*L, 0.0);
	glVertex3d((X - 0.5)*L, 0.5*L, 0.0);
	glVertex3d(-0.5*L, 0.5*L, 0.0);

	glVertex3d(-0.5*L, (Y - 0.5)*L, 0.0); // goal
	glVertex3d((X - 0.5)*L, (Y - 0.5)*L, 0.0);
	glVertex3d((X - 0.5)*L, (Y + 0.5)*L, 0.0);
	glVertex3d(-0.5*L, (Y + 0.5)*L, 0.0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glBegin(GL_QUADS);
	for (i = 1; i < Y; i++)
		for (j = 0; j < X; j++)
		{
		GLdouble v[4][3];
		if (!((i^j) & 1))continue;
		v[0][0] = (j + 0 - 0.5)*L;
		v[0][1] = (i + 0 - 0.5)*L;
		v[0][2] = 0;
		v[1][0] = (j + 1 - 0.5)*L;
		v[1][1] = (i + 0 - 0.5)*L;
		v[1][2] = 0;
		v[2][0] = (j + 1 - 0.5)*L;
		v[2][1] = (i + 1 - 0.5)*L;
		v[2][2] = 0;
		v[3][0] = (j + 0 - 0.5)*L;
		v[3][1] = (i + 1 - 0.5)*L;
		v[3][2] = 0;
		glVertex3dv(v[0]);
		glVertex3dv(v[1]);
		glVertex3dv(v[2]);
		glVertex3dv(v[3]);
		}
	glEnd();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glBegin(GL_QUADS);
	for (i = 0; i < Y; i++)
		for (j = 0; j < X; j++)
		{
		GLdouble v[4][3];
		if ((i^j) & 1)continue;
		v[0][0] = (j + 0 - 0.5)*L;
		v[0][1] = (i + 0 - 0.5)*L;
		v[0][2] = 0;
		v[1][0] = (j + 1 - 0.5)*L;
		v[1][1] = (i + 0 - 0.5)*L;
		v[1][2] = 0;
		v[2][0] = (j + 1 - 0.5)*L;
		v[2][1] = (i + 1 - 0.5)*L;
		v[2][2] = 0;
		v[3][0] = (j + 0 - 0.5)*L;
		v[3][1] = (i + 1 - 0.5)*L;
		v[3][2] = 0;
		glVertex3dv(v[0]);
		glVertex3dv(v[1]);
		glVertex3dv(v[2]);
		glVertex3dv(v[3]);
		}
	glEnd();

	glPopMatrix();
}

void drawJiki(void)
{
	glPushMatrix();

	glTranslatef(xjiki, yjiki, Z);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glutSolidCube(1);
	glPopMatrix();
}

void drawkabe(void)
{
	int i;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	for (i = 0; i < kabeIndex; i++)
	{
		glPushMatrix();
		glTranslatef(kabeList[i][0], kabeList[i][1], kabeList[i][2]);
		glutSolidCone(0.5, 1, 30, 30);
		glPopMatrix();
	}
	glPopMatrix();
}

void drawproj()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glTranslatef(xpro, ypro, 0.5);
	glutSolidSphere(0.5, 30, 30);
	glPopMatrix();
}

void drawteki()
{
	glPushMatrix();

	glTranslatef(xteki, yteki, Z);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glutSolidCube(1);
	glPopMatrix();
}

void aim(void)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3d(1.0,0,0);
	glVertex3d(xjiki,yjiki,Z);
	double aim_x = xjiki + 50*cos(jiki_angle);
	double aim_y = yjiki + 50*sin(jiki_angle);
	glVertex3d(aim_x,aim_y,Z);
	glEnd();
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();
	drawJiki();
	drawkabe();
	if(flagpro) drawproj();
	aim();
	glPopMatrix();
	glutSwapBuffers();
}

int collision() // collision check for tank
{
	int i;
	double MARGIN = 0.05;
	for (i = 0; i < kabeIndex; i++)
	{
		if ((kabeList[i][0] - xjiki_check <1 - MARGIN) && (kabeList[i][0] - xjiki_check >-1 + MARGIN)
			&& (kabeList[i][1] - yjiki_check <1 - MARGIN) && (kabeList[i][1] - yjiki_check >-1 + MARGIN))
		{
			printf("(%.02f,%.02f):(%.02f,%.02f)\n", xjiki, yjiki, kabeList[i][0], kabeList[i][1]);
			return 0;
		}
	}
	return 1;
}

int collision2() // collision check for projectile
{
	int i;
	double MARGIN = 0.3;
	for (i = 0; i < kabeIndex; i++)
	{
		if ((kabeList[i][0] - xpro_check <1 - MARGIN) && (kabeList[i][0] - xpro_check >-1 + MARGIN)
			&& (kabeList[i][1] - ypro_check <1 - MARGIN) && (kabeList[i][1] - ypro_check >-1 + MARGIN))
		{
			printf("(%.02f,%.02f):(%.02f,%.02f)\n", xteki, yteki, kabeList[i][0], kabeList[i][1]);
			return 1;
		}
	}
	return 0;
}

void jikiTimerFunc(int value)
{
	double MARGIN = 0.05;
	if (mySpecialValue & (1 << 0))
	{
		xjiki_check = l*cos(jiki_angle) + xjiki;
		yjiki_check = l*sin(jiki_angle) + yjiki;
		if (collision() && (Y*L > yjiki_check - MARGIN) && (0 * L < xjiki_check + MARGIN)
			&& ((X - 1)*L > xjiki_check - MARGIN) && (0 * L < yjiki_check + MARGIN))
		{
			xjiki = xjiki_check;
			yjiki = yjiki_check;
		}
	}
	if (mySpecialValue & (1 << 1))
	{
		jiki_angle += 0.025;
	}
	if (mySpecialValue & (1 << 2))
	{
		jiki_angle -= 0.025;
	}
	if (mySpecialValue & (1 << 3))
	{
		xjiki_check = xjiki - l*cos(jiki_angle);
		yjiki_check = yjiki - l*sin(jiki_angle);
		if ( collision() && (Y*L > yjiki_check - MARGIN) && (0 * L < xjiki_check + MARGIN)
			&& ((X - 1)*L > xjiki_check - MARGIN) && (0 * L < yjiki_check + MARGIN))
		{
			xjiki = xjiki_check;
			yjiki = yjiki_check;
		}
	}
	glLoadIdentity();
	gluLookAt(-10.0*cos(jiki_angle) + xjiki, -10.0*sin(jiki_angle) + yjiki, 4.0, 0.0 + xjiki, 0.0 + yjiki, 1.5, 0.0, 0.0, 1.0);

	glutTimerFunc(10, jikiTimerFunc, 0);
}
void tekiTimerFunc(int value)
{
	double MARGIN = 0.05;



}

void projfunc1(int value)
{
	double MARGIN = 0.25;
	if (flagproend) {
		xpro_check = xpro + cos(tpro)*l;
		ypro_check = ypro + sin(tpro)*l;
		if (collision2())
		{
			flagpro = 0;
			// TODO: add processing of delete of kabe object
		}
		else if ((Y*L < ypro_check - MARGIN) || (0 * L > xpro_check + MARGIN)
			|| ((X - 1)*L < xpro_check - MARGIN) || (0 * L > ypro_check + MARGIN)) flagpro = 0;
		else
		{
			xpro = xpro_check;
			ypro = ypro_check;
			glutTimerFunc(10, projfunc1, 0);
		}
	}
}

void projfunc2(int value)
{
	double MARGIN = 0.25;
	if (flagproend==0) {
		xpro_check = xpro + cos(tpro)*l;
		ypro_check = ypro + sin(tpro)*l;
		if (collision2())
		{
			flagpro = 0;
			// TODO: add processing of delete of kabe object
		}
		else if ((Y*L < ypro_check - MARGIN) || (0 * L > xpro_check + MARGIN)
			|| ((X - 1)*L < xpro_check - MARGIN) || (0 * L > ypro_check + MARGIN)) flagpro = 0;
		else
		{
			xpro = xpro_check;
			ypro = ypro_check;
			glutTimerFunc(10, projfunc2, 0);
		}
	}
}

void myKeyboardFunc(unsigned char key, int xx, int yy)
{
	switch (key)
	{
	case ' ':
		flagpro = 1;
		tpro = jiki_angle;
		xpro = xjiki, ypro = yjiki;
		if (flagproend)
		{
			flagproend = 0;
			projfunc2(0);
		}
		else
		{
			flagproend = 1;
			projfunc1(0);
		}
		break;
	}
}
void mySpcialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		mySpecialValue |= 1 << 0;
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue |= 1 << 1;
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue |= 1 << 2;
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue |= 1 << 3;
		break;
	default:
		break;
	}
}
void mySpcialUpFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		mySpecialValue &= ~(1 << 0);
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue &= ~(1 << 1);
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue &= ~(1 << 2);
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue &= ~(1 << 3);
		break;
	default:
		break;
	}

}

void idle(void)
{
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpcialFunc);
	glutSpecialUpFunc(mySpcialUpFunc);

	glutIdleFunc(idle);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, .1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -10.0, 4.0, 0.0, 0.0, 1.5, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
	jikiTimerFunc(0);
	tekiTimerFunc(0);

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(650, 650);
	glutCreateWindow("C Dev");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
