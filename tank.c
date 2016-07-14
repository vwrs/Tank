#include "tank.h"

/*
 Global variables
---------------------------------------------------*/
int stage = 1;  // 0: start 1: easy 2: normal 3: hard 4: result
GLfloat pos0[] = { 5.0, 0.0, 0.0, 1.0 };
GLfloat pos1[] = { 0.0, 0.0, 5.0, 1.0 };
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
    { 0.0, 22.0, 0.0 }
};

/*
 display
-----------------------------------*/
void display(void)
{
	int index,j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch (stage) {
        case 0:
            drawString("Test", 10, 10, 0, 0);
            break;

        // easy
        case 1:
            drawGround();
            if (jiki.life > 0) drawJiki();
            for (index = 0;index < TEKI_MAX;index++)
                if (teki[index].life > 0) drawTeki(index);
            drawKabe();
            for (index = 0; index < TAMA_MAX; index++) if (jiki.tama[index].flag) drawJikiProj(index);
            for (index = 0; index < TEKI_MAX; index++)
                for (j = 0;j < TAMA_MAX; j++) if (teki[index].tama[j].flag) drawTekiProj(index, j);
            aim();
            break;

        // normal
        case 2:
            
            break;

        // hard
        case 3:
            
            break;
 
        // result
        case 4:
            
            break;
        default: break;
    }
    
	glutSwapBuffers();
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
	glutInitWindowSize(800, 800);
	glutCreateWindow("Tank Game");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
