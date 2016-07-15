#include <stdio.h>
#include <math.h>
#include "tank.h"

int decidecrash(double w1, double h1, double p1, double x1, double y1, double w2, double h2, double p2, double x2, double y2) {
	int i, j, k, u;
	double corner[2][4][2], w[2] = { w1,w2 }, h[2] = { h1,h2 }, p[2] = { p1,p2 }, x[2] = { x1,x2 }, y[2] = { y1,y2 };

	//長方形の頂点をcornerとして定義
	for (i = 0; i <= 1; i++) {
		for (j = 0; j <= 1; j++) {
			for (k = 0; k <= 1; k++) {
				int a = w1 / 2 * pow(-1, j);
				int b = h1 / 2 * pow(-1, k);
				corner[i][j * 2 + k][0] = cos(p[i])*a - sin(p[i])*b + x[i];
				corner[i][j * 2 + k][1] = cos(p[i])*b + sin(p[i])*a + y[i];
			}
		}
	}


	for (i = 0; i <= 1; i++) {
		for (j = 0; j <= 1; j++) {
			for (k = 0; k <= 1; k++) {
				if (i == 0) u = 1;
				if (i == 1) u = 0;

				//片方の長方形の頂点のうち一つを、もう片方の長方形の中心を原点とした座標系に変換(rx,ry)
				double a = corner[i][j * 2 + k][0] - x[u];
				double b = corner[i][j * 2 + k][1] - y[u];
				double rx = cos(p[u])*a + sin(p[u])*b;
				double ry = cos(p[u])*b - sin(p[u])*a;

				//当たり判定
				if (fabs(rx) < w[u] && fabs(ry) < h[u])return 1;
			}
		}
	}
	return 0;

}