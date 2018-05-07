#include <vector>
#include <algorithm>
#include <cmath>
#include "war.cpp"
using namespace std;

class plan
{
public:
	int digit_opp; //digit before
	int digit;
	int result; //digit after
	char mark;
};

class K_plan
{
private:
	vector<plan> kill_plan; //stack:head in head out
	plan first[4]; //tail in head out
	plan second[16];
	plan third[64];
	plan fourth[256];

	int go_all;
	int go_atk;
	int go_def;
	int go_ran;

	player *me;

	bool plan_run();
	void go_attack();
	void go_defence();
	void random();
public:
	player *enemy;

	K_plan(player &m,player &e);
	void set_diff(int diff);
	void set_diff(int a,int d,int r);
	void plan_init();
	void auto_run();
};

K_plan kp_blue(blue,red),kp_red(red,blue);
