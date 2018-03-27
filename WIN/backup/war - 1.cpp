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
        if(clock()-t1 > 200)
        {
            run();
            t1 = clock();
        }
    }
    game_end();

    return 0;
}
