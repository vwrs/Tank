#include "tank.h"

/*
 TimerFunc for position of projectiles
 -------------------------------------------*/
// TODO: unify projTimerFunc

void projTimerFunc(int index)
{
	int i = 0, j = 0,isTeki = 0, atari[2], damage;
	int *flag;
	double xx, yy, t, w, h, v;
	double *x, *y;
    Tank *tank;
    if (index >= 100) {
        tank = &jiki;
		i = 100;
		j = index - 100; // jiki.tama[j]
		atari[0] = 1;
		atari[1] = 100;
    }
    else {
		i = index / TAMA_MAX;
		j = index % TAMA_MAX; 
		tank = &teki[i];  //teki[i].tama[j]
        isTeki = 1;
		atari[0] = 3;
		atari[1] = index;
    }

	x = &(tank->tama[j].x);
	y = &(tank->tama[j].y);
	t = tank->tama[j].t;
	v = tank->tama[j].v;
	w = tank->tama[j].r * 2;
	h = tank->tama[j].r * 2;
	damage = tank->tama[j].flag;
	flag = &(tank->tama[j].flag);


    if ((*flag))
    {

		*x += cos(t)*v;
		*y += sin(t)*v;
		xx = *x;
		yy = *y;
		if (collision_check(xx, yy, t, w, h, atari))
		{
			*flag = 0;
			switch (atari[0])
			{
			case 0:
				if (isTeki) jiki.life -= damage;
				break;
			case 1:
				jiki.tama[atari[1]].flag = 0;
				break;
			case 2:
				if (isTeki == 0) teki[atari[1]].life -= damage;
			case 3:
				teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].flag = 0;
				break;
			default:
				break;
			}
		}
		else glutTimerFunc(10, projTimerFunc, index);
    }
}




/*
 TimerFunc for position of jiki and teki
 -------------------------------------------*/
void jikiTimerFunc(int value)
{
	int atari[2] = { 0,100 };
    if (jiki.life>0)
    {
        if (mySpecialValue & (1 << 0))
        {
			atari[0] = 0;
            jiki.x += jiki.v*cos(jiki.t);
            jiki.y += jiki.v*sin(jiki.t);
			if (collision_check(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w, atari)) {
				switch (atari[0])
				{
				case 1:
					jiki.tama[atari[1]].flag = 0;
					break;
				case 3:
					jiki.life -= teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].damage;
					teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].flag = 0;
					break;
				default:
					jiki.x -= jiki.v*cos(jiki.t);
					jiki.y -= jiki.v*sin(jiki.t);
					break;
				}
			}
        }
        if (mySpecialValue & (1 << 1))
        {
			atari[0] = 0;
			if (jiki.t < PI) jiki.t += jiki.v_turn;
			else jiki.t += (jiki.v_turn - 2*PI);

			if (collision_check(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w, atari)) {
				switch (atari[0])
				{
				case 1:
					jiki.tama[atari[1]].flag = 0;
					break;
				case 3:
					jiki.life -= teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].damage;
					teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].flag = 0;
					break;
				default:
					jiki.t -= jiki.v_turn;
					break;
				}
			}
		}

        if (mySpecialValue & (1 << 2))
        {
			atari[0] = 0;
			if (-jiki.t < PI) jiki.t -= jiki.v_turn;
			else jiki.t -= (jiki.v_turn - 2*PI);

			if (collision_check(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w, atari)) {
				switch (atari[0])
				{
				case 1:
					jiki.tama[atari[1]].flag = 0;
					break;
				case 3:
					jiki.life -= teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].damage;
					teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].flag = 0;
					break;
				default:
					jiki.t += jiki.v_turn;
					break;
				}
			}
        }
        if (mySpecialValue & (1 << 3))
        {
			atari[0] = 0;
            jiki.x -= jiki.v*cos(jiki.t);
            jiki.y -= jiki.v*sin(jiki.t);
			if (collision_check(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w, atari)) {
				switch (atari[0])
				{
				case 1:
					jiki.tama[atari[1]].flag = 0;
					break;
				case 3:
					jiki.life -= teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].damage;
					teki[atari[1] / TAMA_MAX].tama[atari[1] % TAMA_MAX].flag = 0;
					break;
				default:
					jiki.x += jiki.v*cos(jiki.t);
					jiki.y += jiki.v*sin(jiki.t);
					break;
				}
			}
        }
        glLoadIdentity();
        gluLookAt(-10.0*cos(jiki.t) + jiki.x, -10.0*sin(jiki.t) + jiki.y, 4.0, 0.0 + jiki.x, 0.0 + jiki.y, 1.5, 0.0, 0.0, 1.0);
        
        glutTimerFunc(10, jikiTimerFunc, 0);
    }
}

void teki0TimerFunc(int index)
{
	if (teki[index].life>0) {
		int i, j;
		double MARGIN = 0.01;
		double length;

		length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
			+ (jiki.y - teki[index].y)*(jiki.y - teki[index].y));

		if (teki[index].flag) teki[index].x += teki[index].v;
		else teki[index].x -= teki[index].v;

		for (i = 0;i < kabeIndex;i++)
			if ((flag_kabe[i]) &&
				(collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;

		for (j = 0;j < TEKI_MAX;j++)
			if ((teki[j].life>0) && (j != index) &&
				(collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;

		if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
			|| ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
		{
			if (teki[index].flag)
			{
				teki[index].x -= teki[index].v;
				teki[index].flag = 0;
			}
			else
			{
				teki[index].x += teki[index].v;
				teki[index].flag = 1;
			}
		}

        if (length < 25)
        {
            for (i = 0;i < TAMA_MAX;i++)
                if (teki[index].tama[i].flag == 0) break;
            
            if (i < TAMA_MAX)
            {
                count_interval[index]++;
                if ((count_interval[index] % 100) == 1)
                {
                    count_interval[index] = 1;
                    teki[index].tama[i].flag = 1;
                    teki[index].tama[i].t = atan2(jiki.y - teki[index].y, jiki.x - teki[index].x);
                    teki[index].tama[i].x =
                    teki[index].x + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*cos(teki[index].tama[i].t);
                    teki[index].tama[i].y =
                    teki[index].y + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*sin(teki[index].tama[i].t);
                    projTimerFunc(i + index * TAMA_MAX);
                }
            }
        }
        
        glutTimerFunc(10, teki0TimerFunc, index);
    }
}

void teki1TimerFunc(int index)
{
    if (teki[index].life>0) {
        int i, j;
        double MARGIN = 0.01;
        double length;
        
        length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
                      + (jiki.y - teki[index].y)*(jiki.y - teki[index].y));
        
        if (teki[index].flag) teki[index].x += teki[index].v;
        else teki[index].x -= teki[index].v;
        
        for (i = 0;i < kabeIndex;i++)
            if ((flag_kabe[i]) &&
                (collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;
        
        for (j = 0;j < TEKI_MAX;j++)
            if ((teki[j].life>0) && (j != index) &&
                (collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;
        
        if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
            || ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
        {
            if (teki[index].flag)
            {
                teki[index].x -= teki[index].v;
                teki[index].flag = 0;
            }
            else
            {
                teki[index].x+= teki[index].v;
                teki[index].flag = 1;
            }
        }
        
        if (length < 40)
        {
            for (i = 0;i < TAMA_MAX;i++)
                if (teki[index].tama[i].flag == 0) break;
            
            if (i < TAMA_MAX)
            {
                count_interval[index]++;
                if ((count_interval[index] % 100) == 1)
                {
                    count_interval[index] = 1;
                    teki[index].tama[i].flag = 1;
                    teki[index].tama[i].t = atan2(jiki.y - teki[index].y, jiki.x - teki[index].x);
                    teki[index].tama[i].x =
                    teki[index].x + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*cos(teki[index].tama[i].t);
                    teki[index].tama[i].y =
                    teki[index].y + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*sin(teki[index].tama[i].t);
                    projTimerFunc(i + index * TAMA_MAX);
                }
            }
        }
        glutTimerFunc(10, teki1TimerFunc, index);
    }
}

void teki2TimerFunc(int index)
{
    if (teki[index].life>0) {
        int i, j;
        double MARGIN = 0.01;
        double length;
        
        length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
                      + (jiki.y - teki[index].y)*(jiki.y - teki[index].y));
        
        if (teki[index].flag) teki[index].y += teki[index].v;
        else teki[index].y -= teki[index].v;
        
        for (i = 0;i < kabeIndex;i++)
            if ((flag_kabe[i]) &&
                (collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;
        
        for (j = 0;j < TEKI_MAX;j++)
            if ((teki[j].life>0) && (j != index) &&
                (collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;
        
        if ((i < kabeIndex) || (j<TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
            || ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
        {
            if (teki[index].flag)
            {
                teki[index].y -= teki[index].v;
                teki[index].flag = 0;
            }
            else
            {
                teki[index].y += teki[index].v;
                teki[index].flag = 1;
            }
        }
        
        if (length < 30)
        {
            for (i = 0;i < TAMA_MAX;i++)
                if (teki[index].tama[i].flag == 0) break;
            
            if (i < TAMA_MAX)
            {
                count_interval[index]++;
                if ((count_interval[index] % 100) == 1)
                {
                    count_interval[index] = 1;
                    teki[index].tama[i].flag = 1;
                    teki[index].tama[i].t = atan2(jiki.y - teki[index].y, jiki.x - teki[index].x);
                    teki[index].tama[i].x =
                    teki[index].x + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*cos(teki[index].tama[i].t);
                    teki[index].tama[i].y =
                    teki[index].y + (teki[index].w / 2.0 + teki[index].tama[i].r + MARGIN)*sin(teki[index].tama[i].t);
                    projTimerFunc(i + index * TAMA_MAX);
                }
            }
        }
        glutTimerFunc(10, teki2TimerFunc, index);
    }
}