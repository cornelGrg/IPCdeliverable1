#include "matTrans.h"
#include <iostream>


bool checkSymIMP(const std::vector<std::vector<float>>& mat, int n){  //passed by reference
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {  //only check the upper triangle since mat is square
            if (mat[i][j] != mat[j][i]) return false;
        }
    }
    return true;
}

std::vector<std::vector<float>> matTransposeIMP(std::vector<std::vector<float>> mat, int n){ //passed by copy
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(mat[i][j], mat[j][i]);
        }
    }
    return mat;
}
