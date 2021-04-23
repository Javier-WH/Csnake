#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cwchar>
#include "Csnake.h"

#define u 72
#define d 80
#define l 75
#define r 77


using namespace std;
vector<COORD> snakeBody = {{50,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20},{20,20}};
string snakeSegment = "  ";
int snakeColor = 168;//168 by default
int backgroundColor = 14;


int width = 90;
int height = 40;


void moveSnake(char direction){
	ShowConsoleCursor(false);


	
	switch(direction){
		case u:
			snakeBody[0].Y--;
			break;
		case d:
			snakeBody[0].Y++;
			break;
		case l:
			snakeBody[0].X--;
			break;
		case r:
			snakeBody[0].X++;
			break;
		default:
			
			break;
	}
	
	/////////////////////////////
	
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeColor);
	//gotoxy(snakeBody[0]);
	//cout<<snakeSegment;
	
	for(int i = snakeBody.size(); i>0 ; i--){
		Sleep(1);
		
		if(snakeBody[i].X == snakeBody.back().X && snakeBody[i].Y == snakeBody.back().Y){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
			gotoxy(snakeBody[i]);
			cout<<snakeSegment;
			
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeColor);
		snakeBody[i] = snakeBody[i-1];
		gotoxy(snakeBody[i]);
		
		if(snakeBody[i].Y != snakeBody[i-1].Y){
			cout<<snakeSegment<<snakeSegment;
		}else{
			cout<<snakeSegment;
			
			
		}
		
	}
	
}//


	
	
int main(int argc, char *argv[]) {
	
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd,SW_SHOWMAXIMIZED);
	char direction = r;

	
	
	
	while(direction != 27){
	
		if(kbhit()){
			direction = getch();
		}
		moveSnake(direction);
		
		Sleep(50);
	}
	



	
	
	
	

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	return 0;
}



