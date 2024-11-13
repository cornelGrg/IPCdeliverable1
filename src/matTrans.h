#ifndef MATTRANS_H
#define MATTRANS_H

#include <vector>

bool checkSym(const std::vector<std::vector<float>>& mat, int n);
std::vector<std::vector<float>> matTranspose(std::vector<std::vector<float>> mat, int n);

bool checkSymIMP(const std::vector<std::vector<float>>& mat, int n);
std::vector<std::vector<float>> matTransposeIMP(std::vector<std::vector<float>> mat, int n);

bool checkSymOMP(const std::vector<std::vector<float>>& mat, int n);
std::vector<std::vector<float>> matTransposeOMP(std::vector<std::vector<float>> mat, int n);

#endif