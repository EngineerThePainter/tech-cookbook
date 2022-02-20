#ifndef MATRIX_MATRIX_MULTIPLICATION
#define MATRIX_MATRIX_MULTIPLICATION

namespace matrix
{

void demoMatrixMultiplication();

/**
 * @brief Multiplies two square matrixes A and B to get a matrix C. Using square matrixes just for convienience.
 *
 * @param A first matrix
 * @param B second matrix
 * @param n matrix size.
 * @param C result matrix. Must be initialized when passed to the function
 */
void squareMatrixMultiply(int** A, int** B, int n, int** C);

} // namespace matrix

#endif