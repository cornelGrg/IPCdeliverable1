#include "../include/matTrans.h"
#include <iostream>
#include <vector>
#include <random>
#include <sys/time.h>
#include <cmath>

bool checkSymSEQ(const std::vector<std::vector<float>>& mat, int n){  //passed by reference
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {  //only check the upper triangle since mat is square
            if (mat[i][j] != mat[j][i]) return false;
        }
    }
    return true;
}

void matTransposeSEQ(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //std::swap(mat[i][j], mat[j][i]);
            trans[i][j] = mat[j][i];
        }
    }
}

