#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ======== Windows =======
#include <GL/glut.h>
// ========================

// ====== Mac OS X ======= //
//#include <OpenGL/gl.h>
//#include <GLUT/glut.h>
// ======================= //

#define PI (3.14159)
#define PI2 (PI/2)
#define dt  (10/(double)10000) // interval of time 

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
		{ 0.0, 0.0, 0.0, 1.0 } };//色を増やす場合はここに追加
double x = 0, y = 0, z = 0; // position of tank
double l = 0.1;   // length
double t = PI2; // angle of direction
double xb = 0, yb = 0; // variables for checking collision and range of tanc's position
double xp = 0, yp = 0;// position of projectile
double xpb = 0, ypb = 0; // variables for checking collision and range of projectile's position 
int flagproj = 0;  // this flag decides whether to draw a projectile
int flagprojend = 1; //this flag decides whether to end projfunc
double tt = 0; // angle of projectile 
int mySpecialValue = 0;
double tekiList[][3] = {
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
		{ 0.0, 22.0, 0.0 } };//障害物のリスト
int tekiIndex = 12;
double v = 0;

int X = 50;//地面
int Y = 250;
double L = 1;

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
	glVertex3d(-0.5*L, -0.5*L, 0.0);//スタート
	glVertex3d((X - 0.5)*L, -0.5*L, 0.0);
	glVertex3d((X - 0.5)*L, 0.5*L, 0.0);
	glVertex3d(-0.5*L, 0.5*L, 0.0);

	glVertex3d(-0.5*L, (Y - 0.5)*L, 0.0);//ゴール
	glVertex3d((X - 0.5)*L, (Y - 0.5)*L, 0.0);
	glVertex3d((X - 0.5)*L, (Y + 0.5)*L, 0.0);
	glVertex3d(-0.5*L, (Y + 0.5)*L, 0.0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);//灰色
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

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);//黒
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

	glTranslatef(x, y, z);
	glTranslatef(0.0, 0.0, 0.5);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glutSolidCube(1);
	glPopMatrix();
}
void drawTeki(void)
{
	int i;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	for (i = 0; i < tekiIndex; i++)
	{
		glPushMatrix();
		glTranslatef(tekiList[i][0], tekiList[i][1], tekiList[i][2]);
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
	glTranslatef(xp, yp, 0.5);
	glutSolidSphere(0.5, 30, 30);
	glPopMatrix();

}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();
	drawJiki();
	drawTeki();
	if(flagproj) drawproj();
	glPopMatrix();
	glutSwapBuffers();
}
int collision() // collision check for tank
{
	//衝突判定
	int i;
	double MARGIN = 0.05;
	if (z > 1)return 0;
	for (i = 0; i < tekiIndex; i++)
	{
		//簡単な衝突判定
		if ((tekiList[i][0] - xb <1 - MARGIN) && (tekiList[i][0] - xb >-1 + MARGIN)
			&& (tekiList[i][1] - yb <1 - MARGIN) && (tekiList[i][1] - yb >-1 + MARGIN))
		{
			printf("(%.02f,%.02f):(%.02f,%.02f)\n", x, y, tekiList[i][0], tekiList[i][1]);
			return 0;
		}
	}
	return 1;
}
int collision2() // collision check for projectile
{
	//衝突判定
	int i;
	double MARGIN = 0.3;
	for (i = 0; i < tekiIndex; i++)
	{
		//簡単な衝突判定
		if ((tekiList[i][0] - xpb <1 - MARGIN) && (tekiList[i][0] - xpb >-1 + MARGIN)
			&& (tekiList[i][1] - ypb <1 - MARGIN) && (tekiList[i][1] - ypb >-1 + MARGIN))
		{
			printf("(%.02f,%.02f):(%.02f,%.02f)\n", x, y, tekiList[i][0], tekiList[i][1]);
			return 1;
		}
	}
	return 0;
}

void myTimerFunc(int value)
{
	double MARGIN = 0.05;
	if (mySpecialValue & (1 << 0))
	{
		l = 0.1;
		xb = l*cos(t) + x;
		yb = l*sin(t) + y;
		if (collision() && (Y*L > yb - MARGIN) && (0 * L < xb + MARGIN)
			&& ((X - 1)*L > xb - MARGIN) && (0 * L < yb + MARGIN))
		{
			x = xb;
			y = yb;
		}
	}
	if (mySpecialValue & (1 << 1))
	{
		t -= 0.025;
	}
	if (mySpecialValue & (1 << 2))
	{
		t += 0.025;
	}
	if (mySpecialValue & (1 << 3))
	{
		l = -0.1;
		xb = x + l*cos(t);
		yb = y + l*sin(t);
		if ( collision() && (Y*L > yb - MARGIN) && (0 * L < xb + MARGIN)
			&& ((X - 1)*L > xb - MARGIN) && (0 * L < yb + MARGIN))
		{
			x = xb;
			y = yb;
		}
	}
	//視点を移動
	glLoadIdentity();
	gluLookAt(-10.0*cos(t) + x, -10.0*sin(t) + y, 4.0, 0.0 + x, 0.0 + y, 1.5, 0.0, 0.0, 1.0);

	glutTimerFunc(10, myTimerFunc, 0);
}

void projfunc1(int value)
{
	double MARGIN = 0.25;
	if (flagprojend) {
		xpb = xp + cos(tt)*l;
		ypb = yp + sin(tt)*l;
		if (collision2())
		{
			flagproj = 0;
			// we will add processing of delete of teki object
		}
		else if ((Y*L < ypb - MARGIN) || (0 * L > xpb + MARGIN)
			|| ((X - 1)*L < xpb - MARGIN) || (0 * L > ypb + MARGIN)) flagproj = 0;
		else
		{
			xp = xpb;
			yp = ypb;
			glutTimerFunc(10, projfunc1, 0);
		}
	}
}

void projfunc2(int value)
{
	double MARGIN = 0.25;
	if (flagprojend==0) {
		xpb = xp + cos(tt)*l;
		ypb = yp + sin(tt)*l;
		if (collision2())
		{
			flagproj = 0;
			// we will add processing of delete of teki object
		}
		else if ((Y*L < ypb - MARGIN) || (0 * L > xpb + MARGIN)
			|| ((X - 1)*L < xpb - MARGIN) || (0 * L > ypb + MARGIN)) flagproj = 0;
		else
		{
			xp = xpb;
			yp = ypb;
			glutTimerFunc(10, projfunc2, 0);
		}
	}
}

void myKeyboardFunc(unsigned char key, int xx, int yy)
{
	switch (key)
	{
	case ' ':    
		flagproj = 1;
		tt = t;
		xp = x, yp = y;
		if (flagprojend)
		{
			flagprojend = 0;
			projfunc2(0);
		}
		else
		{
			flagprojend = 1;
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
		mySpecialValue |= 1 << 0;//mySpecialValueの1bit目を1にする
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue |= 1 << 1;//mySpecialValueの2bit目を1にする
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue |= 1 << 2;//mySpecialValueの3bit目を1にする
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue |= 1 << 3;//mySpecialValueの4bit目を1にする
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
		mySpecialValue &= ~(1 << 0);//mySpecialValueの1bit目を0にする
		break;
	case GLUT_KEY_LEFT:
		mySpecialValue &= ~(1 << 1);//mySpecialValueの2bit目を0にする
		break;
	case GLUT_KEY_RIGHT:
		mySpecialValue &= ~(1 << 2);//mySpecialValueの3bit目を0にする
		break;
	case GLUT_KEY_DOWN:
		mySpecialValue &= ~(1 << 3);//mySpecialValueの4bit目を0にする
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
	myTimerFunc(0);
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
