#include"main.h"
extern int LENGTH;
extern int MINES;


void initialization(char baseBoard[][MAXSIDE], char displayBoard[][MAXSIDE]) {
	
	
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			baseBoard[i][j] = '-';
			displayBoard[i][j] = '-';
		}
	}
}
void putMines(random mines[MAXMINES], char baseBoard[][MAXSIDE]) {
	srand(time(NULL));

	bool mark[MAXSIDE * MAXSIDE];

	// initialize all of marks is false, it means game not over:
	memset(mark, false, sizeof(mark));

	// random game:
	for (int i = 0; i < MINES; ) {
		int randoms = rand() % (LENGTH * LENGTH);
		int x = randoms / LENGTH;
		int y = randoms % LENGTH;

		//put mines
		if (mark[randoms] == false) {
			mines[i].x = x;
			mines[i].y = y;

			baseBoard[mines[i].x][mines[i].y] = '*';
			mark[randoms] = true;
			i++;
		}
	}

	return;
}

void outputConsole(char displayBoard[][MAXSIDE]) {

	cout << "  ";

	for (int i = 0; i < LENGTH; i++) {
		setColor(12);
		if (i < 10)
			cout << i << " ";
		else cout << i % 10 << " ";
	}

	cout << endl;

	for (int i = 0; i < LENGTH; i++) {
		setColor(12);
		if (i < 10)
			cout << i << " ";
		else cout << i % 10 << " ";
		setColor(7);
		for (int j = 0; j < LENGTH; j++) {
			cout << displayBoard[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

void putFlag(int x, int y, char displayBoard[][MAXSIDE]) {
	
	if (displayBoard[x][y] == 'P')
		displayBoard[x][y] = '-';
	else displayBoard[x][y] = 'P';
	return;
}

void moving(int& x, int& y) {
	cout << "Enter the cell you choose (row _ colum): ";
	cin >> x >> y;
	return;
}

bool checkMine(int x, int y, char baseBoard[][MAXSIDE]) {
	if (baseBoard[x][y] == '*')
		return true;
	else
		return false;
}

void replaceMine(int row, int col, char board[][MAXSIDE])
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{

			if (board[i][j] != '*')
			{
				board[i][j] = '*';
				board[row][col] = '-';
				return;
			}
		}
	}
	return;
}

bool checkExist(int row, int col)
{
	
	return (row >= 0) && (row < LENGTH) &&
		(col >= 0) && (col < LENGTH);
}

int countAdjacentMines(int row, int col, random mines[MAXMINES],
	char realBoard[][MAXSIDE])
{

	int count = 0;




	if (checkExist(row - 1, col) == true)
	{
		if (checkMine(row - 1, col, realBoard) == true)
			count++;
	}


	if (checkExist(row + 1, col) == true)
	{
		if (checkMine(row + 1, col, realBoard) == true)
			count++;
	}

	if (checkExist(row, col + 1) == true)
	{
		if (checkMine(row, col + 1, realBoard) == true)
			count++;
	}


	if (checkExist(row, col - 1) == true)
	{
		if (checkMine(row, col - 1, realBoard) == true)
			count++;
	}


	if (checkExist(row - 1, col + 1) == true)
	{
		if (checkMine(row - 1, col + 1, realBoard) == true)
			count++;
	}


	if (checkExist(row - 1, col - 1) == true)
	{
		if (checkMine(row - 1, col - 1, realBoard) == true)
			count++;
	}


	if (checkExist(row + 1, col + 1) == true)
	{
		if (checkMine(row + 1, col + 1, realBoard) == true)
			count++;
	}


	if (checkExist(row + 1, col - 1) == true)
	{
		if (checkMine(row + 1, col - 1, realBoard) == true)
			count++;
	}

	return (count);
}

void saveGame(char displayBoard[][MAXSIDE], char baseBoard[][MAXSIDE], random mines[MAXMINES], int remainTurn, clock_t t1) {
	ofstream outFile;
	
	outFile.open("Text.txt");
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			outFile << displayBoard[i][j] << ' ';
			
		}
		outFile << '\n';
	}

	

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			outFile << baseBoard[i][j] << ' ';
		}
		outFile << '\n';
	}

	

	for (int i = 0; i < MINES; i++) {
		outFile << mines[i].x << ' ' << mines[i].y << '\n';
	}

	outFile << remainTurn << ' ' << t1;
	outFile.close();
	return;
}


// open save game:
void openSaveGame(char displayBoard[][MAXSIDE], char baseBoard[][MAXSIDE], random mines[MAXMINES], int& remainTurn, clock_t& t1) {
	ifstream outFile;
	outFile.open("Text.txt");
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			outFile >> displayBoard[i][j];
		}
	}


	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			outFile >> baseBoard[i][j];
		}
	}


	for (int i = 0; i < MINES; i++) {
		outFile >> mines[i].x >> mines[i].y;
	}

	outFile >> remainTurn >> t1;
	outFile.close();
	return;
}
