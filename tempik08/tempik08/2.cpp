////////////////////////////////////////
//***Furyaev Stanislav***             //
//***Moscow, 2013.***                 //
//E-mail:furyaev.stanislav@gmail.com  //
////////////////////////////////////////
 
#include <iostream>
#include <conio.h>
#include <winbase.h>
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include "GraphicMy.h"
 
using namespace std;
 
      char KeyMain; 
       int lev = 1;
      char KEY2;
     const COORD posSt = {0, 0};
     COORD pos2 = {0, 20};
    HANDLE htd = GetStdHandle(STD_OUTPUT_HANDLE); 
 
void KeyF(void* pParams){               //Создаёт ещё один поток, отвечающий за считывание клавиш с клавиатуры
    while(true){
        KeyMain = _getch();
    }
}
 
 
 
void jump(){
    for(int i=1; i<7; i++){
                _beginthread(KeyF, 0, NULL);      //Запускает тот самый поток ^
                SetConsoleTextAttribute(htd, 0);
                pos2.Y--;
                SetConsoleCursorPosition(htd, pos2);
                SetConsoleTextAttribute(htd, BACKGROUND_RED | BACKGROUND_INTENSITY);
                std::cout << " ";
                pos2.Y++;
                SetConsoleCursorPosition(htd, pos2);
                SetConsoleTextAttribute(htd, 0);
                std::cout << " ";
                pos2.Y--;
                Sleep(50);
                switch((int)KeyMain){
                case 75: {
                if(pos2.X == 0)
                    break;
                else{
                 SetConsoleCursorPosition(htd, pos2);
                 std::cout << " ";
                 pos2.X--;
                 break;
                }
                }
                case 77: {
                if(pos2.X == 79){ 
                    SetConsoleCursorPosition(htd, pos2);
                    std::cout << " ";
                    pos2.X = 0;
                    lev++;
                    break;
                }
                else{
                    SetConsoleCursorPosition(htd, pos2);
                    std::cout << " ";
                    pos2.X++;
                    break;
                }
                }
                }
            }
            for(int i2=1; i2<7; i2++){
                _beginthread(KeyF, 0, NULL);
                SetConsoleTextAttribute(htd, 0);
                pos2.Y++;
                SetConsoleCursorPosition(htd, pos2);
                SetConsoleTextAttribute(htd, BACKGROUND_RED | BACKGROUND_INTENSITY);
                std::cout << " ";
                pos2.Y--;
                SetConsoleCursorPosition(htd, pos2);
                SetConsoleTextAttribute(htd, 0);
                std::cout << " ";
                pos2.Y++;
                Sleep(50);
                switch((int)KeyMain){
                case 75: {
                if(pos2.X == 0)
                    break;
                else {
                 SetConsoleCursorPosition(htd, pos2);
                 std::cout << " ";
                 pos2.X--;
                 break;
                 }
                }
                case 77: {
                if(pos2.X == 79){ 
                    SetConsoleCursorPosition(htd, pos2);
                    std::cout << " ";
                    pos2.X = 0;
                    lev++;
                    break;
                }
                else{
                    SetConsoleCursorPosition(htd, pos2);
                    std::cout << " ";
                    pos2.X++;
                    break;
                }
                }
                }
            }
            KeyMain = ' ';
}
 
void GAME(){
 
    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible=false;
    CCI.dwSize=1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CCI);
 
    SetConsoleTextAttribute(htd, 0);
    system("cls");
    _beginthread(KeyF, 0, NULL);
    DrawLine('G', 80, 0, 21);
    
    while(true){
        KeyMain = ' ';
        SetConsoleTextAttribute(htd, 0);
        cout << " ";
        SetConsoleCursorPosition(htd, posSt);
        SetConsoleTextAttribute(htd, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY | 0);
        cout << "Level: " << lev;
        SetConsoleTextAttribute(htd, 0);
        SetConsoleCursorPosition(htd, pos2);
        SetConsoleTextAttribute(htd, BACKGROUND_RED | BACKGROUND_INTENSITY);
        cout << " ";
        
        SetConsoleTextAttribute(htd, 0);
        switch((int)KeyMain){
        case 75: {
            _beginthread(KeyF, 0, NULL);
            if(pos2.X == 0)
                break;
             else{
                 SetConsoleCursorPosition(htd, pos2);
                 cout << " ";
                 pos2.X--;
                 break;
            }
                 }
        case 72: jump();
        case 77: {
            _beginthread(KeyF, 0, NULL);
            if(pos2.X == 79){ 
                SetConsoleCursorPosition(htd, pos2);
                cout << " ";
                pos2.X = 0;
                lev++;
                break;
            }
            else{
                SetConsoleCursorPosition(htd, pos2);
                cout << " ";
                pos2.X++;
                break;
            }
            }
        case  27: break;
        case 113: break;
        }
    }
    
}