#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define PI2 (3.1415*2)
#define N (100)

GLfloat red[] = { 0.7, 0.2, 0.2, 1.0 };
GLfloat white[] = { 1,1,1,1 };
GLfloat black[] = { 0.1,0.1,0.1,1 };
GLfloat brown[] = { 0.7,0.35,0.35,1.0 };
GLfloat pos0[] = { 0.0, 0.0, 0.1, 0.0 };

void entyu(GLdouble lng, GLdouble r) {
	glBegin(GL_POLYGON);
	for (double i = 0.0; i <= N; i++) {
		glNormal3d(0.0, 1.0, 0.0);
		glVertex3d(r*sin(PI2*i / N), lng, r*cos(PI2*i / N));
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (double i = 0.0; i <= N; i++) {
		glNormal3d(0.0, 1.0, 0.0);
		glVertex3d(r*sin(PI2*i / N), 0.0, r*cos(PI2*i / N));
	}
	glEnd();


	glBegin(GL_QUAD_STRIP);
	for (double i = 0.0; i <= N; i++) {
		glNormal3d(cos(PI2*i / N), 0, sin(PI2*i / N));
		glVertex3d(r*cos(PI2*i / N),0, r*sin(PI2*i / N));
		glVertex3d(r*cos(PI2*i / N),lng, r*sin(PI2*i / N));
	}
	
	glEnd();

}

void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glPopMatrix();
	glPushMatrix();
	
	glTranslatef(0, 1.25, 0);
	glRotatef(10, 1, 0, 1);
	glTranslatef(0, 0.25, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	entyu(0.05, 0.6);
	entyu(0.6, 0.3);
	
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, -0.75, 0);
	glRotatef(45, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, brown);
	entyu(1.7, 0.07);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, brown);
	entyu(1.7, 0.07);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.8, 0.7, 0);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	glutSolidCone(0.15, 0.5, 30, 30);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, 0.7, 0);
	glRotatef(30, 0, 1, 0);
	glRotatef(20, 0, 0, 1);
	glTranslatef(0.74, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	glutSolidSphere(0.12, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, 0.7, 0);
	glRotatef(-30, 0, 1, 0);
	glRotatef(20, 0, 0, 1);
	glTranslatef(0.74, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	glutSolidSphere(0.12, 20, 20);

	
	glPopMatrix();
	
	glTranslatef(0, -0.8, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glutSolidSphere(1.0, 30, 30);
	glTranslatef(0, 1.5, 0);
	glutSolidSphere(0.8, 30, 30);
	glTranslatef(0, 2.5, 0);
	

	glPopMatrix();

	glutSwapBuffers();
	
	
}
void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(7.0, 4.0, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Snowman");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
