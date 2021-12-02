#include "main.h"
int LENGTH(0); // The length of the board
int MINES(0); // number of mines on the board



void promptUserToChooseLevel() {
	system("cls");
	setColor(12);
	cout  << "\t\t\tWelcome to playing game Minesweeper\n\n";
	setColor(7);
	int level;
	cout  << "----------------------------NEMU-------------------------------------\n";
	cout << "|Enter the difficulty level you want to choose:                     |";
	cout << "\n|PRESS 0 if you want to choose BEGINNER 9*9 cells and 10 mines      |";
	cout << "\n|PRESS 1 if you want to choose INTERMEDIATE 16*16 cells and 40 mines|";
	cout << "\n|PRESS 2 if you want to choose HARD 24*24 cells and 99 mines        |\n";
	cout << "---------------------------------------------------------------------\n";
	cin >> level;
	if (level == BEGINNER)
	{
		LENGTH = 9;
		MINES = 10;
	}

	if (level == INTERMEDIATE)
	{
		LENGTH = 16;
		MINES = 40;
	}

	if (level == ADVANCED)
	{
		
		LENGTH = 24;
		MINES = 99;
	}

	return;
}

void playMinesweeper() {


	bool gameOver(false);
	clock_t t1, t2;
	t1 = clock();
	// create 2 dimension array
	char baseBoard[MAXSIDE][MAXSIDE], displayBoard[MAXSIDE][MAXSIDE];
	int remainTurn(LENGTH * LENGTH - MINES), x, y;

	random mines[MAXMINES];

	initialization(baseBoard, displayBoard);

	putMines(mines, baseBoard);

	// check whether it is the first time move or not
	bool firstMove = true;
	
	// open save game:
	system("cls");
	char put;
	cout << "Do you want to load your save game? (Y/N): ";
	cin >> put;
	if (put == 'y' || put == 'Y')
		openSaveGame(displayBoard, baseBoard, mines, remainTurn, t1);

	// Start to play game !!!
	while (!gameOver) {
	
		system("cls");
		// check the player want to put plag or move
		char put(0);
		outputConsole(displayBoard);
		cout << endl << "\t\t\tMENU";
		cout << endl << "If you want to put flag, press 'p'";
		cout << endl << "If you want to save game, press 's'";
		cout << endl << "If you want to move, press any key to continue.\n";
		cin >> put;
		cin.ignore(20, '\n');
		if (put == 'p') {
			moving(x, y);
			putFlag(x, y, displayBoard);
			continue;
		}
		else if (put == 's') {
			saveGame( displayBoard,  baseBoard,  mines,  remainTurn,  t1);
			exit(0);
		}
		moving(x, y);

		if (firstMove == true) {
			if (checkMine(x, y, baseBoard) )
				replaceMine(x, y, baseBoard);
		}

		firstMove = false;

		gameOver = continuePlayGame(displayBoard, baseBoard, mines, x, y, remainTurn, t1);

		if ((gameOver == false) && remainTurn == 0) {
			char yn;
			t2 = clock();
			cout << endl << '\t';
			setColor(12);
			cout << " YOU WON !!!";
			cout << "\nTime to complete: " << (((int)t2) - ((int)t1)) / 1000 << " sec\n";
			setColor(7);
			cin.ignore(20, '\n');
			cout << "\nPlay again (Y/N): ";
			
			cin >> yn;
			if (yn == 'Y' || yn == 'y') {
				promptUserToChooseLevel();
				playMinesweeper();
			}
			else exit(0);
		}
	}

	return;
}


//Recursion
bool continuePlayGame(char displayBoard[][MAXSIDE], char baseBoard[][MAXSIDE],
	random mines[MAXSIDE], int x, int y, int& turnRemain, clock_t t1)
{
	clock_t t2;
	// Base Case of Recursion
	if (displayBoard[x][y] != '-')
		return (false);

	int i;

	// if you open a mine, you lose
	if (baseBoard[x][y] == '*')
	{
		char yn;
		displayBoard[x][y] = '*';
		system("cls");
		for (i = 0; i < MINES; i++)
		{


			if (displayBoard[mines[i].x][mines[i].y ] == 'P'
				&& baseBoard[mines[i].x][mines[i].y] == '*')
				continue;
			displayBoard[mines[i].x][mines[i].y] = '*';
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (displayBoard[i][j] == 'P'
					&& baseBoard[i][j] != '*')
					displayBoard[i][j] = 'X';
			}
		}
		outputConsole(displayBoard);
		cout << '\n';
		t2 = clock();
		cout << "\nTime to complete: " << (((int)t2) - ((int)t1)) / 1000 <<" sec\n" ;
		setColor(12);
		cout  << "\tYOU LOSE !!!";

		setColor(7);
		cin.ignore(20, '\n');
		cout << "\nPlay again (Y/N): ";
		
		cin >> yn;
		if (yn == 'Y' || yn == 'y') {
			promptUserToChooseLevel();
			playMinesweeper();
		}
		else exit(0);
		return (true);
	}

	else
	{

		int count = countAdjacentMines(x, y, mines, baseBoard);
		(turnRemain)--;

		displayBoard[x][y] = count + '0';
		baseBoard[x][y] = displayBoard[x][y];

		if (!count)
		{
			


			if (checkExist(x - 1, y) == true)
			{
				if (checkMine(x - 1, y, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x - 1, y, turnRemain, t1);
			}


			if (checkExist(x + 1, y) == true)
			{
				if (checkMine(x + 1, y, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x + 1, y, turnRemain, t1);
			}


			if (checkExist(x, y + 1) == true)
			{
				if (checkMine(x, y + 1, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x, y + 1, turnRemain, t1);
			}


			if (checkExist(x, y - 1) == true)
			{
				if (checkMine(x, y - 1, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x, y - 1, turnRemain, t1);
			}


			if (checkExist(x - 1, y + 1) == true)
			{
				if (checkMine(x - 1, y + 1, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x - 1, y + 1, turnRemain, t1);
			}

			if (checkExist(x - 1, y - 1) == true)
			{
				if (checkMine(x - 1, y - 1, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x - 1, y - 1, turnRemain, t1);
			}


			if (checkExist(x + 1, y + 1) == true)
			{
				if (checkMine(x + 1, y + 1, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x + 1, y + 1, turnRemain, t1);
			}


			if (checkExist(x + 1, y - 1) == true)
			{
				if (checkMine(x + 1, y - 1, baseBoard) == false)
					continuePlayGame(displayBoard, baseBoard, mines, x + 1, y - 1, turnRemain, t1);
			}
		}

		return (false);
	}
}