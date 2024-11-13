#include "matTrans.h"
#include <iostream>
#include <omp.h>


bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n){  //passed by reference
    bool f = true;
    #pragma omp parallel for shared(f)
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {  //only check the upper triangle since mat is square
            if (mat[i][j] != mat[j][i]) f = false;
        }
    }
    return f;
}


std::vector<std::vector<float>> matTransposeOMP(std::vector<std::vector<float>> mat, int n){ //passed by copy
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            std::swap(mat[i][j], mat[j][i]);
        }
    }
    return mat;
}