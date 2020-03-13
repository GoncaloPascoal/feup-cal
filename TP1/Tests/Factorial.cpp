/*
 * Factorial.cpp
 */

#include "Factorial.h"
#include <vector>

int factorialRecurs(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorialRecurs(n - 1);
}

int factorialDinam(int n) {
	int last = 1; // 0!

	for (int i = 1; i <= n; ++i) {
	    last = i * last;
	}

	return last;
}
