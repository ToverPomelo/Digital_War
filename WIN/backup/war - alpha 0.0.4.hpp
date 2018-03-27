#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <cmath>
using namespace std;
#define COL 15
#define ROW 15
#define BUL 4
#define TOP 4
#define LEFT 10
#define STEP 7
#define ATK_SPEED 2  //Խ��Խ��

//char map[ROW+2][COL+2] = {0};  //��ͼ
string s_wall = "��";
string s_atk = "ATK";   //�7�0
string s_move = "   ";   //�7�6
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
    int step; //��ʼΪ 5��0ʱ��ʧ(���þ���)
    int row;
    int pre_row;
    int col;
    int pre_col;
    int r; //λ�����
}bullet;

vector<bullet> bul; //β��ͷ��

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

void setColor(unsigned short ForeColor,unsigned short BackGroundColor)
{
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,(ForeColor%16)|(BackGroundColor%16*16));
}

//��ȡ����
void get_toward()
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

//��ӡ��ͼ
void map_ptint()
{
    symbol_refresh();

    for(int i=0;i<TOP;i++)
        printf("\n");
    setColor(6,0);
    printf("         ");
    for(int c=0;c<COL+2;c++)
    {
        cout<<s_wall;
    }
    printf("\n");
    for(int r=1;r<ROW+1;r++)
    {
        printf("  ");
        setColor(4,0);
        if(r == 4) printf("�� %d  ",red.bullet[3]);
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
        setColor(6,0);
        cout<<' '<<s_wall;
        for(int c=1;c<COL+1;c++)
        {
            if(r==red.row && c==red.col)
            {
                setColor(4,0);
                cout<<red.symbol;
                setColor(6,0);
            }
            else if(r==blue.row && c==blue.col)
            {
                setColor(1,0);
                cout<<blue.symbol;
                setColor(6,0);
            }
            else
            {
                printf("  ");
            }
        }
        cout<<s_wall;
        printf("  ");
        setColor(1,0);
        if(r == 4) printf("%d �� ",blue.bullet[3]);
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
    setColor(6,0);
    printf("         ");
    for(int c=0;c<COL+2;c++)
    {
        cout<<s_wall;
    }
    setColor(7,0);
}

//��ʼ����Ϸ
void game_init()
{
    system("cls");
    //���
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=false;
    SetConsoleCursorInfo(hOut,&cci);
    //���뷨...


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

//�ֲ�����
HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord={0,0};
COORD coord_1={0,1};
COORD coord_2={0,2};
COORD red_ty={3+1,10+TOP};
COORD red_st={5+2,13+TOP};
COORD blue_ty={2*COL+19+1,10+TOP};
COORD blue_st={2*COL+17+2,13+TOP};
void map_refresh()
{
    symbol_refresh();

    setColor(4,0);
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
    //setColor(7,0);

    setColor(1,0);
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
    setColor(7,0);

    SetConsoleCursorPosition(hOutput,coord);
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

    setColor(4,0);
    SetConsoleCursorPosition(hOutput,red_0);
    printf("\b%d",red.bullet[0]);
    SetConsoleCursorPosition(hOutput,red_1);
    printf("\b%d",red.bullet[1]);
    SetConsoleCursorPosition(hOutput,red_2);
    printf("\b%d",red.bullet[2]);
    SetConsoleCursorPosition(hOutput,red_3);
    printf("\b%d",red.bullet[3]);
    setColor(7,0);

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

    setColor(1,0);
    SetConsoleCursorPosition(hOutput,blue_0);
    printf("\b%d",blue.bullet[0]);
    SetConsoleCursorPosition(hOutput,blue_1);
    printf("\b%d",blue.bullet[1]);
    SetConsoleCursorPosition(hOutput,blue_2);
    printf("\b%d",blue.bullet[2]);
    SetConsoleCursorPosition(hOutput,blue_3);
    printf("\b%d",blue.bullet[3]);
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
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=true;
    SetConsoleCursorInfo(hOut,&cci);
    SetConsoleCursorPosition(hOutput,{27,0});
    char a;
    do{a = getch();}while(!(a=='Y' || a=='y' || a=='N' || a=='n'));
    if(a=='Y' || a=='y')
    {
        game_init();
        return 0;
    }
    else if(a=='N' || a=='n')
    {
        //game_end();
        return 1;
    }
}

bool die()
{
    if(red.digit == 0)
    {
        log("P2 win! Play again? (Y/N):");
        return end();
    }
    else if(blue.digit == 0)
    {
        log("P1 win! Play again? (Y/N):");
        return end();
    }
    else
    {
        return 0;
    }
}

void bullet_init(player &owner)
{
    bullet *new_bullet = new bullet;
    new_bullet->owner = owner;
    new_bullet->digit = owner.bullet[0];
    if(owner.name == red.name)
        bullet_refresh_red();
    else if(owner.name == blue.name)
        bullet_refresh_blue();
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
    setColor(7,0);
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
                switch(bul[i].type)
                {
                    case '+':
                    red.digit = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    red.digit = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    red.digit = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    red.digit = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row-1==blue.row && bul[i].col==blue.col) //�� blue
            {
                switch(bul[i].type)
                {
                    case '+':
                    blue.digit = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    blue.digit = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    blue.digit = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    blue.digit = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
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
                switch(bul[i].type)
                {
                    case '+':
                    red.digit = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    red.digit = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    red.digit = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    red.digit = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row+1==blue.row && bul[i].col==blue.col) //�� blue
            {
                switch(bul[i].type)
                {
                    case '+':
                    blue.digit = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    blue.digit = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    blue.digit = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    blue.digit = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
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
                switch(bul[i].type)
                {
                    case '+':
                    red.digit = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    red.digit = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    red.digit = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    red.digit = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row==blue.row && bul[i].col-1==blue.col) //�� blue
            {
                switch(bul[i].type)
                {
                    case '+':
                    blue.digit = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    blue.digit = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    blue.digit = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    blue.digit = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
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
                switch(bul[i].type)
                {
                    case '+':
                    red.digit = (red.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    red.digit = (red.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    red.digit = (red.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    red.digit = (int)pow(red.digit,bul[i].digit)%10;
                    break;
                }
                bul[i].step = 0;
                //die();
            }
            else if(bul[i].row==blue.row && bul[i].col+1==blue.col) //�� blue
            {
                switch(bul[i].type)
                {
                    case '+':
                    blue.digit = (blue.digit+bul[i].digit)%10;
                    break;
                    case '-':
                    blue.digit = (blue.digit-bul[i].digit+10)%10;
                    break;
                    case '*':
                    blue.digit = (blue.digit*bul[i].digit)%10;
                    break;
                    case '^':
                    blue.digit = (int)pow(blue.digit,bul[i].digit)%10;
                    break;
                }
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
