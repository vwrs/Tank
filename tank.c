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
		{ 0.0, 0.0, 0.0, 1.0 },
		{ 1.0, 0.8, 0.2, 1.0 },
        { 0.0, 0.1, 0.7, 1.0 },
		{ 0.6, 0.2, 0.0, 1.0}
};
Tank jiki = { 0 };
Tank teki[10] = { { 0 } };
int flag_kabe[1000];
int TEKI_MAX;
int kabeIndex;
int count_interval[10] = { 0 };
int mySpecialValue = 0;
Powerup powerups[POWERUP_MAX] = { 0 };
int score = 0;
int teki_scores[5] = {
    500, 200, 200, 150, 100  // teki0, ... , teki4
};
int highscore = 0;
int old_score[STAGE_MAX] = { 0 };
double kabeList[1000][3] = { 0 };
int time_count = 0;

/*
 display
-----------------------------------*/
void display(void)
{
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch (current_status) {
        case 0:
            if (!initialized) {
                initSelect();
                initialized = 1;
            }
            drawStageSelect();
            break;

        // easy
        case 1:
            drawGround();
            if (jiki.life > 0) drawJiki();
            for (i = 0;i < TEKI_MAX;i++)
                if (teki[i].life > 0) drawTeki(i);
            drawKabe();
            for (i = 0; i < TAMA_MAX; i++) if (jiki.tama[i].flag) drawJikiProj(i);
            for (i = 0; i < TEKI_MAX; i++)
                for (j = 0;j < TAMA_MAX; j++) if (teki[i].tama[j].flag) drawTekiProj(i, j);
            aim();
            for (i = 0; i < POWERUP_MAX; i++) if (powerups[i].flag)
                drawPowerup(i);
            
            if (!initialized) {
                initStage();
                initialized = 1;
            }
            break;

        // normal
        case 2:
            drawGround();
            if (jiki.life > 0) drawJiki();
            for (i = 0;i < TEKI_MAX;i++)
                if (teki[i].life > 0) drawTeki(i);
            drawKabe();
            for (i = 0; i < TAMA_MAX; i++) if (jiki.tama[i].flag) drawJikiProj(i);
            for (i = 0; i < TEKI_MAX; i++)
                for (j = 0;j < TAMA_MAX; j++) if (teki[i].tama[j].flag) drawTekiProj(i, j);
            aim();
            for (i = 0; i < POWERUP_MAX; i++) if (powerups[i].flag)
                drawPowerup(i);
            
            if (!initialized) {
                initStage();
                initialized = 1;
            }
            break;

        // hard
        case 3:
            drawGround();
            if (jiki.life > 0) drawJiki();
            for (i = 0;i < TEKI_MAX;i++)
                if (teki[i].life > 0) drawTeki(i);
            drawKabe();
            for (i = 0; i < TAMA_MAX; i++) if (jiki.tama[i].flag) drawJikiProj(i);
            for (i = 0; i < TEKI_MAX; i++)
                for (j = 0;j < TAMA_MAX; j++) if (teki[i].tama[j].flag) drawTekiProj(i, j);
            aim();
            for (i = 0; i < POWERUP_MAX; i++) if (powerups[i].flag)
                drawPowerup(i);
            
            if (!initialized) {
                initStage();
                initialized = 1;
            }
            break;
 
        // result
        case 4:
            if (!initialized) {
                initResult();
                initialized = 1;
            }
            drawResult();
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
