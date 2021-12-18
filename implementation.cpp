#include"main.h"
extern int LENGTH;
extern int MINES;
extern int LEVEL;

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
			if (displayBoard[i][j] <= '9' && displayBoard[i][j] >= '1') {
				setColor(3);
				cout << displayBoard[i][j] << " ";
				setColor(7);
			}
			else if (displayBoard[i][j] == 'P') {
				setColor(5);
				cout << displayBoard[i][j] << " ";
				setColor(7);
			}
			else cout << displayBoard[i][j] << " ";
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

/*
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
*/

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
	if ( LEVEL == BEGINNER)
		outFile.open("savegameBEGINNER.txt");
	else if (LEVEL == INTERMEDIATE)
		outFile.open("savegameINTERMEDIATE.txt");
	else if (LEVEL == ADVANCED)
		outFile.open("savegameADVANCED.txt");
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
	if (LEVEL == BEGINNER)
		outFile.open("savegameBEGINNER.txt");
	else if (LEVEL == INTERMEDIATE)
		outFile.open("savegameINTERMEDIATE.txt");
	else if (LEVEL == ADVANCED)
		outFile.open("savegameADVANCED.txt");
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

bool isempty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

void initialscore() {
	typedef struct {
		double time;
		char name[100];
	}  player_n;
	player_n p[5] = {
			{99999,"Non-player"},
			{99999,"Non-player"},
			{99999,"Non-player"},
			{99999,"Non-player"},
			{99999,"Non-player"} };
	ofstream file;
	if (LEVEL == BEGINNER)
		file.open("scorebeginnner.txt");
	else if (LEVEL == INTERMEDIATE)
		file.open("scoreintermediate.txt");
	else if (LEVEL == ADVANCED)
		file.open("scoreadvanced.txt");
	if (!file) {
		cout << "Error: file not opened." << endl;
		return;
	}
	for (short i = 0; i < 5; i++) {
		file << p[i].time << setw(25) << p[i].name << endl;
	}
	file.close();
	return;
}

void highscore(string name, double time) {
	ifstream ifs;
	if (LEVEL == BEGINNER) {
		ifs.open("scorebeginnner.txt");
	}
	else if (LEVEL == INTERMEDIATE) {
		ifs.open("scoreintermediate.txt");
	}
	else if (LEVEL == ADVANCED) {
		ifs.open("scoreadvanced.txt");
	}

	//If file is empty, initialize the file
	if (isempty(ifs)) {
		ifs.close();
		initialscore();
	}
	ifs.close();


	//Save score to file
	ofstream ofs;
	if (LEVEL == BEGINNER) {
		ofs.open("scorebeginnner.txt", ios::app);
	}
	else if (LEVEL == INTERMEDIATE) {
		ofs.open("scoreintermediate.txt", ios::app);
	}
	else if (LEVEL == ADVANCED) {
		ofs.open("scoreadvanced.txt", ios::app);
	}
	ofs << time << setw(23) << name << endl;
	ofs.close();


	//Sort the score
	ifstream ifs1;
	if (LEVEL == BEGINNER) {
		ifs1.open("scorebeginnner.txt");
	}
	else if (LEVEL == INTERMEDIATE) {
		ifs1.open("scoreintermediate.txt");
	}
	else if (LEVEL == ADVANCED) {
		ifs1.open("scoreadvanced.txt");
	}
	int i = 0;
	string k[10];
	while (!ifs1.eof()) {
		char temp[255];
		ifs1.getline(temp, 100);
		k[i++] = temp;
	}
	for (int j = 0; j <= 5; j++) {
		for (int m = j + 1; m <= 5; m++) {
			int q = stoi(k[j]);
			int w = stoi(k[m]);
			if (q > w) k[j].swap(k[m]);
		}
	}
	ifs1.close();

	// Save score to file after sorting
	ofstream ofs1;
	if (LEVEL == BEGINNER) {
		ofs1.open("scorebeginnner.txt");
	}
	else if (LEVEL == INTERMEDIATE) {
		ofs1.open("scoreintermediate.txt");
	}
	else if (LEVEL == ADVANCED) {
		ofs1.open("scoreadvanced.txt");
	}
	for (int i = 0; i < 5; i++) {
		ofs1 << k[i] << "\n";
	}
	ofs1.close();
	return;
}
void showScoreBoard() {
	system("cls");
	ifstream ifs;
	if (LEVEL == BEGINNER) {
		ifs.open("scorebeginnner.txt");
	}
	else if (LEVEL == INTERMEDIATE) {
		ifs.open("scoreintermediate.txt");
	}
	else if (LEVEL == ADVANCED) {
		ifs.open("scoreadvanced.txt");
	}

	//If file is empty, initialize the file
	if (isempty(ifs)) {
		ifs.close();
		initialscore();
	}
	ifs.close();
	char input[100];
	ifstream file;
	if (LEVEL == BEGINNER)
		file.open("scorebeginnner.txt");
	else if (LEVEL == INTERMEDIATE)
		file.open("scoreintermediate.txt");
	else if (LEVEL == ADVANCED)
		file.open("scoreadvanced.txt");
	setColor(12);
	cout << "\t\t\t-------SCORE BOARD-------\n";
	cout << "\t\t\tTime" << setw(20) << "Name" << endl;
	setColor(7);
	while (!file.eof()) {
		file.getline(input, 100);
		cout << "\t\t\t" << input << endl;
	}
	file.close();
	system("pause");
	promptUserToChooseLevel();
	playMinesweeper();
	return;
}
