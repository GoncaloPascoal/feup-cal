/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <vector>
#include <iostream>

int s_recursive(int n, int k) {
   if (k == 1 or k == n) {
       return 1;
   }
   return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
}

int s_dynamic(int n, int k) {
    std::vector<int> v;

    for (int i = 1; i <= n; ++i) {
        std::vector<int> newV;

        for (int j = 1; j <= i; ++j) {
            if (j == 1 || j == i) {
                newV.push_back(1);
            }
            else {
                newV.push_back(v[j - 2] + j * v[j - 1]);
            }
        }

        v = newV;
    }

	return v[k - 1];
}


int b_recursive(int n) {
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        sum += s_recursive(n, k);
    }
    return sum;
}

int b_dynamic(int n) {
	int sum = 0;
	for (int k = 1; k <= n; ++k) {
	    sum += s_dynamic(n, k);
	}
	return sum;
}


