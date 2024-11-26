#include "../include/matTrans.h"
#include "../include/support.h"
#include <omp.h>
#include <iostream>

//In-Place transposition algorithm
int main(int argc, char** argv) {
    bool isSym = false;
    double wt1, wt2, totT;
    int executions = 0;
    std::string OMPcsvFile = "../data/csv/OMPtime.csv";
    std::string SEQcsvFile = "../data/csv/SEQtime.csv";
    std::string IMPcsvFile = "../data/csv/IMPtime.csv";
    std::vector<int> threads = {1, 2, 4, 8, 16, 32, 64, 96};

    int pow = 4; //default value
    if (argc > 1) {
        try {
            pow = std::stoi(argv[1]);
        } catch (const std::invalid_argument &e) {
            std::cout << "Insert an integer to be used as the size of the matrix" << std::endl;
        }
        if (argc > 2) {
            IMPcsvFile = argv[2];
        }
    }

    int size = (1 << pow);  //2^size
    std::vector<std::vector<float>> M = matInit(size, 3);
    std::vector<std::vector<float>> T(size, std::vector<float>(size));


    //SEQUENTIAL
    totT = 0.0;
    isSym = checkSymSEQ(M, size);
    if (!isSym) {
        for (int i = 0; i < 5; ++i) {  //medium time of 5 executions
            executions++;

            T = M; //resets the matrix

            wt1 = omp_get_wtime();
            matTransposeSEQ(T, size);
            wt2 = omp_get_wtime();

            if (!checkTrans(M, T)) std::cout << "Error: matrix not transposed properly! (SEQUENTIAL)" << std::endl;

            totT += (wt2 - wt1);
            saveToCSV(1, "seq", (wt2 - wt1), pow, SEQcsvFile);

            //printMatrix(M);
            //printMatrix(T);
        }
    }else{
            T = M;
            std::cout << "Matrix was symmetric against all odds! No transposition required" << std::endl;
    }

    std::vector<std::vector<float>> CheckT = T; //support matrix for checking if imp/omp match the serial transposed

    std::cout << "Sequential: wall clock time (avg of "<< executions << ") = " << totT / executions <<  " sec" << std::endl;
    executions = 0;

    //IMPLICIT
    totT = 0.0;
    isSym = checkSymIMP(M, size);
    if (!isSym) {
        for (int i = 0; i < 5; ++i) {
            executions++;

            T = M; //resets the matrix

            wt1 = omp_get_wtime();
            matTransposeIMP(T, size);
            wt2 = omp_get_wtime();

            if (T != CheckT) std::cout << "Error: matrix not transposed properly! (IMPLICIT)" << std::endl;

            totT += (wt2 - wt1);
            saveToCSV(1, "imp", (wt2 - wt1), pow, IMPcsvFile);
        }
    }else {
            T = M;
            std::cout << "Matrix was symmetric against all odds! No transposition required" << std::endl;
    }

    std::cout << "Implicit: wall clock time (avg of "<< executions << ") = " << totT / executions << " sec" << std::endl;
    executions = 0;

    //OpenMP
    std::cout << std::endl << "OpenMP:" << std::endl;
    std::cout << "N_threads|wall_clock_time (avg)|n_of_executions" << std::endl;

    for (int thread: threads) {
        totT = 0.0;
        isSym = checkSymOMP(M, size, thread);
        if (!isSym) {
            for (int i = 0; i < 5; ++i) {
                executions++;

                T = M; //resets the matrix

                wt1 = omp_get_wtime();
                matTransposeOMP(T, size, thread);
                wt2 = omp_get_wtime();

                if (T != CheckT) std::cout << "Error: matrix not transposed properly! (OMP)" << std::endl;

                totT += (wt2 - wt1);
                saveToCSV(thread, "omp", (wt2 - wt1), pow, OMPcsvFile);
            }

            std::cout << thread << "\t  " << (totT / executions) << "\t        (avg of " << executions << ")" << std::endl;
            executions = 0;
        }else {
            T = M;
            std::cout << "Matrix was symmetric against all odds! No transposition required" << std::endl;
        }
    }

    return 0;
}

