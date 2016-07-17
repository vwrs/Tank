#include "tank.h"

// collision check
int collision(double x1, double y1,double x2, double y2, double length) // collision check for kabe
{
    
    double MARGIN = 0.01;
    if ((x1 - x2 < length+MARGIN) && (x2 - x1 < length + MARGIN) && (y1 - y2 < length + MARGIN) && (y2 - y1 < length + MARGIN))
    {
        printf("(%.02f,%.02f):(%.02f,%.02f)\n", x2, y2, x1, y1);
        return 1;
    }
    return 0;
}

/**
 * Simple Collision Checker
 * @param t angle of advancing direction of object [rad]
 * @param w length perpendicular to advancing direction of object
 * @param h length pararell to its advancing direction of object
 * @return collided(1) or not(0)
 */
int decideCrash(double x1, double y1, double t1, double w1, double h1,
                double x2, double y2, double t2, double w2, double h2)
{
    int i, j, k, m, u;
    double a[2], b[2];
    double x_corner[2][4],y_corner[2][4], w[2] = { w1,w2 }, h[2] = { h1,h2 }, t[2] = { t1,t2 }, x[2] = { x1,x2 }, y[2] = { y1,y2 };
    double x_corner_turned[2][4], y_corner_turned[2][4];
    
    if ((h1*h1 + w1*w1 + h2*h2 + w2*w2) > (2 * (x1 - x2)*(x1 - x2) + 2 * (y1 - y2)*(y1 - y2)))
    {
        for (i = 0; i <= 1; i++) {
            for (j = 0; j <= 1; j++) {
                for (k = 0; k <= 1; k++) {
                    a[i] = h[i] * (1 - 2 * j) / 2.0;
                    b[i] = w[i] * (1 - 2 * k) / 2.0;
                    x_corner[i][j * 2 + k] = cos(t[i]) * a[i] - sin(t[i]) * b[i] + x[i];
                    y_corner[i][j * 2 + k] = sin(t[i]) * a[i] + cos(t[i]) * b[i] + y[i];
                }
            }
        }
        
        // a[i] = -h[i]/2, b[i] = -w[i]/2
        
        for (i = 0;i < 2;i++) {
            for (j = 0;j < 2;j++) {
                for (k = 0;k < 2;k++)
                {
                    m = 1 - i;
                    u = 2 * j + k;
                    x_corner[i][u] -= x[m];
                    y_corner[i][u] -= y[m];
                    x_corner_turned[i][u] = x_corner[i][u] * cos(t[m]) - y_corner[i][u] * sin(t[m]);
                    y_corner_turned[i][u] = x_corner[i][u] * sin(t[m]) + y_corner[i][u] * cos(t[m]);
                    if ((a[m] < x_corner_turned[i][u]) && (x_corner_turned[i][u] < -a[m])
                        && (b[m] < y_corner_turned[i][u]) && (y_corner_turned[i][u] < -b[m])) return 1;
                }
            }
        }
        return 0;
    }
    else return 0;
}


/** United collsion check
 * atari[2] has following meanings:
 * atari[0] = 0 : jiki
            = 1 : jiki.tama
			= 2 : teki
			= 3 : teki.tama
			= 4 : kabe
			= 5 : edge
 * atari[1] : index
*/
int collision_check(double x, double y, double t, double w, double h, int atari[])
{ 
	int i, j, k, l, m;
	switch (atari[0])
	{
	case 0:
		i = 100;
		j = 100;
		break;
	case 1:
		i = 100;
		j = atari[1];
		break;
	case 2:
		i = atari[1];
		j = 100;
		break;
	case 3:
		i = atari[1] / TAMA_MAX;
		j = atari[1] % TAMA_MAX;
		break;
	default:
		printf("wrong number in atari[0] = %d\n", atari[0]);
		break;
	}

	if (decideCrash(X / 2.0, Y + 5.0, 0, 10.0, X + 20.0, x, y, t, w, h) ||
		decideCrash(X / 2.0, -5.0, 0, 10.0, X + 20.0, x, y, t, w, h) ||
		decideCrash(-5.0, Y / 2.0, 0, Y + 20.0, 10.0, x, y, t, w, h) ||
		decideCrash(X + 5.0, Y / 2.0, 0, Y + 20.0, 10.0, x, y, t, w, h))
	{
		atari[0] = 5;
		atari[1] = 100;
		printf("hit to kabe\n");
		return 1;
	}

	for (k = 0;k < kabeIndex;k++) {
		if ((decideCrash(kabeList[k][0], kabeList[k][1], 0.0, 1.0, 1.0,
			x, y, t, w, h)) && (flag_kabe[k]))
		{
			atari[0] = 4;
			atari[1] = k;
			return 1;
		}
	}

	if ((jiki.life > 0) && (atari[0] != 0) &&
		(decideCrash(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w, x, y, t, w, h)))
	{
		atari[0] = 0;
		atari[1] = 100;
		return 1;
	}

	for (m = 0;m < TAMA_MAX;m++)
	{
		if ((jiki.tama[m].flag) && ((atari[0] != 2) || (j != m)) && (decideCrash(x, y, t, w, h,
			jiki.tama[m].x, jiki.tama[m].y, jiki.tama[m].t, jiki.tama[m].r * 2, jiki.tama[m].r * 2)))
		{
			atari[0] = 1;
			atari[1] = m;
			return 1;
		}

	}


	for (l = 0;l < TEKI_MAX;l++)
	{
		if ((teki[l].life>0) && (decideCrash(x, y, t, w, h,
			teki[l].x, teki[l].y, teki[l].t, teki[l].w, teki[l].w)) && ((atari[0] != 3) || (i != l)))
		{
			atari[0] = 2;
			atari[1] = l;
			return 1;
		}

		for (m = 0;m < TAMA_MAX;m++)
		{
			if ((teki[l].tama[m].flag) && ((i != l) || (j != m)) && (decideCrash(x, y, t, w, h,
				teki[l].tama[m].x, teki[l].tama[m].y, teki[l].tama[m].t, teki[l].tama[m].r * 2, teki[l].tama[m].r * 2)))
			{
				atari[0] = 3;
				atari[1] = l*TAMA_MAX + m;
				return 1;
			}

		}
	}

	return 0;
}

/*
 for drawGround()
----------------------------*/
void calcNormal(GLdouble v0[3], GLdouble v1[3], GLdouble v2[3], GLdouble n[3])
{
    GLdouble v2v[2][3];
    GLdouble vt[3];
    double abs;
    int i;
    for (i = 0; i < 3; i++)
    {
        v2v[0][i] = v1[i] - v0[i];
        v2v[1][i] = v2[i] - v0[i];
    }
    vt[0] = v2v[0][1] * v2v[1][2] - v2v[0][2] * v2v[1][1];
    vt[1] = v2v[0][2] * v2v[1][0] - v2v[0][0] * v2v[1][2];
    vt[2] = v2v[0][0] * v2v[1][1] - v2v[0][1] * v2v[1][0];
    abs = sqrt(vt[0] * vt[0] + vt[1] * vt[1] + vt[2] * vt[2]);
    for (i = 0; i < 3; i++)
        n[i] = vt[i] / abs;
}

void idle(void)
{
    glutPostRedisplay();
}
