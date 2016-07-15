#include "tank.h"

/*
 Global variables
---------------------------------------------------*/
int current_status = 0;  // 0: start 1: easy 2: normal 3: hard 4: result
int initialized = 0;
Stage stages[STAGE_MAX] = { { 0 } };
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
Tank teki[TEKI_MAX] = { { 0 } };
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
    
    switch (current_status) {
        case 0:
            drawGround();
            drawStageSelect(stages);
            if (!initialized) {
                initSelect();
                initialized = 1;
            }
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
            if (!initialized) {
                initStage();
                initialized = 1;
            }
            break;

        // normal
        case 2:
            drawGround();
            if (jiki.life > 0) drawJiki();
            for (index = 0;index < TEKI_MAX;index++)
                if (teki[index].life > 0) drawTeki(index);
            drawKabe();
            for (index = 0; index < TAMA_MAX; index++) if (jiki.tama[index].flag) drawJikiProj(index);
            for (index = 0; index < TEKI_MAX; index++)
                for (j = 0;j < TAMA_MAX; j++) if (teki[index].tama[j].flag) drawTekiProj(index, j);
            aim();
            if (!initialized) {
                initStage();
                initialized = 1;
            }
            break;

        // hard
        case 3:
            drawGround();
            if (jiki.life > 0) drawJiki();
            for (index = 0;index < TEKI_MAX;index++)
                if (teki[index].life > 0) drawTeki(index);
            drawKabe();
            for (index = 0; index < TAMA_MAX; index++) if (jiki.tama[index].flag) drawJikiProj(index);
            for (index = 0; index < TEKI_MAX; index++)
                for (j = 0;j < TAMA_MAX; j++) if (teki[index].tama[j].flag) drawTekiProj(index, j);
            aim();
            if (!initialized) {
                initStage();
                initialized = 1;
            }
            break;
 
        // result
        case 4:
            
            break;
        default: break;
    }
    
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Tank Game");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
