#include "matTrans.h"
#include <iostream>
#include <random>
#include <cmath>
#include <omp.h>

std::vector<std::vector<float>> matInit(int n, int decimals){
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

int main(int argc, char** argv) {
    double wt1, wt2;

    int size = 4; //default value
    if (argc > 1) {
        try {
            size = std::stoi(argv[1]);
        } catch (const std::invalid_argument &e) {
            std::cout << "Insert an integer to be used as the size of the matrix" << std::endl;
        }
    }

    int pow = (1 << size);  //2^size
    std::vector<std::vector<float>> M = matInit(pow, 3);
    std::vector<std::vector<float>> T;


    //SEQUENTIAL
    wt1 = omp_get_wtime();

    if (!checkSym(M, size)){
        T = matTranspose(M, size);

        /**
        for (int i = 0; i < pow; ++i) {
            for (int j = 0; j < pow; ++j) {
                std::cout << T[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        **/
    } else {
        T = M;
    }

    wt2 = omp_get_wtime();
    std::cout << "wall clock time (omp_get_wtime) SEQUENTIAL = " << (wt2 - wt1) << " sec" << std::endl;

    //IMPLICIT
    wt1 = omp_get_wtime();

    if (!checkSymIMP(M, size)){
        T = matTransposeIMP(M, size);

        /**
        for (int i = 0; i < pow; ++i) {
            for (int j = 0; j < pow; ++j) {
                std::cout << T[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        **/
    } else {
        T = M;
    }

    wt2 = omp_get_wtime();
    std::cout << "wall clock time (omp_get_wtime) IMPLICIT = " << (wt2 - wt1) << " sec" << std::endl;


    //OpenMP
    wt1 = omp_get_wtime();

    if (!checkSymOMP(M, size)){
        T = matTransposeOMP(M, size);

        /**
        for (int i = 0; i < pow; ++i) {
            for (int j = 0; j < pow; ++j) {
                std::cout << T[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        **/

    } else {
        T = M;
    }

    wt2 = omp_get_wtime();
    std::cout << "wall clock time (omp_get_wtime) OPENMP = " << (wt2 - wt1) << " sec" << std::endl;

    return 0;
}

