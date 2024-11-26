#include "../include/matTrans.h"
#include <iostream>
#include <vector>
#include <random>
#include <sys/time.h>
#include <cmath>

bool checkSymSEQ(const std::vector<std::vector<float>>& mat, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] != mat[j][i]) return false;
        }
    }
    return true;
}

void matTransposeSEQ(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int blockSize){
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int bi = i; bi < std::min(i + blockSize, n); ++bi) {
                for (int bj = j; bj < std::min(j + blockSize, n); ++bj) {
                    trans[bj][bi] = mat[bi][bj];
                }
            }
        }
    }
}

