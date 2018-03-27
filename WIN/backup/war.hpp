#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
using namespace std;
#define COL 15
#define ROW 15

char map[ROW+2][COL+2] = {0};  //地图
char wall = '#';

typedef struct player{
    char toward; //u:上，d:下，l:左，r:右
    char type; //+ - * ^
    char status; //a:atk,m:move
    int digit;
    int row;
    int pre_row;
    int col;
    int pre_col;
}player;

player red,blue;

void setColor(unsigned short ForeColor,unsigned short BackGroundColor)
{
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,(ForeColor%16)|(BackGroundColor%16*16));
}

//获取输入
void get_toward()
{
    if(kbhit())
    {
        switch(getch())
        {
            //red 上
            case 'w':
                red.toward = 'u';
                break;
            //red 下
            case 's':
                red.toward = 'd';
                break;
            //red 左
            case 'a':
                red.toward = 'l';
                break;
            //red 右
            case 'd':
                red.toward = 'r';
                break;
            //red 加法
            case 'u':
                red.type = '+';
                break;
            //red 减法
            case 'i':
                red.type = '-';
                break;
            //red 乘法
            case 'o':
                red.type = '*';
                break;
            //red 次方
            case 'l':
                red.type = '^';
                break;
            //red 攻击
            case 'j':
                red.status = 'a';
                break;
            //red 移动
            case 'k':
                red.status = 'm';
                break;

            case -32:  //这里。。我的电脑是这样：方向键
                switch(getch())
                {
                    //blue 上
                    case 72:
                        blue.toward = 'u';
                        break;
                    //blue 下
                    case 80:
                        blue.toward = 'd';
                        break;
                    //blue 左
                    case 75:
                        blue.toward = 'l';
                        break;
                    //blue 右
                    case 77:
                        blue.toward = 'r';
                        break;
                }
                break;
            //blue 加法
            case '4':
                blue.type = '+';
                break;
            //blue 减法
            case '5':
                blue.type = '-';
                break;
            //blue 乘法
            case '6':
                blue.type = '*';
                break;
            //blue 次方
            case '3':
                blue.type = '^';
                break;
            //blue 攻击
            case '1':
                blue.status = 'a';
                break;
            //blue 移动
            case '2':
                blue.status = 'm';
                break;
            default:
                break;
        }
    }
}

//初始化游戏
void game_init()
{
    srand(time(NULL));
    red.row = 4;
    red.col = 3;
    red.pre_row = red.row;
    red.pre_col = red.col;
    red.digit = rand()%9+1;
    blue.row = 13;
    blue.col = 13;
    blue.pre_row = blue.row;
    blue.pre_col = blue.col;
    blue.digit = rand()%9+1;
}

//结束游戏
void game_end()
{
    COORD red_coord={0,0};
    system("cls");
}

//打印地图
void map_ptint()
{
    printf("\n");
    setColor(6,0);
    printf(" ");
    for(int c=0;c<COL+2;c++)
    {
        printf("%c ",wall);
    }
    printf("\n");
    for(int r=1;r<ROW+1;r++)
    {
        printf(" %c ",wall);
        for(int c=1;c<COL+1;c++)
        {
            if(r==red.row && c==red.col)
            {
                setColor(4,0);
                printf("%d ",red.digit);
                setColor(6,0);
            }
            else if(r==blue.row && c==blue.col)
            {
                setColor(1,0);
                printf("%d ",blue.digit);
                setColor(6,0);
            }
            else
            {
                printf("  ");
            }
        }
        printf("%c \n",wall);
    }
    setColor(6,0);
    printf(" ");
    for(int c=0;c<COL+2;c++)
    {
        printf("%c ",wall);
    }
    setColor(7,0);
}

HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
void map_refresh()
{
    setColor(4,0);
    COORD pre_red_coord={2*(red.pre_col+1),red.pre_row+1};
    COORD red_coord={2*(red.col+1),red.row+1};
    SetConsoleCursorPosition(hOutput,pre_red_coord);
    printf("\b ");
    SetConsoleCursorPosition(hOutput,red_coord);
    //printf("\b%d",red.digit);
    printf("\b%d",rand()%9+1); //test
    setColor(7,0);

    setColor(1,0);
    COORD pre_blue_coord={2*(blue.pre_col+1),blue.pre_row+1};
    COORD blue_coord={2*(blue.col+1),blue.row+1};
    SetConsoleCursorPosition(hOutput,pre_blue_coord);
    printf("\b ");
    SetConsoleCursorPosition(hOutput,blue_coord);
    //printf("\b%d",blue.digit);
    printf("\b%d",rand()%9+1);  //test
    setColor(7,0);
}
