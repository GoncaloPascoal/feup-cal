/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <vector>
#include <sstream>
#include <iostream>
#include <numeric>

pair<int, int> getMin(const vector<int> &vec) {
    int min = INT_MAX;
    size_t idx = -1;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec.at(i) < min) {
            min = vec.at(i);
            idx = i;
        }
    }

    return {min, idx};
}

string calcSum(int* sequence, int size) {
    auto start = chrono::high_resolution_clock::now();
    ostringstream oss;

    for (int m = 1; m <= size; ++m) {
        if (m == 1) {
            int min = INT_MAX;
            size_t idx = -1;

            for (size_t i = 0; i < size; ++i) {
                if (sequence[i] < min) {
                    min = sequence[i];
                    idx = i;
                }
            }

            oss << min << "," << idx << ";";
        }
        else {
            int min = accumulate(sequence, sequence + m, 0);
            size_t idx = 0;

            int currentSum = min;

            for (size_t i = m; i < size; ++i) {
                currentSum += sequence[i];
                currentSum -= sequence[i - m];
                if (currentSum < min) {
                    min = currentSum;
                    idx = i - m + 1;
                }
            }

            oss << min << "," << idx << ";";
        }
    }

    auto finish = chrono::high_resolution_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

    cout << "Time elapsed (N = " << size << "): " << ms << "ms" << endl;

    return oss.str();
}

void testCalcSum(const int ARRAY_SIZE) {
    srand(time(NULL));

    int seq[ARRAY_SIZE];

    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        seq[i] = rand() % ARRAY_SIZE * 10 + 1;
    }

    calcSum(seq, ARRAY_SIZE);
}