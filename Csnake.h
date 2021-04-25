#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>


#define u 72
#define d 80
#define l 75
#define r 77


#define ESI 201
#define ESD 187
#define EII 200
#define EID 188
#define BV 186
#define BH 205



using namespace std;



vector<COORD> snakeBody;
string snakeSegment = "  ";
string foodSegment = "  ";
int snakeColor = 168;//168 by default
int backgroundColor = 14;
int foodColor = 70;
int borderColor = 2;
COORD foodCoord;
int width = 100;
int height = 40;
int _width = 10;
int _height = 1;
char prevDirection;
bool UP = false;
bool DOWN = false;
bool LEFT = false;
bool RIGHT = false;


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


void showInfo(string info){
	gotoxy(0,0);
	cout<<"                                                        ";
	gotoxy(0,0);
	cout<<info;
	
}
void showInfo(char info){
	gotoxy(0,0);
	cout<<"                                                        ";
	gotoxy(0,0);
	cout<<info;
	
}
void showInfo(int info){
	gotoxy(0,0);
	cout<<"                                                        ";
	gotoxy(0,0);
	cout<<info;
	
}
void showInfo(float info){
	gotoxy(0,0);
	cout<<"                                                        ";
	gotoxy(0,0);
	cout<<info;
	
}
	
	
void moveSnake(char direction){
	ShowConsoleCursor(false);
	
	COORD AUX = snakeBody[0];
	COORD AUX2;
	
	switch(direction){
	case u:
		
		if(prevDirection != d){
			snakeBody[0].Y--;
			prevDirection = u;
		}else{
			snakeBody[0].Y++;
		}
		
		break;
	case d:
		
		if(prevDirection != u){
			snakeBody[0].Y++;
			prevDirection = d;
		}
		else{
			snakeBody[0].Y--;
		}
		break;
	case l:
		if(prevDirection != r){
			snakeBody[0].X-=2;
			prevDirection = l;
		}
		else{
			snakeBody[0].X+=2;
		}
		
		break;
	case r:
		if(prevDirection != l){
			snakeBody[0].X+=2;
			prevDirection = r;
		}
		else{
			snakeBody[0].X-=2;
		}
		
		break;
	default:
		break;
	}
	
	
	//draw head
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeColor);
	gotoxy(snakeBody[0]);
	cout<<snakeSegment;
	
	
	//move body coods
	for (int i = 1 ; i < (signed)snakeBody.size() ; i++){
		AUX2 = snakeBody[i];
		snakeBody[i] = AUX;
		gotoxy(snakeBody[i]);
		cout<<snakeSegment;
		
		AUX = AUX2;
	}
	
	//erase tail
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
	gotoxy(snakeBody.back());
	cout<<snakeSegment;
	
	
	
	
}//
	
	
bool checkColition(){
	
	if(snakeBody[0].Y <= _height || snakeBody[0].Y >= height || snakeBody[0].X <= _width || snakeBody[0].X >= width){
		return true;
	}
	
	for(int i = 3 ; i < (signed) snakeBody.size(); i++){
		
		if(snakeBody[0].X == snakeBody[i].X && snakeBody[0].Y == snakeBody[i].Y){
			return true;
		}
		
	}
	
	
	return false;
}
	
void drawMap(){
	
	for (int i = _height ; i <= height ; i++){
		for (int j = _width ; j <= width; j++){
			gotoxy(j,i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borderColor);
			if(i == _height ){
				
				if(j==_width ){
					cout<<(char)ESI;
				}
				else if(j==width){
					cout<<(char)ESD;
				}
				else{
					cout<<(char)BH;
				}
				
			}
			else if(i == height){
				if(j==_width ){
					cout<<(char)EII;
				}
				else if(j==width){
					cout<<(char)EID;
				}
				else{
					cout<<(char)BH;
				}
			}
			else{
				if(j== _width || j == width){
					cout<<(char)BV;
				}
			}
			
			
		}
		
		
	}
	
}
	
	
void grow(int newSegments){
	for(int i = 0 ; i< newSegments ; i++){
		snakeBody.push_back(snakeBody.back());
	}
}
void spawnFood(){
	
	foodCoord.X = rand()%width;
	foodCoord.Y = rand()%height;
	
	for(int i = 0 ; i < snakeBody.size(); i++){
		if(snakeBody[i].X == foodCoord.X && snakeBody[i].Y == foodCoord.Y){
			foodCoord.X = rand()%width;
			foodCoord.Y = rand()%height;
		}
	}
	
	
	
	if(foodCoord.X < _width){
		foodCoord.X = _width + 3;
	}
	if(foodCoord.Y < _height){
		foodCoord.Y = _height +3;
	}
	
	gotoxy(foodCoord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foodColor);
	cout<<foodSegment;
	
}
	
	
	
	
	
bool ateFood(){
	
	if((snakeBody[0].Y == foodCoord.Y && snakeBody[0].X == foodCoord.X) || (snakeBody[0].X == (foodCoord.X+1) &&  snakeBody[0].Y == foodCoord.Y ) || (snakeBody[0].X == (foodCoord.X-1) &&  snakeBody[0].Y == foodCoord.Y ) ){
		
		gotoxy(foodCoord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
		cout<<snakeSegment;
		
		return true;
	}
	
	
	
	return false;
}
			
			
			
			
			
			
			
				
