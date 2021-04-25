#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cwchar>
#include "Csnake.h"


using namespace std;


int main(int argc, char *argv[]) {
	system("cls");
	snakeBody.push_back({50,20});
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd,SW_SHOWMAXIMIZED);
	char direction = r;
	char auxDirection = direction;
	int speed = 90;
	int initialSize = 4;
	int scoreLostPerloop = 1;
	int score ;
	int foodTimer = 500;
	int eatenFood = 0;
	snakeBody.resize(initialSize,{0,0});
	drawMap();
	spawnFood();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
	gotoxy(_width +5 , _height-1);
	cout<<"Csnake   Level: 1   Eaten Food: "<<eatenFood;
	gotoxy(width -15 , _height-1);
	cout<<"Score: 0 ";
	
	while(direction != 27){
		if(scoreLostPerloop < 100){
			scoreLostPerloop++;
		}
		
		if(kbhit()){
			getch();//corrige un bug
			direction = getch();
		}
		
		if(direction == u || direction == d || direction == l ||direction == r){
			moveSnake(direction);
			auxDirection = direction;
		}
		else{
			moveSnake(auxDirection);
		}
		
		
		if(checkColition()){
			break;
		}
		
		
		if(ateFood()){
			eatenFood++;
			spawnFood();
			grow(2);
			speed--;
			score = ((snakeBody.size()-initialSize) * 100)-scoreLostPerloop;
			gotoxy(width-15 , _height-1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
			cout<<"Score: "<<score;
			gotoxy(_width +5 , _height-1);
			cout<<"Csnake   Level: 1   Eaten Food: "<<eatenFood;
			scoreLostPerloop = 1;
		}
		
		if(foodTimer == 0){
			foodTimer = 500;
			gotoxy(foodCoord);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
			cout<<snakeSegment;
			spawnFood();
		}
		foodTimer--;
		Sleep(speed);
	}
	

	
	gotoxy(((_width + width)/2)-4 , (_height + height)/2);
	cout<<"GAME OVER";
	Sleep(3000);
	
	gotoxy(width+5, height+5);
	
	
	return 0;
}



