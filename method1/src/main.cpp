#include "../include/matTrans.h"
#include "../include/support.h"
#include <omp.h>
#include <iostream>


int main(int argc, char** argv) {
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
            //T = matTransposeSEQ(M, size);
            matTransposeSEQ(M, T, size);
            wt2 = omp_get_wtime();

            if(!checkTrans(M, T)) std::cout << "Error: matrix not transposed properly! (SEQUENTIAL)" << std::endl;

            totT += (wt2 - wt1);
            saveToCSV(1, "imp", (wt2-wt1), pow, SEQcsvFile);

            //printMatrix(M);
            //printMatrix(T);
        } else {
            T = M;
        }
    }


    std::vector<std::vector<float>> CheckT = T; //support matrix for checking if imp/omp match the serial transposed


    //wt2 = omp_get_wtime();

    std::cout << "Sequential: wall clock time (avg of "<< executions << ") = " << totT / executions <<  " sec" << std::endl;
    executions = 0;

    //IMPLICIT
    totT = 0.0;
    for (int i = 0; i < 5; ++i) {
        if (!checkSymIMP(M, size)) {
            executions++;
            wt1 = omp_get_wtime();
            //T = matTransposeIMP(M, size);
            matTransposeIMP(M,T, size);
            wt2 = omp_get_wtime();

            if(T != CheckT) std::cout << "Error: matrix not transposed properly! (IMPLICIT)" << std::endl;

            totT += (wt2-wt1);
            saveToCSV(1, "imp", (wt2-wt1), pow, IMPcsvFile);
        } else {
            T = M;
        }
    }


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
                //T = matTransposeOMP(M, size);
                matTransposeOMP(M, T, size, thread);
                wt2 = omp_get_wtime();

                if(T != CheckT) std::cout << "Error: matrix not transposed properly! (OMP)" << std::endl;

                totT += (wt2-wt1);
                saveToCSV(thread, "omp", (wt2-wt1), pow, OMPcsvFile);
            } else {
                T = M;
            }
        }
        //wt2 = omp_get_wtime();

        std::cout << thread << "\t  " << (totT / executions) << "\t        (avg of " << executions << ")" << std::endl;
        executions = 0;
    }

    return 0;
}
