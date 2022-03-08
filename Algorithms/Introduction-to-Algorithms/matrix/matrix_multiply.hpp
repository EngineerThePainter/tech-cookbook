#ifndef MATRIX_MATRIX_MULTIPLICATION
#define MATRIX_MATRIX_MULTIPLICATION

#include <vector>

namespace matrix
{

void demoMatrixMultiplication();

void squareMatrixMultiply(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n);

void squareMatrixMultiplyRecursive(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C,
                                   const int n);

std::vector<int> squareMatrixMultiplyRecursive(const std::vector<int>& A, const std::vector<int>& B, const int n);

void strassenMultiplication(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n);

std::vector<int> strassenMultiplication(const std::vector<int>& A, const std::vector<int>& B, const int n);

} // namespace matrix

#endif
