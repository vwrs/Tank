#include "tank.h"

void drawStageSelect(void)
{
    int i, j, stagex, left, right;
    char title[] = "Tank Game";
    char info1[] = "<- and -> : select level";
    char info2[] = "Space key : start game!!";
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 40, 0, 40);  // left,right,bottom,top
    glRasterPos2f(17, 35);
    for (i = 0; title[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    glRasterPos2f(15, 5);
    for (i = 0; info1[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, info1[i]);
    glRasterPos2f(15, 3);
    for (i = 0; info2[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, info2[i]);
    
    for (i = 0; i < STAGE_MAX; i++) {
        stagex = stages[i].x;
        /* draw selector
         ------------------*/
        if (stages[i].selected) {
            left = stagex - 4;
            right = stagex + 6;
            if (i == 1)  right++;
            glBegin(GL_LINES);
            glColor3f(1.0,0.0,0.0);
            glVertex2f(left,15);
            glColor3f(0.0,1.0,0.0);
            glVertex2f(right,15);
            glColor3f(0.0,0.0,1.0);
            glVertex2f(right,15);
            glColor3f(1.0,1.0,0.0);
            glVertex2f(right,25);
            glColor3f(1.0,0.0,0.0);
            glVertex2f(right,25);
            glColor3f(0.0,1.0,0.0);
            glVertex2f(left,25);
            glColor3f(0.0,0.0,1.0);
            glVertex2f(left,25);
            glColor3f(1.0,1.0,0.0);
            glVertex2f(left,15);
            glEnd();
        }
        /* draw string
         -------------------*/
        glColor3f(0.0,0.0,0.0);
        glRasterPos2f(stages[i].x, stages[i].y);
        for (j = 0; stages[i].name[j]; j++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stages[i].name[j]);
    }
    glPopMatrix();
    
}

void drawGround(void)
{
    /*int i, j;
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
    
    glPopMatrix();*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[DARK_BROWN]);
	glBegin(GL_LINES);
	for (double ly = 0;ly <= Y; ly++) {
		glVertex3d(0, ly, 0);
		glVertex3d(X, ly, 0);
	}
	for (double lx = 0;lx <= X; lx++) {
		glVertex3d(lx, Y, 0);
		glVertex3d(lx, 0, 0);
	}
	glEnd();

}

void drawtank(double x, double y, double t, double w, double h, int isTeki)
{
	int i = 0;
	double step, init;

	step = 60.0*PI / 180.0;
	init = 30.0 * PI / 180.0;

	glPushMatrix();

	glTranslatef(x, y, 0);
	glRotatef(t*180.0 / PI, 0.0, 0.0, 1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	glBegin(GL_QUADS);
	glVertex3d(-h / 2.0, -w / 2.0, 0.25);
	glVertex3d(-(h - 0.5) / 2.0, -w / 2.0, 0);
	glVertex3d((h - 0.5) / 2.0, -w / 2.0, 0);
	glVertex3d(h / 2.0, -w / 2.0, 0.25);

	glVertex3d(h / 2.0, -w / 2.0, 0.25);
	glVertex3d((h - 0.5) / 2.0, -w / 2.0, 0);
	glVertex3d((h - 0.5) / 2.0, w / 2.0, 0);
	glVertex3d(h / 2.0, w / 2.0, 0.25);

	glVertex3d(h / 2.0, w / 2.0, 0.25);
	glVertex3d((h - 0.5) / 2.0, w / 2.0, 0);
	glVertex3d(-(h - 0.5) / 2.0, w / 2.0, 0);
	glVertex3d(-h / 2.0, w / 2.0, 0.25);

	glVertex3d(-h / 2.0, w / 2.0, 0.25);
	glVertex3d(-(h - 0.5) / 2.0, w / 2.0, 0);
	glVertex3d(-(h - 0.5) / 2.0, -w / 2.0, 0);
	glVertex3d(-h / 2.0, -w / 2.0, 0.25);

	glEnd();

	glTranslatef(0, 0, 0.375);
	glPushMatrix();
	glScalef(h, w, 0.25);
	if (isTeki)glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
	else glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0, 0, 0.125);

	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	for (i = 0;i < 6;i++) {
		glVertex3d(0.4*cos(step*(double)i + init), 0.4*sin(step*(double)i + init), 0);
		glVertex3d(0.4*cos(step*(double)(i + 1) + init), 0.4*sin(step*(double)(i + 1) + init), 0);
		glVertex3d(0.4*cos(step*(double)(i + 1) + init), 0.4*sin(step*(double)(i + 1) + init), 0.25);
		glVertex3d(0.4*cos(step*(double)i + init), 0.4*sin(step*(double)i + init), 0.25);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BROWN]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	for (i = 0;i < 6;i++) {
		glVertex3d(0.4*cos(step*(double)i + init), 0.4*sin(step*(double)i + init), 0.25);
	}

	glEnd();

	glTranslatef(sqrt(0.3*0.3 + 0.2*0.2), 0, 0.125);
	step = 180.0 / PI;

	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[YELLOW]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	for (i = 0; i < 360;i++)
	{
		glVertex3d(0, 0.1*cos(step*(double)i), 0.1*sin(step*(double)i));
		glVertex3d(0, 0.1*cos(step*(double)(i + 1)), 0.1*sin(step*(double)(i + 1)));
		glVertex3d(1.5, 0.1*cos(step*(double)(i + 1)), 0.1*sin(step*(double)(i + 1)));
		glVertex3d(1.5, 0.1*cos(step*(double)i), 0.1*sin(step*(double)i));
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (i = 0;i < 360;i++) glVertex3d(1.5, 0.1*cos(step*(double)i), 0.1*sin(step*(double)i));
	glEnd();

	glPopMatrix();

}

void drawJiki(void)
{
	drawtank(jiki.x, jiki.y, jiki.t, jiki.w, jiki.h, 0);
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
			glutSolidCube(1);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void drawJikiProj(int i)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glTranslatef(jiki.tama[i].x, jiki.tama[i].y, z);
    glutSolidSphere(jiki.tama[i].r, 30, 30);
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
	drawtank(teki[i].x, teki[i].y, teki[i].t, teki[i].w, teki[i].h, 1);
}

void aim(void)
{
    double aim_x = jiki.x + 50*cos(jiki.t);
    double aim_y = jiki.y + 50*sin(jiki.t);
    // TODO
    if (1){}
    glPushMatrix();
    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glVertex3d(jiki.x,jiki.y,z);
    glVertex3d(aim_x,aim_y,z);
    glEnd();
    glPopMatrix();
}

void drawPowerup(int type, double x, double y)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[SKYBLUE]);
        glTranslatef(x, y, 0.1);
    glutSolidTorus(0.1, 0.5, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef(0.5, 0.5, 0.5);
    glutSolidOctahedron();
    
    glPopMatrix();
}
