#include<iostream>
#include<vector>

using namespace std;
void displayBoard(const vector<vector<int>>& board, int rows, int cols);
int countNeighbor(vector<vector<int>> board, int row, int col, int rows, int cols);
void updateBoard(vector<vector<int>> board, int rows, int cols);
bool boardsAreEqual(const vector<vector<int>>& board1, const vector<vector<int>>& board2, int rows, int cols);
bool allCellsAreDead(const vector<vector<int>>& board, int rows, int cols);
int countAliveCells(const vector<vector<int>>& board, int rows, int cols);
//function to check and count alive neighbor cells
int countNeighbor(vector<vector<int>> board, int row, int col, int rows, int cols) {
	int aliveNeighbors = 0;
	// check 8 directions 
	for (int counter1 = -1; counter1 <= 1; ++counter1) {
		for (int counter2 = -1; counter2 <= 1; ++counter2) {
			int neighborRow = row + counter1;
			int neighborCol = col + counter2;

			// check if cell in board
			if (neighborRow >= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < cols) {
				aliveNeighbors += board[neighborRow][neighborCol]; // count the number of cells that are alive
			}
		}
	}
	return aliveNeighbors; 
}
// function to apply the rules of game and update the board
void updateBoard(vector<vector<int>> board,int rows, int cols) {
	vector<vector<int>>newBoard = board;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			int aliveNeighbor = countNeighbor(board, row, col, rows, cols);

			// apply The Rules of the Game Of Life
			if (board[row][col] == 1) {
				//cell is alive
				if (aliveNeighbor < 2 || aliveNeighbor > 3) {
					newBoard[row][col] == 0; // cell is dead
				}
			}
			else{
				if (aliveNeighbor == 3) {
					newBoard[row][col] == 1; // cell is alive
				}
			}
		}
	}
	board = newBoard;
}
// function to compare new board and old board
bool boardsAreEqual(const vector<vector<int>>& board1, const vector<vector<int>>& board2, int rows, int cols) {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			if (board1[row][col] != board2[row][col]) {
				return false;
			}
		}
	}
	return true;
}
// function to check if all cells are dead
bool allCellsAreDead(const vector<vector<int>>& board, int rows, int cols) {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			if (board[row][col] == 1) {
				return false; // found an alive cell
			}
		}
	}
	return true;
}
// function to count alive cell
int countAliveCells(const vector<vector<int>>& board, int rows, int cols) {
	int aliveCells = 0;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			if (board[row][col] == 1) {
				aliveCells++;
			}
		}
	}
	return aliveCells;
}
// function to display the board 
void displayBoard(const vector<vector<int>>& board, int rows, int cols) {
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
		  cout << board[row][col] << " ";
		}
		cout <<endl;
	}
}
int main() {
	const int rows = 30;
	const int cols = 30;
	// initialize the board
	vector<vector<int>> board(rows, vector<int>(cols, 0));
	vector<vector<int>> previousboard = board;// save the initial board before update
	int noChangeYear = 0;
	const int maxYear = 1;
	const int maxTotalYear = 30;
	int years = 0;
	while (noChangeYear < maxYear && years < maxTotalYear) {
		cout << "Year: " << years + 1 << endl;
		displayBoard(board, rows, cols); // display the state of board after each year
		updateBoard(board, rows, cols); // update the board
		if (allCellsAreDead(board, rows, cols)) {
			cout << "The game stop because all cells are dead! \n";
			break;
		}
		if (boardsAreEqual(board, previousboard, rows, cols)) {
			noChangeYear++;
		}
		else {
			noChangeYear = 0; // Reset if there is a change
		}
		previousboard = board;// save the board before update
		years++; // increase a year

		if (noChangeYear >= maxYear) {
			cout << "The game stop because there is no change in year.\n";
			break;
		}

		if (years >= maxTotalYear) {
			cout << "The game stop because 30 years have passed. \n ";
			break;
		}
	}
	return 0;
}
