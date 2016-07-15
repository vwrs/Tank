#include "tank.h"


/*
 select
-----------------------*/
void selectKeyboardFunc(unsigned char key, int x, int y)
{
    int i;
    switch(key)
    {
        case ' ':
            for (i = 0; i < STAGE_MAX; i++) {
                if (stages[i].selected)
                    current_status = stages[i].level;
            }
            initialized = 0;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
}

void selectSpecialFunc(int key, int x, int y)
{
    int i;
    switch (key) {
        case GLUT_KEY_RIGHT:
            for (i = 0; i < STAGE_MAX; i++) {
                if (stages[i].selected) {
                    stages[i].selected = 0;
                    if (i == STAGE_MAX-1)
                        stages[0].selected = 1;
                    else
                        stages[i+1].selected = 1;
                    break;
                }
            }
            break;
        case GLUT_KEY_LEFT:
            for (i = 0; i < STAGE_MAX; i++) {
                if (stages[i].selected) {
                    stages[i].selected = 0;
                    if (i == 0)
                        stages[STAGE_MAX-1].selected = 1;
                    else
                        stages[i-1].selected = 1;
                    break;
                }
            }
            break;
    }
}

/*
 stage
 -----------------------*/
void stageKeyboardFunc(unsigned char key, int x, int y)
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
        case 27:  // ESC
            exit(0);
            break;
    }
}

void stageSpecialFunc(int key, int x, int y)
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

void stageSpecialUpFunc(int key, int x, int y)
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
