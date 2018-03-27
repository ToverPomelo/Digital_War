#include "war.hpp"
#include "menu.hpp"

int main()
{
    system("mode con cols=52 lines=28");
    system("title=Digital_War");

    clock_t t1 = clock();
    game_init();
    while(1)
    {
        get_toward();
        Sleep(50);
        bullet_run();
        die();
        if(clock()-t1 > 150)
        {
            run();
            SetConsoleCursorPosition(hOutput,coord);
            t1 = clock();
        }
    }
    game_end();

    return 0;
}
