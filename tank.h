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
} Projectile;

typedef struct tank
{
	double x;  // x coordinate
	double y;  // y coordinate
	double t;  // direction of a tank[rad]
	double v;  // velocity
	double v_turn;  // rotational speed
	double w;  // length of each side of a tank
	Projectile tama;
} Tank;

#endif
