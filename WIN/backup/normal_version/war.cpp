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
    hwnd=FindWindow("ConsoleWindowClass",NULL);/*  控制台窗口句柄 */
    //HWND hwnd=GetForegroundWindow();
	hInput = GetStdHandle(STD_INPUT_HANDLE); /*  输入设备句柄 */

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
        Sleep(100); //手动消抖
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
        GetCursorPos(&p);//获取鼠标坐标
        //SetCursorPos(p.x+3,p.y);//更改鼠标坐标
        SetConsoleCursorPosition(hOutput,coord);
        cout<<(double)(p.x-rect.left)/(rect.right-rect.left)<<" , "<<(double)(p.y-rect.top)/(rect.bottom-rect.top)<<"              "<<endl;
        Sleep(10);//控制移动时间间隔
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
    cout<<"生 存 模 式";

    if(menu_pos == 1) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_1);
    cout<<"多 人 游 戏";

    if(menu_pos == 2) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_2);
    cout<<"游 戏 说 明";

    if(menu_pos == 3) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_3);
    cout<<"游 戏 设 置";

    if(menu_pos == 4) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,menu_4);
    cout<<"退 出 游 戏";

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
                cout<<"生 存 模 式";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"多 人 游 戏";
                break;
            case 1:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"多 人 游 戏";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"游 戏 说 明";
                break;
            case 2:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"游 戏 说 明";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"游 戏 设 置";
                break;
            case 3:
                color_log();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"游 戏 设 置";
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_4);
                cout<<"退 出 游 戏";
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
                cout<<"生 存 模 式";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"多 人 游 戏";
                break;
            case 2:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_1);
                cout<<"多 人 游 戏";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"游 戏 说 明";
                break;
            case 3:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_2);
                cout<<"游 戏 说 明";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"游 戏 设 置";
                break;
            case 4:
                color_normal();
                SetConsoleCursorPosition(hOutput,menu_3);
                cout<<"游 戏 设 置";
                color_log();
                SetConsoleCursorPosition(hOutput,menu_4);
                cout<<"退 出 游 戏";
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
    //set_diff(0);  //调试
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
    log_3("得分：",score);
    while(1)
    {
        sound_bgm_game();
        if(!hasFocus())
        {
            color_log();
            log_bot_1("     --暂停--");
            while(1) if(hasFocus())
            {
                log_bot_1("          ");
                break;
            }
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            color_log();
            log_bot_1("     --暂停--");
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
                    log_bot_1("     --暂停--");
                    log_3("得分：",score);
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
            log_bot_1("     --暂停--");
            while(1) if(hasFocus())
            {
                log_bot_1("          ");
                break;
            }
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            color_log();
            log_bot_1("     --暂停--");
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
                    log_bot_1("     --暂停--");
                }
                else if(GetAsyncKeyState(VK_SPACE) & 0x8000)
                {
                    log_bot_1("          ");
                    Sleep(200);
                    break;
                }
            }
        }
        GetConsoleCursorInfo(hOut,&cci);  //光标，切换全屏时
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
    cout<<"播放全部说明？(Y/N)";
    while(1)
    {
        if (GetAsyncKeyState('Y') & 0x8000)
        {
            color_normal();
            SetConsoleCursorPosition(hOutput,mid_2);
            cout<<"下面提示输入任意键继续时按‘B’可中止";
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
                Sleep(100); //手动消抖
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
    cout<<"神 奇 的 数 字";

    if(tutorial_pos == 1) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_1);
    cout<<"敌 人 的 子 弹";

    if(tutorial_pos == 2) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_2);
    cout<<"四 则 的 运 算";

    if(tutorial_pos == 3) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_3);
    cout<<"快 速 地 移 动";

    if(tutorial_pos == 4) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_4);
    cout<<"该 要 反 击 了";

    if(tutorial_pos == 5) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_5);
    cout<<"双 人 的 游 戏";

    if(tutorial_pos == 6) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_6);
    cout<<"新 手 训 练 场";

    if(tutorial_pos == 7) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,tutorial_7);
    cout<<"   返   回   ";
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
                cout<<"神 奇 的 数 字";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"敌 人 的 子 弹";
                break;
            case 1:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"敌 人 的 子 弹";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"四 则 的 运 算";
                break;
            case 2:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"四 则 的 运 算";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"快 速 地 移 动";
                break;
            case 3:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"快 速 地 移 动";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"该 要 反 击 了";
            break;
            case 4:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"该 要 反 击 了";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"双 人 的 游 戏";
            break;
            case 5:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"双 人 的 游 戏";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"新 手 训 练 场";
                break;
            case 6:
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"新 手 训 练 场";
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_7);
                cout<<"   返   回   ";
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
                cout<<"神 奇 的 数 字";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"敌 人 的 子 弹";
                break;
            case 2:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_1);
                cout<<"敌 人 的 子 弹";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"四 则 的 运 算";
                break;
            case 3:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_2);
                cout<<"四 则 的 运 算";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"快 速 地 移 动";
                break;
            case 4:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_3);
                cout<<"快 速 地 移 动";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"该 要 反 击 了";
                break;
            case 5:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_4);
                cout<<"该 要 反 击 了";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"双 人 的 游 戏";
                break;
            case 6:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_5);
                cout<<"双 人 的 游 戏";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"新 手 训 练 场";
                break;
            case 7:
                color_normal();
                SetConsoleCursorPosition(hOutput,tutorial_6);
                cout<<"新 手 训 练 场";
                color_log();
                SetConsoleCursorPosition(hOutput,tutorial_7);
                cout<<"   返   回   ";
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
    string str_1 = "    现在是凌晨两点，你正在肝《高等数学》，不知不觉，你睡着了。当你醒来的时候，你发现你变成了一个数字。";
    string str_2 = "    你还没搞清楚发生了什么事，但听见远处传来脚步声，你发现是另外一个数字...";
    string str_3 = "    你想问他发生了什么事，但发现他是带有敌意的，他向你扔了一个数字，你猝不及防。";
    string str_4 = "    那个数字击中了你，然后你变成了另一个数字 ...";
    tutorial_printer(str_1);
    tutorial_printer(str_2);
    tutorial_printer(str_3);
    tutorial_printer(str_4);
    SetConsoleCursorPosition(hOutput,deemo_1_1);
    color_red();
    cout<<"⑤";
    SetConsoleCursorPosition(hOutput,deemo_1_2);
    color_blue();
    cout<<"⑧";
    COORD deemo_1_2_iter = deemo_1_2;
    for(int i=36;i>20;i-=2)
    {
        deemo_1_2_iter = {i,20};
        SetConsoleCursorPosition(hOutput,deemo_1_2_iter);
        cout<<"⑧  ";
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
    cout<<"②";
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
    cout<<"②";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"⑧";

    SetConsoleCursorPosition(hOutput,coord);
    line = 1;
    color_back();
    string str_1 = "    聪明的你很快就看出来，那个数字7作用在你身上的结果是你本身的数加上那个数再除10取余数，公式是：";
    string str_2 = "        结果 = (本身+子弹) mod 10";
    string str_3 = "    你很快就学会了这个技能，趁着这个时间空隙，他又向你扔了第二个数字...";

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
    cout<<"⑥";
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
    cout<<"⑥";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"⑧";

    SetConsoleCursorPosition(hOutput,coord);
    line = 1;
    color_back();
    string str_1 = "    这次作用的结果和上次推算出来的不同，但这难不到聪明的你，很明显那个数字6作用在你身上的结果是你本身的数加上10再减去那个数得到的结果除10取余数，公式是：";
    string str_2 = "        结果 = (本身-子弹+10) mod 10";
    string str_3 = "    你很快习得了这项技能，不仅如此，你还摸索出了乘法与次方的作用，公式分别是：";
    string str_4 = " 乘法：";
    string str_5 = "        结果 = (本身*子弹) mod 10";
    string str_6 = " 次方：";
    string str_7 = "        结果 = (本身^子弹) mod 10";
    string str_8 = "    更换攻击模式的操作键分别是：加法(U)、减法(I)、乘法(O)、次方(L)。";

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
    cout<<"⑥";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"⑧";

    SetConsoleCursorPosition(hOutput,coord);
    line = 2;
    color_back();

    string str_1 = "    陌生人持续向你攻击，但这次被你躲开了，移动角色的操作是：上(W)、下(S)、左(A)、右(D)。";
    string str_2 = "    下面请按W往上闪躲避攻击：";

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
    cout<<"⑥";
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
    cout<<"⑥";
    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"⑧";

    SetConsoleCursorPosition(hOutput,coord);
    line = 1;
    color_back();

    string str_1 = "    “居然躲开了，差一点就把他变成0了！”陌生人说道。原来把一个人变成0后他就会死亡。陌生人追上来继续攻击，已经习得四项技能的你不能挨打，是时候反击了！";
    string str_2 = "    在攻击前要变为攻击(ATK)状态，切换为攻击状态的操作键是：攻击(J)，进入攻击状态后按相应的方向键即可向对应的方向按相应的攻击模式进行攻击。";
    string str_3 = "    在攻击状态时是不能移动的，要移动的话必须取消攻击状态，相关的操作键是：取消(K)。";
    string str_4 = "    现在陌生人追上来了，快点打倒他吧！(提示：先按J，再按D。)";
    string str_5 = "    带有敌意的陌生人被你干掉了，但前面似乎还有更强大的敌人等着你...";

    tutorial_printer(str_1);
    tutorial_printer(str_2);
    tutorial_printer(str_3);
    tutorial_printer(str_4);

    SetConsoleCursorPosition(hOutput,deemo_2_2);
    color_blue();
    cout<<"  ";
    SetConsoleCursorPosition(hOutput,deemo_5_2);
    cout<<"⑧";

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
    cout<<"◎";
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
    string str_1 = "    另外，在双人游戏中，P2的相关操作为：上(↑)、下(↓)、左(←)、右(→)、攻击(1)、取消(2)、加法(4)、减法(5)、乘法(6)、次方(3)。";
    string str_2 = "          上         加法  减法  乘法";
    string str_3 = "          |             \\   |   /";
    string str_4 = "          ↑             4  5  6";
    string str_5 = "       ← ↓ →          1  2  3";
    string str_6 = "       /  |  \\          /   |   \\";
    string str_7 = "     左   下   右    攻击  取消  次方";
    string str_8 = "    下面想进入训练模式吗？(Y/N)";

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
    string str_1 = ("这里是新手训练模式，红色的是你，蓝色的是敌人，左右两边的数字分别代表你们的子弹，箭头是子弹顺序。下面来尝试一下吧！");
    SetConsoleCursorPosition(hOutput,coord);
    tutorial_printer(str_1);
    log_bot_1("←这里显示的是子弹击中的信息流");
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
            log_bot_1("     --暂停--");
            while(1) if(hasFocus())
            {
                log_bot_1("          ");
                break;
            }
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            color_log();
            log_bot_1("     --暂停--");
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
                    log_bot_1("     --暂停--");
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
        Sleep(100); //手动消抖
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
    cout<<"游 戏 难 度: ";
    switch(setting_case_0){
        case 1:
            cout<<"超简单";
            break;
        case 2:
            cout<<"简  单";
            break;
        case 3:
            cout<<"普  通";
            break;
        case 4:
            cout<<"困  难";
            break;
        case 5:
            cout<<"屌炸天";
            break;
        default:
            break;
    }

    if(setting_pos == 1) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_1);
    cout<<"背 景 颜 色: ";
    switch(setting_case_1){
        case 0:
            cout<<"纯  黑";
            break;
        case 1:
            cout<<"纯  白";
            break;
        default:
            break;
    }

    if(setting_pos == 2) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_2);
    cout<<"背 景 音 乐: ";
    switch(setting_case_2){
        case 1:
            cout<<"  开";
            break;
        case 0:
            cout<<"  关";
            break;
        default:
            break;
    }

    if(setting_pos == 3) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_3);
    cout<<"游 戏 音 效: ";
    switch(setting_case_3){
        case 1:
            cout<<"  开";
            break;
        case 0:
            cout<<"  关";
            break;
        default:
            break;
    }

    if(setting_pos == 4) color_log();
    else color_normal();
    SetConsoleCursorPosition(hOutput,setting_4);
    cout<<"返 回 上 页";
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
                cout<<"游 戏 难 度: ";
                switch(setting_case_0){
                    case 1:
                        cout<<"超简单";
                        break;
                    case 2:
                        cout<<"简  单";
                        break;
                    case 3:
                        cout<<"普  通";
                        break;
                    case 4:
                        cout<<"困  难";
                        break;
                    case 5:
                        cout<<"屌炸天";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"背 景 颜 色: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"纯  黑";
                        break;
                    case 1:
                        cout<<"纯  白";
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"背 景 颜 色: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"纯  黑";
                        break;
                    case 1:
                        cout<<"纯  白";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"背 景 音 乐: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"背 景 音 乐: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"游 戏 音 效: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                color_log();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"游 戏 音 效: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_4);
                cout<<"返 回 上 页";
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
                cout<<"游 戏 难 度: ";
                switch(setting_case_0){
                    case 1:
                        cout<<"超简单";
                        break;
                    case 2:
                        cout<<"简  单";
                        break;
                    case 3:
                        cout<<"普  通";
                        break;
                    case 4:
                        cout<<"困  难";
                        break;
                    case 5:
                        cout<<"屌炸天";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"背 景 颜 色: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"纯  黑";
                        break;
                    case 1:
                        cout<<"纯  白";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_1);
                cout<<"背 景 颜 色: ";
                switch(setting_case_1){
                    case 0:
                        cout<<"纯  黑";
                        break;
                    case 1:
                        cout<<"纯  白";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"背 景 音 乐: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_2);
                cout<<"背 景 音 乐: ";
                switch(setting_case_2){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"游 戏 音 效: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                color_normal();
                SetConsoleCursorPosition(hOutput,setting_3);
                cout<<"游 戏 音 效: ";
                switch(setting_case_3){
                    case 1:
                        cout<<"  开";
                        break;
                    case 0:
                        cout<<"  关";
                        break;
                    default:
                        break;
                }
                color_log();
                SetConsoleCursorPosition(hOutput,setting_4);
                cout<<"返 回 上 页";
                break;
            default:
                break;
        }
    }
    return 1;
}
