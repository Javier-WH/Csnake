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

bool LEVEL_CHANGER = false;

vector<COORD> obstacle;
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
	
	for(int i = 4 ; i < (signed) snakeBody.size(); i++){
		
		if(snakeBody[0].X == snakeBody[i].X && snakeBody[0].Y == snakeBody[i].Y){
			return true;
		}
		
	}
	
	for(int i = 0 ; i < (signed) obstacle.size(); i++){
		if(snakeBody[0].X == obstacle[i].X && snakeBody[0].Y == obstacle[i].Y){
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
		if((snakeBody[i].X == foodCoord.X || snakeBody[i].X+1 == foodCoord.X) && snakeBody[i].Y == foodCoord.Y){
			foodCoord.X = rand()%width;
			foodCoord.Y = rand()%height;
		}
	}
	
	for(int i = 0 ; i < (signed) obstacle.size(); i++){
		if(obstacle[i].X == foodCoord.X && obstacle[i].Y == foodCoord.Y){
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
	
	
	void putObstacle(int type){
		obstacle.resize(0);
		
		if(type == 1){
			int obsSize = width/3;
			obstacle.resize(obsSize);
			short Xpos = 33;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borderColor);
			
			for (int i = 0 ; i < (signed) obstacle.size() ; i++){
				obstacle[i] = {Xpos++, 20};
				gotoxy(obstacle[i]);
				cout<<(char)BH;
			}
		}
		
		else if(type == 2){
			int obsSize = 20;
			obstacle.resize(obsSize);
			short Ypos = 10;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borderColor);
			
			for (int i = 0 ; i < (signed) obstacle.size() ; i++){
				obstacle[i] = {50, Ypos++};
				gotoxy(obstacle[i]);
				cout<<(char)BV;

			}
		}
		
		else if(type == 3){
			int obsSize = 100;
			obstacle.resize(obsSize);
			short Ypos = 11;
			short Xpos = 25;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borderColor);
			
			for (int i = 0 ; i < 20 ; i++){
				obstacle[i] = {50, Ypos++};
				gotoxy(obstacle[i]);
				cout<<(char)BV;
				
			}
			
			for (int i = 21 ; i < 71 ; i++){
				obstacle[i] = {Xpos++, 20};
				gotoxy(obstacle[i]);
				cout<<(char)BH;
			}
			
			gotoxy(50, 20);
			cout<<(char)206;
		}
		
	
		else if(type == 4){
			int obsSize = 100;
			obstacle.resize(obsSize);
			short Ypos = 20;
			short Xpos1 = 1;
			short Xpos2 = 100;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borderColor);
			
			for (int i = 0 ; i < 40 ; i++){
				obstacle[i] = {Xpos1++, Ypos};
				gotoxy(obstacle[i]);
				cout<<(char)BH;
				
			}
			
			for (int i = 80 ; i > 40 ; i--){
				obstacle[i] = {Xpos2--, Ypos};
				gotoxy(obstacle[i]);
				cout<<(char)BH;
				
			}
			
			
			gotoxy(1, 20);
			cout<<(char)204;
			gotoxy(100, 20);
			cout<<(char)185;
		}
		
		else if(type == 5){
			int obsSize = 111;
			obstacle.resize(obsSize);
			short Ypos = 1;
			short Ypos2 = 40;
			short Xpos1 = 1;
			short Xpos2 = 100;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), borderColor);
			
			for (int i = 0 ; i < 40 ; i++){
				obstacle[i] = {Xpos1++, 20};
				gotoxy(obstacle[i]);
				cout<<(char)BH;
				
			}
			
			for (int i = 80 ; i > 40 ; i--){
				obstacle[i] = {Xpos2--, 20};
				gotoxy(obstacle[i]);
				cout<<(char)BH;
				
			}
			
			for (int i = 81 ; i < 95 ; i++){
				obstacle[i] = {50, Ypos++};
				gotoxy(obstacle[i]);
				cout<<(char)BV;
				
			}
			
			for (int i = 110 ; i > 96 ; i--){
				obstacle[i] = {50, Ypos2--};
				gotoxy(obstacle[i]);
				cout<<(char)BV;
				
			}
			
			
			
			gotoxy(1, 20);
			cout<<(char)204;
			gotoxy(100, 20);
			cout<<(char)185;
			gotoxy(50,1);
			cout<<(char)203;
			gotoxy(50,40);
			cout<<(char)202;
			
			
		}
		
		
		
		
	}
	
	
	
//////////////////////////////////////Levels///////////////////////////////////////////////////////////
	

	
	int makeLevel(int nLevel, int _snakeColor, int _foodColor, int _borderColor, int _snakeTailColor, int _scoreCap, int obstacleType, COORD startPosition){
		
		
		
		
		snakeColor = _snakeColor;
		backgroundColor = 14;
		foodColor = _foodColor;
		borderColor = _borderColor;
		snakeTailColor = _snakeTailColor;
		

		
		system("cls");
		
		setMapColor(snakeTailColor);
		int levelScoreCap = _scoreCap;
		char direction = r;
		char auxDirection = direction;
		int speed = 100;
		int initialSize = 4;
		int scoreLostPerloop = 1;
		int score ;
		int foodTimer = 500;
		int eatenFood = 0;
		snakeBody.resize(0);
		snakeBody.push_back(startPosition);
		snakeBody.resize(initialSize,{0,0});
		drawMap();
		spawnFood();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
		gotoxy(_width +5 , _height-1);
		cout<<"Csnake   Level: "<<nLevel<<"   Eaten Food: "<<eatenFood;
		gotoxy(width -15 , _height-1);
		cout<<"Score: 0 ";
		
		putObstacle(obstacleType);
		
		while(true){
			if(scoreLostPerloop < 100){
				scoreLostPerloop++;
			}
			
			if(kbhit()){
				if(getch() == 224){
					direction = getch();
				}
			}
			
			if(direction == u || direction == d || direction == l ||direction == r){
				moveSnake(direction);
				auxDirection = direction;
			}
			else{
				moveSnake(auxDirection);
				if(direction == 81 && LEVEL_CHANGER){
					break;
				}
			}
			
			
			if(checkColition()){
				return 0;
			}
			
			
			if(ateFood()){
				foodTimer = 500;
				eatenFood++;
				spawnFood();
				grow(2);
				if(speed >50){
					speed--;	
				}
				score = ((snakeBody.size()-initialSize) * 100)-scoreLostPerloop;
				gotoxy(width-15 , _height-1);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
				cout<<"Score: "<<score;
				gotoxy(_width +5 , _height-1);
				cout<<"Csnake   Level: "<<nLevel<<"   Eaten Food: "<<eatenFood;
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

