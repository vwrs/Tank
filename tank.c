#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// ======== Windows ======
// #include <GL/glut.h>
// ====== Mac OS X =======
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
// =======================
#include "tank.h"
#define PI (3.14159)
#define X (50)  //range of the field
#define Y (50) // range of the field
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
Tank teki[5] = {{0}};
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

void drawproj(int index)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glTranslatef(jiki.tama[index].x, jiki.tama[index].y, z);
	glutSolidSphere(0.5, 30, 30);
	glPopMatrix();
}

void drawteki()
{
	glPushMatrix();
 
	glTranslatef(teki[0].x, teki[0].y, z);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glutSolidCube(1);
	glPopMatrix();
}

void aim(void)
{
	double aim_x, aim_y;
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3d(1.0,0,0);
	glVertex3d(jiki.x,jiki.y,z);
	aim_x = jiki.x + 50*cos(jiki.t);
	aim_y = jiki.y + 50*sin(jiki.t);
	glVertex3d(aim_x,aim_y,z);
	glEnd();
	glPopMatrix();
}

void display(void)
{
	int index;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();
	drawJiki();
	drawteki();
	drawkabe();
	for (index = 0; index < TAMA_MAX; index++) if (jiki.tama[index].flag) drawproj(index);
	aim();
	glPopMatrix();
	glutSwapBuffers();
}

int collision(double x1,double y1,double x2,double y2,double MARGIN) // collision check for kabe
{
	if ((x1 - x2 <1 - MARGIN) && (x1 - x2 >-1 + MARGIN) && (y1 - y2 <1 - MARGIN) && (y1 - y2 >-1 + MARGIN))
	{
		printf("(%.02f,%.02f):(%.02f,%.02f)\n", x2, y2, x1, y1);
		return 1;
	}
	return 0;
}

/*
 TimerFunc
-----------------------------------*/
void jikiTimerFunc(int value)
{
	int i,sum_kabe;
	double MARGIN = 0.05;
	if (mySpecialValue & (1 << 0))
	{
		jiki.x += jiki.v*cos(jiki.t);
		jiki.y += jiki.v*sin(jiki.t);

		sum_kabe = 0;
		for (i = 0; i<kabeIndex;i++)
			sum_kabe += collision(kabeList[i][0], kabeList[i][1], jiki.x, jiki.y, MARGIN);

		if ((sum_kabe>0) || (Y*L < jiki.y - MARGIN) || (0 * L > jiki.x + MARGIN)
			|| ((X - 1)*L < jiki.x - MARGIN) || (0 * L > jiki.y + MARGIN))
		{
			jiki.x -= jiki.v*cos(jiki.t);
			jiki.y -= jiki.v*sin(jiki.t);
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
		jiki.x -= jiki.v*cos(jiki.t);
		jiki.y -= jiki.v*sin(jiki.t);

		sum_kabe = 0;
		for (i = 0; i<kabeIndex;i++)
			sum_kabe += collision(kabeList[i][0], kabeList[i][1], jiki.x, jiki.y, MARGIN);

		if ((sum_kabe>0) || (Y*L < jiki.y - MARGIN) || (0 * L > jiki.x + MARGIN)
			|| ((X - 1)*L < jiki.x - MARGIN) || (0 * L > jiki.y + MARGIN))
		{
			jiki.x += jiki.v*cos(jiki.t);
			jiki.y += jiki.v*sin(jiki.t);
		}
	}
	glLoadIdentity();
	gluLookAt(-10.0*cos(jiki.t) + jiki.x, -10.0*sin(jiki.t) + jiki.y, 4.0, 0.0 + jiki.x, 0.0 + jiki.y, 1.5, 0.0, 0.0, 1.0);

	glutTimerFunc(10, jikiTimerFunc, 0);
}

void tekiTimerFunc(int index)
{
	int i,sum_kabe;
	double MARGIN = 0.05;
	index = 0;
	if (teki[index].flag) teki[index].t = rand() % 100;
	teki[index].x += teki[index].v*cos(teki[index].t) ;
	teki[index].y += teki[index].v*sin(teki[index].t) ;

	sum_kabe = 0;
	for (i = 0;i<kabeIndex;i++)
		sum_kabe += collision(kabeList[i][index], kabeList[i][1], teki[index].x, teki[index].y, MARGIN);

	if ((sum_kabe>0) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
	    || ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
	{
		teki[index].x -= teki[index].v*cos(teki[index].t);
		teki[index].y -= teki[index].v*sin(teki[index].t);
		teki[index].flag = 1;
	}
	else teki[index].flag = 0;

	glutTimerFunc(10, tekiTimerFunc, index);
}

void projJikiTimerFunc(int index)
{
	int i,sum_kabe;
	double MARGIN = 0.25;
	Projectile tama_temp = jiki.tama[index];
	jiki.tama[index].x += cos(tama_temp.t)*tama_temp.v;
	jiki.tama[index].y += sin(tama_temp.t)*tama_temp.v;

	sum_kabe = 0;
	for (i = 0;i<kabeIndex;i++)
		sum_kabe += collision(kabeList[i][0], kabeList[i][1], tama_temp.x, tama_temp.y, MARGIN*2);

	if (sum_kabe>0)
	{
		jiki.tama[index].flag = 0;
		//TODO: add processing of delete of kabe object
	}
	else if ((Y*L < tama_temp.y - MARGIN) || (0 * L > tama_temp.x + MARGIN)
		|| ((X - 1)*L < tama_temp.x - MARGIN) || (0 * L > tama_temp.y + MARGIN)) jiki.tama[index].flag = 0;
	else glutTimerFunc(10, projJikiTimerFunc, index);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	int i;
	for (i = 0; i < TAMA_MAX; i++)
	  if (jiki.tama[i].flag == 0)
			break;
  if (i < TAMA_MAX) {
		switch (key)
		{
		// launch
		case ' ':
			jiki.tama[i].flag = 1;
			jiki.tama[i].t = jiki.t;
			jiki.tama[i].x = jiki.x;
			jiki.tama[i].y = jiki.y;
		  projJikiTimerFunc(i);
			break;
		}
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
	jiki.t = PI/2;
	jiki.w = 1;
	jiki.v = 0.3;
	jiki.v_turn = 0.02;
	jiki.life = 3;
	int i;
	for (i = 0; i < TAMA_MAX; i++) {
		jiki.tama[i].v = 0.7;
		jiki.tama[i].damage = 1;
	}

	teki[0].x = X/2;
	teki[0].y = Y/2;
	teki[0].t = PI/2;
	teki[0].w = 1;
	teki[0].v = 0.1;
	teki[0].v_turn = 0.03;
	for (i = 0;i < TAMA_MAX; i++) {
		teki[0].tama[i].v = 0.2;
		teki[0].tama[i].damage = 1;
		teki[0].life = 3;
	}
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
