#ifndef TANK_H
#define TANK_H

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

#define TAMA_MAX 5
#define kabeIndex 12

typedef struct tank
{
	double x;  // x coordinate
	double y;  // y coordinate
	double t;  // direction of a tank[rad]
	double v;  // velocity
	double v_turn;  // rotational speed
	double w;  // length of each side of a tank
	int life;  // life of a tank
	Projectile tama[TAMA_MAX];
} Tank;

#endif
