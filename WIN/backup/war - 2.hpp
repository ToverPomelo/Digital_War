#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
using namespace std;
#define COL 15
#define ROW 15
#define BUL 4

//char map[ROW+2][COL+2] = {0};  //地图
char wall = '#';

typedef struct player{
    char toward; //u:上，d:下，l:左，r:右
    char atk_toward;
    char type; //+ - * ^
    char status; //a:atk,m:move
    int digit;
    int row;
    int pre_row;
    int col;
    int pre_col;
    int bullet[BUL];
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
    //red 上
    if (GetAsyncKeyState('W') & 0x8000)
    red.status=='a'? red.atk_toward='u' : red.toward='u';
    //red 下
    if (GetAsyncKeyState('S') & 0x8000)
    red.status=='a'? red.atk_toward='d' : red.toward='d';
    //red 左
    if (GetAsyncKeyState('A') & 0x8000)
    red.status=='a'? red.atk_toward='l' : red.toward='l';
    //red 右
    if (GetAsyncKeyState('D') & 0x8000)
    red.status=='a'? red.atk_toward='r' : red.toward='r';
    //red 加法
    if (GetAsyncKeyState('U') & 0x8000)
    red.type = '+';
    //red 减法
    if (GetAsyncKeyState('I') & 0x8000)
    red.type = '-';
    //red 乘法
    if (GetAsyncKeyState('O') & 0x8000)
    red.type = '*';
    //red 次方
    if (GetAsyncKeyState('L') & 0x8000)
    red.type = '^';
    //red 攻击
    if (GetAsyncKeyState('J') & 0x8000)
    {
        red.status = 'a';
        red.toward = 0;
    }
    //red 移动
    if (GetAsyncKeyState('K') & 0x8000)
    {
        red.status = 'm';
        red.atk_toward = 0;
    }


    //blue 上
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    blue.status=='a'? blue.atk_toward='u' : blue.toward='u';
    //blue 下
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    blue.status=='a'? blue.atk_toward='d' : blue.toward='d';
    //blue 左
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    blue.status=='a'? blue.atk_toward='l' : blue.toward='l';
    //blue 右
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    blue.status=='a'? blue.atk_toward='r' : blue.toward='r';
    //blue 加法
    if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
    blue.type = '+';
    //blue 减法
    if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
    blue.type = '-';
    //blue 乘法
    if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
    blue.type = '*';
    //blue 次方
    if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
    blue.type = '^';
    //blue 攻击
    if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
    {
        blue.status = 'a';
        blue.toward = 0;
    }
    //blue 移动
    if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
    {
        blue.status = 'm';
        blue.atk_toward = 0;
    }
}

//初始化游戏
void game_init()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=false;
    SetConsoleCursorInfo(hOut,&cci);

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

    red.type = '+';
    blue.type = '+';
    red.status = 'm';
    blue.status = 'm';

    for(int i=0;i<BUL;i++)
    red.bullet[i] = rand()%9+1;
    for(int i=0;i<BUL;i++)
    blue.bullet[i] = rand()%9+1;
}

//打印地图
void map_ptint()
{
    printf("\n");
    setColor(6,0);
    printf("         ");
    for(int c=0;c<COL+2;c++)
    {
        printf("%c ",wall);
    }
    printf("\n");
    for(int r=1;r<ROW+1;r++)
    {
        printf("  ");
        setColor(4,0);
        if(r == 4) printf("   %d  ",red.bullet[3]);
        else if(r == 6) printf("   %d  ",red.bullet[2]);
        else if(r == 8) printf("   %d  ",red.bullet[1]);
        else if(r == 10) printf(" %c %d  ",red.type,red.bullet[0]);
        else if(r == 13) printf("  %c   ",red.status);
        else printf("      ");
        setColor(6,0);
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
    printf("         ");
    for(int c=0;c<COL+2;c++)
    {
        printf("%c ",wall);
    }
    setColor(7,0);
}

//局部输入
HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord={0,0};
void map_refresh()
{
    setColor(4,0);
    COORD pre_red_coord={2*red.pre_col+10,red.pre_row+1};
    COORD red_coord={2*red.col+10,red.row+1};
    SetConsoleCursorPosition(hOutput,pre_red_coord);
    printf("\b ");
    SetConsoleCursorPosition(hOutput,red_coord);
    printf("\b%d",red.digit);
    //setColor(7,0);

    setColor(1,0);
    COORD pre_blue_coord={2*blue.pre_col+10,blue.pre_row+1};
    COORD blue_coord={2*blue.col+10,blue.row+1};
    SetConsoleCursorPosition(hOutput,pre_blue_coord);
    printf("\b ");
    SetConsoleCursorPosition(hOutput,blue_coord);
    printf("\b%d",blue.digit);
    setColor(7,0);

    SetConsoleCursorPosition(hOutput,coord);
}

bullet_refresh_red()
{
    for(int i=1;i<BUL;i++)
        red.bullet[i-1] = red.bullet[i];
    red.bullet[BUL-1] = rand()%9+1;

    setColor(4,0);
    COORD red_0={6,11};
    COORD red_1={6,9};
    COORD red_2={6,7};
    COORD red_3={6,5};
    COORD red_ty={4,11};
    COORD red_st={5,14};
    SetConsoleCursorPosition(hOutput,red_0);
    printf("\b%d",red.bullet[0]);
    SetConsoleCursorPosition(hOutput,red_1);
    printf("\b%d",red.bullet[1]);
    SetConsoleCursorPosition(hOutput,red_2);
    printf("\b%d",red.bullet[2]);
    SetConsoleCursorPosition(hOutput,red_3);
    printf("\b%d",red.bullet[3]);
    SetConsoleCursorPosition(hOutput,red_ty);
    printf("\b%c",red.type);
    SetConsoleCursorPosition(hOutput,red_st);
    printf("\b%c",red.status);
    setColor(7,0);

    SetConsoleCursorPosition(hOutput,coord);
}

//结束游戏
void game_end()
{
    SetConsoleCursorPosition(hOutput,coord);
    system("cls");

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=true;
    SetConsoleCursorInfo(hOut,&cci);
}

void run()
{
    //red 移动
    if(red.status == 'm')
    {
        red.pre_col = red.col;
        red.pre_row = red.row;
        switch(red.toward)
        {
            case 'u':
                if(red.row-1>0 && !(red.row-1==blue.row&&red.col==blue.col))
                    red.row--;
                break;
            case 'd':
                if(red.row+1<=15 && !(red.row+1==blue.row&&red.col==blue.col))
                    red.row++;
                break;
            case 'l':
                if(red.col-1>0 && !(red.row==blue.row&&red.col-1==blue.col))
                    red.col--;
                break;
            case 'r':
                if(red.col+1<=15 && !(red.row==blue.row&&red.col+1==blue.col))
                    red.col++;
                break;
        }
        red.toward = 0;
    }

    //blue 移动
    if(blue.status == 'm')
    {
        blue.pre_row = blue.row;
        blue.pre_col = blue.col;
        switch(blue.toward)
        {
            case 'u':
                if(blue.row-1>0 && !(blue.row-1==red.row&&blue.col==red.col))
                    blue.row--;
                break;
            case 'd':
                if(blue.row+1<=15 && !(blue.row+1==red.row&&blue.col==red.col))
                    blue.row++;
                break;
            case 'l':
                if(blue.col-1>0 && !(blue.row==red.row&&blue.col-1==red.col))
                    blue.col--;
                break;
            case 'r':
                if(blue.col+1<=15 && !(blue.row==red.row&&blue.col+1==red.col))
                    blue.col++;
                break;
        }
        blue.toward = 0;
    }
    cout<<red.status<<"   "<<blue.status<<"        ";

    map_refresh();
}
