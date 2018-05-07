#include "auto.cpp"
using namespace std;

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

COORD menu_0={20,10};
COORD menu_1={20,12};
COORD menu_2={20,14};
COORD menu_3={20,16};
COORD menu_4={20,18};
COORD test={15,25};

COORD mid = {16,13};
COORD mid_2 = {8,13};

COORD tutorial_0={18,8};
COORD tutorial_1={18,10};
COORD tutorial_2={18,12};
COORD tutorial_3={18,14};
COORD tutorial_4={18,16};
COORD tutorial_5={18,18};
COORD tutorial_6={18,20};
COORD tutorial_7={18,22};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
COORD iter;
int line = 1;

COORD deemo_1_1={12,20};
COORD deemo_1_2={36,20};

COORD deemo_2_2={20,20};

COORD deemo_4_1={12,19};

COORD deemo_5_2={20,19};
COORD deemo_5_0={3,19};
COORD deemo_5_3={3,21};

COORD setting_0={16,10};
COORD setting_1={16,12};
COORD setting_2={16,14};
COORD setting_3={16,16};
COORD setting_4={20,18};
