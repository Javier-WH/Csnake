#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cwchar>
#include "Csnake.h"
#include "MakeMenu.h"

using namespace std;

int LEVEL = 0;
bool GAME_OVER = false; 

void playLevel(int);

int main(int argc, char *argv[]) {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd,SW_SHOWMAXIMIZED);
	
	MakeMenu mainMenu = MakeMenu(width, height, {"Nuevo Juego", "Continuar", "Salir"});
	mainMenu.title = "Csnake";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
	int opc;

	
	while(1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor);
		opc = mainMenu.drawMenu();
		if(opc == 1){
			LEVEL = 1;
			playLevel(1);
			
		}else if(opc == 2){
			playLevel(LEVEL);
			
		}else if(opc == 3){
			
			gotoxy(((_width + width)/2)-4 , (_height + height)/2);
			cout<<"Hasta luego...";
			Sleep(3000);
			break;
			
		}
		
	
		
	}//main bucle
	
	
	gotoxy(width+5, height+5);
	
	
	return 0;
}



void playLevel(int level){
	GAME_OVER = false;
	switch(level){
		case 0:
			gotoxy(((_width + width)/2)-4 , (_height + height)/2);
			cout<<"Debes iniciar una partida primero";
			GAME_OVER = true;
			Sleep(2000);
		break;
		
		case 1:
			if (level_1()){
				LEVEL = 2;
			}
			else{
				GAME_OVER = true;
			}
		break;
		case 2:
			if (level_2()){
				LEVEL = 3;
			}
			else{
				GAME_OVER = true;
			}
		break;
		case 3:
			gotoxy(((_width + width)/2)-4 , (_height + height)/2);
			cout<<"Level 3, comming soon";
			GAME_OVER = true;
			Sleep(3000);
		break;
		
	}//
	
	if(!GAME_OVER){
		playLevel(LEVEL);
	}
	else{
		gotoxy(((_width + width)/2)-4 , (_height + height)/2);
		cout<<"GAME OVER";
		GAME_OVER = true;
		Sleep(3000);
	}
	
}


