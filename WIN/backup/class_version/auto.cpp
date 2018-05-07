#include "auto.hpp"

K_plan::K_plan(player &m,player &e)
{
    enemy = &e;
    me = &m;
    go_all = 10;
    go_atk = 3;
    go_def = 6;
    go_ran = 8;
}

void K_plan::set_diff(int diff)
{
	switch(diff)
	{
		case 0:
			go_atk = 0;
			go_def = 0;
			go_ran = 1;
            break;
		case 1:
			go_atk = 1;
			go_def = 2;
			go_ran = 4;
            break;
        case 2:
			go_atk = 2;
			go_def = 5;
			go_ran = 7;
            break;
        case 3:
			go_atk = 2;
			go_def = 7;
			go_ran = 9;
            break;
        case 4:
			go_atk = 3;
			go_def = 6;
			go_ran = 8;
            break;
        case 5:
			go_atk = 2;
			go_def = 8;
			go_ran = 10;
            break;
        default:
            break;
	}
}

void K_plan::set_diff(int a,int d,int r)
{
    go_atk = a;
    go_def = d;
    go_ran = r;
}


void K_plan::plan_init()
{
	plan kp;
	kp.digit_opp = 0;
	kp.digit = 0;
	for(int i=0;i<4;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		first[i] = kp;
	}
	for(int i=0;i<16;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		second[i] = kp;
	}
	for(int i=0;i<64;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		third[i] = kp;
	}
	for(int i=0;i<256;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		fourth[i] = kp;
	}
}

bool K_plan::plan_run()
{
	while(kill_plan.size() != 0) {kill_plan.erase(kill_plan.begin());} //clean

	for(int i=0;i<4;i++)
	{
		if(i%4 == 0) //'+';
		{
			first[i].digit_opp = enemy->digit;
			first[i].digit = me->bullet[0];
			first[i].result = (first[i].digit_opp+first[i].digit)%10;
			if(first[i].result == 0)
			{
				kill_plan.push_back(first[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			first[i].digit_opp = enemy->digit;
			first[i].digit = me->bullet[0];
			first[i].result = (first[i].digit_opp-first[i].digit+10)%10;
			if(first[i].result == 0)
			{
				kill_plan.push_back(first[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			first[i].digit_opp = enemy->digit;
			first[i].digit = me->bullet[0];
			first[i].result = (first[i].digit_opp*first[i].digit)%10;
			if(first[i].result == 0)
			{
				kill_plan.push_back(first[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			first[i].digit_opp = enemy->digit;
			first[i].digit = me->bullet[0];
			first[i].result = (int)pow(first[i].digit_opp,first[i].digit)%10;
			if(first[i].result == 0)
			{
				kill_plan.push_back(first[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<16;i++)
	{
		if(i%4 == 0) //'+';
		{
			second[i].digit_opp = first[i/4].result;
			second[i].digit = me->bullet[1];
			second[i].result = (second[i].digit_opp+second[i].digit)%10;
			if(second[i].result == 0)
			{
				kill_plan.push_back(first[i/4]);
				kill_plan.push_back(second[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			second[i].digit_opp = first[i/4].result;
			second[i].digit = me->bullet[1];
			second[i].result = (second[i].digit_opp-second[i].digit+10)%10;
			if(second[i].result == 0)
			{
				kill_plan.push_back(first[i/4]);
				kill_plan.push_back(second[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			second[i].digit_opp = first[i/4].result;
			second[i].digit = me->bullet[1];
			second[i].result = (second[i].digit_opp*second[i].digit)%10;
			if(second[i].result == 0)
			{
				kill_plan.push_back(first[i/4]);
				kill_plan.push_back(second[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			second[i].digit_opp = first[i/4].result;
			second[i].digit = me->bullet[1];
			second[i].result = (int)pow(second[i].digit_opp,second[i].digit)%10;
			if(second[i].result == 0)
			{
				kill_plan.push_back(first[i/4]);
				kill_plan.push_back(second[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<64;i++)
	{
		if(i%4 == 0) //'+';
		{
			third[i].digit_opp = second[i/4].result;
			third[i].digit = me->bullet[2];
			third[i].result = (third[i].digit_opp+third[i].digit)%10;
			if(third[i].result == 0)
			{
				kill_plan.push_back(first[i/16]);
				kill_plan.push_back(second[i/4]);
				kill_plan.push_back(third[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			third[i].digit_opp = second[i/4].result;
			third[i].digit = me->bullet[2];
			third[i].result = (third[i].digit_opp-third[i].digit+10)%10;
			if(third[i].result == 0)
			{
				kill_plan.push_back(first[i/16]);
				kill_plan.push_back(second[i/4]);
				kill_plan.push_back(third[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			third[i].digit_opp = second[i/4].result;
			third[i].digit = me->bullet[2];
			third[i].result = (third[i].digit_opp*third[i].digit)%10;
			if(third[i].result == 0)
			{
				kill_plan.push_back(first[i/16]);
				kill_plan.push_back(second[i/4]);
				kill_plan.push_back(third[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			third[i].digit_opp = second[i/4].result;
			third[i].digit = me->bullet[2];
			third[i].result = (int)pow(third[i].digit_opp,third[i].digit)%10;
			if(third[i].result == 0)
			{
				kill_plan.push_back(first[i/16]);
				kill_plan.push_back(second[i/4]);
				kill_plan.push_back(third[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<256;i++)
	{
		if(i%4 == 0) //'+';
		{
			fourth[i].digit_opp = third[i/4].result;
			fourth[i].digit = me->bullet[3];
			fourth[i].result = (fourth[i].digit_opp+fourth[i].digit)%10;
			if(fourth[i].result == 0)
			{
				//fourth_blue[i].mark = '+';
				kill_plan.push_back(first[i/64]);
				kill_plan.push_back(second[i/16]);
				kill_plan.push_back(third[i/4]);
				kill_plan.push_back(fourth[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			fourth[i].digit_opp = third[i/4].result;
			fourth[i].digit = me->bullet[3];
			fourth[i].result = (fourth[i].digit_opp-fourth[i].digit+10)%10;
			if(fourth[i].result == 0)
			{
				kill_plan.push_back(first[i/64]);
				kill_plan.push_back(second[i/16]);
				kill_plan.push_back(third[i/4]);
				kill_plan.push_back(fourth[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			fourth[i].digit_opp = third[i/4].result;
			fourth[i].digit = me->bullet[3];
			fourth[i].result = (fourth[i].digit_opp*fourth[i].digit)%10;
			if(fourth[i].result == 0)
			{
				kill_plan.push_back(first[i/64]);
				kill_plan.push_back(second[i/16]);
				kill_plan.push_back(third[i/4]);
				kill_plan.push_back(fourth[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			fourth[i].digit_opp = third[i/4].result;
			fourth[i].digit = me->bullet[3];
			fourth[i].result = (int)pow(fourth[i].digit_opp,fourth[i].digit)%10;
			if(fourth[i].result == 0)
			{
				kill_plan.push_back(first[i/64]);
				kill_plan.push_back(second[i/16]);
				kill_plan.push_back(third[i/4]);
				kill_plan.push_back(fourth[i]);
				return 1;
			}
		}
	}

	return 0;
}

void K_plan::go_attack()
{
	int aim_row = enemy->row;
	int aim_col = enemy->col;
	switch(enemy->toward)
	{
		case 'u':
			if(enemy->row-1>0 && !(enemy->row-1==me->row&&enemy->col==me->col))
				aim_row--;
			break;
		case 'd':
			if(enemy->row+1<=ROW && !(enemy->row+1==me->row&&enemy->col==me->col))
				aim_row++;
			break;
		case 'l':
			if(enemy->col-1>0 && !(enemy->row==me->row&&enemy->col-1==me->col))
				aim_col--;
			break;
		case 'r':
			if(enemy->col+1<=COL && !(enemy->row==me->row&&enemy->col+1==me->col))
				aim_col++;
			break;
	}

	if(me->row==aim_row && abs(me->col-aim_col)<STEP-1) //attack
	{
		me->status='a';
		if(me->col>aim_col) me->atk_toward='l';
		else me->atk_toward='r';

		me->type = kill_plan[0].mark;
		kill_plan.erase(kill_plan.begin());
		return;
	}
	else if(me->col==aim_col && abs(me->row-aim_row)<STEP-1)
	{
		me->status='a';
		if(me->row>aim_row) me->atk_toward='u';
		else me->atk_toward='d';

		me->type = kill_plan[0].mark;
		kill_plan.erase(kill_plan.begin());
		return;
	}
	else me->status='m';

	if(abs(me->row-aim_row)>=STEP-1 && abs(me->col-aim_col)>=STEP-1) //攻击范围外，从远处靠近
	{
		if(abs(me->row-aim_row) > abs(me->col-aim_col))
		{
			if(me->row>aim_row) me->toward = 'u';
			else me->toward = 'd';
		}
		else
		{
			if(me->col>aim_col) me->toward = 'l';
			else me->toward = 'r';
		}
	}
	else if(abs(me->row-aim_row)>=STEP-1)
	{
		if(me->row>aim_row) me->toward = 'u';
		else me->toward = 'd';
	}
	else if(abs(me->col-aim_col)>=STEP-1)
	{
		if(me->col>aim_col) me->toward = 'l';
		else me->toward = 'r';
	}
	else //攻击范围内，从近处逼近
	{
		if(abs(me->row-aim_row) < abs(me->col-aim_col))
		{
			if(me->row>aim_row) me->toward = 'u';
			else me->toward = 'd';
		}
		else
		{
			if(me->col>aim_col) me->toward = 'l';
			else me->toward = 'r';
		}
	}
}

void K_plan::go_defence() //简易版(重攻击轻回避)
{
	int aim_row = enemy->row;
	int aim_col = enemy->col;
	switch(enemy->toward)
	{
		case 'u':
			if(enemy->row-1>0 && !(enemy->row-1==me->row&&enemy->col==me->col))
				aim_row--;
			break;
		case 'd':
			if(enemy->row+1<=ROW && !(enemy->row+1==me->row&&enemy->col==me->col))
				aim_row++;
			break;
		case 'l':
			if(enemy->col-1>0 && !(enemy->row==me->row&&enemy->col-1==me->col))
				aim_col--;
			break;
		case 'r':
			if(enemy->col+1<=COL && !(enemy->row==me->row&&enemy->col+1==me->col))
				aim_col++;
			break;
	}

	if(me->row==aim_row && abs(me->col-aim_col)<STEP-1) //attack
	{
		me->status='m';
		if(enemy->toward == 'u') me->toward = 'd';
		else if(enemy->toward == 'd') me->toward = 'u';
		else
		{
			if(me->row<ROW/2) me->toward = 'd';
			else me->toward = 'u';
		}
		return;
	}
	else if(me->col==aim_col && abs(me->row-aim_row)<STEP-1)
	{
		me->status='m';
		if(enemy->toward == 'l') me->toward = 'r';
		else if(enemy->toward == 'r') me->toward = 'l';
		else
		{
			if(me->col<COL/2) me->toward = 'r';
			else me->toward = 'l';
		}
		return;
	}
}

void K_plan::random()
{
	me->status='m';
	switch(rand()%4)
	{
		case 0:
			me->toward = 'u';
			break;
		case 1:
			me->toward = 'd';
			break;
		case 2:
			me->toward = 'l';
			break;
		case 3:
			me->toward = 'r';
			break;
	}
}

void K_plan::auto_run()
{
	if(!kill_plan.size() || kill_plan[0].digit_opp!=enemy->digit) plan_run();

	int mode = rand()%go_all;
	if(mode < go_atk) go_attack(); //增大失误率
	else if(mode < go_def) go_defence();
	else if(mode < go_ran) random();
}


/**********************************  deemo  ***********************************/

int r[3];
void ai_r()
{
	r[0]=rand()%10+1;
	r[1]=rand()%10+1;
	r[2]=rand()%10+1;
	sort(r,r+3);
}


void deemo(int diff_1=rand()%5+1,int diff_2=rand()%5+1)
{
	ai_r();
    kp_blue.set_diff(r[0],r[1],r[2]);
	ai_r();
	kp_red.set_diff(r[0],r[1],r[2]);

	kp_blue.plan_init();
	kp_red.plan_init();
	clock_t t1 = clock();
	clock_t t2 = clock();
	sound_on = 0;

	ban_blue = 1;
	ban_red = 1;
	game_init();
	Sleep(1000);
	while(1)
	{
		sound_bgm_menu();
		for(int i=0x01;i<=0x60;i++)
		{
			if(GetAsyncKeyState(i) & 0x8000) return;
		}
		check_cci();
		Sleep(30);
		bullet_run();
		kp_blue.auto_run();
		kp_red.auto_run();
		if(die_a()) return;
		if(clock()-t1 > 150)
		{
			run();
			SetConsoleCursorPosition(hOutput,coord);
			t1 = clock();
		}
		if(clock()-t2 > 300000) return;

	}
	return;
}

void deemo_ai()
{
    score = 0;
  /*
	go_atk = d_1_1;
	go_def = d_1_2;
	go_ran = d_1_3;
	go_atk_enemy = d_2_1;
	go_def_enemy = d_2_2;
	go_ran_enemy = d_2_3;
  */
/*
    ai_r();
    kp_blue.set_diff(r[0],r[1],r[2]);
    ai_r();
    kp_red.set_diff(r[0],r[1],r[2]);
*/

	kp_blue.set_diff(6,7,9);

	kp_red.set_diff(5,9,10);

    kp_blue.plan_init();
    kp_red.plan_init();
	bgm_on = 0;
	sound_on = 0;
    clock_t t1 = clock();

    ban_blue = 1;
    ban_red = 1;
    game_init();
    Sleep(1000);
	log_3("得分：",score);
	/*SetConsoleCursorPosition(hOutput,coord);
	color_red();
	cout<<go_atk_red<<' '<<go_def_red<<' '<<go_ran_red;
	color_normal();
	cout<<" vs ";
	color_blue();
	cout<<go_atk<<' '<<go_def<<' '<<go_ran;*/
    while(1)
    {
        if(GetAsyncKeyState('B') & 0x8000) return;
		if(GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			color_log();
			log_bot_1("     --暂停--");
			Sleep(200);
			while(1)
			{
				if(GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					log_bot_1("          ");
					Sleep(200);
					break;
				}
			}
		}

        check_cci();
        //get_toward();
        Sleep(30);
		bullet_run();
        kp_blue.auto_run();
		kp_red.auto_run();
		if(die_a()) return;
			//game_end();

		if(clock()-t1 > 150)
		{
			run();
			SetConsoleCursorPosition(hOutput,coord);
			t1 = clock();
		}

    }
	return;
}
