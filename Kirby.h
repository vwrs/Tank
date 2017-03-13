#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 5.0, 0.0, 0.0, 0.0 };
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat black[] = { .1, .1, .1, 1.0 };
GLfloat pink[] = { 1.0, 0.512, 0.706, 0.0 };
GLfloat hotpink[] = { 1.0, 0.2, 0.3, 0.0 };
GLfloat blown[] = { 0.60, 0.1, 0.15, 0.0 };
GLfloat orange[] = { 0.83, 0.23, 0.17, 0.0 };

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();//ì∑ëÃ
	glMaterialfv(GL_FRONT, GL_DIFFUSE, pink);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	glutSolidSphere(0.5, 30, 30);
	glPopMatrix();

	glPushMatrix();//òr
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(30, 0, 1, 0.1);
	glutSolidSphere(0.1875, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glRotatef(30, 0, 1, 0.1);
	glutSolidSphere(0.1875, 30, 30);
	glPopMatrix();

	glPushMatrix();//ë´
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glTranslatef(0.25, -0.4375, 0.0);
	glScalef(1.5, 1, 1);
	glutSolidSphere(0.15625, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -0.4375, 0.0);
	glScalef(1.5, 1, 1);
	glutSolidSphere(0.15625, 30, 30);
	glPopMatrix();

	glPushMatrix();//çïñ⁄
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glTranslatef(0.15, 0.09375, 0.425);
	glScalef(1, 1.8, 1);
	glutSolidSphere(0.0625, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, 0.09375, 0.425);
	glScalef(1, 1.8, 1);
	glutSolidSphere(0.0625, 30, 30);
	glPopMatrix();

	glPushMatrix();//îíñ⁄
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glTranslatef(0.15, 0.140625, 0.44375);
	glScalef(1, 1.6, 1);
	glutSolidSphere(0.0375, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, 0.140625, 0.44375);
	glScalef(1, 1.6, 1);
	glutSolidSphere(0.0375, 30, 30);
	glPopMatrix();

	glPushMatrix();//ñj
	glMaterialfv(GL_FRONT, GL_DIFFUSE, hotpink);
	glTranslatef(0.25, -0.0625, 0.39375);
	glRotatef(60, 0, 1, 0);
	glScalef(1.5, 1, 1);
	glutSolidSphere(0.04375, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, hotpink);
	glTranslatef(-0.25, -0.0625, 0.39375);
	glRotatef(-60, 0, 1, 0);
	glScalef(1.5, 1, 1);
	glutSolidSphere(0.04375, 30, 30);
	glPopMatrix();

	glPushMatrix();//å˚1
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blown);
	glTranslatef(0.0, -0.09375, 0.40625);
	glRotatef(15, 1, 0, 0);
	glScalef(1.3, 1.5, 0.9);
	glutSolidSphere(0.125, 30, 30);
	glPopMatrix();

	glPushMatrix();//å˚2
	glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
	glTranslatef(0.0, -0.125, 0.44375);
	glRotatef(15, 1, 0, 0);
	glScalef(1.3, 1.3, 0.8);
	glutSolidSphere(0.09375, 30, 30);
	glPopMatrix();;

	glutSwapBuffers();
}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(4.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, -2.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("C Dev");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
