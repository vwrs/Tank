#include "tank.h"

// unite collision check
int collision_check(double x, double y, double t, double w, double h, int *atari)
{ /*
  atari[1] has following meanings 
		atari[0] : isKabe * 2^0 + isTeki * 2^1 +isTama * 2^2  
		atari[1] : index
  */
	int i, j, k, l, m;
	if ((atari[0]=4))
	{
		i = 100;
		j = atari[1]; // jiki.tama[j]
	}
	else if (atari[0]=0)
	{
		i = 100;
		j = 100;    //jiki
	}
	else if (atari[0]=6)
	{
		i = atari[1] / TAMA_MAX;
		j = atari[1] % TAMA_MAX; // teki[i].tama[j]
	}
	else if(atari[0]=2)
	{
		i = atari[1];
		j = 100;       //teki[i]
	}


	for (k = 0;k < kabeIndex;k++) {
		if ((decidecrash(kabeList[k][0], kabeList[k][1], 0.0, 1.0, 1.0,
						x, y, t, w, h))&&(flag_kabe[k]))
		{
			atari[0] = 1;
			atari[1] = k;
			return 1;
		}
	}

	if ((jiki.life > 0) && (atari[0]!=0) &&
		(decidecrash(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w, x, y, t, w, h)))
	{
		atari[0] = 0;
		atari[1] = 100;
		return 1;
	}

	for (m = 0;m < TAMA_MAX;m++)
	{
		if ((jiki.tama[m].flag) && ((atari[0] != 4) || (j != m)) && (decidecrash(x, y, t, w, h,
			jiki.tama[m].x, jiki.tama[m].y, jiki.tama[m].t, jiki.tama[m].r * 2, jiki.tama[m].r * 2)))
		{
			atari[0] = 4;
			atari[1] = m;
			return 1;
		}

	}


	for (l = 0;l < TEKI_MAX;l++)
	{
		if ((teki[l].life>0) && (decidecrash(x, y, t, w, h,
			teki[l].x, teki[l].y, teki[l].t, teki[l].w, teki[l].w)) && (j != 100) && (i != l))
		{
			atari[0] = 2;
			atari[1] = l;
			return 1;
		}

		for (m = 0;m < TAMA_MAX;m++)
		{
			if ((teki[l].tama[m].flag) && (i != l) && (j != m) && (decidecrash(x, y, t, w, h,
				teki[l].tama[m].x, teki[l].tama[m].y, teki[l].tama[m].t, teki[l].tama[m].r * 2, teki[l].tama[m].r * 2)))
			{
				atari[0] = 6;
				atari[1] = l*TAMA_MAX + m;
				return 1;
			}

		}
	}
	
	return 0;
}

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

/*
 TimerFunc for position of projectiles
 -------------------------------------------*/
// TODO: unify projTimerFunc

void projTimerFunc(int index)
{
    int i = 0, j = 0, k = 0, isTeki = 0;
    double MARGIN = 0.25;
    Tank *tank;
    if (index >= 100) {
        tank = &jiki;
        index -= 100;
    }
    else {
        tank = &teki[index];
        isTeki = 1;
    }
    
    if ((tank->life > 0)&&(tank->tama[index].flag))
    {
        tank->tama[index].x += cos(tank->tama[index].t)*tank->tama[index].v;
        tank->tama[index].y += sin(tank->tama[index].t)*tank->tama[index].v;
        
        /* collision check
         -----------------------*/
        if (isTeki) {
            if (collision(jiki.x, jiki.y, tank->tama[j].x, tank->tama[j].y, jiki.w / 2.0 + tank->tama[j].r))
            {
                jiki.life -= tank->tama[j].damage;
                tank->tama[j].flag = 0;
            }
        }
        
        for (k = 0;k < kabeIndex;k++)
            if ((flag_kabe[k]) && (collision(kabeList[k][0], kabeList[k][1],
                                             tank->tama[index].x, tank->tama[index].y, tank->tama[index].r + 0.5))) break;
        
        for (i = 0;i < TEKI_MAX;i++)
        {
            if (isTeki && index == i) continue;
            if ((teki[i].life>0) && (collision(teki[i].x, teki[i].y,
                                               tank->tama[index].x, tank->tama[index].y, teki[i].w / 2.0 + tank->tama[index].r)))
            {
                j = TAMA_MAX;
                break;
            }
            for (j = 0;j < TAMA_MAX;j++)
                if ((teki[i].tama[j].flag) && (collision(teki[i].tama[j].x, teki[i].tama[j].y, tank->tama[index].x, tank->tama[index].y, teki[i].tama[j].r + tank->tama[index].r))) break;
            if (j < TAMA_MAX) break;
        }
        
        if ((Y*L < tank->tama[index].y - MARGIN) || (0 * L > tank->tama[index].x + MARGIN)
            || ((X - 1)*L < tank->tama[index].x - MARGIN) || (0 * L > tank->tama[index].y + MARGIN))
        {
            tank->tama[index].flag = 0;
        }
        else if (collision(tank->x, tank->y, tank->tama[index].x, tank->tama[index].y, tank->w / 2.0 + tank->tama[index].r))
        {
            tank->tama[index].flag = 0;
        }
        else if (k < kabeIndex)
        {
            tank->tama[index].flag = 0;
            flag_kabe[k] = 0;
        }
        else if ((i < TEKI_MAX) && (j < TAMA_MAX))
        {
            tank->tama[index].flag = 0;
            teki[i].tama[j].flag = 0;
        }
        else if (i < TEKI_MAX)
        {
            tank->tama[index].flag = 0;
            teki[i].life -= tank->tama[index].damage;
        }
        else glutTimerFunc(10, projTimerFunc, index);
    }
}



////////////////////////////////////////////////////////////////////////
void projJikiTimerFunc(int index)
{
    int i = 0, j = 0, k;
    double MARGIN = 0.25;
    if ((jiki.life > 0)&&(jiki.tama[index].flag))
    {
        jiki.tama[index].x += cos(jiki.tama[index].t)*jiki.tama[index].v;
        jiki.tama[index].y += sin(jiki.tama[index].t)*jiki.tama[index].v;
        
        for (k = 0;k < kabeIndex;k++)
            if ((flag_kabe[k]) && (collision(kabeList[k][0], kabeList[k][1],
                                             jiki.tama[index].x, jiki.tama[index].y, jiki.tama[index].r + 0.5))) break;
        
        for (i = 0;i < TEKI_MAX;i++)
        {
            if ((teki[i].life>0) && (collision(teki[i].x, teki[i].y,
                                               jiki.tama[index].x, jiki.tama[index].y, teki[i].w / 2.0 + jiki.tama[index].r)))
            {
                j = TAMA_MAX;
                break;
            }
            for (j = 0;j < TAMA_MAX;j++)
                if ((teki[i].tama[j].flag) && (collision(teki[i].tama[j].x, teki[i].tama[j].y,
                                                         jiki.tama[index].x, jiki.tama[index].y, teki[i].tama[j].r + jiki.tama[index].r))) break;
            if (j < TAMA_MAX) break;
        }
        
        if ((Y*L < jiki.tama[index].y - MARGIN) || (0 * L > jiki.tama[index].x + MARGIN)
            || ((X - 1)*L < jiki.tama[index].x - MARGIN) || (0 * L > jiki.tama[index].y + MARGIN))
        {
            jiki.tama[index].flag = 0;
        }
        else if (collision(jiki.x, jiki.y,
                           jiki.tama[index].x, jiki.tama[index].y, jiki.w / 2.0 + jiki.tama[index].r))
        {
            jiki.tama[index].flag = 0;
        }
        else if (k < kabeIndex)
        {
            jiki.tama[index].flag = 0;
            flag_kabe[k] = 0;
        }
        else if ((i < TEKI_MAX) && (j < TAMA_MAX))
        {
            jiki.tama[index].flag = 0;
            teki[i].tama[j].flag = 0;
        }
        else if (i < TEKI_MAX)
        {
            jiki.tama[index].flag = 0;
            teki[i].life -= jiki.tama[index].damage;
        }
        else glutTimerFunc(10, projJikiTimerFunc, index);
    }
}

void projTekiTimerFunc(int index)
{
	int i, j, k, l = 0, m = 0;
	double MARGIN = 0.25;
	j = index % TAMA_MAX;
	i = index / TAMA_MAX;

	if ((teki[i].tama[j].flag) && (teki[i].life>0))
	{
		teki[i].tama[j].x += cos(teki[i].tama[j].t)*teki[i].tama[j].v;
		teki[i].tama[j].y += sin(teki[i].tama[j].t)*teki[i].tama[j].v;

		for (k = 0;k < kabeIndex;k++) // collision check for kabe
			if ((flag_kabe[k]) && (collision(kabeList[k][0], kabeList[k][1],
				teki[i].tama[j].x, teki[i].tama[j].y, teki[i].tama[j].r + 0.5))) break;

		if (k >= kabeIndex) //collison check for other tama and teki
		{
			for (l = 0;l < TEKI_MAX;l++)
			{
				if ((teki[l].life>0) && (collision(teki[i].tama[j].x, teki[i].tama[j].y,
					teki[l].x, teki[l].y, teki[i].tama[j].r + teki[l].w / 2.0)))
				{
					m = TAMA_MAX;
					break;
				}
				for (m = 0;m < TAMA_MAX;m++)
					if ((teki[l].tama[m].flag) && (l != i) && (m != j) && (collision(teki[l].tama[m].x, teki[l].tama[m].y,
						teki[i].tama[j].x, teki[i].tama[j].y, teki[i].tama[j].r + teki[l].tama[m].r)))
						break;
				if (m < TAMA_MAX) break;
			}
		}



		if ((Y*L < teki[i].tama[j].y - MARGIN) || (0 * L > teki[i].tama[j].x + MARGIN)
			|| ((X - 1)*L < teki[i].tama[j].x - MARGIN) || (0 * L > teki[i].tama[j].y + MARGIN))
		{
			teki[i].tama[j].flag = 0;
		}
		else if (decidecrash(jiki.x, jiki.y, jiki.t, jiki.w, jiki.w,
				teki[i].tama[j].x, teki[i].tama[j].y, teki[i].tama[j].t, teki[i].tama[j].r * 2, teki[i].tama[j].r * 2))
		{
			jiki.life -= teki[i].tama[j].damage;
			teki[i].tama[j].flag = 0;
			printf("%d\n", jiki.life);
		}
		else if (k < kabeIndex)
		{
			flag_kabe[k] = 0;
			teki[i].tama[j].flag = 0;
		}
		else if ((l < TEKI_MAX) && (m < TAMA_MAX))
		{
			teki[i].tama[j].flag = 0;
			teki[l].tama[m].flag = 0;
		}
		else if (l < TEKI_MAX) teki[i].tama[j].flag = 0;
		else glutTimerFunc(10, projTekiTimerFunc, index);
	}
    else teki[i].tama[j].flag = 0;
}


/*
 TimerFunc for position of jiki and teki
 -------------------------------------------*/
void jikiTimerFunc(int value)
{
    int i,j;
    double MARGIN = 0.01;
    if (jiki.life>0)
    {
        if (mySpecialValue & (1 << 0))
        {
            jiki.x += jiki.v*cos(jiki.t);
            jiki.y += jiki.v*sin(jiki.t);
            
            for (i = 0; i < kabeIndex;i++)
                if ((flag_kabe[i]) &&
                    (collision(kabeList[i][0], kabeList[i][1], jiki.x, jiki.y, jiki.w / 2.0 + 0.5))) break;
            for (j = 0;j < TEKI_MAX;j++)
                if ((teki[j].life>0) &&
                    (collision(teki[j].x, teki[j].y, jiki.x, jiki.y, jiki.w / 2.0 + teki[j].w / 2.0))) break;
            
            if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < jiki.y - MARGIN) || (0 * L > jiki.x + MARGIN)
                || ((X - 1)*L < jiki.x - MARGIN) || (0 * L > jiki.y + MARGIN))
            {
                jiki.x -= jiki.v*cos(jiki.t);
                jiki.y -= jiki.v*sin(jiki.t);
            }
        }
        if (mySpecialValue & (1 << 1))
        {
            jiki.t += jiki.v_turn;
        }
        if (mySpecialValue & (1 << 2))
        {
            jiki.t -= jiki.v_turn;
        }
        if (mySpecialValue & (1 << 3))
        {
            jiki.x -= jiki.v*cos(jiki.t);
            jiki.y -= jiki.v*sin(jiki.t);
            
            for (i = 0; i < kabeIndex;i++)
                if ((flag_kabe[i]) &&
                    (collision(kabeList[i][0], kabeList[i][1], jiki.x, jiki.y, jiki.w / 2.0 + 0.5))) break;
            
            for (j = 0;j < TEKI_MAX;j++)
                if ((teki[j].life>0) &&
                    (collision(teki[j].x, teki[j].y, jiki.x, jiki.y, jiki.w / 2.0 + teki[j].w / 2.0))) break;
            
            if ((i < kabeIndex) || (j < TEKI_MAX) || (Y*L < jiki.y - MARGIN) || (0 * L > jiki.x + MARGIN)
                || ((X - 1)*L < jiki.x - MARGIN) || (0 * L > jiki.y + MARGIN))
            {
                jiki.x += jiki.v*cos(jiki.t);
                jiki.y += jiki.v*sin(jiki.t);
            }
        }
        glLoadIdentity();
        gluLookAt(-10.0*cos(jiki.t) + jiki.x, -10.0*sin(jiki.t) + jiki.y, 4.0, 0.0 + jiki.x, 0.0 + jiki.y, 1.5, 0.0, 0.0, 1.0);
        
        glutTimerFunc(10, jikiTimerFunc, 0);
    }
}

void teki0TimerFunc(int index)
{
    if (teki[index].life > 0) {
        int i, j;
        double MARGIN = 0.01;
        double length;
        
        length = sqrt((jiki.x - teki[index].x)*(jiki.x - teki[index].x)
                      + (jiki.y - teki[index].y)*(jiki.y - teki[index].y));
        
        teki[index].x += teki[index].v*cos(teki[index].t);
        teki[index].y += teki[index].v*sin(teki[index].t);
        
        for (i = 0;i < kabeIndex;i++)
            if ((flag_kabe[i])&&
                (collision(kabeList[i][0], kabeList[i][1], teki[index].x, teki[index].y, teki[index].w / 2.0 + 0.5))) break;
        
        for (j = 0;j < TEKI_MAX;j++)
            if ((teki[j].life>0) && (j != index) &&
                (collision(teki[j].x, teki[j].y, teki[index].x, teki[index].y, teki[j].w / 2.0 + teki[index].w / 2.0))) break;
        
        if ((i < kabeIndex)||(j<TEKI_MAX) || (Y*L < teki[index].y - MARGIN) || (0 * L > teki[index].x + MARGIN)
            || ((X - 1)*L < teki[index].x - MARGIN) || (0 * L > teki[index].y + MARGIN))
        {
            teki[index].x -= teki[index].v*cos(teki[index].t);
            teki[index].y -= teki[index].v*sin(teki[index].t);
            teki[index].t = (rand() / (double)RAND_MAX) * 2.0 * PI;
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
                    projTekiTimerFunc(i + index * TAMA_MAX);
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
                    projTekiTimerFunc(i + index * TAMA_MAX);
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
                    projTekiTimerFunc(i + index * TAMA_MAX);
                }
            }
        }
        glutTimerFunc(10, teki2TimerFunc, index);
    }
}