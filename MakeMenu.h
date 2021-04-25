#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>


#define ESI 201
#define ESD 187
#define EII 200
#define EID 188
#define BV 186
#define BH 205
#define ENTER 13
#define ESCAPE 27
#define UP 72
#define DOWN 80
#define UP 72
#define DOWN 80
#define ENTER 13

using namespace std;

int drawMenu();
void ShowConsoleCursor(bool);
void gotoxy(int,int);

using namespace std;

struct MakeMenu {
	int width;
	int height;
	vector<string>options;
	string title;
	bool index;
	char arrow[2];
	
	MakeMenu(int _width, int _height, vector<string>_options){
		width = _width;
		height = _height;
		options = _options;
		title = "";
		index = false;
		strcpy(arrow,"->");
		
	}
		void setArrow(string newArrow){
			if(newArrow.length() <=2){
				strcpy(arrow,newArrow.c_str());
			}
		}
		void setArrow(int arr1, int arr2){
			arrow[0] = arr1;
			arrow[1] = arr2;
		}
		void setArrow(int arr1){
			arrow[0] = ' ';
			arrow[1] = arr1;
		}
			
		int drawMenu(){
			int OPC = 1;
			system("cls");
			HWND hWnd = GetConsoleWindow();
			ShowWindow(hWnd,SW_SHOWMAXIMIZED);
			ShowConsoleCursor(false);
			
			for(int i = 1 ;  i <= height ; i++){
				for (int j = 1 ; j<= width ; j++){
					gotoxy(j,i);
					if(i == 1){
						if(j==1){
							cout<<(char)ESI;
						}
						else if(j == width){
							cout<<(char)ESD;
						}
						else{
							cout<<(char)BH;
						}
					}
					else if(i == height){
						if(j==1){
							cout<<(char)EII;
						}
						else if(j == width){
							cout<<(char)EID;
						}
						else{
							cout<<(char)BH;
						}
					}
					else{
						if(j==1 || j==width){
							cout<<(char)BV;
						}
					}
				}
			}
			///////////////////////////////////////
			
			if(title.length() != 0){
				gotoxy((width-title.length())/2, 1);
				cout<<" "<<title<<" ";
				
			}
			
			int initialArrowPostY = (height/2)-(options.size()/2);
			int initialArrowPostX = (width/2)-(options[0].length()/2)-3;
			int arrowMaxReach = options.size()-1;
			
			for(int i = 0; i< (signed)options.size() ; i++){//pint all option 
				gotoxy((width/2)-(options[0].length()/2), (height/2)-(options.size()/2)+i);
				if (index){
					
					cout<<i+1<<" - "<<options[i]<<endl;
				}else{
					cout<<options[i]<<endl;
				}
			}
			
			
			int input;
			int ArrowPostY = initialArrowPostY;
			int ArrowPostX = initialArrowPostX;
			while(true){
				gotoxy(ArrowPostX, ArrowPostY);
				cout<<arrow;
				
				input = getch();
				
				for(int i = 0 ; i < (signed)options.size() ; i++){
					gotoxy(ArrowPostX, initialArrowPostY +i);
					cout<<"  ";
				}
				
				switch(input){
					
				case UP:
					if(ArrowPostY == initialArrowPostY){
						ArrowPostY += arrowMaxReach;
						OPC = options.size();
					}
					else{
						ArrowPostY--;
						OPC--;
					}
					break;
				case DOWN:
					if(ArrowPostY == initialArrowPostY+arrowMaxReach){
						ArrowPostY = initialArrowPostY;
						OPC = 1;
					}
					else{
						ArrowPostY++;
						OPC++;
					}
					break;
				case ENTER:
					system("cls");
					return OPC;
				}
			}
			return 0;
		}
};




