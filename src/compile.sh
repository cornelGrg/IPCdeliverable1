#!/bin/bash

#compiler settings
module load gcc91
alias gcc=gcc-9.1.0
alias g++=g++-9.1.0

#compilation
g++-9.1.0 -c main.cpp -fopenmp -o ../build/main.o
g++-9.1.0 -c matTransSEQ.cpp -o ../build/matTransSEQ.o
g++-9.1.0 -c matTransIMP.cpp -O3 -o ../build/matTransIMP.o
g++-9.1.0 -c matTransOMP.cpp -fopenmp -o ../build/matTransOMP.o
g++-9.1.0 ../build/main.o ../build/matTransSEQ.o ../build/matTransIMP.o ../build/matTransOMP.o -fopenmp -o matTrans

echo "Compilation was successful!"