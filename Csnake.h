#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>


using namespace std;


void gotoxy(int x, int y) 
{ 
	COORD coord;
	coord.X = x; 
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void gotoxy(COORD coord) 
{ 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}


