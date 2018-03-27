#include "war.hpp"

int main()
{
    clock_t t1 = clock();
    system("cls");
    game_init();
    map_ptint();
    while(1)
    {
        if(clock()-t1 > 100)
        {
            map_refresh();
            t1 = clock();
        }
    }

    return 0;
}
