#include "../include/matTrans.h"
#include <iostream>
#include <omp.h>


bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n, int thN){  //passed by reference
    bool f = true;
    #pragma omp parallel for collapse(2) num_threads(thN)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {  //only check the upper triangle since mat is square
            if (mat[i][j] != mat[j][i]) f = false;
        }
    }
    return f;
}


void matTransposeOMP(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int thN){ //passed by copy
    //std::vector<std::vector<float>> trans(n, std::vector<float>(n));
    #pragma omp parallel for collapse(2) num_threads(thN)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            trans[i][j] = mat[j][i];
        }
    }
}