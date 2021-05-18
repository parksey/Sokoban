#pragma once


#include <stdio.h>
#include <conio.h>


#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define MAXSTAGE 2

#define SIZEX 8
#define SIZEY 9
#define INDEXY 0
#define INDEXX 1
#define RESULT 9

#define DEBUGX 50
#define DEBUGY 1

typedef enum { false, true } bool;

/******************************/

char MainMenu();
int* LoadMap(int);
void GameLoop();
bool GameStart(int);
bool StageDone(char [][SIZEX]);
void MovePlayer(char, char[][SIZEX], int*);
void resetpoint(char [][SIZEX]);
void Setting(char);
void SettingMenu();
void GameOver();
void SettingView();