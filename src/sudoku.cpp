#include "sudoku.h"

Sudoku::Sudoku(std::array<int, 81> &matrix)
	: matrix(matrix)
{

}

bool Sudoku::validInput()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j ++) {
			int n = matrix[i * 9 + j];
			if (n < 0 || n > 9) {
				return false;
			}
			matrix[i * 9 + j] = 0;
			if (n && !noConflicts(i, j, n)) {
				return false;
			}
			matrix[i * 9 + j] = n;
		}
	}
	return true;
}

bool Sudoku::findUnassigned(int &row, int &col)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j ++) {
			if (matrix[i * 9 + j] == 0) {
				row = i;
				col = j;
				return true;
			}
		}
	}
	return false;
}

bool Sudoku::noConflicts(int row, int col, int n)
{
	// check row and col
	for (int i = 0; i < 9; i++) {
		if (matrix[row * 9 + i] == n || matrix[i * 9 + col] == n) {
			return false;
		}
	}

	// check block
	for (int i = row - row % 3; i < row - row % 3 + 3; i++) {
		for (int j = col - col % 3; j < col - col % 3 + 3; j++) {
			if (matrix[i * 9 + j] == n) {
				return false;
			}
		}
	}

	return true;
}

bool Sudoku::solveSudoku()
{
	int row, col;

	if (!findUnassigned(row, col)) {
		return true;
	}

	for (int n = 1; n <= 9; n++) {
		if (noConflicts(row, col, n)) {
			matrix[row * 9 + col] = n;
			if (solveSudoku()) {
				return true;
			}
			matrix[row * 9 + col] = 0;
		}
	}

	return false;
}
