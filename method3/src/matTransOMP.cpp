#include "../include/matTrans.h"
#include <iostream>
#include <omp.h>


bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n, int thN){
    bool f = true;
    #pragma omp parallel for collapse(2) num_threads(thN) reduction(&&: f)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] != mat[j][i]) f = false;
        }
    }
    return f;
}


void matTransposeOMP(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int thN, int blockSize){
    #pragma omp parallel for collapse(2) num_threads(thN)
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int bi = i; bi < std::min(i + blockSize, n); ++bi) { //divide the matrix in blocks
                for (int bj = j; bj < std::min(j + blockSize, n); ++bj) {
                    trans[bj][bi] = mat[bi][bj];
                }
            }
        }
    }
}