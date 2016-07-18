#include "tank.h"

void drawStageSelect(void)
{
    int i, j, stagex, left, right;
    char title[] = "Tank Game";
    char high[] = "Highscore";
    char high1[50]; sprintf(high1, "EASY  : %d", old_score[0]);
    char high2[50]; sprintf(high2, "NORMAL: %d", old_score[1]);
    char high3[50]; sprintf(high3, "HARD  : %d", old_score[2]);
    char info1[] = "<- and -> : select level";
    char info2[] = "Space key : start game!!";
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 40, 0, 40);  // left,right,bottom,top
    glRasterPos2f(17, 35);
    for (i = 0; title[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    glRasterPos2f(17, 30);
    for (i = 0; high[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, high[i]);
    glRasterPos2f(17, 28);
    for (i = 0; high1[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, high1[i]);
    glRasterPos2f(17, 27);
    for (i = 0; high2[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, high2[i]);
    glRasterPos2f(17, 26);
    for (i = 0; high3[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, high3[i]);
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
    int i,j;
    double lx, ly;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[DARK_BROWN]);
	glBegin(GL_LINES);
	for (ly = 0;ly <= Y; ly++) {
		glVertex3d(0, ly, 0);
		glVertex3d(X, ly, 0);
	}
	for (lx = 0;lx <= X; lx++) {
		glVertex3d(lx, Y, 0);
		glVertex3d(lx, 0, 0);
    }
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color[DARK_BROWN]);
	glBegin(GL_LINES);
	for (i = 0;i <= Y; i++) {
		glVertex3d(0, i, 0);
		glVertex3d(X, i, 0);
	}
	for (j = 0;j <= X; j++) {
		glVertex3d(j, Y, 0);
		glVertex3d(j, 0, 0);
	}
	glEnd();
}

void drawTank(double x, double y, double t, double w, double h, int isTeki)
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
	if (isTeki) glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
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
	drawTank(jiki.x, jiki.y, jiki.t, jiki.w, jiki.h, 0);
}

void drawKabe(void)
{
    int i;
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[DARK_BROWN]);
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
	drawTank(teki[i].x, teki[i].y, teki[i].t, teki[i].w, teki[i].h, 1);
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

void drawPowerup(int index)
{
    glPushMatrix();
    switch (powerups[index].type) {
        case 0:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
            glMaterialfv(GL_FRONT, GL_SPECULAR, color[SKYBLUE]);
            break;
        case 1:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
            glMaterialfv(GL_FRONT, GL_SPECULAR, color[SKYBLUE]);
            break;
        case 2:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
            glMaterialfv(GL_FRONT, GL_SPECULAR, color[MAGENTA]);
            break;
    }
    glTranslatef(powerups[index].x, powerups[index].y, 0.1);
    glutSolidTorus(0.1, 0.5, 10, 10);
    glTranslatef(0, 0, 0.5);
    glScalef(0.5, 0.5, 0.5);
    glutSolidOctahedron();
    glPopMatrix();
}

void drawResult(void)
{
    int i;
    char title[] = "Result";
    char total_score_info[50];
    sprintf(total_score_info, "Total Score: %d", score);
    char highscore_info[50];
    sprintf(highscore_info, "High Score: %d", highscore);
    char info1[] = "Press ESC to exit";
    char info2[] = "Press r to restart";
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 40, 0, 40);
    glColor3fv(color[BLACK]);
    glRasterPos2f(17, 35);
    for (i = 0; title[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    glRasterPos2f(15, 25);
    for (i = 0; total_score_info[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, total_score_info[i]);
    glRasterPos2f(15, 20);
    for (i = 0; highscore_info[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, highscore_info[i]);
    glRasterPos2f(15, 10);
    for (i = 0; info1[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, info1[i]);
    glRasterPos2f(15, 5);
    for (i = 0; info2[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, info2[i]);
    
    glPopMatrix();
}
