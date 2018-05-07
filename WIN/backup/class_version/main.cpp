//#include "war.hpp"
//#include "menu.hpp"
#include "game.cpp"

int main()
{
    system("mode con cols=52 lines=28");
    system("title=Digital_War");
    hwnd=FindWindow("ConsoleWindowClass",NULL);/*  控制台窗口句柄 */
	hInput = GetStdHandle(STD_INPUT_HANDLE); /*  输入设备句柄 */

    if(theme == 'w') system("color 70");
    else if(theme == 'b') system("color 07");

    menu();



    return 0;
}

/*******************************************************************************/
