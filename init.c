#include "tank.h"

//======== for visual studio =======//
#pragma warning( disable:4996 )


void initSelect(void)
{
    int i;
    /* variables
     ----------------------*/
    stages[0].selected = 1;
    for (i = 0; i < STAGE_MAX; i++) {
        stages[i].level = i + 1;
        stages[i].x = (i+1) * 10;
        if (i < 2) stages[i].x -= 2;
        stages[i].y = 20;
    }
    strncpy(stages[0].name, "easy", 4);
    strncpy(stages[1].name, "normal", 6);
    strncpy(stages[2].name, "hard", 4);
    
    /* ------------------ */
    glClearColor(1.0, 1.0, 1.0, 1.0);  // background color
    glutKeyboardFunc(selectKeyboardFunc);
    glutSpecialFunc(selectSpecialFunc);
    glutIdleFunc(idle);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, 1, 0, 10);
}

void initStage(void)
{
    int i;
    srand((unsigned)time(NULL));
    /* variables
    ----------------------*/
    for (i = 0;i < kabeIndex;i++) flag_kabe[i] = 1;
    jiki.t = PI/2.0;
    jiki.w = 1.0;
    /*--------------------*/
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
    switch (current_status) {
        case 1: initEasy(); break;
        case 2: initNormal(); break;
        case 3: initHard(); break;
    }
}

void initEasy(void)
{
    int i, j;
    jiki.v = 0.133;
	jiki.x = 1;
	jiki.y = 1;
    jiki.v_turn = 0.02;
    jiki.life = 50;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].v = 0.33;
        jiki.tama[i].r = 0.5;
        jiki.tama[i].damage = 1;
    }
    teki[0].x = X / 2.0;
    teki[0].y = Y / 2.0;
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
        teki[j].t = rand();
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.166;
            teki[j].tama[i].damage = 1;
            teki[j].tama[i].r = 0.3;
        }
    }
    jikiTimerFunc(0);
    teki0TimerFunc(0);
    teki1TimerFunc(1);
    teki2TimerFunc(2);
}

void initNormal(void)
{
    int i, j;
    jiki.v = 0.13;
    jiki.v_turn = 0.06;
    jiki.life = 20;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].v = 0.25;
        jiki.tama[i].r = 0.3;
        jiki.tama[i].damage = 1;
    }
    
    teki[0].x = X / 2.0;
    teki[0].y = Y / 2.0;
    teki[1].x = X / 4.0;
    teki[1].y = Y / 4.0;
    teki[2].x = X * 3.0 / 4.0;
    teki[2].y = Y / 4.0;
    
    for (j = 0;j < TEKI_MAX;j++)
    {
        teki[j].life = 3;
        teki[j].w = 1.0;
        teki[j].v = 0.07;
        teki[j].v_turn = 0.03;
        teki[j].t = rand();
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.2;
            teki[j].tama[i].damage = 1;
            teki[j].tama[i].r = 0.3;
        }
    }
    jikiTimerFunc(0);
    teki0TimerFunc(0);
    teki1TimerFunc(1);
    teki2TimerFunc(2);
}

void initHard(void)
{
    int i, j;
    jiki.v = 0.1;
    jiki.v_turn = 0.06;
    jiki.life = 15;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].v = 0.2;
        jiki.tama[i].r = 0.2;
        jiki.tama[i].damage = 1;
    }
    
    teki[0].x = X / 2.0;
    teki[0].y = Y / 2.0;
    teki[1].x = X / 4.0;
    teki[1].y = Y / 4.0;
    teki[2].x = X * 3.0 / 4.0;
    teki[2].y = Y / 4.0;
    
    for (j = 0;j < TEKI_MAX;j++)
    {
        teki[j].life = 10;
        teki[j].w = 1.0;
        teki[j].v = 0.05;
        teki[j].v_turn = 0.1;
        teki[j].t = rand();
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.1;
            teki[j].tama[i].damage = 2;
            teki[j].tama[i].r = 0.3;
        }
    }
    jikiTimerFunc(0);
    teki0TimerFunc(0);
    teki1TimerFunc(1);
    teki2TimerFunc(2);
}
