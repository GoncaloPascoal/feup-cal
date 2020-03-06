/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"
#include <vector>
#include <algorithm>

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku() {
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteudo inicial.
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
 * Obtem o conteudo actual (so para leitura!).
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
 * Verifica se o Sudoku ja esta completamente resolvido
 */
bool Sudoku::isComplete() {
	return countFilled == 9 * 9;
}



/**
 * Solves the Sudoku.
 * Retorna indicacao de sucesso ou insucesso (sudoku impossivel).
 */
bool Sudoku::solve() {
    if (isComplete()) {
        return true;
    }

    vector<int> candidates, temp, intersection;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (numbers[i][j] == 0) {
                for (int k = 1; k < 10; ++k) {
                    if (!columnHasNumber[j][k]) {
                        candidates.push_back(k);
                    }
                }

                for (int k = 1; k < 10; ++k) {
                    if (!lineHasNumber[i][k]) {
                        temp.push_back(k);
                    }
                }

                set_intersection(candidates.begin(), candidates.end(), temp.begin(), temp.end(), back_inserter(intersection));
                candidates = intersection;
                intersection.clear();
                temp.clear();

                for (int k = 1; k < 10; ++k) {
                    if (!block3x3HasNumber[i / 3][j / 3][k]) {
                        temp.push_back(k);
                    }
                }

                set_intersection(candidates.begin(), candidates.end(), temp.begin(), temp.end(), back_inserter(intersection));
                candidates = intersection;

                for (int candidate : candidates) {
                    numbers[i][j] = candidate;
                    ++countFilled;
                    if (solve()) return true;
                }
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
