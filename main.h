// pre-processor: 
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<cstdlib>
#include<math.h>
#include<cstring>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include"console.h"
using namespace std;

//level of the game:
#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2

// size of game
#define MAXSIDE 25
#define MAXMINES 99
#define MAXMOVE 526 // = 25*25 - 99

// create mines:
struct random {
	int x;
	int y;
};

// A Function uses to choose the difficulty of the game.
void promptUserToChooseLevel();

// A function to begin this game
void playMinesweeper();

// Initial the game:
void initialization(char displayBoard[][MAXSIDE], char baseBoard[][MAXSIDE]);

// place mines randomly
void putMines(random mines[MAXMINES], char baseBoard[][MAXSIDE]);

// display current game:
void outputConsole(char displayBoard[][MAXSIDE]);

// get the user's move;
void moving(int& x, int& y);

//put flag:
void putFlag(int x, int y, char displayBoard[][MAXSIDE]);

//check mines:
bool checkMine(int x, int y, char baseBoard[][MAXSIDE]);

// replace mines:
void replaceMine(int x, int y, char baseBoard[][MAXSIDE]);


// play game until meet boom or open all of the boom
bool continuePlayGame(char displayBoard[][MAXSIDE], char baseBoard[][MAXSIDE], random mines[MAXMINES], int x, int y, int& remainTurn, clock_t t1);

// recursion to count adjacent mines:
int countAdjacentMines(int row, int col, random mines[MAXMINES],
	char baseBoard[][MAXSIDE]);

bool checkExist(int row, int col);

// save file:
void saveGame(char displayBoard[][MAXSIDE], char baseBoard[][MAXSIDE], random mines[MAXMINES], int& remainTurn, clock_t& t1);