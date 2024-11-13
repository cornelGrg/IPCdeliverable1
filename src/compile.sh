#!/bin/bash

module load gcc91
alias gcc=gcc-9.1.0
alias g++=g++-9.1.0

g++-9.1.0 -c main.cpp -fopenmp
g++-9.1.0 -c matTransSEQ.cpp
g++-9.1.0 -c matTransIMP.cpp -O3
g++-9.1.0 -c matTransOMP.cpp -fopenmp
g++-9.1.0 main.o matTransSEQ.o matTransIMP.o matTransOMP.o -fopenmp -o matTrans
