#include <vector>
#include <algorithm>
#include <cmath>
#include "war.hpp"

//int diff = 3;
int go_all = 10;
int go_atk = 3;
int go_def = 6;
int go_ran = 8;

typedef struct
{
	int digit_opp; //digit before
	int digit;
	int result; //digit after
	char mark;
}kp_blue;
vector<kp_blue> kill_plan_blue; //stack:head in head out
kp_blue first_blue[4]; //tail in head out
kp_blue second_blue[16];
kp_blue third_blue[64];
kp_blue fourth_blue[256];

void set_diff(int diff)
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

void plan_init_blue()
{
	kp_blue kp;
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
		first_blue[i] = kp;
	}
	for(int i=0;i<16;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		second_blue[i] = kp;
	}
	for(int i=0;i<64;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		third_blue[i] = kp;
	}
	for(int i=0;i<256;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		fourth_blue[i] = kp;
	}
}

bool plan_blue()
{
	while(kill_plan_blue.size() != 0)	{kill_plan_blue.erase(kill_plan_blue.begin());} //clean

	for(int i=0;i<4;i++)
	{
		if(i%4 == 0) //'+';
		{
			first_blue[i].digit_opp = red.digit;
			first_blue[i].digit = blue.bullet[0];
			first_blue[i].result = (first_blue[i].digit_opp+first_blue[i].digit)%10;
			if(first_blue[i].result == 0)
			{
				//first_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			first_blue[i].digit_opp = red.digit;
			first_blue[i].digit = blue.bullet[0];
			first_blue[i].result = (first_blue[i].digit_opp-first_blue[i].digit+10)%10;
			if(first_blue[i].result == 0)
			{
				//first_blue[i].mark = '-';
				kill_plan_blue.push_back(first_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			first_blue[i].digit_opp = red.digit;
			first_blue[i].digit = blue.bullet[0];
			first_blue[i].result = (first_blue[i].digit_opp*first_blue[i].digit)%10;
			if(first_blue[i].result == 0)
			{
				//first_blue[i].mark = '*';
				kill_plan_blue.push_back(first_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			first_blue[i].digit_opp = red.digit;
			first_blue[i].digit = blue.bullet[0];
			first_blue[i].result = (int)pow(first_blue[i].digit_opp,first_blue[i].digit)%10;
			if(first_blue[i].result == 0)
			{
				//first_blue[i].mark = '^';
				kill_plan_blue.push_back(first_blue[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<16;i++)
	{
		if(i%4 == 0) //'+';
		{
			second_blue[i].digit_opp = first_blue[i/4].result;
			second_blue[i].digit = blue.bullet[1];
			second_blue[i].result = (second_blue[i].digit_opp+second_blue[i].digit)%10;
			if(second_blue[i].result == 0)
			{
				//second_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i/4]);
				kill_plan_blue.push_back(second_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			second_blue[i].digit_opp = first_blue[i/4].result;
			second_blue[i].digit = blue.bullet[1];
			second_blue[i].result = (second_blue[i].digit_opp-second_blue[i].digit+10)%10;
			if(second_blue[i].result == 0)
			{
				//second_blue[i].mark = '-';
				kill_plan_blue.push_back(first_blue[i/4]);
				kill_plan_blue.push_back(second_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			second_blue[i].digit_opp = first_blue[i/4].result;
			second_blue[i].digit = blue.bullet[1];
			second_blue[i].result = (second_blue[i].digit_opp*second_blue[i].digit)%10;
			if(second_blue[i].result == 0)
			{
				//second_blue[i].mark = '*';
				kill_plan_blue.push_back(first_blue[i/4]);
				kill_plan_blue.push_back(second_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			second_blue[i].digit_opp = first_blue[i/4].result;
			second_blue[i].digit = blue.bullet[1];
			second_blue[i].result = (int)pow(second_blue[i].digit_opp,second_blue[i].digit)%10;
			if(second_blue[i].result == 0)
			{
				//second_blue[i].mark = '^';
				kill_plan_blue.push_back(first_blue[i/4]);
				kill_plan_blue.push_back(second_blue[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<64;i++)
	{
		if(i%4 == 0) //'+';
		{
			third_blue[i].digit_opp = second_blue[i/4].result;
			third_blue[i].digit = blue.bullet[2];
			third_blue[i].result = (third_blue[i].digit_opp+third_blue[i].digit)%10;
			if(third_blue[i].result == 0)
			{
				//third_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i/16]);
				kill_plan_blue.push_back(second_blue[i/4]);
				kill_plan_blue.push_back(third_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			third_blue[i].digit_opp = second_blue[i/4].result;
			third_blue[i].digit = blue.bullet[2];
			third_blue[i].result = (third_blue[i].digit_opp-third_blue[i].digit+10)%10;
			if(third_blue[i].result == 0)
			{
				//third_blue[i].mark = '-';
				kill_plan_blue.push_back(first_blue[i/16]);
				kill_plan_blue.push_back(second_blue[i/4]);
				kill_plan_blue.push_back(third_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			third_blue[i].digit_opp = second_blue[i/4].result;
			third_blue[i].digit = blue.bullet[2];
			third_blue[i].result = (third_blue[i].digit_opp*third_blue[i].digit)%10;
			if(third_blue[i].result == 0)
			{
				//third_blue[i].mark = '*';
				kill_plan_blue.push_back(first_blue[i/16]);
				kill_plan_blue.push_back(second_blue[i/4]);
				kill_plan_blue.push_back(third_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			third_blue[i].digit_opp = second_blue[i/4].result;
			third_blue[i].digit = blue.bullet[2];
			third_blue[i].result = (int)pow(third_blue[i].digit_opp,third_blue[i].digit)%10;
			if(third_blue[i].result == 0)
			{
				//third_blue[i].mark = '^';
				kill_plan_blue.push_back(first_blue[i/16]);
				kill_plan_blue.push_back(second_blue[i/4]);
				kill_plan_blue.push_back(third_blue[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<256;i++)
	{
		if(i%4 == 0) //'+';
		{
			fourth_blue[i].digit_opp = third_blue[i/4].result;
			fourth_blue[i].digit = blue.bullet[3];
			fourth_blue[i].result = (fourth_blue[i].digit_opp+fourth_blue[i].digit)%10;
			if(fourth_blue[i].result == 0)
			{
				//fourth_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i/64]);
				kill_plan_blue.push_back(second_blue[i/16]);
				kill_plan_blue.push_back(third_blue[i/4]);
				kill_plan_blue.push_back(fourth_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			fourth_blue[i].digit_opp = third_blue[i/4].result;
			fourth_blue[i].digit = blue.bullet[3];
			fourth_blue[i].result = (fourth_blue[i].digit_opp-fourth_blue[i].digit+10)%10;
			if(fourth_blue[i].result == 0)
			{
				//fourth_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i/64]);
				kill_plan_blue.push_back(second_blue[i/16]);
				kill_plan_blue.push_back(third_blue[i/4]);
				kill_plan_blue.push_back(fourth_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			fourth_blue[i].digit_opp = third_blue[i/4].result;
			fourth_blue[i].digit = blue.bullet[3];
			fourth_blue[i].result = (fourth_blue[i].digit_opp*fourth_blue[i].digit)%10;
			if(fourth_blue[i].result == 0)
			{
				//fourth_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i/64]);
				kill_plan_blue.push_back(second_blue[i/16]);
				kill_plan_blue.push_back(third_blue[i/4]);
				kill_plan_blue.push_back(fourth_blue[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			fourth_blue[i].digit_opp = third_blue[i/4].result;
			fourth_blue[i].digit = blue.bullet[3];
			fourth_blue[i].result = (int)pow(fourth_blue[i].digit_opp,fourth_blue[i].digit)%10;
			if(fourth_blue[i].result == 0)
			{
				//fourth_blue[i].mark = '+';
				kill_plan_blue.push_back(first_blue[i/64]);
				kill_plan_blue.push_back(second_blue[i/16]);
				kill_plan_blue.push_back(third_blue[i/4]);
				kill_plan_blue.push_back(fourth_blue[i]);
				return 1;
			}
		}
	}

	return 0;
}

void go_attack_blue()
{
	int aim_row = red.row;
	int aim_col = red.col;
	switch(red.toward)
	{
		case 'u':
			if(red.row-1>0 && !(red.row-1==blue.row&&red.col==blue.col))
				aim_row--;
			break;
		case 'd':
			if(red.row+1<=ROW && !(red.row+1==blue.row&&red.col==blue.col))
				aim_row++;
			break;
		case 'l':
			if(red.col-1>0 && !(red.row==blue.row&&red.col-1==blue.col))
				aim_col--;
			break;
		case 'r':
			if(red.col+1<=COL && !(red.row==blue.row&&red.col+1==blue.col))
				aim_col++;
			break;
	}

	if(blue.row==aim_row && abs(blue.col-aim_col)<STEP-1) //attack
	{
		blue.status='a';
		if(blue.col>aim_col) blue.atk_toward='l';
		else blue.atk_toward='r';

		blue.type = kill_plan_blue[0].mark;
		kill_plan_blue.erase(kill_plan_blue.begin());
		return;
	}
	else if(blue.col==aim_col && abs(blue.row-aim_row)<STEP-1)
	{
		blue.status='a';
		if(blue.row>aim_row) blue.atk_toward='u';
		else blue.atk_toward='d';

		blue.type = kill_plan_blue[0].mark;
		kill_plan_blue.erase(kill_plan_blue.begin());
		return;
	}
	else blue.status='m';

	if(abs(blue.row-aim_row)>=STEP-1 && abs(blue.col-aim_col)>=STEP-1) //攻击范围外，从远处靠近
	{
		if(abs(blue.row-aim_row) > abs(blue.col-aim_col))
		{
			if(blue.row>aim_row) blue.toward = 'u';
			else blue.toward = 'd';
		}
		else
		{
			if(blue.col>aim_col) blue.toward = 'l';
			else blue.toward = 'r';
		}
	}
	else if(abs(blue.row-aim_row)>=STEP-1)
	{
		if(blue.row>aim_row) blue.toward = 'u';
		else blue.toward = 'd';
	}
	else if(abs(blue.col-aim_col)>=STEP-1)
	{
		if(blue.col>aim_col) blue.toward = 'l';
		else blue.toward = 'r';
	}
	else //攻击范围内，从近处逼近
	{
		if(abs(blue.row-aim_row) < abs(blue.col-aim_col))
		{
			if(blue.row>aim_row) blue.toward = 'u';
			else blue.toward = 'd';
		}
		else
		{
			if(blue.col>aim_col) blue.toward = 'l';
			else blue.toward = 'r';
		}
	}
}

void go_defence_blue() //简易版(重攻击轻回避)
{
	int aim_row = red.row;
	int aim_col = red.col;
	switch(red.toward)
	{
		case 'u':
			if(red.row-1>0 && !(red.row-1==blue.row&&red.col==blue.col))
				aim_row--;
			break;
		case 'd':
			if(red.row+1<=ROW && !(red.row+1==blue.row&&red.col==blue.col))
				aim_row++;
			break;
		case 'l':
			if(red.col-1>0 && !(red.row==blue.row&&red.col-1==blue.col))
				aim_col--;
			break;
		case 'r':
			if(red.col+1<=COL && !(red.row==blue.row&&red.col+1==blue.col))
				aim_col++;
			break;
	}

	if(blue.row==aim_row && abs(blue.col-aim_col)<STEP-1) //attack
	{
		blue.status='m';
		if(red.toward == 'u') blue.toward = 'd';
		else if(red.toward == 'd') blue.toward = 'u';
		else
		{
			if(blue.row<ROW/2) blue.toward = 'd';
			else blue.toward = 'u';
		}
		return;
	}
	else if(blue.col==aim_col && abs(blue.row-aim_row)<STEP-1)
	{
		blue.status='m';
		if(red.toward == 'l') blue.toward = 'r';
		else if(red.toward == 'r') blue.toward = 'l';
		else
		{
			if(blue.col<COL/2) blue.toward = 'r';
			else blue.toward = 'l';
		}
		return;
	}
}

void random_blue()
{
	blue.status='m';
	switch(rand()%4)
	{
		case 0:
			blue.toward = 'u';
			break;
		case 1:
			blue.toward = 'd';
			break;
		case 2:
			blue.toward = 'l';
			break;
		case 3:
			blue.toward = 'r';
			break;
	}
}

void auto_blue()
{
	if(!kill_plan_blue.size() || kill_plan_blue[0].digit_opp!=red.digit) plan_blue();

	int mode = rand()%go_all;
	if(mode < go_atk) go_attack_blue(); //增大失误率
	else if(mode < go_def) go_defence_blue();
	else if(mode < go_ran) random_blue();

/*
	SetConsoleCursorPosition(hOutput,coord);
	if(kill_plan_blue.size() >=1 )cout<<kill_plan_blue[0].digit_opp<<kill_plan_blue[0].mark<<kill_plan_blue[0].digit<<'='<<kill_plan_blue[0].result;
	else cout<<"             ";
	SetConsoleCursorPosition(hOutput,coord_1);
	if(kill_plan_blue.size() >=2 )cout<<kill_plan_blue[1].digit_opp<<kill_plan_blue[1].mark<<kill_plan_blue[1].digit<<'='<<kill_plan_blue[1].result;
	else cout<<"             ";
	SetConsoleCursorPosition(hOutput,coord_2);
	if(kill_plan_blue.size() >=3 )cout<<kill_plan_blue[2].digit_opp<<kill_plan_blue[2].mark<<kill_plan_blue[2].digit<<'='<<kill_plan_blue[2].result;
	else cout<<"             ";
	SetConsoleCursorPosition(hOutput,coord_3);
	if(kill_plan_blue.size() >=4 )cout<<kill_plan_blue[3].digit_opp<<kill_plan_blue[3].mark<<kill_plan_blue[3].digit<<'='<<kill_plan_blue[3].result;
	else cout<<"             ";
*/
}


/************************************  red == blue  *************************************/

int go_all_red = 10;
int go_atk_red = 3;
int go_def_red = 6;
int go_ran_red = 8;

void set_diff_red(int diff)
{
	switch(diff)
	{
		case 0:
			go_atk_red = 0;
			go_def_red = 0;
			go_ran_red = 1;
            break;
		case 1:
			go_atk_red = 1;
			go_def_red = 2;
			go_ran_red = 4;
            break;
        case 2:
			go_atk_red = 2;
			go_def_red = 5;
			go_ran_red = 7;
            break;
        case 3:
			go_atk_red = 2;
			go_def_red = 7;
			go_ran_red = 9;
            break;
        case 4:
			go_atk_red = 3;
			go_def_red = 6;
			go_ran_red = 8;
            break;
        case 5:
			go_atk_red = 5;
			go_def_red = 8;
			go_ran_red = 10;
            break;
        default:
            break;
	}
}

typedef struct
{
	int digit_opp; //digit before
	int digit;
	int result; //digit after
	char mark;
}kp_red;
vector<kp_red> kill_plan_red; //stack:head in head out
kp_red first_red[4]; //tail in head out
kp_red second_red[16];
kp_red third_red[64];
kp_red fourth_red[256];

void plan_init_red()
{
	kp_red kp;
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
		first_red[i] = kp;
	}
	for(int i=0;i<16;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		second_red[i] = kp;
	}
	for(int i=0;i<64;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		third_red[i] = kp;
	}
	for(int i=0;i<256;i++)
	{
		char mark;
		if(i%4 == 0) mark = '+';
		else if(i%4 == 1) mark = '-';
		else if(i%4 == 2) mark = '*';
		else if(i%4 == 3) mark = '^';
		kp.mark = mark;
		fourth_red[i] = kp;
	}
}

bool plan_red()
{
	while(kill_plan_red.size() != 0)	{kill_plan_red.erase(kill_plan_red.begin());} //clean

	for(int i=0;i<4;i++)
	{
		if(i%4 == 0) //'+';
		{
			first_red[i].digit_opp = blue.digit;
			first_red[i].digit = red.bullet[0];
			first_red[i].result = (first_red[i].digit_opp+first_red[i].digit)%10;
			if(first_red[i].result == 0)
			{
				//first_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			first_red[i].digit_opp = blue.digit;
			first_red[i].digit = red.bullet[0];
			first_red[i].result = (first_red[i].digit_opp-first_red[i].digit+10)%10;
			if(first_red[i].result == 0)
			{
				//first_red[i].mark = '-';
				kill_plan_red.push_back(first_red[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			first_red[i].digit_opp = blue.digit;
			first_red[i].digit = red.bullet[0];
			first_red[i].result = (first_red[i].digit_opp*first_red[i].digit)%10;
			if(first_red[i].result == 0)
			{
				//first_red[i].mark = '*';
				kill_plan_red.push_back(first_red[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			first_red[i].digit_opp = blue.digit;
			first_red[i].digit = red.bullet[0];
			first_red[i].result = (int)pow(first_red[i].digit_opp,first_red[i].digit)%10;
			if(first_red[i].result == 0)
			{
				//first_red[i].mark = '^';
				kill_plan_red.push_back(first_red[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<16;i++)
	{
		if(i%4 == 0) //'+';
		{
			second_red[i].digit_opp = first_red[i/4].result;
			second_red[i].digit = red.bullet[1];
			second_red[i].result = (second_red[i].digit_opp+second_red[i].digit)%10;
			if(second_red[i].result == 0)
			{
				//second_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i/4]);
				kill_plan_red.push_back(second_red[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			second_red[i].digit_opp = first_red[i/4].result;
			second_red[i].digit = red.bullet[1];
			second_red[i].result = (second_red[i].digit_opp-second_red[i].digit+10)%10;
			if(second_red[i].result == 0)
			{
				//second_red[i].mark = '-';
				kill_plan_red.push_back(first_red[i/4]);
				kill_plan_red.push_back(second_red[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			second_red[i].digit_opp = first_red[i/4].result;
			second_red[i].digit = red.bullet[1];
			second_red[i].result = (second_red[i].digit_opp*second_red[i].digit)%10;
			if(second_red[i].result == 0)
			{
				//second_red[i].mark = '*';
				kill_plan_red.push_back(first_red[i/4]);
				kill_plan_red.push_back(second_red[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			second_red[i].digit_opp = first_red[i/4].result;
			second_red[i].digit = red.bullet[1];
			second_red[i].result = (int)pow(second_red[i].digit_opp,second_red[i].digit)%10;
			if(second_red[i].result == 0)
			{
				//second_red[i].mark = '^';
				kill_plan_red.push_back(first_red[i/4]);
				kill_plan_red.push_back(second_red[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<64;i++)
	{
		if(i%4 == 0) //'+';
		{
			third_red[i].digit_opp = second_red[i/4].result;
			third_red[i].digit = red.bullet[2];
			third_red[i].result = (third_red[i].digit_opp+third_red[i].digit)%10;
			if(third_red[i].result == 0)
			{
				//third_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i/16]);
				kill_plan_red.push_back(second_red[i/4]);
				kill_plan_red.push_back(third_red[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			third_red[i].digit_opp = second_red[i/4].result;
			third_red[i].digit = red.bullet[2];
			third_red[i].result = (third_red[i].digit_opp-third_red[i].digit+10)%10;
			if(third_red[i].result == 0)
			{
				//third_red[i].mark = '-';
				kill_plan_red.push_back(first_red[i/16]);
				kill_plan_red.push_back(second_red[i/4]);
				kill_plan_red.push_back(third_red[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			third_red[i].digit_opp = second_red[i/4].result;
			third_red[i].digit = red.bullet[2];
			third_red[i].result = (third_red[i].digit_opp*third_red[i].digit)%10;
			if(third_red[i].result == 0)
			{
				//third_red[i].mark = '*';
				kill_plan_red.push_back(first_red[i/16]);
				kill_plan_red.push_back(second_red[i/4]);
				kill_plan_red.push_back(third_red[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			third_red[i].digit_opp = second_red[i/4].result;
			third_red[i].digit = red.bullet[2];
			third_red[i].result = (int)pow(third_red[i].digit_opp,third_red[i].digit)%10;
			if(third_red[i].result == 0)
			{
				//third_red[i].mark = '^';
				kill_plan_red.push_back(first_red[i/16]);
				kill_plan_red.push_back(second_red[i/4]);
				kill_plan_red.push_back(third_red[i]);
				return 1;
			}
		}
	}

	for(int i=0;i<256;i++)
	{
		if(i%4 == 0) //'+';
		{
			fourth_red[i].digit_opp = third_red[i/4].result;
			fourth_red[i].digit = red.bullet[3];
			fourth_red[i].result = (fourth_red[i].digit_opp+fourth_red[i].digit)%10;
			if(fourth_red[i].result == 0)
			{
				//fourth_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i/64]);
				kill_plan_red.push_back(second_red[i/16]);
				kill_plan_red.push_back(third_red[i/4]);
				kill_plan_red.push_back(fourth_red[i]);
				return 1;
			}
		}
		else if(i%4 == 1) //'-';
		{
			fourth_red[i].digit_opp = third_red[i/4].result;
			fourth_red[i].digit = red.bullet[3];
			fourth_red[i].result = (fourth_red[i].digit_opp-fourth_red[i].digit+10)%10;
			if(fourth_red[i].result == 0)
			{
				//fourth_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i/64]);
				kill_plan_red.push_back(second_red[i/16]);
				kill_plan_red.push_back(third_red[i/4]);
				kill_plan_red.push_back(fourth_red[i]);
				return 1;
			}
		}
		else if(i%4 == 2) //'*';
		{
			fourth_red[i].digit_opp = third_red[i/4].result;
			fourth_red[i].digit = red.bullet[3];
			fourth_red[i].result = (fourth_red[i].digit_opp*fourth_red[i].digit)%10;
			if(fourth_red[i].result == 0)
			{
				//fourth_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i/64]);
				kill_plan_red.push_back(second_red[i/16]);
				kill_plan_red.push_back(third_red[i/4]);
				kill_plan_red.push_back(fourth_red[i]);
				return 1;
			}
		}
		else if(i%4 == 3) //'^';
		{
			fourth_red[i].digit_opp = third_red[i/4].result;
			fourth_red[i].digit = red.bullet[3];
			fourth_red[i].result = (int)pow(fourth_red[i].digit_opp,fourth_red[i].digit)%10;
			if(fourth_red[i].result == 0)
			{
				//fourth_red[i].mark = '+';
				kill_plan_red.push_back(first_red[i/64]);
				kill_plan_red.push_back(second_red[i/16]);
				kill_plan_red.push_back(third_red[i/4]);
				kill_plan_red.push_back(fourth_red[i]);
				return 1;
			}
		}
	}

	return 0;
}

void go_attack_red()
{
	int aim_row = blue.row;
	int aim_col = blue.col;
	switch(blue.toward)
	{
		case 'u':
			if(blue.row-1>0 && !(blue.row-1==red.row&&blue.col==red.col))
				aim_row--;
			break;
		case 'd':
			if(blue.row+1<=ROW && !(blue.row+1==red.row&&blue.col==red.col))
				aim_row++;
			break;
		case 'l':
			if(blue.col-1>0 && !(blue.row==red.row&&blue.col-1==red.col))
				aim_col--;
			break;
		case 'r':
			if(blue.col+1<=COL && !(blue.row==red.row&&blue.col+1==red.col))
				aim_col++;
			break;
	}

	if(red.row==aim_row && abs(red.col-aim_col)<STEP-1) //attack
	{
		red.status='a';
		if(red.col>aim_col) red.atk_toward='l';
		else red.atk_toward='r';

		red.type = kill_plan_red[0].mark;
		kill_plan_red.erase(kill_plan_red.begin());
		return;
	}
	else if(red.col==aim_col && abs(red.row-aim_row)<STEP-1)
	{
		red.status='a';
		if(red.row>aim_row) red.atk_toward='u';
		else red.atk_toward='d';

		red.type = kill_plan_red[0].mark;
		kill_plan_red.erase(kill_plan_red.begin());
		return;
	}
	else red.status='m';

	if(abs(red.row-aim_row)>=STEP-1 && abs(red.col-aim_col)>=STEP-1) //攻击范围外，从远处靠近
	{
		if(abs(red.row-aim_row) > abs(red.col-aim_col))
		{
			if(red.row>aim_row) red.toward = 'u';
			else red.toward = 'd';
		}
		else
		{
			if(red.col>aim_col) red.toward = 'l';
			else red.toward = 'r';
		}
	}
	else if(abs(red.row-aim_row)>=STEP-1)
	{
		if(red.row>aim_row) red.toward = 'u';
		else red.toward = 'd';
	}
	else if(abs(red.col-aim_col)>=STEP-1)
	{
		if(red.col>aim_col) red.toward = 'l';
		else red.toward = 'r';
	}
	else //攻击范围内，从近处逼近
	{
		if(abs(red.row-aim_row) < abs(red.col-aim_col))
		{
			if(red.row>aim_row) red.toward = 'u';
			else red.toward = 'd';
		}
		else
		{
			if(red.col>aim_col) red.toward = 'l';
			else red.toward = 'r';
		}
	}
}

void go_defence_red() //简易版(重攻击轻回避)
{
	int aim_row = blue.row;
	int aim_col = blue.col;
	switch(blue.toward)
	{
		case 'u':
			if(blue.row-1>0 && !(blue.row-1==red.row&&blue.col==red.col))
				aim_row--;
			break;
		case 'd':
			if(blue.row+1<=ROW && !(blue.row+1==red.row&&blue.col==red.col))
				aim_row++;
			break;
		case 'l':
			if(blue.col-1>0 && !(blue.row==red.row&&blue.col-1==red.col))
				aim_col--;
			break;
		case 'r':
			if(blue.col+1<=COL && !(blue.row==red.row&&blue.col+1==red.col))
				aim_col++;
			break;
	}

	if(red.row==aim_row && abs(red.col-aim_col)<STEP-1) //attack
	{
		red.status='m';
		if(blue.toward == 'u') red.toward = 'd';
		else if(blue.toward == 'd') red.toward = 'u';
		else
		{
			if(red.row<ROW/2) red.toward = 'd';
			else red.toward = 'u';
		}
		return;
	}
	else if(red.col==aim_col && abs(red.row-aim_row)<STEP-1)
	{
		red.status='m';
		if(blue.toward == 'l') red.toward = 'r';
		else if(blue.toward == 'r') red.toward = 'l';
		else
		{
			if(red.col<COL/2) red.toward = 'r';
			else red.toward = 'l';
		}
		return;
	}
}

void random_red()
{
	red.status='m';
	switch(rand()%4)
	{
		case 0:
			red.toward = 'u';
			break;
		case 1:
			red.toward = 'd';
			break;
		case 2:
			red.toward = 'l';
			break;
		case 3:
			red.toward = 'r';
			break;
	}
}

void auto_red()
{
	if(!kill_plan_red.size() || kill_plan_red[0].digit_opp!=blue.digit) plan_red();

	int mode = rand()%go_all_red;
	if(mode < go_atk_red) go_attack_red(); //增大失误率
	else if(mode < go_def_red) go_defence_red();
	else if(mode < go_ran_red) random_red();

/*
	SetConsoleCursorPosition(hOutput,coord);
	if(kill_plan_red.size() >=1 )cout<<kill_plan_red[0].digit_opp<<kill_plan_red[0].mark<<kill_plan_red[0].digit<<'='<<kill_plan_red[0].result;
	else cout<<"             ";
	SetConsoleCursorPosition(hOutput,coord_1);
	if(kill_plan_red.size() >=2 )cout<<kill_plan_red[1].digit_opp<<kill_plan_red[1].mark<<kill_plan_red[1].digit<<'='<<kill_plan_red[1].result;
	else cout<<"             ";
	SetConsoleCursorPosition(hOutput,coord_2);
	if(kill_plan_red.size() >=3 )cout<<kill_plan_red[2].digit_opp<<kill_plan_red[2].mark<<kill_plan_red[2].digit<<'='<<kill_plan_red[2].result;
	else cout<<"             ";
	SetConsoleCursorPosition(hOutput,coord_3);
	if(kill_plan_red.size() >=4 )cout<<kill_plan_red[3].digit_opp<<kill_plan_red[3].mark<<kill_plan_red[3].digit<<'='<<kill_plan_red[3].result;
	else cout<<"             ";
*/
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
	go_atk = r[0];
	go_def = r[1];
	go_ran = r[2];
	ai_r();
	go_atk_red = r[0];
	go_def_red = r[1];
	go_ran_red = r[2];

	plan_init_blue();
	plan_init_red();
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
		auto_blue();
		auto_red();
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

void deemo_ai(int d_1_1=go_atk,int d_1_2=go_def,int d_1_3=go_ran,int d_2_1=go_atk_red,int d_2_2=go_def_red,int d_2_3=go_ran_red)
{
    score = 0;
  /*
	go_atk = d_1_1;
	go_def = d_1_2;
	go_ran = d_1_3;
	go_atk_red = d_2_1;
	go_def_red = d_2_2;
	go_ran_red = d_2_3;
  */
/*
	ai_r();
	go_atk = r[0];
	go_def = r[1];
	go_ran = r[2];
	ai_r();
	go_atk_red = r[0];
	go_def_red = r[1];
	go_ran_red = r[2];
*/

	go_atk = 6;
	go_def = 7;
	go_ran = 9;

	go_atk_red = 5;
	go_def_red = 9;
	go_ran_red = 10;

    plan_init_blue();
    plan_init_red();
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
		auto_blue();
		auto_red();
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
