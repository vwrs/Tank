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
