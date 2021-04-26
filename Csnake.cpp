#include <iostream>
#include "Csnake.h"
#include "MakeMenu.h"

using namespace std;

int LEVEL = 0;
bool GAME_OVER = false; 

void playLevel(int);

int main(int argc, char *argv[]) {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd,SW_SHOWMAXIMIZED);
	
	MakeMenu mainMenu = MakeMenu(width, height, {"New Game", "Continue", "Credits", "Quit"});
	mainMenu.title = "Csnake";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
	int opc;

	
	while(1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
		opc = mainMenu.drawMenu();
		if(opc == 1){
			LEVEL = 1;
			playLevel(90);
			
		}else if(opc == 2){
			playLevel(LEVEL);
			
		}else if (opc ==3){
			
			int timer = 5000;
			while(timer > 0){
				gotoxy(((_width + width)/2)-4 , (_height + height)/2);
				cout<<"Created by Francisco Rodriguez";
				gotoxy(((_width + width)/2)-4 , (_height + height +2)/2);
				cout<<"Practicas c++";
				gotoxy(((_width + width)/2)-4 , (_height + height +4)/2);
				cout<<"2021";
				
				timer --;
				
				if(kbhit()){
					int key = getch();
					if(key == 81){
						LEVEL_CHANGER = true;
						cout<<"Level Changer";
						break;
					}
					if(key == 27){
						break;	
					}
					
				}
				
				Sleep(1);
			}
			
			
			
		}else if(opc == 4){
			
			break;
			
		}
		
	
		
	}//main bucle
	
	
	gotoxy(width+5, height+5);
	
	
	return 0;
}



void playLevel(int level){
	GAME_OVER = false;
	bool hadGame = false;
	switch(level){
		case 0:
			gotoxy(((_width + width)/2)-4 , (_height + height)/2);
			cout<<"Yo have to start a game first";
			GAME_OVER = true;
			
			Sleep(2000);
		break;
		
		case 1:
			hadGame = true;
			if (makeLevel(1, 168, 70, 2, 14, 10000, 0, {50,20})){
				LEVEL = 2;
			}
			else{
				GAME_OVER = true;
			}
		break;
		case 2:
			hadGame = true;
			if (makeLevel(2, 190, 90, 9, 14, 15000, 1, {50,10})){
				LEVEL = 3;
			}
			else{
				GAME_OVER = true;
			}
		break;
		case 3:
			hadGame = true;
			if (makeLevel(3, 114, 70, 7, 14, 16000, 2, {50,10})){
				LEVEL = 4;
			}
			else{
				GAME_OVER = true;
			}
			
			
		break;
		case 4:
			hadGame = true;
			if (makeLevel(4, 100, 200, 14, 14, 17000, 3, {30,10})){
				LEVEL = 5;
			}
			else{
				GAME_OVER = true;
			}
		break;
		case 5:
			hadGame = true;
			if (makeLevel(5, 200, 100, 4, 4, 17500, 4, {30,10})){
				LEVEL = 6;
			}
			else{
				GAME_OVER = true;
			}
			break;
		case 6:
			hadGame = true;
			if (makeLevel(6, 10, 168, 112, 112, 18000, 5, {30,10})){
			LEVEL = 1;
			}
			else{
				GAME_OVER = true;
			}
			break;
	
		default:{
			
		};
		
	}//
	
	if(!GAME_OVER){
		playLevel(LEVEL);
	}
	else if(hadGame){
		int timer = 3000;
		while(timer > 0){
			gotoxy(((_width + width)/2)-4 , (_height + height)/2);
			cout<<"GAME OVER";
			timer --;
			
			if(kbhit()){
				int key = getch();
				if(key == 27){
					break;	
				}
			}
			
			Sleep(1);
		}
	}
}


