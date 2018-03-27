#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <cmath>
using namespace std;

int GetCommand()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		cout<<"left"<<endl;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	cout<<"right"<<endl;
	if (GetAsyncKeyState(VK_UP) & 0x8000)		cout<<"up"<<endl;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)		cout<<"down"<<endl;

}


int main()
{
    cout<<pow(8,2)<<endl;

}
