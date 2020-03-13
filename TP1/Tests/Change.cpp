/*
 * Change.cpp
 */

#include "Change.h"
#include <vector>
#include <climits>
#include <iostream>

string calcChange(int m, int numCoins, int *coinValues) {
    // Convert the coin values array to a vector
    vector<int> coinValuesVector({0});
    coinValuesVector.insert(coinValuesVector.end(), coinValues, coinValues + numCoins);

    vector<int> change(numCoins, 0);

    vector<int> minCoins({0});
    minCoins.insert(minCoins.end(), INT_MAX, m);
    vector<int> lastCoin(m + 1, 0);

    for (int i = 0; i <= numCoins; ++i) {
        vector<int> newMinCoins(minCoins.size(), 0);
        vector<int> newLastCoin(lastCoin.size(), 0);

        for (int k = 0; k <= m; ++k) {
            if (k == 0) {
                newMinCoins.at(k) = 0;
                newLastCoin.at(k) = 0;
            }
            else if (k >= coinValuesVector.at(i)) {
                if (newMinCoins.at(k - coinValuesVector.at(i)) + 1 < minCoins.at(k)) {
                    newMinCoins.at(k) = newMinCoins.at(k - coinValuesVector.at(i)) + 1;
                    newLastCoin.at(k) = coinValuesVector.at(i);
                }
            }
            else {
                newMinCoins.at(k) = minCoins.at(k);
                newLastCoin.at(k) = lastCoin.at(k);
            }
        }

        minCoins = newMinCoins;
        lastCoin = newLastCoin;
    }

    for (int mc : minCoins) {
        cout << mc << " ";
    }
    cout << endl;

    return "";
}


