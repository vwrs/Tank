#ifndef TANK_H
#define TANK_H

/*
 includes
-----------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
// ======== Windows ======
#include <GL/glut.h>
#pragma warning( disable:4996 )
// ====== Mac OS X =======
//#include <OpenGL/gl.h>
//#include <GLUT/glut.h>
// =======================

/*
 consts
-----------------------*/
#define PI (3.1415926536)
#define X (50)  //range of the field
#define Y (50) // range of the field
#define L (1)
#define z (0.5) // height of object
#define STAGE_MAX (3)
#define TAMA_MAX (5)
#define POWERUP_MAX (3)

/*
 structs
-----------------------*/
typedef struct projectile
{
	double x;  // x coordinate
	double y;  // y coordinate
	double t;  // direction of a projectile [rad]
	double v;  // velocity of  a projectile
	double r;  // radious of the projectile
	int damage;  // damage of a projectile
	int flag; //decide whether to draw the projectile
} Projectile;

typedef struct tank
{
	double x;  // x coordinate
	double y;  // y coordinate
	double t;  // direction of a tank[rad]
	double v;  // velocity
	double v_turn;  // rotational speed
	double w;  // length of each side of a tank
	double h;
	double flag; // decide motion of tank
	int life;  // life of a tank
    int score;  // score when destroyed
	Projectile tama[TAMA_MAX];
} Tank;

typedef struct stage
{
    int x;
    int y;
    int level;  // easy:1 normal: 2 hard: 3
    int selected;
    char name[10];  // easy, normal, hard
} Stage;

typedef struct powerup
{
    int type;
    double x;
    double y;
    int flag;
} Powerup;

/*
 global variables
-----------------------*/
enum COLOR { WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY, BLACK, BROWN, SKYBLUE,DARK_BROWN };
extern int current_status;  // select: 0 easy: 1 normal: 2 hard: 3 result: 4
extern int initialized;
extern Stage stages[STAGE_MAX];
extern Tank jiki;
extern Tank teki[10];
extern int TEKI_MAX;
extern int flag_kabe[1000];
extern int kabeIndex;
extern int count_interval[10];
extern GLfloat pos0[];
extern GLfloat pos1[];
extern GLfloat color[][4];
extern double kabeList[][3];
extern int mySpecialValue;
extern Powerup powerups[POWERUP_MAX];
extern int score;
extern int teki_scores[5];
extern int highscore;
extern int old_score[STAGE_MAX];
extern int time_count;

/*
 functions
-----------------------*/
// draw.c
void drawStageSelect(void);
void drawGround(void);
void drawTank(double x, double y, double t, double w, double h, int isTeki);
void drawJiki(void);
void drawTeki(int i);
void drawKabe(void);
void drawJikiProj(int i);
void drawTekiProj(int i, int j);
void aim(void);
void drawPowerup(int index);
void drawResult(void);
void drawTama(double x,double y,double t,double r);

// timerFunc.c
void projTimerFunc(int index);
void jikiTimerFunc(int value);
void teki0TimerFunc(int index);
void teki1TimerFunc(int index);
void teki2TimerFunc(int index);
void teki3TimerFunc(int index);
void teki4TimerFunc(int index);
void timeCount(int value);


void powerupTimerFunc(int index);

// keyboardFunc.c
void selectKeyboardFunc(unsigned char key, int x, int y);
void selectSpecialFunc(int key, int x, int y);
void stageKeyboardFunc(unsigned char key, int x, int y);
void stageSpecialFunc(int key, int x, int y);
void stageSpecialUpFunc(int key, int x, int y);
void resultKeyboardFunc(unsigned char key, int x, int y);

// init.c
void initSelect(void);
void initStage(void);
void initEasy(void);
void initNormal(void);
void initHard(void);
void initResult(void);

// helpers.c
int collision(double x1, double y1, double x2, double y2, double length);
int decideCrash(double x1, double y1, double t1, double w1, double h1, double x2, double y2, double t2, double w2, double h2);
int collision_check(double x, double y, double t, double w, double h, int atari[]);
void calcNormal(GLdouble v0[3], GLdouble v1[3], GLdouble v2[3], GLdouble n[3]);
void idle(void);
void gameover(void);
void scoreRead(void);
void scoreSave(void);
void calNorm(double x1,double y1,double z1,double x2,double y2,double z2, double normal[]);

// tank.c
void display(void);

#endif
