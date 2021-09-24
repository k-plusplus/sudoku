#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function Prototypes
bool sudoku(int board[][9], int r, int c, int num);
bool inSector(int board[][9], int r, int c, int n);
bool inRow(int board[][9], int r, int n);
bool inColumn(int board[][9], int c, int n);
void printBoard(int board[][9]);

int main() {

	// Variable initialization
	int board[9][9];
	bool done = false;
	int n = 1;

	// Initialize board to empty
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			board[i][j] = 0;
		}
	}

	// Prompt user to open puzzle file
	ifstream inFile;
	string fileName = "";

	// Main program loop - will continuosly ask user for file until
	// they input "NO"
	while (!done) {

		do {
			cout << "Enter initial sudoku board file: ";
			cin >> fileName;
			if (fileName == "NO") {
				cout << "So Desu Ne" << endl;
				done = true;
				return 0;
			}
			inFile.open(fileName.c_str());
		} while (!inFile.is_open());

		// Read in values from file to board
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				inFile >> board[i][j];
			}
		}

		cout << "Initial board read in " << endl;
		inFile.close();

		printBoard(board);

		if (sudoku(board, 0, 0, 1)) {
			cout << "Sudoku puzzle solved" << endl;
			// Print out Soduku board
			printBoard(board);
			cout << endl;
		}//end if
	}//end while
}//end main

// ---------------------------------------------------------------------
// Function definitions

/* sudoku(): brute force recursive backtracking method to solve the game
 * parameters: board, r, c, n
 * return value: bool - will return true when done, otherwise false
*/
bool sudoku(int board[][9], int r, int c, int num) {
	// Iterate to next row if column is solved
	if (c == 9) {
		c = 0;
		r++;
	}
	// Base case
	// Puzzle is solved - r is out of bounds
	if (r == 9)
		return true;

	// If the space is not empty, go to next space
	if (board[r][c] != 0)
		return sudoku(board, r, c + 1, 1);

	// If there is an empty space...
	// iterate n from 1 to 9
	// check if n can be used at board[r][c]
	// check if not in sector, row and column
	// if yes, board[r][c] = n
	for (int n = 1; n < 10; n++) {
		if ( (!inSector(board, r, c, n)) && (!inRow(board, r, n))
		        && (!inColumn(board, c, n)) ) {
			board[r][c] = n;
			if (sudoku(board, r, c + 1, n))
				return true;

		}
		board[r][c] = 0;
	}

	return false;
}

/* inSector(): checks to see if n is in the sector
 * parameters: board, r, c, n
 * return value: bool - will return true if it is in the sector
*/
bool inSector(int board[][9], int r, int c, int n) {

	int rowSector = r - r % 3;
	int colSector = c - c % 3;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (board[i + rowSector][j + colSector] == n)
				return true;
		}
	}

	return false;
}

/* inRow(): checks to see if n is in the row
 * parameters: board, r, n
 * return value: bool - will return true if it is in the row
*/
bool inRow(int board[][9], int r, int n) {
	for (int i = 0; i < 9; i++) {
		if (board[r][i] == n)
			return true;
	}
	return false;
}

/* inCol(): checks to see if n is in the column
 * parameters: board, c, n
 * return value: bool - will return true if it is in the col
*/
bool inColumn(int board[][9], int c, int n) {
	for (int i = 0; i < 9; i++) {
		if (board[i][c] == n)
			return true;
	}
	return false;
}

/* printBoard(): displays soduku board to console
 * parameters: board
 * return value: N/A
*/
void printBoard(int board[][9]) {
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0)
			cout << "-------------------------------" << endl;
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0)
				cout << "|";
			if (board[i][j] != 0)
				cout << " " << board[i][j] << " ";
			else
				cout << " - ";
			if (j == 8)
				cout << "|";
		}
		cout << endl;
		if (i == 8)
			cout << "-------------------------------";
	}
	cout << endl;
}
