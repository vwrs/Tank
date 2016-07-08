#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// ======== Windows ======
#include <GL/glut.h>
// ====== Mac OS X =======
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
// =======================
#include "tank.h"
#define PI (3.14159)
#define PI2 (PI/2)
#define dt  (10/(double)10000) // interval of time
#define X (50)  //range of the field
#define X2 (X/2)
#define Y (50) // range of the field
#define Y2 (Y/2)
#define L (1)
#define z (0.5) // height of object

/*
 Global variables
---------------------------------------------------*/
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
Tank jiki = {0};
Tank teki[5] = {0};
double xteki = X2, yteki = Y2;
double xteki_check, yteki_check;
double tteki;
double l = 0.1;   // length
double xjiki_check = 0, yjiki_check = 0; // variables for checking collision and range of tanc's position
double xpro_check = 0, ypro_check = 0; // variables for checking collision and range of projectile's position
int flagpro = 0;  // this flag decides whether to draw a projectile
int flagproend = 1; //this flag decides whether to end projfunc
int flagteki = 1;
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
/*
  drawXXX
-----------------------------------------*/
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

	glTranslatef(jiki.x, jiki.y, z);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glutSolidCube(jiki.w);
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
	glTranslatef(jiki.tama.x, jiki.tama.y, z);
	glutSolidSphere(0.5, 30, 30);
	glPopMatrix();
}

void drawteki()
{
	glPushMatrix();
  // TODO: xteki -> teki.x[i]
	glTranslatef(xteki, yteki, z);

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
	glVertex3d(jiki.x,jiki.y,z);
	double aim_x = jiki.x + 50*cos(jiki.t);
	double aim_y = jiki.y + 50*sin(jiki.t);
	glVertex3d(aim_x,aim_y,z);
	glEnd();
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();
	drawJiki();
	drawteki();
	drawkabe();
	if(flagpro) drawproj();
	aim();
	glPopMatrix();
	glutSwapBuffers();
}
// TODO: unify collision check func
int collision() // collision check for tank
{
	int i;
	double MARGIN = 0.05;
	for (i = 0; i < kabeIndex; i++)
	{
		if ((kabeList[i][0] - xjiki_check <1 - MARGIN) && (kabeList[i][0] - xjiki_check >-1 + MARGIN)
			&& (kabeList[i][1] - yjiki_check <1 - MARGIN) && (kabeList[i][1] - yjiki_check >-1 + MARGIN))
		{
			printf("(%.02f,%.02f):(%.02f,%.02f)\n", jiki.x, jiki.y, kabeList[i][0], kabeList[i][1]);
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

int collision3()  // collision check for teki
{
	int i;
	double MARGIN = 0.05;
	for (i = 0; i < kabeIndex; i++)
	{
		if ((kabeList[i][0] - xjiki_check <1 - MARGIN) && (kabeList[i][0] - xjiki_check >-1 + MARGIN)
			&& (kabeList[i][1] - yjiki_check <1 - MARGIN) && (kabeList[i][1] - yjiki_check >-1 + MARGIN))
		{
			printf("(%.02f,%.02f):(%.02f,%.02f)\n", jiki.x, jiki.y, kabeList[i][0], kabeList[i][1]);
			return 0;
		}
	}
	return 1;
}
/*
 TimerFunc
-----------------------------------*/
void jikiTimerFunc(int value)
{
	double MARGIN = 0.05;
	if (mySpecialValue & (1 << 0))
	{
		xjiki_check = jiki.x + jiki.v*cos(jiki.t);
		yjiki_check = jiki.y + jiki.v*sin(jiki.t);
		if (collision() && (Y*L > yjiki_check - MARGIN) && (0 * L < xjiki_check + MARGIN)
			&& ((X - 1)*L > xjiki_check - MARGIN) && (0 * L < yjiki_check + MARGIN))
		{
			jiki.x = xjiki_check;
			jiki.y = yjiki_check;
		}
	}
	if (mySpecialValue & (1 << 1))
	{
		jiki.t += jiki.v_turn;
	}
	if (mySpecialValue & (1 << 2))
	{
		jiki.t -= jiki.v_turn;
	}
	if (mySpecialValue & (1 << 3))
	{
		xjiki_check = jiki.x - jiki.v*cos(jiki.t);
		yjiki_check = jiki.y - jiki.v*sin(jiki.t);
		if (collision() && (Y*L > yjiki_check - MARGIN) && (0 * L < xjiki_check + MARGIN)
			&& ((X - 1)*L > xjiki_check - MARGIN) && (0 * L < yjiki_check + MARGIN))
		{
			jiki.x = xjiki_check;
			jiki.y = yjiki_check;
		}
	}
	glLoadIdentity();
	gluLookAt(-10.0*cos(jiki.t) + jiki.x, -10.0*sin(jiki.t) + jiki.y, 4.0, 0.0 + jiki.x, 0.0 + jiki.y, 1.5, 0.0, 0.0, 1.0);

	glutTimerFunc(10, jikiTimerFunc, 0);
}

void tekiTimerFunc(int value)
{
	double MARGIN = 0.05;
	if ((xteki - jiki.x)*(xteki - jiki.x) + (yteki - jiki.y)*(yteki - jiki.y)>600)
	{
		if (flagteki) tteki = rand() % 100;
		xteki_check = xteki + l*cos(tteki) * 3;
		yteki_check = yteki + l*sin(tteki) * 3;
		if ((collision3()) && (Y*L > yteki_check - MARGIN) && (0 * L < xteki_check + MARGIN)
			&& ((X - 1)*L > xteki_check - MARGIN) && (0 * L < yteki_check + MARGIN))
		{
			xteki = xteki_check;
			yteki = yteki_check;
			flagteki = 0;
		}
		else flagteki = 1;
	}
	else
	{
		tteki = rand() % 100;
		xteki_check = xteki + l*cos(tteki) * 3;
		yteki_check = yteki + l*sin(tteki) * 3;
		if ((collision3()) && (Y*L > yteki_check - MARGIN) && (0 * L < xteki_check + MARGIN)
			&& ((X - 1)*L > xteki_check - MARGIN) && (0 * L < yteki_check + MARGIN))
		{
			xteki = xteki_check;
			yteki = yteki_check;
			flagteki = 0;
		}

	}

	glutTimerFunc(10, tekiTimerFunc, 0);
}
// TODO: unify projfunc1,2
void projfunc1(int value)
{
	double MARGIN = 0.25;
	if (flagproend) {
		xpro_check = jiki.tama.x + cos(jiki.tama.t)*jiki.tama.v;
		ypro_check = jiki.tama.y + sin(jiki.tama.t)*jiki.tama.v;
		if (collision2())
		{
			flagpro = 0;
			//TODO: add processing of delete of kabe object
		}
		else if ((Y*L < ypro_check - MARGIN) || (0 * L > xpro_check + MARGIN)
			|| ((X - 1)*L < xpro_check - MARGIN) || (0 * L > ypro_check + MARGIN)) flagpro = 0;
		else
		{
			jiki.tama.x = xpro_check;
			jiki.tama.y = ypro_check;
			glutTimerFunc(10, projfunc1, 0);
		}
	}
}

void projfunc2(int value)
{
	double MARGIN = 0.25;
	if (flagproend==0) {
		xpro_check = jiki.tama.x + cos(jiki.tama.t)*jiki.tama.v;
		ypro_check = jiki.tama.y + sin(jiki.tama.t)*jiki.tama.v;
		if (collision2())
		{
			flagpro = 0;
			// TODO: add processing of delete of kabe object
		}
		else if ((Y*L < ypro_check - MARGIN) || (0 * L > xpro_check + MARGIN)
			|| ((X - 1)*L < xpro_check - MARGIN) || (0 * L > ypro_check + MARGIN)) flagpro = 0;
		else
		{
			jiki.tama.x = xpro_check;
			jiki.tama.y = ypro_check;
			glutTimerFunc(10, projfunc2, 0);
		}
	}
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	// launch
	case ' ':
		flagpro = 1;
		jiki.tama.t = jiki.t;
		jiki.tama.x = jiki.x;
		jiki.tama.y = jiki.y;
		// TODO: delete else{...}
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
	/* variables
	----------------------*/
	jiki.t = PI2;
	jiki.w = 1;
	jiki.v = 0.3;
	jiki.v_turn = 0.03;
	jiki.tama.v = 1;
	// TODO: teki
	/* ------------------ */
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

	srand((unsigned)time(NULL));
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
	glutCreateWindow("Tank Game");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
