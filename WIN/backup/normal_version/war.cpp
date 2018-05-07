//#include "war.hpp"
//#include "menu.hpp"
#include "auto.hpp"

void menu();
void menu_init();
bool menu_refresh();
void game_single();
void game_pair();
void game_tutorial();
void tutorial_printer();
void tutorial_init();
bool tutorial_refresh();
void game_tutorial_1();
void game_tutorial_2();
void game_tutorial_3();
void game_tutorial_4();
void game_tutorial_5();
void game_tutorial_6();
void game_tutorial_deemo();
void game_setting();
void game_setting_init();
bool game_setting_refresh();

int setting_case_0 = 3;   //0~5
int setting_case_1 = 0;
int setting_case_2 = 1;
int setting_case_3 = 1;

int menu_pos = 0;
int setting_pos = 0;
int tutorial_pos = 0;

int game_on = 0;

int main()
{
    system("mode con cols=52 lines=28");
    system("title=Digital_War");
    hwnd=FindWindow("ConsoleWindowClass",NULL);/*  ����̨���ھ�� */
    //HWND hwnd=GetForegroundWindow();
	hInput = GetStdHandle(STD_INPUT_HANDLE); /*  �����豸��� */

    if(theme == 'w') system("color 70");
    else if(theme == 'b') system("color 07");

    menu();



    return 0;
}

/*******************************************************************************/

COORD menu_0={20,10};
COORD menu_1={20,12};
COORD menu_2={20,14};
COORD menu_3={20,16};
COORD menu_4={20,18};
COORD test={15,25};

void menu()
{
    menu_pos = 0;
    menu_init();
    clock_t t1 = clock();
    while(1)
    {
        if(!hasFocus()) while(1) if(hasFocus()) break;
        check_cci();
        if(menu_refresh()) t1 = clock();;
        Sleep(100); //�ֶ�����
        if(clock()-t1 > 30000)
		{
            deemo();
            Sleep(100);
            menu_init();
			t1 = clock();
		}
    }
/*
    while(1){
        GetWindowRect(hwnd,&rect);
        GetCursorPos(&p);//��ȡ�������
        //SetCursorPos(p.x+3,p.y);//�����������
        SetConsoleCursorPosition(hOutput,coord);
        cout<<(double)(p.x-rect.left)/(rect.right-rect.left)<<" , "<<(double)(p.y-rect.top)/(rect.bottom-rect.top)<<"              "<<endl;
        Sleep(10);//�����ƶ�ʱ����
    }
*/
}

void menu_init()
{
    system("cls");
    hook_cci();
    bgm_on = setting_case_2;
    sound_on = setting_case_3;
    sound_bgm_menu();

    if(menu_pos == 0) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_0);
    cout<<"�� �� ģ ʽ";

    if(menu_pos == 1) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_1);
    cout<<"�� �� �� Ϸ";

    if(menu_pos == 2) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_2);
    cout<<"�� Ϸ ˵ ��";

    if(menu_pos == 3) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_3);
    cout<<"�� Ϸ �� ��";

    if(menu_pos == 4) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_4);
    cout<<"�� �� �� Ϸ";

    //SetConsoleCursorPosition(hOutput,test);
    //system("pause");
}

bool menu_refresh()
{
    if((GetAsyncKeyState('V')&0x8000))
    {
        deemo();
        Sleep(100);
        /*deemo();
        Sleep(100);
        deemo();*/
        menu_init();
        return 1;
    }
    else if((GetAsyncKeyState(VK_LBUTTON)&0x8000))
    {
        GetWindowRect(hwnd,&rect);
        GetCursorPos(&p);
        if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.375 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.6) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.375 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.42))
        {
            menu_pos = 0;
            sound_chosen();
            sound_bgm_menu_close();
            game_on = 1;
            game_single();
            game_on = 0;
            sound_bgm_game_close();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.375 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.6) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.45 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.485))
        {
            menu_pos = 1;
            sound_chosen();
            sound_bgm_menu_close();
            game_on = 1;
            game_pair();
            game_on = 0;
            sound_bgm_game_close();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.375 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.6) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.51 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.55))
        {
            menu_pos = 2;
            sound_chosen();
            sound_bgm_menu_close();
            game_tutorial();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.375 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.6) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.58 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.615))
        {
            menu_pos = 3;
            sound_chosen();
            game_setting();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.375 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.6) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.65 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.685))
        {
            menu_pos = 4;
            sound_chosen();
            Sleep(350);
            game_end();
        }
        menu_init();
        return 1;
    }
    else if((GetAsyncKeyState(VK_RETURN)&0x8000) || (GetAsyncKeyState('J')&0x8000) || (GetAsyncKeyState(VK_NUMPAD1)&0x8000))
    {
        sound_chosen();
        switch(menu_pos)
        {
            case 0:
                sound_bgm_menu_close();
                game_on = 1;
                game_single();
                game_on = 0;
                sound_bgm_game_close();
                break;
            case 1:
                sound_bgm_menu_close();
                game_on = 1;
                game_pair();
                game_on = 0;
                sound_bgm_game_close();
                break;
            case 2:
                sound_bgm_menu_close();
                game_tutorial();
                break;
            case 3:
                game_setting();
                break;
            case 4:
                Sleep(350);
                game_end();
                break;
            default:
                break;
        }
        menu_init();
        return 1;
    }
    else if((GetAsyncKeyState(VK_UP)&0x8000) || (GetAsyncKeyState('W')&0x8000))
    {
        menu_pos--;
        if(menu_pos < 0) menu_pos = 0;
        sound_choose();
        Sleep(80);
        switch(menu_pos)
        {
            case 0:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_0);
                cout<<"�� �� ģ ʽ";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"�� �� �� Ϸ";
                break;
            case 1:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"�� �� �� Ϸ";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"�� Ϸ ˵ ��";
                break;
            case 2:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"�� Ϸ ˵ ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"�� Ϸ �� ��";
                break;
            case 3:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"�� Ϸ �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_4);
                cout<<"�� �� �� Ϸ";
                break;
            default:
                break;
        }
        return 1;
    }
    else if((GetAsyncKeyState(VK_DOWN)&0x8000) || (GetAsyncKeyState('S')&0x8000))
    {
        menu_pos++;
        if(menu_pos > 4) menu_pos = 4;
        sound_choose();
        Sleep(80);
        switch(menu_pos)
        {
            case 1:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_0);
                cout<<"�� �� ģ ʽ";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"�� �� �� Ϸ";
                break;
            case 2:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"�� �� �� Ϸ";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"�� Ϸ ˵ ��";
                break;
            case 3:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"�� Ϸ ˵ ��";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"�� Ϸ �� ��";
                break;
            case 4:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"�� Ϸ �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_4);
                cout<<"�� �� �� Ϸ";
                break;
            default:
                break;
        }
        return 1;
    }
    return 0;
}

void game_single()
{
    score = 0;
    plan_init_blue();
    set_diff(setting_case_0);
    bgm_on = setting_case_2;
    sound_on = setting_case_3;
    //set_diff(0);  //����
    clock_t t1 = clock();

    ban_blue = 1;
    ban_red = 0;
    game_init();
    log_3("  3");
    Sleep(300);
    sound_bgm_game();
    Sleep(700);
    log_3("  2");
    sound_chosen();
    Sleep(1000);
    log_3("  1");
    sound_chosen();
    Sleep(1000);
    log_3("�÷֣�",score);
    while(1)
    {
        sound_bgm_game();
        if(!hasFocus())
        {
            color_log();
            log_bot_1("     --��ͣ--");
            while(1) if(hasFocus())
            {
                log_bot_1("          ");
                break;
            }
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            color_log();
            log_bot_1("     --��ͣ--");
            Sleep(200);
            while(1)
            {
                if(GetAsyncKeyState('B') & 0x8000) return;
                else if(GetAsyncKeyState('C') & 0x8000)
                {
                    game_setting();
                    map_refresh();
                    map_ptint();
                    color_log();
                    log_bot_1("     --��ͣ--");
                    log_3("�÷֣�",score);
                }
                else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
                {
                    log_bot_1("          ");
                    Sleep(200);
                    break;
                }
            }
        }
        check_cci();
        get_toward();
        Sleep(30);
        bullet_run();
        auto_blue();
        if(die_s()) return;
            //game_end();

        if(clock()-t1 > 80)
        {
            run();
            SetConsoleCursorPosition(hOutput,coord);
            t1 = clock();
        }
    }
}

void game_pair()
{
    bgm_on = setting_case_2;
    sound_on = setting_case_3;
    clock_t t1 = clock();

    ban_blue = 0;
    ban_red = 0;
    game_init();
    Sleep(300);
    sound_bgm_game();
    Sleep(700);
    while(1)
    {
        sound_bgm_game();
        if(!hasFocus())
        {
            color_log();
            log_bot_1("     --��ͣ--");
            while(1) if(hasFocus())
            {
                log_bot_1("          ");
                break;
            }
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            color_log();
            log_bot_1("     --��ͣ--");
            Sleep(200);
            while(1)
            {
                if(GetAsyncKeyState('B') & 0x8000) return;
                else if(GetAsyncKeyState('C') & 0x8000)
                {
                    game_setting();
                    map_refresh();
                    map_ptint();
                    color_log();
                    log_bot_1("     --��ͣ--");
                }
                else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
                {
                    log_bot_1("          ");
                    Sleep(200);
                    break;
                }
            }
        }
        GetConsoleCursorInfo(hOut,&cci);  //��꣬�л�ȫ��ʱ
        check_cci();
        get_toward();
        Sleep(30);
        bullet_run();
        if(die_p()) return;
            //game_end();

        if(clock()-t1 > 80)
        {
            run();
            SetConsoleCursorPosition(hOutput,coord);
            t1 = clock();
        }
    }

}

COORD mid = {16,13};
COORD mid_2 = {8,13};
void game_tutorial()
{
    system("cls");
    color_light();
    SetConsoleCursorPosition(hOutput,mid);
    cout<<"����ȫ��˵����(Y/N)";
    while(1)
    {
        if (GetAsyncKeyState('Y') & 0x8000)
        {
            color_normal();
            SetConsoleCursorPosition(hOutput,mid_2);
            cout<<"������ʾ�������������ʱ����B������ֹ";
            Sleep(2000);
            if(GetAsyncKeyState('B') & 0x8000) return;
            game_tutorial_1();
            if(GetAsyncKeyState('B') & 0x8000) return;
            game_tutorial_2();
            if(GetAsyncKeyState('B') & 0x8000) return;
            game_tutorial_3();
            if(GetAsyncKeyState('B') & 0x8000) return;
            game_tutorial_4();
            if(GetAsyncKeyState('B') & 0x8000) return;
            game_tutorial_5();
            if(GetAsyncKeyState('B') & 0x8000) return;
            game_tutorial_6();
            return;
        }
        if (GetAsyncKeyState('N') & 0x8000)
        {
            tutorial_pos = 0;
            system("cls");
            tutorial_init();
            while(1)
            {
                if(!hasFocus()) while(1) if(hasFocus()) break;
                check_cci();
                Sleep(100); //�ֶ�����
                if(!tutorial_refresh()) return;
            }
            return;
        }
    }


}

COORD tutorial_0={18,8};
COORD tutorial_1={18,10};
COORD tutorial_2={18,12};
COORD tutorial_3={18,14};
COORD tutorial_4={18,16};
COORD tutorial_5={18,18};
COORD tutorial_6={18,20};
COORD tutorial_7={18,22};
void tutorial_init()
{
    system("cls");
    hook_cci();

    if(tutorial_pos == 0) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_0);
    cout<<"�� �� �� �� ��";

    if(tutorial_pos == 1) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_1);
    cout<<"�� �� �� �� ��";

    if(tutorial_pos == 2) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_2);
    cout<<"�� �� �� �� ��";

    if(tutorial_pos == 3) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_3);
    cout<<"�� �� �� �� ��";

    if(tutorial_pos == 4) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_4);
    cout<<"�� Ҫ �� �� ��";

    if(tutorial_pos == 5) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_5);
    cout<<"˫ �� �� �� Ϸ";

    if(tutorial_pos == 6) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_6);
    cout<<"�� �� ѵ �� ��";

    if(tutorial_pos == 7) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_7);
    cout<<"   ��   ��   ";
}

bool tutorial_refresh()
{
    if((GetAsyncKeyState(VK_LBUTTON)&0x8000))
    {
        GetWindowRect(hwnd,&rect);
        GetCursorPos(&p);
        if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.310 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.350))
        {
            tutorial_pos = 0;
            sound_chosen_2();
            Sleep(100);
            game_tutorial_1();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.380 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.420))
        {
            tutorial_pos = 1;
            sound_chosen_2();
            Sleep(100);
            game_tutorial_2();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.445 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.485))
        {
            tutorial_pos = 2;
            sound_chosen_2();
            Sleep(100);
            game_tutorial_3();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.515 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.550))
        {
            tutorial_pos = 3;
            sound_chosen_2();
            Sleep(100);
            game_tutorial_4();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.580 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.615))
        {
            tutorial_pos = 4;
            sound_chosen_2();
            Sleep(100);
            game_tutorial_5();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.645 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.685))
        {
            tutorial_pos = 5;
            sound_chosen_2();
            Sleep(100);
            game_tutorial_6();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.345 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.61) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.715 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.750))
        {
            tutorial_pos = 6;
            sound_chosen_2();
            Sleep(100);
            game_on = 1;
            game_tutorial_deemo();
            game_on = 0;
            sound_bgm_game_close();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.405 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.535) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.785 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.815))
        {
            tutorial_pos = 7;
            sound_chosen_2();
            Sleep(100);
            return 0;
        }
        tutorial_init();
    }
    else if((GetAsyncKeyState('K')&0x8000) || (GetAsyncKeyState(VK_NUMPAD2)&0x8000))
    {
        return 0;
    }
    else if((GetAsyncKeyState(VK_RETURN)&0x8000) || (GetAsyncKeyState('J')&0x8000) || (GetAsyncKeyState(VK_NUMPAD1)&0x8000))
    {
        sound_chosen_2();
        Sleep(100);
        switch(tutorial_pos)
        {
            case 0:
                game_tutorial_1();
                break;
            case 1:
                game_tutorial_2();
                break;
            case 2:
                game_tutorial_3();
                break;
            case 3:
                game_tutorial_4();
                break;
            case 4:
                game_tutorial_5();
                break;
            case 5:
                game_tutorial_6();
                break;
            case 6:
                //sound_bgm_menu_close();
                game_on = 1;
                game_tutorial_deemo();
                game_on = 0;
                sound_bgm_game_close();
                break;
            case 7:
                return 0;
                break;
            default:
                break;
        }
        tutorial_init();
    }
    else if((GetAsyncKeyState(VK_UP)&0x8000) || (GetAsyncKeyState('W')&0x8000))
    {
        tutorial_pos--;
        if(tutorial_pos < 0) tutorial_pos = 0;
        sound_choose();
        Sleep(80);
        switch(tutorial_pos)
        {
            case 0:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_0);
                cout<<"�� �� �� �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"�� �� �� �� ��";
                break;
            case 1:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"�� �� �� �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"�� �� �� �� ��";
                break;
            case 2:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"�� �� �� �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"�� �� �� �� ��";
                break;
            case 3:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"�� �� �� �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"�� Ҫ �� �� ��";
            break;
            case 4:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"�� Ҫ �� �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"˫ �� �� �� Ϸ";
            break;
            case 5:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"˫ �� �� �� Ϸ";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"�� �� ѵ �� ��";
                break;
            case 6:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"�� �� ѵ �� ��";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_7);
                cout<<"   ��   ��   ";
                break;
            default:
                break;
        }
    }
    else if((GetAsyncKeyState(VK_DOWN)&0x8000) || (GetAsyncKeyState('S')&0x8000))
    {
        tutorial_pos++;
        if(tutorial_pos > 7) tutorial_pos = 7;
        sound_choose();
        Sleep(80);
        switch(tutorial_pos)
        {
            case 1:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_0);
                cout<<"�� �� �� �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"�� �� �� �� ��";
                break;
            case 2:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"�� �� �� �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"�� �� �� �� ��";
                break;
            case 3:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"�� �� �� �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"�� �� �� �� ��";
                break;
            case 4:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"�� �� �� �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"�� Ҫ �� �� ��";
                break;
            case 5:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"�� Ҫ �� �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"˫ �� �� �� Ϸ";
                break;
            case 6:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"˫ �� �� �� Ϸ";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"�� �� ѵ �� ��";
                break;
            case 7:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"�� �� ѵ �� ��";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_7);
                cout<<"   ��   ��   ";
                break;
            default:
                break;
        }
    }
    return 1;

}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
COORD iter;
int line = 1;
void tutorial_printer(string str,bool sk=0,bool sl=1,bool cl=1,bool el=1)
{
    bool skip = sk;
    for(int i=0;i<str.length();i++)
    {
        check_cci();
        if(sound_on) mciSendString("play ./sounds/message.mp3",0,0,0);
        if(sound_on) mciSendString("set ./sounds/message.mp3 speed 1200",0,0,0);
        if(sound_on) mciSendString("setaudio ./sounds/message.mp3 volume to 50",0,0,0);
        //mciSendString("set NOWMUSIC speed 10000",0,0,0);
        if(GetAsyncKeyState(VK_RETURN)&0x8000) skip = 1;
        if(GetConsoleScreenBufferInfo(hConsole, &csbi))
        {
            if(csbi.dwCursorPosition.X < 4)
            {
                iter = {3,line};
                SetConsoleCursorPosition(hOutput,iter);
                line++;
            }
            else if(csbi.dwCursorPosition.X > 45)
            {
                iter = {3,line};
                SetConsoleCursorPosition(hOutput,iter);
            }
        }
        cout<<str[i];
        if(!skip) Sleep(30);
    }
    mciSendString("close ./sounds/message.mp3",0,0,0);
    if(el) cout<<endl;
    if(cl) line++;
    if(sl) Sleep(700);
}

COORD deemo_1_1={12,20};
COORD deemo_1_2={36,20};
void game_tutorial_1()
{
    Sleep(100);
    line = 1;
    color_back();
    system("cls");
    string str_1 = "    �������賿���㣬�����ڸΡ��ߵ���ѧ������֪��������˯���ˡ�����������ʱ���㷢��������һ�����֡�";
    string str_2 = "    �㻹û�����������ʲô�£�������Զ�������Ų������㷢��������һ������...";
    string str_3 = "    ��������������ʲô�£����������Ǵ��е���ģ�����������һ�����֣���⧲�������";
    string str_4 = "    �Ǹ����ֻ������㣬Ȼ����������һ������ ...";
    tutorial_printer(str_1);
    tutorial_printer(str_2);
    tutorial_printer(str_3);
    tutorial_printer(str_4);
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"��";
    SetConsoleCursorPosition(hOutput,deemo_1_2);
    color_blue();
    cout<<"��";
    COORD deemo_1_2_iter = deemo_1_2;
    for(int i=36;i>20;i-=2)
    {
        deemo_1_2_iter = {i,20};
        SetConsoleCursorPosition(hOutput,deemo_1_2_iter);
        cout<<"��  ";
        Sleep(50);
    }
    Sleep(500);
    color_bullet();
    if(sound_on) mciSendString("play ./sounds/shot_3.wav",0,0,0);
    for(int i=18;i>12;i--)
    {
        deemo_1_2_iter = {i,20};
        SetConsoleCursorPosition(hOutput,deemo_1_2_iter);
        cout<<"7 ";
        Sleep(50);
    }
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"��";
    if(sound_on) mciSendString("play ./sounds/dead_1.wav",0,0,0);
    color_normal();
    SetConsoleCursorPosition(hOutput,test);
    system("pause");
}

COORD deemo_2_2={20,20};
void game_tutorial_2()
{
    Sleep(100);
    system("cls");
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"��";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"��";

    SetConsoleCursorPosition(hOutput,coord);
    line = 1;
    color_back();
    string str_1 = "    ��������ܿ�Ϳ��������Ǹ�����7�����������ϵĽ�����㱾����������Ǹ����ٳ�10ȡ��������ʽ�ǣ�";
    string str_2 = "        ��� = (����+�ӵ�) mod 10";
    string str_3 = "    ��ܿ��ѧ����������ܣ��������ʱ���϶�������������˵ڶ�������...";

    tutorial_printer(str_1,0);
    tutorial_printer(str_2,1);
    tutorial_printer(str_3);

    COORD deemo_2_2_iter = deemo_2_2;
    Sleep(1500);
    color_bullet();
    if(sound_on) mciSendString("play ./sounds/shot_3.wav",0,0,0);
    for(int i=18;i>12;i--)
    {
        deemo_2_2_iter = {i,20};
        SetConsoleCursorPosition(hOutput,deemo_2_2_iter);
        cout<<"6 ";
        Sleep(50);
    }
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"��";
    if(sound_on) mciSendString("play ./sounds/dead_1.wav",0,0,0);

    color_normal();
    SetConsoleCursorPosition(hOutput,test);
    system("pause");
}

void game_tutorial_3()
{
    Sleep(100);
    system("cls");
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"��";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"��";

    SetConsoleCursorPosition(hOutput,coord);
    line = 1;
    color_back();
    string str_1 = "    ������õĽ�����ϴ���������Ĳ�ͬ�������Ѳ����������㣬�������Ǹ�����6�����������ϵĽ�����㱾���������10�ټ�ȥ�Ǹ����õ��Ľ����10ȡ��������ʽ�ǣ�";
    string str_2 = "        ��� = (����-�ӵ�+10) mod 10";
    string str_3 = "    ��ܿ�ϰ��������ܣ�������ˣ��㻹�������˳˷���η������ã���ʽ�ֱ��ǣ�";
    string str_4 = " �˷���";
    string str_5 = "        ��� = (����*�ӵ�) mod 10";
    string str_6 = " �η���";
    string str_7 = "        ��� = (����^�ӵ�) mod 10";
    string str_8 = "    ��������ģʽ�Ĳ������ֱ��ǣ��ӷ�(U)������(I)���˷�(O)���η�(L)��";

    tutorial_printer(str_1);
    tutorial_printer(str_2,1);
    tutorial_printer(str_3);
    tutorial_printer(str_4,0,1,0);
    tutorial_printer(str_5,1,1,0);
    tutorial_printer(str_6,0,1,0);
    tutorial_printer(str_7,1);
    tutorial_printer(str_8);

    color_normal();
    SetConsoleCursorPosition(hOutput,test);
    system("pause");
}

COORD deemo_4_1={12,19};
void game_tutorial_4()
{
    Sleep(100);
    system("cls");
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"��";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"��";

    SetConsoleCursorPosition(hOutput,coord);
    line = 2;
    color_back();

    string str_1 = "    İ���˳������㹥��������α���㿪�ˣ��ƶ���ɫ�Ĳ����ǣ���(W)����(S)����(A)����(D)��";
    string str_2 = "    �����밴W��������ܹ�����";

    tutorial_printer(str_1);
    tutorial_printer(str_2);

    COORD deemo_2_2_iter = deemo_2_2;
    color_bullet();
    if(sound_on) mciSendString("play ./sounds/shot_3.wav",0,0,0);
    for(int i=18;i>14;i--)
    {
        deemo_2_2_iter = {i,20};
        SetConsoleCursorPosition(hOutput,deemo_2_2_iter);
        cout<<"4 ";
        Sleep(50);
    }
    while(1)
    {
        if(GetAsyncKeyState('W') & 0x8000) break;
    }
    if(sound_on) mciSendString("play ./sounds/choose_5.wav",0,0,0);
    color_red();
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    cout<<"  ";
    SetConsoleCursorPosition(hOutput,deemo_4_1);
    cout<<"��";
    color_bullet();
    for(int i=14;i>10;i--)
    {
        deemo_2_2_iter = {i,20};
        SetConsoleCursorPosition(hOutput,deemo_2_2_iter);
        cout<<"4 ";
        Sleep(50);
    }
    SetConsoleCursorPosition(hOutput,deemo_2_2_iter);
    cout<<" ";

    color_normal();
    SetConsoleCursorPosition(hOutput,test);
    system("pause");

}

COORD deemo_5_2={20,19};
COORD deemo_5_0={3,19};
COORD deemo_5_3={3,21};
void game_tutorial_5()
{
    Sleep(100);
    system("cls");
    SetConsoleCursorPosition(hOutput,deemo_4_1);
    color_red();
    cout<<"��";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"��";

    SetConsoleCursorPosition(hOutput,coord);
    line = 1;
    color_back();

    string str_1 = "    ����Ȼ�㿪�ˣ���һ��Ͱ������0�ˣ���İ����˵����ԭ����һ���˱��0�����ͻ�������İ����׷���������������Ѿ�ϰ������ܵ��㲻�ܰ�����ʱ�򷴻��ˣ�";
    string str_2 = "    �ڹ���ǰҪ��Ϊ����(ATK)״̬���л�Ϊ����״̬�Ĳ������ǣ�����(J)�����빥��״̬����Ӧ�ķ�����������Ӧ�ķ�����Ӧ�Ĺ���ģʽ���й�����";
    string str_3 = "    �ڹ���״̬ʱ�ǲ����ƶ��ģ�Ҫ�ƶ��Ļ�����ȡ������״̬����صĲ������ǣ�ȡ��(K)��";
    string str_4 = "    ����İ����׷�����ˣ��������ɣ�(��ʾ���Ȱ�J���ٰ�D��)";
    string str_5 = "    ���е����İ���˱���ɵ��ˣ���ǰ���ƺ����и�ǿ��ĵ��˵�����...";

    tutorial_printer(str_1);
    tutorial_printer(str_2);
    tutorial_printer(str_3);
    tutorial_printer(str_4);

    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"  ";
    SetConsoleCursorPosition(hOutput,deemo_5_2);
    cout<<"��";

    while(1)
    {
        if(GetAsyncKeyState('J') & 0x8000) break;
    }
    SetConsoleCursorPosition(hOutput,deemo_5_0);
    color_red();
    if(sound_on) mciSendString("play ./sounds/choose_4.wav",0,0,0);
    cout<<"ATK";
    while(1)
    {
        if(GetAsyncKeyState('D') & 0x8000) break;
    }
    SetConsoleCursorPosition(hOutput,deemo_5_0);
    color_red();
    cout<<"   ";
    COORD deemo_5_1_iter = deemo_4_1;
    if(sound_on) mciSendString("play ./sounds/shot_1.wav",0,0,0);
    color_bullet();
    for(int i=14;i<20;i++)
    {
        deemo_5_1_iter = {i,19};
        SetConsoleCursorPosition(hOutput,deemo_5_1_iter);
        cout<<" 2";
        Sleep(50);
    }
    SetConsoleCursorPosition(hOutput,deemo_5_2);
    color_blue();
    cout<<"��";
    if(sound_on) mciSendString("play ./sounds/dead_2.wav",0,0,0);

    Sleep(1500);
    line += 4;
    SetConsoleCursorPosition(hOutput,deemo_5_3);
    color_back();
    tutorial_printer(str_5);

    color_normal();
    SetConsoleCursorPosition(hOutput,test);
    system("pause");
}

void game_tutorial_6()
{
    Sleep(100);
    line = 1;
    color_back();
    system("cls");
    string str_1 = "    ���⣬��˫����Ϸ�У�P2����ز���Ϊ����(��)����(��)����(��)����(��)������(1)��ȡ��(2)���ӷ�(4)������(5)���˷�(6)���η�(3)��";
    string str_2 = "          ��         �ӷ�  ����  �˷�";
    string str_3 = "          |             \\   |   /";
    string str_4 = "          ��             4  5  6";
    string str_5 = "       �� �� ��          1  2  3";
    string str_6 = "       /  |  \\          /   |   \\";
    string str_7 = "     ��   ��   ��    ����  ȡ��  �η�";
    string str_8 = "    ���������ѵ��ģʽ��(Y/N)";

    tutorial_printer(str_1);
    line++;
    tutorial_printer(str_2,1,0,0);
    tutorial_printer(str_3,1,0,0);
    color_blue();
    tutorial_printer(str_4,1,0,1);
    tutorial_printer(str_5,1,0,0);
    color_back();
    tutorial_printer(str_6,1,0,0);
    tutorial_printer(str_7,1,0,1);
    line+=2;
    tutorial_printer(str_8);

    while(1)
    {
        if(GetAsyncKeyState('Y') & 0x8000)
        {
            game_on = 1;
            game_tutorial_deemo();
            game_on = 0;
            sound_bgm_game_close();
        }
        else if(GetAsyncKeyState('N') & 0x8000) break;
    }

    color_normal();
}

void game_tutorial_deemo()
{
    Sleep(100);
    line = -1;
    plan_init_blue();
    set_diff(0);
    bgm_on = setting_case_2;
    sound_on = setting_case_3;

    clock_t t1 = clock();

    ban_blue = 1;
    ban_red = 0;
    game_init();
    color_log();
    string str_1 = ("����������ѵ��ģʽ����ɫ�����㣬��ɫ���ǵ��ˣ��������ߵ����ֱַ�������ǵ��ӵ�����ͷ���ӵ�˳������������һ�°ɣ�");
    SetConsoleCursorPosition(hOutput,coord);
    tutorial_printer(str_1);
    log_bot_1("��������ʾ�����ӵ����е���Ϣ��");
    color_normal();
    log_3("  3");
    sound_chosen();
    Sleep(300);
    sound_bgm_game();
    Sleep(700);
    log_3("  2");
    sound_chosen();
    Sleep(1000);
    log_3("  1");
    sound_chosen();
    Sleep(1000);
    log_3("   ");
    while(1)
    {
        sound_bgm_game();
        if(!hasFocus())
        {
            color_log();
            log_bot_1("     --��ͣ--");
            while(1) if(hasFocus())
            {
                log_bot_1("          ");
                break;
            }
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            color_log();
            log_bot_1("     --��ͣ--");
            Sleep(200);
            while(1)
            {
                if(GetAsyncKeyState('B') & 0x8000) return;
                else if(GetAsyncKeyState('C') & 0x8000)
                {
                    game_setting();
                    map_refresh();
                    map_ptint();
                    color_log();
                    log_bot_1("     --��ͣ--");
                }
                else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
                {
                    log_bot_1("          ");
                    Sleep(200);
                    break;
                }
            }
        }
        check_cci();
        get_toward();
        Sleep(30);
        bullet_run();
        auto_blue();
        if(die_d()) return;
            //game_end();

        if(clock()-t1 > 80)
        {
            run();
            SetConsoleCursorPosition(hOutput,coord);
            t1 = clock();
        }
    }
}

void game_setting()
{
    setting_pos = 0;
    system("cls");
    game_setting_init();
    while(1)
    {
        if(!hasFocus()) while(1) if(hasFocus()) break;
        check_cci();
        Sleep(100); //�ֶ�����
        if(!game_setting_refresh()) return;
    }
}


COORD setting_0={16,10};
COORD setting_1={16,12};
COORD setting_2={16,14};
COORD setting_3={16,16};
COORD setting_4={20,18};
void game_setting_init()
{
    if(setting_pos == 0) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_0);
    cout<<"�� Ϸ �� ��: ";
    switch(setting_case_0){
        case 1:
            cout<<"����";
            break;
        case 2:
            cout<<"��  ��";
            break;
        case 3:
            cout<<"��  ͨ";
            break;
        case 4:
            cout<<"��  ��";
            break;
        case 5:
            cout<<"��ը��";
            break;
        default:
            break;
    }

    if(setting_pos == 1) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_1);
    cout<<"�� �� �� ɫ: ";
    switch(setting_case_1){
        case 0:
            cout<<"��  ��";
            break;
        case 1:
            cout<<"��  ��";
            break;
        default:
            break;
    }

    if(setting_pos == 2) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_2);
    cout<<"�� �� �� ��: ";
    switch(setting_case_2){
        case 1:
            cout<<"  ��";
            break;
        case 0:
            cout<<"  ��";
            break;
        default:
            break;
    }

    if(setting_pos == 3) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_3);
    cout<<"�� Ϸ �� Ч: ";
    switch(setting_case_3){
        case 1:
            cout<<"  ��";
            break;
        case 0:
            cout<<"  ��";
            break;
        default:
            break;
    }

    if(setting_pos == 4) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_4);
    cout<<"�� �� �� ҳ";
}

bool game_setting_refresh()
{

    if((GetAsyncKeyState(VK_LBUTTON)&0x8000))
    {
        GetWindowRect(hwnd,&rect);
        GetCursorPos(&p);
        if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.305 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.67) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.375 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.42))
        {
            setting_pos = 0;
            setting_case_0++;
            if(setting_case_0 > 5) setting_case_0 = 1;
            sound_change();
            Sleep(300);
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.305 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.67) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.45 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.485))
        {
            setting_pos = 1;
            setting_case_1++;
            if(setting_case_1 > 1) setting_case_1 = 0;
            sound_change();
            Sleep(300);
            if(setting_case_1) {theme = 'w';system("color 70");}  //set theme
            else {theme = 'b';system("color 07");}
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.305 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.67) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.51 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.55))
        {
            setting_pos = 2;
            setting_case_2 = !setting_case_2;
            bgm_on = setting_case_2;
            sound_change();
            Sleep(300);
            if(game_on) sound_bgm_game();
            else sound_bgm_menu();
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.305 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.67) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.58 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.615))
        {
            setting_pos = 3;
            setting_case_3 = !setting_case_3;
            sound_on = setting_case_3;
            sound_change();
            Sleep(300);
        }
        else if(((double)(p.x-rect.left)/(rect.right-rect.left)>=0.375 && (double)(p.x-rect.left)/(rect.right-rect.left)<=0.6) && ((double)(p.y-rect.top)/(rect.bottom-rect.top)>=0.65 && (double)(p.y-rect.top)/(rect.bottom-rect.top)<=0.685))
        {
            setting_pos = 4;
            sound_chosen_2();
            Sleep(100);
            return 0;
        }
        game_setting_init();
    }
    else if((GetAsyncKeyState(VK_RETURN)&0x8000) || (GetAsyncKeyState('K')&0x8000) || (GetAsyncKeyState(VK_NUMPAD2)&0x8000))
    {
        sound_chosen_2();
        Sleep(100);
        return 0;
    }
    else if((GetAsyncKeyState('D')&0x8000) || (GetAsyncKeyState(VK_RIGHT)&0x8000))
    {
        switch(setting_pos)
        {
            case 0:
                setting_case_0++;
                if(setting_case_0 > 5) setting_case_0 = 1;
                sound_change();
                Sleep(300);
                break;
            case 1:
                setting_case_1++;
                if(setting_case_1 > 1) setting_case_1 = 0;
                sound_change();
                Sleep(300);
                if(setting_case_1) {theme = 'w';system("color 70");}  //set theme
                else {theme = 'b';system("color 07");}
                break;
            case 2:
                setting_case_2 = !setting_case_2;
                bgm_on = setting_case_2;
                sound_change();
                Sleep(300);
                if(game_on) sound_bgm_game();
                else sound_bgm_menu();
                break;
            case 3:
                setting_case_3 = !setting_case_3;
                sound_on = setting_case_3;
                sound_change();
                Sleep(300);
                break;
            default:
                break;
        }
        game_setting_init();
    }
    else if((GetAsyncKeyState('J')&0x8000) || (GetAsyncKeyState(VK_NUMPAD1)&0x8000))
    {
        switch(setting_pos)
        {
            case 0:
                setting_case_0++;
                if(setting_case_0 > 5) setting_case_0 = 1;
                sound_change();
                Sleep(300);
                break;
            case 1:
                setting_case_1++;
                if(setting_case_1 > 1) setting_case_1 = 0;
                sound_change();
                Sleep(300);
                if(setting_case_1) {theme = 'w';system("color 70");}  //set theme
                else {theme = 'b';system("color 07");}
                break;
            case 2:
                setting_case_2 = !setting_case_2;
                bgm_on = setting_case_2;
                sound_change();
                Sleep(300);
                if(game_on) sound_bgm_game();
                else sound_bgm_menu();
                break;
            case 3:
                setting_case_3 = !setting_case_3;
                sound_on = setting_case_3;
                sound_change();
                Sleep(300);
                break;
            case 4:
                sound_chosen_2();
                Sleep(100);
                return 0;
            default:
                break;
        }
        game_setting_init();
    }
    else if((GetAsyncKeyState('A')&0x8000) || (GetAsyncKeyState(VK_LEFT)&0x8000))
    {
        switch(setting_pos)
        {
            case 0:
                setting_case_0--;
                if(setting_case_0 < 1) setting_case_0 = 5;
                sound_change();
                Sleep(300);
                break;
            case 1:
                setting_case_1--;
                if(setting_case_1 < 0) setting_case_1 = 1;
                sound_change();
                Sleep(300);
                if(setting_case_1) {theme = 'w';system("color 70");}  //set theme
                else {theme = 'b';system("color 07");}
                break;
            case 2:
                setting_case_2 = !setting_case_2;
                bgm_on = setting_case_2;
                sound_change();
                Sleep(300);
                if(game_on) sound_bgm_game();
                else sound_bgm_menu();
                break;
            case 3:
                setting_case_3 = !setting_case_3;
                sound_on = setting_case_3;
                sound_change();
                Sleep(300);
                break;
            default:
                break;
        }
        game_setting_init();
    }
    else if((GetAsyncKeyState(VK_UP)&0x8000) || (GetAsyncKeyState('W')&0x8000))
    {
        setting_pos--;
        if(setting_pos < 0) setting_pos = 0;
        sound_choose();
        Sleep(80);
        switch(setting_pos)
        {
            case 0:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_0);
                cout<<"�� Ϸ �� ��: ";
                switch(setting_case_0){
                    case 1:
                        cout<<"����";
                        break;
                    case 2:
                        cout<<"��  ��";
                        break;
                    case 3:
                        cout<<"��  ͨ";
                        break;
                    case 4:
                        cout<<"��  ��";
                        break;
                    case 5:
                        cout<<"��ը��";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"�� �� �� ɫ: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"��  ��";
                        break;
                    case 1:
                        cout<<"��  ��";
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"�� �� �� ɫ: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"��  ��";
                        break;
                    case 1:
                        cout<<"��  ��";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"�� �� �� ��: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"�� �� �� ��: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"�� Ϸ �� Ч: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"�� Ϸ �� Ч: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_4);
                cout<<"�� �� �� ҳ";
                break;
            default:
                break;
        }
    }
    else if((GetAsyncKeyState(VK_DOWN)&0x8000) || (GetAsyncKeyState('S')&0x8000))
    {
        setting_pos++;
        if(setting_pos > 4) setting_pos = 4;
        sound_choose();
        Sleep(80);
        switch(setting_pos)
        {
            case 1:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_0);
                cout<<"�� Ϸ �� ��: ";
                switch(setting_case_0){
                    case 1:
                        cout<<"����";
                        break;
                    case 2:
                        cout<<"��  ��";
                        break;
                    case 3:
                        cout<<"��  ͨ";
                        break;
                    case 4:
                        cout<<"��  ��";
                        break;
                    case 5:
                        cout<<"��ը��";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"�� �� �� ɫ: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"��  ��";
                        break;
                    case 1:
                        cout<<"��  ��";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"�� �� �� ɫ: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"��  ��";
                        break;
                    case 1:
                        cout<<"��  ��";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"�� �� �� ��: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"�� �� �� ��: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"�� Ϸ �� Ч: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"�� Ϸ �� Ч: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  ��";
                        break;
                    case 0:
                        cout<<"  ��";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_4);
                cout<<"�� �� �� ҳ";
                break;
            default:
                break;
        }
    }
    return 1;
}
