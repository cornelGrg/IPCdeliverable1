#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <sys/time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

const int n = 2;

std::vector<std::vector<float>>  matInit(int n, int decimals){
    std::random_device rd;
    std::mt19937 generator(rd());  //19937 for better random numbers
    std::uniform_real_distribution<float> distr(0.0f, 10.0f);

    std::vector<std::vector<float>> mat(n, std::vector<float>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
	    
            mat[i][j] = std::round(distr(generator) * std::pow(10.0f, decimals)) / std::pow(10.0f, decimals);
        }
    }

    return mat;
}

bool checkSym(const std::vector<std::vector<float>>& mat){  //passed by reference
    int n = mat.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {  //only check the upper triangle since mat is square
            if (mat[i][j] != mat[j][i]) return false;
        }
    }

    return true;
}

std::vector<std::vector<float>> matTranspose(std::vector<std::vector<float>> mat){ //passed by copy
    int n = mat.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(mat[i][j], mat[j][i]);
        }
    }
    return mat;
}

int main(int argc, char** argv) {
    //2^n
    int pow = (1 << n);
    std::vector<std::vector<float>> M = matInit(pow, 3);

    for (int i = 0; i < pow; ++i) {
        for (int j = 0; j < pow; ++j) {
            std::cout << M[i][j] << "\t";
        }
        std::cout << std::endl;
    }

#ifdef _OPENMP
    double wt1, wt2;
#endif

#ifdef _OPENMP
    wt1 = omp_get_wtime();
#endif

    std::cout << std::endl;
if (!checkSym(M)){
    std::vector<std::vector<float>> T = matTranspose(M);

    for (int i = 0; i < pow; ++i) {
        for (int j = 0; j < pow; ++j) {
            std::cout << T[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


#ifdef _OPENMP
    wt2 = omp_get_wtime();
#endif

#ifdef _OPENMP
    std::cout << "wall clock time (omp_get_wtime) = " << (wt2 - wt1) << " sec" << std::endl;
#endif
    return 0;
}
