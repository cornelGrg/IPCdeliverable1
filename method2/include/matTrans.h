#ifndef MATTRANS_H
#define MATTRANS_H

#include <vector>

bool checkSymSEQ(const std::vector<std::vector<float>>& mat, int n);
void matTransposeSEQ(std::vector<std::vector<float>>& mat, int n);

bool checkSymIMP(const std::vector<std::vector<float>>& mat, int n);
void matTransposeIMP(std::vector<std::vector<float>>& mat, int n);

bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n, int thN);
void matTransposeOMP(std::vector<std::vector<float>>& mat, int n, int thN);

#endif