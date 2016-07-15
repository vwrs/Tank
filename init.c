#include "tank.h"

void idle(void)
{
    glutPostRedisplay();
}

void initSelect(void)
{
    /* variables
     ----------------------*/

    /* ------------------ */
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glutKeyboardFunc(selectKeyboardFunc);
    glutSpecialFunc(selectSpecialFunc);
    
    glutIdleFunc(idle);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, 1, .1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 10.0, 5.0, 5.0, 0, 0.0, 1.0, 0.0);
    
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
    
}

void initStage(void)
{
    int i,j;
    srand((unsigned)time(NULL));
    /* variables
     ----------------------*/
    for (i = 0;i < kabeIndex;i++) flag_kabe[i] = 1;
    jiki.t = PI/2.0;
    jiki.w = 1.0;
    jiki.v = 0.4;
    jiki.v_turn = 0.06;
    jiki.life = 50;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].v = 0.8;
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
        teki[j].v = 0.2;
        teki[j].v_turn = 0.03;
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.5;
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
    
    glutKeyboardFunc(stageKeyboardFunc);
    glutSpecialFunc(stageSpecialFunc);
    glutSpecialUpFunc(stageSpecialUpFunc);
    
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
