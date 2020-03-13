/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"
#include <vector>
#include <algorithm>

/** Initializes an empty sudoku.
 */
Sudoku::Sudoku() {
	this->initialize();
}

/**
 * Initializes the sudoku with given values.
 * Lanca excepcao IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]) {
	this->initialize();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (nums[i][j] != 0) {
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int n = 0; n < 10; n++) {
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Gets the current content of the sudoku (read only).
 */
int** Sudoku::getNumbers() {
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++) {
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Checks if the sudoku is already complete (all spaces are filled with a number).
 */
bool Sudoku::isComplete() {
	return countFilled == 9 * 9;
}


bool Sudoku::isValid(int line, int col, int num) {
    return !lineHasNumber[line][num] && !columnHasNumber[col][num] && !block3x3HasNumber[line / 3][col / 3][num];
}


/**
 * Solves the Sudoku.
 * Returns true if the sudoku is possible, false if impossible.
 */
bool Sudoku::solve() {
    if (isComplete()) {
        // We filled all the spaces following the restrictions
        return true;
    }

    for (int i = 0; i < 9; ++i) { // For every line
        for (int j = 0; j < 9; ++j) { // For every column
            if (numbers[i][j] == 0) { // If we find a blank space
                for (int k = 1; k < 10; ++k) { // For every possible number from 1 to 9
                    if (isValid(i, j, k)) { // Check if it's valid (can be placed there)
                        numbers[i][j] = k;
                        ++countFilled;
                        lineHasNumber[i][k] = true;
                        columnHasNumber[j][k] = true;
                        block3x3HasNumber[i / 3][j / 3][k] = true;
                        // Try to solve the sudoku with the chosen number
                        if (solve()) return true;
                        // If we got here the chosen number failed, so reset and try again
                        numbers[i][j] = 0;
                        --countFilled;
                        lineHasNumber[i][k] = false;
                        columnHasNumber[j][k] = false;
                        block3x3HasNumber[i / 3][j / 3][k] = false;
                    }
                }
                // All possible numbers failed, this branch does not lead to the solution
                return false;
            }
        }
    }

	return false;
}



/**
 * Prints the Sudoku.
 */
void Sudoku::print() {
	for (int i = 0; i < 9; i++) {
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
