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
int snakeTailColor = 14;
int backgroundColor = 14;
int foodColor = 70;
int borderColor = 2;
COORD foodCoord;
int width = 100;
int height = 40;
int _width = 1;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeTailColor);
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
	
	for(int i = 0 ; i < (signed) snakeBody.size(); i++){
		if(snakeBody[i].X == foodCoord.X && snakeBody[i].Y == foodCoord.Y){
			foodCoord.X = rand()%width;
			foodCoord.Y = rand()%height;
		}
	}
	
	
	
	if(foodCoord.X <= _width){
		foodCoord.X = _width + 3;
	}
	if(foodCoord.Y <= _height){
		foodCoord.Y = _height +3;
	}
	
	gotoxy(foodCoord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foodColor);
	cout<<foodSegment;
	
}
	
	
	
	
	
bool ateFood(){
	
	if((snakeBody[0].Y == foodCoord.Y && snakeBody[0].X == foodCoord.X) || (snakeBody[0].X == (foodCoord.X+1) &&  snakeBody[0].Y == foodCoord.Y ) || (snakeBody[0].X == (foodCoord.X-1) &&  snakeBody[0].Y == foodCoord.Y ) ){
		
		gotoxy(foodCoord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakeTailColor);
		cout<<snakeSegment;
		
		return true;
	}
	
	
	
	return false;
}
		
	void setMapColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		for (int i = _height ; i <= height ; i++){
			for (int j = _width ; j <= width; j++){
				gotoxy(j,i);
				cout<<" ";
			}
		}

	}
	
	
	
//////////////////////////////////////Levels///////////////////////////////////////////////////////////
	
	
	int level_1(){
		
		snakeColor = 168;//168 by default
		backgroundColor = 14;
		foodColor = 70;
		borderColor = 2;
		snakeTailColor = 14;
		
		
		
		
		system("cls");
		setMapColor(snakeTailColor);
		int levelScoreCap = 1000;
		char direction = r;
		char auxDirection = direction;
		int speed = 90;
		int initialSize = 4;
		int scoreLostPerloop = 1;
		int score ;
		int foodTimer = 500;
		int eatenFood = 0;
		snakeBody.resize(0);
		snakeBody.push_back({50,20});
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
				return 0;
			}
			
			
			if(ateFood()){
				foodTimer = 500;
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
				
				if (score >= levelScoreCap){
					return 1;
				}
				
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
		
		
		
		
		return 1;
	}

		
		
		int level_2(){
			
			
			snakeColor = 190;
			backgroundColor = 14;
			foodColor = 90;
			borderColor = 9;
			snakeTailColor = 14;
			
			system("cls");
			setMapColor(snakeTailColor);
			int levelScoreCap = 1000;
			char direction = r;
			char auxDirection = direction;
			int speed = 80;
			int initialSize = 4;
			int scoreLostPerloop = 1;
			int score ;
			int foodTimer = 500;
			int eatenFood = 0;
			snakeBody.resize(0);
			snakeBody.push_back({50,20});
			snakeBody.resize(initialSize,{0,0});
			drawMap();
			spawnFood();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
			gotoxy(_width +5 , _height-1);
			cout<<"Csnake   Level: 2   Eaten Food: "<<eatenFood;
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
					return 0;
				}
				
				
				if(ateFood()){
					foodTimer = 500;
					eatenFood++;
					spawnFood();
					grow(2);
					speed--;
					score = ((snakeBody.size()-initialSize) * 100)-scoreLostPerloop;
					gotoxy(width-15 , _height-1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
					cout<<"Score: "<<score;
					gotoxy(_width +5 , _height-1);
					cout<<"Csnake   Level: 2   Eaten Food: "<<eatenFood;
					scoreLostPerloop = 1;
					
					if (score >= levelScoreCap){
						return 1;
					}
					
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
			
			
			
			
			return 1;
		}
			
			
			
			
			
				
