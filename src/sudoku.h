#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>

class Sudoku
{
public:
	Sudoku(std::array<int, 81> &matrix);
	bool validInput();
	bool solveSudoku();

private:
	bool findUnassigned(int &row, int &col);
	bool noConflicts(int row, int col, int n);

	std::array<int, 81> &matrix;
};

#endif // SUDOKU_H
