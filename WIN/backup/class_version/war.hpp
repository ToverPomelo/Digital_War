#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <cmath>
#include <mmsystem.h>
using namespace std;

#define COL 15
#define ROW 15
#define BUL 4
#define TOP 4
#define LEFT 10
#define STEP 7
#define ATK_SPEED 4  //越大越慢

char theme = 'b';

bool ban_blue = 0;
bool ban_red = 0;

int score = 0;

//char map[ROW+2][COL+2] = {0};  //地图
string s_wall = "■";
string s_atk = "ATK";   //??
string s_move = "   ";   //??
string s_add = "+ ";
string s_sub = "- ";
string s_mul = "* ";
string s_pow = "^ ";


class player{
private:
    COORD bul_pos_0;
    COORD bul_pos_1;
    COORD bul_pos_2;
    COORD bul_pos_3;
    string mycolor;

public:
    string name;
    char toward; //u:上，d:下，l:左，r:右
    char atk_toward;
    char type; //+ - * ^
    char status; //a:atk,m:move
    int digit;
    string symbol;
    int row;
    int pre_row;
    int col;
    int pre_col;
    int bullet[BUL];
    int atkable;

    player(string pos,string c);
    player();
    bullet_refresh(); //刷新子弹
};
player red("left","red"),blue("right","blue");

typedef struct{
public:
    int digit;
    char toward;
    char type;
    player owner;
    char color;
    int step; //开始为 5，0时消失(作用距离)
    int row;
    int pre_row;
    int col;
    int pre_col;
    int r; //位置随机
}bullet;
vector<bullet> bul; //尾入头出

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;

bool sound_on = 1;
bool bgm_on = 1;

HWND hwnd;//  控制台窗口句柄
HANDLE hInput; // 输入设备句柄
INPUT_RECORD inRec;//  返回数据记录
DWORD numRead; //  返回已读取的记录数  //有用？
POINT p; //鼠标坐标
RECT rect; //窗口坐标
HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);

COORD coord={0,0};
COORD coord_1={0,1};
COORD coord_2={0,2};
COORD coord_3={0,3};
COORD coord_bot_1={16,23};
COORD coord_bot_2={16,24};
COORD coord_bot_3={16,25};
COORD log_pos={0,22};
COORD no_use={100,0};
COORD red_ty={3+1,10+TOP};
COORD red_st={5+2,13+TOP};
COORD blue_ty={2*COL+19+1,10+TOP};
COORD blue_st={2*COL+17+2,13+TOP};

typedef struct
{
    int digit_1;
    int digit_2;
    char type;
    char color_1;
    char color_2;
    int result;
}Log;
vector<Log> logs; //tail in head out

void hook_cci();
void check_cci();
void symbol_refresh();
void type_print(char t);
bool hasFocus();


void setColor(unsigned short ForeColor,unsigned short BackGroundColor);
void color_red();
void color_blue();
void color_bullet();
void color_wall();
void color_back();
void color_symbol();
void color_log();
void color_normal();
void color_light();

void sound_bgm_menu();
void sound_bgm_menu_close();
void sound_bgm_game();
void sound_bgm_game_close();
void sound_choose();
void sound_chosen_2();
void sound_change();
void sound_chosen();
void sound_got();
void sound_shot();
void sound_dead_s();
void sound_dead_p();
void sound_dead_d();

void map_refresh();
void get_toward();
void map_ptint();

void log_print();
void logs_clear();
void logs_empty();

void log_0(string a);
void log_1(string a);
void log_2(string a);
void log_3(string a);
void log_3(string a,int b);
void log_bot_1(string a);

void game_init();
void game_end();
bool end();
bool die_p();
bool die_s();
bool die_d();
bool die_a();
void run();

void bullet_init(player &owner);
void bullet_refresh();
void bullet_clear(bullet &b);
void bullet_run();
