#ifndef TANK_H
#define TANK_H

typedef struct projectile
{
	double x;  // x coordinate
	double y;  // y coordinate
	double t;  // direction of a projectile [rad]
	double v;  // velocity of  a projectile
	double w;  // length of the shorter side
	double h;  // length of the longer side
	int flag_tama; //decide whether to draw the projectile
} Projectile;

typedef struct tank
{
	double x;  // x coordinate
	double y;  // y coordinate
	double t;  // direction of a tank[rad]
	double v;  // velocity
	double v_turn;  // rotational speed
	double w;  // length of each side of a tank
	double flag_tank; // this changes motion of the tank
	Projectile tama[5];
} Tank;

#endif
