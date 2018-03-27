#include "war.hpp"

int main()
{
    clock_t t1 = clock();
    system("cls");
    game_init();
    map_ptint();
    while(1)
    {
        get_toward();
        Sleep(50);
        bullet_run();
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
