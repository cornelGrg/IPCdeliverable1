#ifndef MATTRANS_H
#define MATTRANS_H

#include <vector>

bool checkSymSEQ(const std::vector<std::vector<float>>& mat, int n);
//std::vector<std::vector<float>> matTransposeSEQ(std::vector<std::vector<float>>& mat, int n);
void matTransposeSEQ(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n);

bool checkSymIMP(const std::vector<std::vector<float>>& mat, int n);
//std::vector<std::vector<float>> matTransposeIMP(std::vector<std::vector<float>>& mat, int n);
void matTransposeIMP(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n);

bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n, int thN);
//std::vector<std::vector<float>> matTransposeOMP(std::vector<std::vector<float>>& mat, int n);
void matTransposeOMP(const std::vector<std::vector<float>>& mat, std::vector<std::vector<float>>& trans, int n, int thN);

#endif