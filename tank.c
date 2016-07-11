#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// ======== Windows ======
#include <GL/glut.h>
// ====== Mac OS X =======
//#include <OpenGL/gl.h>
//#include <GLUT/glut.h>
// =======================
#include "tank.h"
#define PI (3.1415926536)
#define X (50)  //range of the field
#define Y (50) // range of the field
#define L (1)
#define z (0.5) // height of object
#define kabeIndex 12
#define TEKI_MAX 3

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
Tank jiki = { 0 };
Tank teki[TEKI_MAX] = { 0 };
int flag_kabe[kabeIndex];
int count_interval[TEKI_MAX] = { 0 };
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

void drawKabe(void)
{
	int i;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	for (i = 0; i < kabeIndex; i++)
	{
		if (flag_kabe[i])
		{
			glPushMatrix();
			glTranslatef(kabeList[i][0], kabeList[i][1], kabeList[i][2]);
			glutSolidCone(0.5, 1, 30, 30);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawJikiProj(int index)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glTranslatef(jiki.tama[index].x, jiki.tama[index].y, z);
	glutSolidSphere(jiki.tama[index].r, 30, 30);
	glPopMatrix();
}

void drawTekiProj(int i, int j)
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[MAGENTA]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glTranslatef(teki[i].tama[j].x, teki[i].tama[j].y, z);
	glutSolidSphere(teki[i].tama[j].r, 30, 30);
	glPopMatrix();
}

void drawTeki(int i)
{
	glPushMatrix();
 
	glTranslatef(teki[i].x, teki[i].y, z);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glutSolidCube(teki[i].w);
	glPopMatrix();
}

void aim(void)
{
	double aim_x, aim_y;
	glPushMatrix();
	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glVertex3d(jiki.x,jiki.y,z);
	aim_x = jiki.x + 50*cos(jiki.t);
	aim_y = jiki.y + 50*sin(jiki.t);
	glVertex3d(aim_x,aim_y,z);
	glEnd();
	glPopMatrix();
}

void display(void)
{
	int index,j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	drawGround();
	if (jiki.life > 0)drawJiki();
	for (index = 0;index < TEKI_MAX;index++)
		if (teki[index].life > 0) drawTeki(index);
	drawKabe();
    for (index = 0; index < TAMA_MAX; index++) if (jiki.tama[index].flag) drawJikiProj(index);
    for (index = 0; index < TEKI_MAX; index++)
		for (j = 0;j < TAMA_MAX; j++) if (teki[index].tama[j].flag) drawTekiProj(index, j);
	aim();
	glPopMatrix();
	glutSwapBuffers();
}

int collision(double x1,double y1,double x2,double y2,double length) // collision check for kabe
{   // length is following:
	//			tank to tank             : tank.w/2 + tank.w/2 = tank.w
	//			tank to projectile       : (tank.x / 2) + projectile.r
	//			projectile to projectile : projectile.r + projectile.r
	//			projectile to kabe       : projectile.r + 0.5
	//			tank to kabe             : tank.w/2 + 0.5

	double MARGIN = 0.01;
	if ((x1 - x2 < length+MARGIN) && (x2 - x1 < length + MARGIN) && (y1 - y2 < length + MARGIN) && (y2 - y1 < length + MARGIN))
	{
		printf("(%.02f,%.02f):(%.02f,%.02f)\n", x2, y2, x1, y1);
		return 1;
	}
	return 0;
}

/*
TimerFunc for position of projectiles
-------------------------------------------*/
// TODO: unify projTimerFunc

void projTimerFunc(int index)
{
    int i, j, k, isTeki = 0;
    double MARGIN = 0.25;
    Tank *tank;
    if (index >= 100) {
        tank = &jiki;
        index -= 100;
    }
    else {
        tank = &teki[index];
        isTeki = 1;
    }
    
    if ((tank->life > 0)&&(tank->tama[index].flag))
    {
        tank->tama[index].x += cos(tank->tama[index].t)*tank->tama[index].v;
        tank->tama[index].y += sin(tank->tama[index].t)*tank->tama[index].v;
        
        /* collision check
        -----------------------*/
        if (isTeki) {
            if (collision(jiki.x, jiki.y, tank->tama[j].x, tank->tama[j].y, jiki.w / 2.0 + tank->tama[j].r))
            {
                jiki.life -= tank->tama[j].damage;
                tank->tama[j].flag = 0;
            }
        }
        
        for (k = 0;k < kabeIndex;k++)
            if ((flag_kabe[k]) && (collision(kabeList[k][0], kabeList[k][1],
                                             tank->tama[index].x, tank->tama[index].y, tank->tama[index].r + 0.5))) break;
        
        for (i = 0;i < TEKI_MAX;i++)
        {
            if (isTeki && index == i) continue;
            if ((teki[i].life>0) && (collision(teki[i].x, teki[i].y,
                                               tank->tama[index].x, tank->tama[index].y, teki[i].w / 2.0 + tank->tama[index].r)))
            {
                j = TAMA_MAX;
                break;
            }
            for (j = 0;j < TAMA_MAX;j++)
                if ((teki[i].tama[j].flag) && (collision(teki[i].tama[j].x, teki[i].tama[j].y, tank->tama[index].x, tank->tama[index].y, teki[i].tama[j].r + tank->tama[index].r))) break;
            if (j < TAMA_MAX) break;
        }
        
        if ((Y*L < tank->tama[index].y - MARGIN) || (0 * L > tank->tama[index].x + MARGIN)
            || ((X - 1)*L < tank->tama[index].x - MARGIN) || (0 * L > tank->tama[index].y + MARGIN))
        {
            tank->tama[index].flag = 0;
        }
        else if (collision(tank->x, tank->y, tank->tama[index].x, tank->tama[index].y, tank->w / 2.0 + tank->tama[index].r))
        {
            tank->tama[index].flag = 0;
        }
        else if (k < kabeIndex)
        {
            tank->tama[index].flag = 0;
            flag_kabe[k] = 0;
        }
        else if ((i < TEKI_MAX) && (j < TAMA_MAX))
        {
            tank->tama[index].flag = 0;
            teki[i].tama[j].flag = 0;
        }
        else if (i < TEKI_MAX)
        {
            tank->tama[index].flag = 0;
            teki[i].life -= tank->tama[index].damage;
        }
        else glutTimerFunc(10, projTimerFunc, index);
    }
}



////////////////////////////////////////////////////////////////////////
void projJikiTimerFunc(int index)
{
	int i, j, k;
	double MARGIN = 0.25;
	if ((jiki.life > 0)&&(jiki.tama[index].flag))
	{
		jiki.tama[index].x += cos(jiki.tama[index].t)*jiki.tama[index].v;
		jiki.tama[index].y += sin(jiki.tama[index].t)*jiki.tama[index].v;

		for (k = 0;k < kabeIndex;k++)
			if ((flag_kabe[k]) && (collision(kabeList[k][0], kabeList[k][1],
				jiki.tama[index].x, jiki.tama[index].y, jiki.tama[index].r + 0.5))) break;

		for (i = 0;i < TEKI_MAX;i++)
		{
			if ((teki[i].life>0) && (collision(teki[i].x, teki[i].y,
				jiki.tama[index].x, jiki.tama[index].y, teki[i].w / 2.0 + jiki.tama[index].r)))
			{
				j = TAMA_MAX;
				break;
			}
			for (j = 0;j < TAMA_MAX;j++)
				if ((teki[i].tama[j].flag) && (collision(teki[i].tama[j].x, teki[i].tama[j].y,
					jiki.tama[index].x, jiki.tama[index].y, teki[i].tama[j].r + jiki.tama[index].r))) break;
			if (j < TAMA_MAX) break;
		}

		if ((Y*L < jiki.tama[index].y - MARGIN) || (0 * L > jiki.tama[index].x + MARGIN)
			|| ((X - 1)*L < jiki.tama[index].x - MARGIN) || (0 * L > jiki.tama[index].y + MARGIN))
		{
			jiki.tama[index].flag = 0;
		}
		else if (collision(jiki.x, jiki.y,
					jiki.tama[index].x, jiki.tama[index].y, jiki.w / 2.0 + jiki.tama[index].r))
		{
			jiki.tama[index].flag = 0;
		}
		else if (k < kabeIndex)
		{
			jiki.tama[index].flag = 0;
			flag_kabe[k] = 0;
		}
		else if ((i < TEKI_MAX) && (j < TAMA_MAX))
		{
			jiki.tama[index].flag = 0;
			teki[i].tama[j].flag = 0;
		}
		else if (i < TEKI_MAX)
		{
			jiki.tama[index].flag = 0;
			teki[i].life -= jiki.tama[index].damage;
		}
		else glutTimerFunc(10, projJikiTimerFunc, index);
	}
}



void projTekiTimerFunc(int index)
{
	int i, j, k, l, m;
	double MARGIN = 0.25;
	j = index % TAMA_MAX;
	i = index / TAMA_MAX;
	
	if ((teki[i].tama[j].flag)&&(teki[i].life>0))
	{
		teki[i].tama[j].x += cos(teki[i].tama[j].t)*teki[i].tama[j].v;
		teki[i].tama[j].y += sin(teki[i].tama[j].t)*teki[i].tama[j].v;

		for (k = 0;k < kabeIndex;k++) // collision check for kabe
			if ((flag_kabe[k]) && (collision(kabeList[k][0], kabeList[k][1],
				teki[i].tama[j].x, teki[i].tama[j].y, teki[i].tama[j].r + 0.5))) break; 

		if (k >= kabeIndex) //collison check for other tama and teki
		{
			for (l = 0;l < TEKI_MAX;l++)
			{
				if ((teki[l].life>0) && (collision(teki[i].tama[j].x, teki[i].tama[j].y,
					teki[l].x, teki[l].y, teki[i].tama[j].r + teki[l].w / 2.0)))
				{
					m = TAMA_MAX;
					break;
				}
				for (m = 0;m < TAMA_MAX;m++)
					if ((teki[l].tama[m].flag) &&(l!=i)&&(m!=j)&&(collision(teki[l].tama[m].x, teki[l].tama[m].y,
						teki[i].tama[j].x, teki[i].tama[j].y, teki[i].tama[j].r + teki[l].tama[m].r)))
						break;
				if (m < TAMA_MAX) break;
			}
		}



		if ((Y*L < teki[i].tama[j].y - MARGIN) || (0 * L > teki[i].tama[j].x + MARGIN)
			|| ((X - 1)*L < teki[i].tama[j].x - MARGIN) || (0 * L > teki[i].tama[j].y + MARGIN))
		{
			teki[i].tama[j].flag = 0;
		}
		else if (collision(jiki.x, jiki.y,
					teki[i].tama[j].x, teki[i].tama[j].y, jiki.w / 2.0 + teki[i].tama[j].r))
		{
			jiki.life -= teki[i].tama[j].damage;
			teki[i].tama[j].flag = 0;
		}
		else if (k < kabeIndex)
		{
			flag_kabe[k] = 0;
			teki[i].tama[j].flag = 0;
		}
		else if ((l < TEKI_MAX) && (m < TAMA_MAX))
		{
			teki[i].tama[j].flag = 0;
			teki[l].tama[m].flag = 0;
		}
		else if (l < TEKI_MAX) teki[i].tama[j].flag = 0;
		else glutTimerFunc(10, projTekiTimerFunc, index);
	}
	else teki[i].tama[j].flag = 0;
}


/*
 TimerFunc for position of jiki and teki
-------------------------------------------*/
void jikiTimerFunc(int value)
{
	int i,j;
	double MARGIN = 0.01;
	if (jiki.life>0)
	{
		if (mySpecialValue & (1 << 0))
		{
			jiki.x += jiki.v*cos(jiki.t);
			jiki.y += jiki.v*sin(jiki.t);

			for (i = 0; i < kabeIndex;i++)
				if ((flag_kabe[i]) &&
					(collision(kabeList[i][0], kabeList[i][1], jiki.x, jiki.y, jiki.w / 2.0 + 0.5))) break;
			for (j = 0;j < TEKI_MAX;j++)
				if ((teki[j].life>0) &&
					(collision(teki[j].x, teki[j].y, jiki.x, jiki.y, jiki.w / 2.0 + teki[j].w / 2.0))) break;

			if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < jiki.y - MARGIN) || (0 * L > jiki.x + MARGIN)
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

			for (i = 0; i < kabeIndex;i++)
				if ((flag_kabe[i]) &&
					(collision(kabeList[i][0], kabeList[i][1], jiki.x, jiki.y, jiki.w / 2.0 + 0.5))) break;

			for (j = 0;j < TEKI_MAX;j++)
				if ((teki[j].life>0) &&
					(collision(teki[j].x, teki[j].y, jiki.x, jiki.y, jiki.w / 2.0 + teki[j].w / 2.0))) break;

			if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < jiki.y - MARGIN) || (0 * L > jiki.x + MARGIN)
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
}

void teki0TimerFunc(int index)
{
	if (teki[index].life > 0) {
		int i, j;
		double MARGIN = 0.01;
		double length;

		length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
			+ (jiki.y - teki[index].y)*(jiki.y - teki[index].y));

		teki[index].x += teki[index].v*cos(teki[index].t);
		teki[index].y += teki[index].v*sin(teki[index].t);

		for (i = 0;i < kabeIndex;i++)
			if ((flag_kabe[i])&&
				(collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;

		for (j = 0;j < TEKI_MAX;j++)
			if ((teki[j].life>0) && (j != index) &&
				(collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;

		if ((i < kabeIndex)||(j<TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
			|| ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
		{
			teki[index].x -= teki[index].v*cos(teki[index].t);
			teki[index].y -= teki[index].v*sin(teki[index].t);
			teki[index].t = (rand() / (double)RAND_MAX) * 2.0 * PI;
		}

		if (length < 25)
		{
			for (i = 0;i < TAMA_MAX;i++)
				if (teki[index].tama[i].flag == 0) break;

			if (i < TAMA_MAX)
			{
				count_interval[index]++;
				if ((count_interval[index] % 100) == 1)
				{
					count_interval[index] = 1;
					teki[index].tama[i].flag = 1;
					teki[index].tama[i].t = atan2(jiki.y - teki[index].y, jiki.x - teki[index].x);
					teki[index].tama[i].x =
						teki[index].x + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*cos(teki[index].tama[i].t);
					teki[index].tama[i].y =
						teki[index].y + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*sin(teki[index].tama[i].t);
					projTekiTimerFunc(i + index * TAMA_MAX);
				}
			}
		}

		glutTimerFunc(10, teki0TimerFunc, index);
	}
}

void teki1TimerFunc(int index)
{
	if (teki[index].life>0) {
		int i, j;
		double MARGIN = 0.01;
		double length;

		length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
			+ (jiki.y - teki[index].y)*(jiki.y - teki[index].y));

		if (teki[index].flag) teki[index].x += teki[index].v;
		else teki[index].x -= teki[index].v;

		for (i = 0;i < kabeIndex;i++)
			if ((flag_kabe[i]) &&
				(collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;

		for (j = 0;j < TEKI_MAX;j++)
			if ((teki[j].life>0) && (j != index) &&
				(collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;

		if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
			|| ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
		{
			if (teki[index].flag)
			{
				teki[index].x -= teki[index].v;
				teki[index].flag = 0;
			}
			else
			{
				teki[index].x+= teki[index].v;
				teki[index].flag = 1;
			}
		}

		if (length < 40)
		{
			for (i = 0;i < TAMA_MAX;i++)
				if (teki[index].tama[i].flag == 0) break;

			if (i < TAMA_MAX)
			{
				count_interval[index]++;
				if ((count_interval[index] % 100) == 1)
				{
					count_interval[index] = 1;
					teki[index].tama[i].flag = 1;
					teki[index].tama[i].t = atan2(jiki.y - teki[index].y, jiki.x - teki[index].x);
					teki[index].tama[i].x =
						teki[index].x + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*cos(teki[index].tama[i].t);
					teki[index].tama[i].y =
						teki[index].y + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*sin(teki[index].tama[i].t);
					projTekiTimerFunc(i + index * TAMA_MAX);
				}
			}
		}
		glutTimerFunc(10, teki1TimerFunc, index);
	}
}

void teki2TimerFunc(int index)
{
	if (teki[index].life>0) {
		int i, j;
		double MARGIN = 0.01;
		double length;

		length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
			+ (jiki.y - teki[index].y)*(jiki.y - teki[index].y));

		if (teki[index].flag) teki[index].y += teki[index].v;
		else teki[index].y -= teki[index].v;

		for (i = 0;i < kabeIndex;i++)
			if ((flag_kabe[i]) &&
				(collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;

		for (j = 0;j < TEKI_MAX;j++)
			if ((teki[j].life>0) && (j != index) &&
				(collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;

		if ((i < kabeIndex) || (j<TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
			|| ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
		{
			if (teki[index].flag)
			{
				teki[index].y -= teki[index].v;
				teki[index].flag = 0;
			}
			else
			{
				teki[index].y += teki[index].v;
				teki[index].flag = 1;
			}
		}

		if (length < 30)
		{
			for (i = 0;i < TAMA_MAX;i++)
				if (teki[index].tama[i].flag == 0) break;

			if (i < TAMA_MAX)
			{
				count_interval[index]++;
				if ((count_interval[index] % 100) == 1)
				{
					count_interval[index] = 1;
					teki[index].tama[i].flag = 1;
					teki[index].tama[i].t = atan2(jiki.y - teki[index].y, jiki.x - teki[index].x);
					teki[index].tama[i].x =
						teki[index].x + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*cos(teki[index].tama[i].t);
					teki[index].tama[i].y =
						teki[index].y + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*sin(teki[index].tama[i].t);
					projTekiTimerFunc(i + index * TAMA_MAX);
				}
			}
		}
		glutTimerFunc(10, teki2TimerFunc, index);
	}


}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	int i;
	double MARGIN = 0.01;

	switch (key)
	{
	case ' ':
		for (i = 0; i < TAMA_MAX; i++)
			if (jiki.tama[i].flag == 0) break;
		if ((i < TAMA_MAX)&&(jiki.life>0))
		{
		// launch
			jiki.tama[i].flag = 1;
			jiki.tama[i].t = jiki.t;
			jiki.tama[i].x = jiki.x + (jiki.w / 2.0 + jiki.tama[i].r + MARGIN)*cos(jiki.t);
			jiki.tama[i].y = jiki.y + (jiki.w / 2.0 + jiki.tama[i].r + MARGIN)*sin(jiki.t);
			projJikiTimerFunc(i);
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
	int i,j;
	srand((unsigned)time(NULL));
	/* variables
	----------------------*/
	for (i = 0;i < kabeIndex;i++) flag_kabe[i] = 1;
	jiki.t = PI/2.0;
	jiki.w = 1.0;
	jiki.v = 0.2;
	jiki.v_turn = 0.03;
	jiki.life = 50;
	for (i = 0; i < TAMA_MAX; i++) {
		jiki.tama[i].v = 0.5;
		jiki.tama[i].r = 0.3;
		jiki.tama[i].damage = 1;
	}

	teki[0].x = X / 2.0;
	teki[0].y = Y / 2.0;
	teki[0].t = rand();
	teki[1].x = X / 4.0;
	teki[1].y = Y / 4.0;
	teki[2].x = X * 3.0 / 4.0;
	teki[2].y = Y / 4.0;
	for (j = 0;j < TEKI_MAX;j++)
	{
		teki[j].life = 3;
		teki[j].w = 1.0;
		teki[j].v = 0.1;
		teki[j].v_turn = 0.03;
		for (i = 0;i < TAMA_MAX; i++) {
			teki[j].tama[i].v = 0.2;
			teki[j].tama[i].damage = 1;
			teki[j].tama[i].r = 0.3;
		}
	}
	teki[1].life = 5;
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

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, .1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -10.0, 4.0, 0.0, 0.0, 1.5, 0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
	jikiTimerFunc(0);
	teki0TimerFunc(0);
	teki1TimerFunc(1);
	teki2TimerFunc(2);

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
