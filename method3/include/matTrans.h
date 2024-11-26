#ifndef MATTRANS_H
#define MATTRANS_H

#include <vector>

bool checkSymSEQ(const std::vector<std::vector<float>>& mat, int n);
void matTransposeSEQ(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int blockSize);

bool checkSymIMP(const std::vector<std::vector<float>>& mat, int n);
void matTransposeIMP(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int blockSize);

bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n, int thN);
void matTransposeOMP(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int thN);

#endif