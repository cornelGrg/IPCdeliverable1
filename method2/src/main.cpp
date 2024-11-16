#include "../include/matTrans.h"
#include "../include/support.h"
#include <omp.h>
#include <iostream>


int main(int argc, char** argv) {
    double wt1, wt2, totT;
    int executions = 0;
    std::string OMPcsvFile = "../data/OMPtime.csv";
    std::string SEQcsvFile = "../data/SEQtime.csv";
    std::string IMPcsvFile = "../data/IMPtime.csv";
    std::vector<int> threads = {1, 2, 4, 8, 16, 32, 64, 96};

    int pow = 4; //default value
    if (argc > 1) {
        try {
            pow = std::stoi(argv[1]);
        } catch (const std::invalid_argument &e) {
            std::cout << "Insert an integer to be used as the size of the matrix" << std::endl;
        }
    }

    int size = (1 << pow);  //2^size
    std::vector<std::vector<float>> M = matInit(size, 3);
    std::vector<std::vector<float>> T(size, std::vector<float>(size));


    //SEQUENTIAL
    //wt1 = omp_get_wtime();
    totT = 0.0;
    for (int i = 0; i < 5; ++i) {  //medium time of 5 executions
        if (!checkSymSEQ(M, size)){
            executions++;

            wt1 = omp_get_wtime();
            T = matTransposeSEQ(M, size);
            wt2 = omp_get_wtime();

            if(!checkTrans(M, T)) std::cout << "Error: matrix not transposed properly! (SEQUENTIAL)" << std::endl;

            totT += (wt2 - wt1);

            /**
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << M[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << T[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            **/
        } else {
            T = M;
        }
    }

    //wt2 = omp_get_wtime();
    saveToCSV(1, "imp", (totT/executions), pow, SEQcsvFile);
    std::cout << "Sequential: wall clock time (avg of "<< executions << ") = " << totT / executions <<  " sec" << std::endl;
    executions = 0;

    //IMPLICIT
    totT = 0.0;
    for (int i = 0; i < 5; ++i) {
        if (!checkSymIMP(M, size)) {
            executions++;
            wt1 = omp_get_wtime();
            T = matTransposeIMP(M, size);
            wt2 = omp_get_wtime();

            if(!checkTrans(M, T)) std::cout << "Error: matrix not transposed properly! (IMPLICIT)" << std::endl;

            totT += (wt2-wt1);
        } else {
            T = M;
        }
    }

    saveToCSV(1, "imp", (totT/executions), pow, IMPcsvFile);
    std::cout << "Implicit: wall clock time (avg of "<< executions << ") = " << totT / executions << " sec" << std::endl;
    executions = 0;

    //OpenMP
    //wt1 = omp_get_wtime();
    std::cout << std::endl << "OpenMP:" << std::endl;
    std::cout << "N_threads|wall_clock_time (avg)|n_of_executions" << std::endl;
    for (int thread : threads) {
        totT = 0.0;
        for (int i = 0; i < 5; ++i) {
            if (!checkSymOMP(M, size, thread)) {
                executions++;
                wt1 = omp_get_wtime();
                T = matTransposeOMP(M, size, thread);
                wt2 = omp_get_wtime();

                if(!checkTrans(M, T)) std::cout << "Error: matrix not transposed properly! (OMP)" << std::endl;

                totT += (wt2-wt1);
            } else {
                T = M;
            }
        }
        //wt2 = omp_get_wtime();
        saveToCSV(thread, "omp", (totT/executions), pow, OMPcsvFile);
        std::cout << thread << "\t  " << (totT / executions) << "\t        (avg of " << executions << ")" << std::endl;
        executions = 0;
    }

    return 0;
}

