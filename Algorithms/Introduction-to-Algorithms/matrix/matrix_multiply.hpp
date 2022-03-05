#ifndef MATRIX_MATRIX_MULTIPLICATION
#define MATRIX_MATRIX_MULTIPLICATION

namespace matrix
{

void demoMatrixMultiplication();

void squareMatrixMultiply(int* A, int* B, int n, int* C);

void squareMatrixMultiplyRecursive(int* A, int* B, int n, int* C);

int* squareMatrixMultiplyRecursive(int* A, int* B, int n);

void strassenMultiplication(int* A, int* B, int n, int* C);

int* strassenMultiplication(int* A, int* B, int n);

} // namespace matrix

#endif