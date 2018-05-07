#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <cmath>
#include<mmsystem.h>
using namespace std;
#define COL 15
#define ROW 15
#define BUL 4
#define TOP 4
#define LEFT 10
#define STEP 7
#define ATK_SPEED 4  //Խ��Խ��

char theme = 'b';

bool ban_blue = 0;
bool ban_red = 0;

int score = 0;

//char map[ROW+2][COL+2] = {0};  //��ͼ
string s_wall = "��";
string s_atk = "ATK";   //??
string s_move = "   ";   //??
string s_add = "+ ";
string s_sub = "- ";
string s_mul = "* ";
string s_pow = "^ ";

typedef struct player{
    string name;
    char toward; //u:�ϣ�d:�£�l:��r:��
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
}player;

player red,blue;

typedef struct bullet{
    int digit;
    char toward;
    char type;
    player owner;
    char color;
    int step; //��ʼΪ 5��0ʱ��ʧ(���þ���)
    int row;
    int pre_row;
    int col;
    int pre_col;
    int r; //λ�����
}bullet;

vector<bullet> bul; //β��ͷ��

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
void hook_cci()
{
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=false;
    SetConsoleCursorInfo(hOut,&cci);
}

void check_cci()
{
    GetConsoleCursorInfo(hOut,&cci);  //��꣬�л�ȫ��ʱ
    if(cci.bVisible == true)
    {
        cci.bVisible=false;
        SetConsoleCursorInfo(hOut,&cci);
    }
}

void symbol_refresh()
{
    switch(red.digit)
    {
        case 1:red.symbol = "��";
        break;
        case 2:red.symbol = "��";
        break;
        case 3:red.symbol = "��";
        break;
        case 4:red.symbol = "��";
        break;
        case 5:red.symbol = "��";
        break;
        case 6:red.symbol = "��";
        break;
        case 7:red.symbol = "��";
        break;
        case 8:red.symbol = "��";
        break;
        case 9:red.symbol = "��";
        break;
        case 0:red.symbol = "��";
        break;
    }

    switch(blue.digit)
    {
        case 1:blue.symbol = "��";
        break;
        case 2:blue.symbol = "��";
        break;
        case 3:blue.symbol = "��";
        break;
        case 4:blue.symbol = "��";
        break;
        case 5:blue.symbol = "��";
        break;
        case 6:blue.symbol = "��";
        break;
        case 7:blue.symbol = "��";
        break;
        case 8:blue.symbol = "��";
        break;
        case 9:blue.symbol = "��";
        break;
        case 0:blue.symbol = "��";
        break;
    }
}

void type_print(char t)
{
    switch(t)
    {
        case '+':cout<<s_add;
        break;
        case '-':cout<<s_sub;
        break;
        case '*':cout<<s_mul;
        break;
        case '^':cout<<s_pow;
        break;
    }
}

//��ɫ
void setColor(unsigned short ForeColor,unsigned short BackGroundColor)
{
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,(ForeColor%16)|(BackGroundColor%16*16));
}

void color_red()
{
    if(theme == 'w') setColor(4,7);
    else if(theme == 'b') setColor(4,0);
}

void color_blue()
{
    if(theme == 'w') setColor(1,7);
    else if(theme == 'b') setColor(1,0);
}

void color_bullet()
{
    if(theme == 'w') setColor(2,7);
    else if(theme == 'b') setColor(2,0);
}

void color_wall()
{
    if(theme == 'w') setColor(6,7);
    else if(theme == 'b') setColor(6,0);
}

void color_back()
{
    if(theme == 'w') setColor(8,7);
    else if(theme == 'b') setColor(8,0);
}

void color_symbol()
{
    if(theme == 'w') setColor(10,7);
    else if(theme == 'b') setColor(10,0);
}

void color_log()
{
    if(theme == 'w') setColor(10,7);
    else if(theme == 'b') setColor(10,0);
}

void color_normal()
{
    if(theme == 'w') setColor(0,7);
    else if(theme == 'b') setColor(7,0);
}

void color_light()
{
    if(theme == 'w') setColor(13,7);
    else if(theme == 'b') setColor(13,0);
}

//����
bool sound_on = 1;
bool bgm_on = 1;
int volume = 100;
void sound_bgm_menu()
{
    if(!bgm_on) mciSendString("close ./sounds/bgm_1.mp3",0,0,0);
    else
    {
        mciSendString("play ./sounds/bgm_1.mp3",0,0,0);
        mciSendString("setaudio ./sounds/bgm_1.mp3 volume to 250",0,0,0);
    }
}

void sound_bgm_menu_close()
{
    mciSendString("close ./sounds/bgm_1.mp3",0,0,0);
}

void sound_bgm_game()
{
    if(!bgm_on) mciSendString("close ./sounds/bgm_2.mp3",0,0,0);
    else
    {
        mciSendString("play ./sounds/bgm_2.mp3",0,0,0);
        mciSendString("setaudio ./sounds/bgm_2.mp3 volume to 500",0,0,0);
    }
}

void sound_bgm_game_close()
{
    mciSendString("close ./sounds/bgm_2.mp3",0,0,0);
}

void sound_choose()
{
    if(!sound_on) return;
    //try
    //{
        mciSendString("close ./sounds/choose_1.wav ",0,0,0);
        mciSendString("play ./sounds/choose_1.wav ",0,0,0);
    //}
    //catch(const *char e)
    //{
    //    cerr<<e;
    //}
}

void sound_chosen_2()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/choose_5.wav ",0,0,0);
    mciSendString("play ./sounds/choose_5.wav ",0,0,0);
}

void sound_change()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/choose_2.wav ",0,0,0);
    mciSendString("play ./sounds/choose_2.wav ",0,0,0);
}

void sound_chosen()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/choose_3.wav ",0,0,0);
    mciSendString("play ./sounds/choose_3.wav ",0,0,0);
}

void sound_got()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/got_1.wav ",0,0,0);
    mciSendString("play ./sounds/got_1.wav ",0,0,0);
}

void sound_shot()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/shot_1.wav ",0,0,0);
    mciSendString("play ./sounds/shot_1.wav ",0,0,0);
}

void sound_dead_s()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/dead_1.wav ",0,0,0);
    mciSendString("play ./sounds/dead_1.wav ",0,0,0);
}

void sound_dead_p()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/dead_3.wav ",0,0,0);
    mciSendString("play ./sounds/dead_3.wav ",0,0,0);
}

void sound_dead_d()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/dead_2.wav ",0,0,0);
    mciSendString("play ./sounds/dead_2.wav ",0,0,0);
}
 /*
void sound_message()
{
    if(!sound_on) return;
    mciSendString("close ./sounds/message.mp3",0,0,0);
    mciSendString("play ./sounds/message.mp3",0,0,0);
}
 */
//�ֲ�����

HWND hwnd;//  ����̨���ھ��
HANDLE hInput; // �����豸���
INPUT_RECORD inRec;//  �������ݼ�¼
DWORD numRead; //  �����Ѷ�ȡ�ļ�¼��  //���ã�
POINT p; //�������
RECT rect; //��������
HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
bool hasFocus()
{
    HWND top = GetForegroundWindow();
    return (top==hwnd);
}

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
void map_refresh()
{
    symbol_refresh();

    color_red();
    COORD pre_red_coord={2*red.pre_col+LEFT+1,red.pre_row+TOP};
    COORD red_coord={2*red.col+LEFT+1,red.row+TOP};
    SetConsoleCursorPosition(hOutput,pre_red_coord);
    printf("\b\b  ");
    SetConsoleCursorPosition(hOutput,red_coord);
    cout<<"\b\b"<<red.symbol;
    SetConsoleCursorPosition(hOutput,red_ty);
    cout<<"\b\b";
    type_print(red.type);
    SetConsoleCursorPosition(hOutput,red_st);
    if(red.status=='a') cout<<"\b\b\b"<<s_atk;
    else cout<<"\b\b\b"<<s_move;

    color_blue();
    COORD pre_blue_coord={2*blue.pre_col+LEFT+1,blue.pre_row+TOP};
    COORD blue_coord={2*blue.col+LEFT+1,blue.row+TOP};
    SetConsoleCursorPosition(hOutput,pre_blue_coord);
    printf("\b\b  ");
    SetConsoleCursorPosition(hOutput,blue_coord);
    cout<<"\b\b"<<blue.symbol;
    SetConsoleCursorPosition(hOutput,blue_ty);
    cout<<"\b\b";
    type_print(blue.type);
    SetConsoleCursorPosition(hOutput,blue_st);
    if(blue.status=='a') cout<<"\b\b\b"<<s_atk;
    else cout<<"\b\b\b"<<s_move;
    color_back();

    SetConsoleCursorPosition(hOutput,coord);
}

//��ȡ����
void get_toward()
{
    if(!ban_red)
    {
        //red ��
        if (GetAsyncKeyState('W') & 0x8000)
        red.status=='a'? red.atk_toward='u' : red.toward='u';
        //red ��
        if (GetAsyncKeyState('S') & 0x8000)
        red.status=='a'? red.atk_toward='d' : red.toward='d';
        //red ��
        if (GetAsyncKeyState('A') & 0x8000)
        red.status=='a'? red.atk_toward='l' : red.toward='l';
        //red ��
        if (GetAsyncKeyState('D') & 0x8000)
        red.status=='a'? red.atk_toward='r' : red.toward='r';
        //red �ӷ�
        if (GetAsyncKeyState('U') & 0x8000)
        red.type = '+';
        //red ����
        if (GetAsyncKeyState('I') & 0x8000)
        red.type = '-';
        //red �˷�
        if (GetAsyncKeyState('O') & 0x8000)
        red.type = '*';
        //red �η�
        if (GetAsyncKeyState('L') & 0x8000)
        red.type = '^';
        //red ����
        if (GetAsyncKeyState('J') & 0x8000)
        {
            red.status = 'a';
            red.toward = 0;
        }
        //red �ƶ�
        if (GetAsyncKeyState('K') & 0x8000)
        {
            red.status = 'm';
            red.atk_toward = 0;
        }
    }

    if(!ban_blue)
    {
        //blue ��
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        blue.status=='a'? blue.atk_toward='u' : blue.toward='u';
        //blue ��
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        blue.status=='a'? blue.atk_toward='d' : blue.toward='d';
        //blue ��
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        blue.status=='a'? blue.atk_toward='l' : blue.toward='l';
        //blue ��
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        blue.status=='a'? blue.atk_toward='r' : blue.toward='r';
        //blue �ӷ�
        if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
        blue.type = '+';
        //blue ����
        if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
        blue.type = '-';
        //blue �˷�
        if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
        blue.type = '*';
        //blue �η�
        if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
        blue.type = '^';
        //blue ����
        if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
        {
            blue.status = 'a';
            blue.toward = 0;
        }
        //blue �ƶ�
        if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
        {
            blue.status = 'm';
            blue.atk_toward = 0;
        }
    }
}

//��ӡ��ͼ
void map_ptint()
{
    symbol_refresh();

    for(int i=0;i<TOP;i++)
        printf("\n");
    color_wall();
    printf("         ");
    for(int c=0;c<COL+2;c++)
    {
        cout<<s_wall;
    }
    printf("\n");
    for(int r=1;r<ROW+1;r++)
    {
        printf("  ");
        color_red();
        if(r == 4) printf("   %d  ",red.bullet[3]);
        else if(r == 5) printf("��    ");
        else if(r == 6) printf("�� %d  ",red.bullet[2]);
        else if(r == 7) printf("��    ");
        else if(r == 8) printf("   %d  ",red.bullet[1]);
        else if(r == 10)
        {
            type_print(red.type);
            cout<<" "<<red.bullet[0]<<"  ";
        }
        //else if(r == 13) printf("  %c   ",red.status);
        else printf("      ");
        color_wall();
        cout<<' '<<s_wall;
        for(int c=1;c<COL+1;c++)
        {
            if(r==red.row && c==red.col)
            {
                color_red();
                cout<<red.symbol;
                color_wall();
            }
            else if(r==blue.row && c==blue.col)
            {
                color_blue();
                cout<<blue.symbol;
                color_wall();
            }
            else
            {
                printf("  ");
            }
        }
        cout<<s_wall;
        printf("  ");
        color_blue();
        if(r == 4) printf("%d    ",blue.bullet[3]);
        else if(r == 5) printf("  ��");
        else if(r == 6) printf("%d �� ",blue.bullet[2]);
        else if(r == 7) printf("  ��");
        else if(r == 8) printf("%d  ",blue.bullet[1]);
        else if(r == 10)
        {
            cout<<blue.bullet[0]<<"  ";
            type_print(blue.type);
        }
        //else if(r == 13) printf(" %c   ",blue.status);
        printf("\n");
    }
    color_wall();
    printf("         ");
    for(int c=0;c<COL+2;c++)
    {
        cout<<s_wall;
    }

    color_back();
    SetConsoleCursorPosition(hOutput,log_pos);
    cout<<"Logs:";
}

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
void log_print()
{
    SetConsoleCursorPosition(hOutput,log_pos);
    cout<<endl;
    for(int i=0;i<logs.size();i++)
    {
        cout<<"  ";
        if(logs[i].color_1 == 'r') color_red();
        else if(logs[i].color_1 == 'b') color_blue();
        cout<<logs[i].digit_1;
        color_symbol();
        cout<<logs[i].type;
        if(logs[i].color_2 == 'r') color_red();
        else if(logs[i].color_2 == 'b') color_blue();
        cout<<logs[i].digit_2;
        color_symbol();
        cout<<'=';
        color_bullet();
        cout<<logs[i].result;
        cout<<endl;
        color_back();
    }
}

void logs_clear()
{
    while(logs.size()>4)
    {
        logs.erase(logs.begin());
    }
}

void logs_empty()
{
    while(logs.size())
    {
        logs.erase(logs.begin());
    }
}

void log(string a)
{
    SetConsoleCursorPosition(hOutput,coord);
    cout<<a<<"                                                                                     ";
}

void log_1(string a)
{
    SetConsoleCursorPosition(hOutput,coord_1);
    cout<<a<<"                                                                                     ";
}

void log_2(string a)
{
    SetConsoleCursorPosition(hOutput,coord_2);
    cout<<a<<"                                                                                     ";
}

void log_3(string a)
{
    SetConsoleCursorPosition(hOutput,coord_3);
    cout<<a<<"           ";
}

void log_3(string a,int b)
{
    SetConsoleCursorPosition(hOutput,coord_3);
    cout<<a<<b<<"        ";
}

void log_bot_1(string a)
{
    SetConsoleCursorPosition(hOutput,coord_bot_1);
    cout<<a<<"                                                                                     ";
}


//��ʼ����Ϸ
void game_init()
{
    system("cls");
    hook_cci();
    logs_empty();
    //���
    /*HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=false;
    SetConsoleCursorInfo(hOut,&cci);*/
    //���뷨...


    srand(time(NULL));
    red.row = 3;
    red.col = 3;
    red.pre_row = red.row;
    red.pre_col = red.col;
    red.digit = rand()%9+1;
    blue.row = 13;
    blue.col = 13;
    blue.pre_row = blue.row;
    blue.pre_col = blue.col;
    blue.digit = rand()%9+1;
    red.atkable = ATK_SPEED;
    blue.atkable = ATK_SPEED;

    red.name = "P1";
    blue.name = "P2";
    red.type = '+';
    blue.type = '+';
    red.status = 'm';
    blue.status = 'm';

    for(int i=0;i<BUL;i++)
    red.bullet[i] = rand()%9+1;
    for(int i=0;i<BUL;i++)
    blue.bullet[i] = rand()%9+1;

    map_ptint();
}

//ˢ�� red���ӵ�
COORD red_0={6,10+TOP};
COORD red_1={6,8+TOP};
COORD red_2={6,6+TOP};
COORD red_3={6,4+TOP};
bullet_refresh_red()
{
    for(int i=1;i<BUL;i++)
        red.bullet[i-1] = red.bullet[i];
    red.bullet[BUL-1] = rand()%9+1;

    color_red();
    SetConsoleCursorPosition(hOutput,red_0);
    printf("\b%d",red.bullet[0]);
    SetConsoleCursorPosition(hOutput,red_1);
    printf("\b%d",red.bullet[1]);
    SetConsoleCursorPosition(hOutput,red_2);
    printf("\b%d",red.bullet[2]);
    SetConsoleCursorPosition(hOutput,red_3);
    printf("\b%d",red.bullet[3]);
    color_back();

    SetConsoleCursorPosition(hOutput,coord);
}

//ˢ�� blue���ӵ�
COORD blue_0={2*COL+16,10+TOP};
COORD blue_1={2*COL+16,8+TOP};
COORD blue_2={2*COL+16,6+TOP};
COORD blue_3={2*COL+16,4+TOP};
bullet_refresh_blue()
{
    for(int i=1;i<BUL;i++)
        blue.bullet[i-1] = blue.bullet[i];
    blue.bullet[BUL-1] = rand()%9+1;

    color_blue();
    SetConsoleCursorPosition(hOutput,blue_0);
    printf("\b%d",blue.bullet[0]);
    SetConsoleCursorPosition(hOutput,blue_1);
    printf("\b%d",blue.bullet[1]);
    SetConsoleCursorPosition(hOutput,blue_2);
    printf("\b%d",blue.bullet[2]);
    SetConsoleCursorPosition(hOutput,blue_3);
    printf("\b%d",blue.bullet[3]);

    color_back();
    SetConsoleCursorPosition(hOutput,coord);
}

//������Ϸ
void game_end()
{
    SetConsoleCursorPosition(hOutput,coord);
    system("cls");

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=true;
    SetConsoleCursorInfo(hOut,&cci);

    exit(0);
}

bool end()
{
    map_refresh();
    while(1)
    {
        if (GetAsyncKeyState('Y') & 0x8000)
        {
            game_init();
            return 0;
        }
        if (GetAsyncKeyState('N') & 0x8000)
        {
            //game_end();
            return 1;
        }
    }
}

bool die_p()
{
    if(red.digit == 0)
    {
        sound_dead_p();
        log("    P2Ӯ�ˣ�����һ����(Y/N)");
        return end();
    }
    else if(blue.digit == 0)
    {
        sound_dead_p();
        log("    P1Ӯ�ˣ�����һ����(Y/N)");
        return end();
    }
    else
    {
        return 0;
    }
}

bool die_s()
{
    if(red.digit == 0)
    {
        sound_dead_s();
        log("    �����ˣ�����һ����(Y/N)");
        bool iter = end();
        if(!iter)
        {
            score = 0;
            color_back();
            log_3("�÷֣�",score);
        }
        return iter;
    }
    else if(blue.digit == 0)
    {
        score++;
        sound_got();
        color_back();
        log_3("�÷֣�",score);
        blue.pre_row = blue.row;
        blue.pre_col = blue.col;
        do{
            blue.row = rand()%15+1;
            blue.col = rand()%15+1;
        }while(blue.row!=red.row && blue.col!=red.col);
        blue.digit = rand()%9+1;
        blue.atkable = ATK_SPEED;

        blue.type = '+';
        blue.status = 'm';

        map_refresh();
        return 0;
        //return end();
    }
    else
    {
        return 0;
    }
}

bool die_d()
{
    if(red.digit == 0)
    {
        log("    ʲô���㾹Ȼ���ˣ��ⲻ���ܣ�����һ�Σ���(Y/N)");
        sound_dead_s();
        log_1("");
        log_2("");
        return end();
    }
    else if(blue.digit == 0)
    {
        log("    �������Ѿ������˽����Ϸ��Ҫ����һ����(Y/N)");
        sound_dead_d();
        log_1("");
        log_2("");
        return end();
    }
    else
    {
        return 0;
    }
}

bool die_a()
{
    if(red.digit == 0)
    {
        score--;
        color_back();
        //log_3("�÷֣�",score);  //test
        red.pre_row = red.row;
        red.pre_col = red.col;
        do{
            red.row = rand()%15+1;
            red.col = rand()%15+1;
        }while(red.row!=blue.row && red.col!=red.col);
        red.digit = rand()%9+1;
        red.atkable = ATK_SPEED;

        red.type = '+';
        red.status = 'm';

        map_refresh();
        return 0;
    }
    else if(blue.digit == 0)
    {
        score++;
        color_back();
        //log_3("�÷֣�",score);
        blue.pre_row = blue.row;
        blue.pre_col = blue.col;
        do{
            blue.row = rand()%15+1;
            blue.col = rand()%15+1;
        }while(blue.row!=red.row && blue.col!=red.col);
        blue.digit = rand()%9+1;
        blue.atkable = ATK_SPEED;

        blue.type = '+';
        blue.status = 'm';

        map_refresh();
        return 0;
    }
    else
    {
        return 0;
    }
}

void bullet_init(player &owner)
{
    sound_shot();
    bullet *new_bullet = new bullet;
    new_bullet->owner = owner;
    new_bullet->digit = owner.bullet[0];
    if(owner.name == red.name)
    {
        new_bullet->color = 'r';
        bullet_refresh_red();
    }
    else if(owner.name == blue.name)
    {
        new_bullet->color = 'b';
        bullet_refresh_blue();
    }
    new_bullet->toward = owner.atk_toward;
    new_bullet->type = owner.type;
    new_bullet->step = STEP;
    new_bullet->row = owner.row;
    new_bullet->col = owner.col;
    new_bullet->pre_row = new_bullet->row;
    new_bullet->pre_col = new_bullet->col;
    new_bullet->r = rand()%2;

    bul.push_back(*new_bullet);
    owner.atk_toward = 0;
    owner.status = 'm';
}

void bullet_refresh()
{
    COORD pre;
    COORD now;
    color_bullet();
    for(int i=bul.size()-1;i>=0;i--)
    {
        if(!(bul[i].pre_row==red.row && bul[i].pre_col==red.col) && !(bul[i].pre_row==blue.row && bul[i].pre_col==blue.col))
        {
            bul[i].r ? pre={2*bul[i].pre_col+LEFT+1,bul[i].pre_row+TOP} : pre={2*bul[i].pre_col+LEFT,bul[i].pre_row+TOP};
            SetConsoleCursorPosition(hOutput,pre);
            printf("\b ");
        }
        bul[i].r ? now={2*bul[i].col+LEFT+1,bul[i].row+TOP} : now={2*bul[i].col+LEFT,bul[i].row+TOP};
        SetConsoleCursorPosition(hOutput,now);
        printf("\b%d",bul[i].digit);
    }
    SetConsoleCursorPosition(hOutput,coord);
}

//���stepΪ 0�� bullet
void bullet_clear(bullet &b)
{
    COORD pos;
    b.r ? pos={2*b.pre_col+LEFT+1,b.pre_row+TOP} : pos={2*b.pre_col+LEFT,b.pre_row+TOP};
    SetConsoleCursorPosition(hOutput,pos);
    printf("\b ");
}

void bullet_run()
{
    for(int i=0;i<bul.size();i++)
    {
        //���ƶ�
        bul[i].pre_row = bul[i].row;
        bul[i].pre_col = bul[i].col;
        switch (bul[i].toward) {
            //����
            case 'u':
            if(bul[i].row-1<=0) //��ǽ
            {
                bul[i].toward = 'd';
                bul[i].step--;
            }
            else if(bul[i].row-1==red.row && bul[i].col==red.col) //�� red
            {
                Log iter;
                iter.digit_1 = red.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'r';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                red.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row-1==blue.row && bul[i].col==blue.col) //�� blue
            {
                Log iter;
                iter.digit_1 = blue.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'b';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
                blue.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else
            {
                bul[i].row--;
                bul[i].step--;
            }
            break;

            //����
            case 'd':
            if(bul[i].row+1>ROW) //��ǽ
            {
                bul[i].toward = 'u';
                bul[i].step--;
            }
            else if(bul[i].row+1==red.row && bul[i].col==red.col) //�� red
            {
                Log iter;
                iter.digit_1 = red.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'r';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                red.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row+1==blue.row && bul[i].col==blue.col) //�� blue
            {
                Log iter;
                iter.digit_1 = blue.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'b';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
                blue.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else
            {
                bul[i].row++;
                bul[i].step--;
            }
            break;

            //����
            case 'l':
            if(bul[i].col-1<=0) //��ǽ
            {
                bul[i].toward = 'r';
                bul[i].step--;
            }
            else if(bul[i].row==red.row && bul[i].col-1==red.col) //�� red
            {
                Log iter;
                iter.digit_1 = red.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'r';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                red.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row==blue.row && bul[i].col-1==blue.col) //�� blue
            {
                Log iter;
                iter.digit_1 = blue.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'b';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
                blue.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else
            {
                bul[i].col--;
                bul[i].step--;
            }
            break;

            //����
            case 'r':
            if(bul[i].col+1>COL) //��ǽ
            {
                bul[i].toward = 'l';
                bul[i].step--;
            }
            else if(bul[i].row==red.row && bul[i].col+1==red.col) //�� red
            {
                Log iter;
                iter.digit_1 = red.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'r';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                red.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row==blue.row && bul[i].col+1==blue.col) //�� blue
            {
                Log iter;
                iter.digit_1 = blue.digit;
                iter.digit_2 = bul[i].digit;
                iter.type = bul[i].type;
                iter.color_1 = 'b';
                iter.color_2 = bul[i].color;
                switch(bul[i].type)
                {
                    case '+':
                    iter.result = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    iter.result = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    iter.result = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    iter.result = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
                blue.digit = iter.result;
                logs.push_back(iter);
                //logs_clear();
                bul[i].step = 0;
                //die();
            }
            else
            {
                bul[i].col++;
                bul[i].step--;
            }
            break;
        }
    }
    logs_clear();
    log_print();

    //�����(������)
    for(int i=0;i<bul.size();i++)
    {
        if(bul[i].step <= 0)
            bullet_clear(bul[i]);
    }

    vector<bullet>::iterator it = bul.begin();
    for(;it!=bul.end();)
    {
        if(it->step<=0)
        {
            it = bul.erase(it);
        }

        else
            it++;
    }
    bullet_refresh();
}

void run()
{
    //red �ƶ�
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
                if(red.row+1<=ROW && !(red.row+1==blue.row&&red.col==blue.col))
                    red.row++;
                break;
            case 'l':
                if(red.col-1>0 && !(red.row==blue.row&&red.col-1==blue.col))
                    red.col--;
                break;
            case 'r':
                if(red.col+1<=COL && !(red.row==blue.row&&red.col+1==blue.col))
                    red.col++;
                break;
        }
        red.toward = 0;
    }
    //red ����
    else if(red.status=='a' && red.atk_toward)
    {
        if(red.atkable <=0 )
        {
            bullet_init(red);
            red.atkable = ATK_SPEED;
        }
    }

    //blue �ƶ�
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
                if(blue.row+1<=ROW && !(blue.row+1==red.row&&blue.col==red.col))
                    blue.row++;
                break;
            case 'l':
                if(blue.col-1>0 && !(blue.row==red.row&&blue.col-1==red.col))
                    blue.col--;
                break;
            case 'r':
                if(blue.col+1<=COL && !(blue.row==red.row&&blue.col+1==red.col))
                    blue.col++;
                break;
        }
        blue.toward = 0;
    }
    //blue ����
    else if(blue.status=='a' && blue.atk_toward)
    {
        if(blue.atkable <=0 )
        {
            bullet_init(blue);
            blue.atkable = ATK_SPEED;
        }
    }

    if(red.atkable>0) red.atkable--;
    if(blue.atkable>0) blue.atkable--;

    map_refresh();
}
