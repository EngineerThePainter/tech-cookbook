#include "matrix_multiply.hpp"

#include <functional>
#include <iostream>

#include "time_tracker.hpp"

namespace matrix
{
void demoMatrixMultiplication()
{
  const int size = 10;
  int** A = new int*[size];
  int** B = new int*[size];
  int** BruteForceMatrix = new int*[size];

  for (int i = 0; i < size; ++i) {
    A[i] = new int[size];
    B[i] = new int[size];
    BruteForceMatrix[i] = new int[size];
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      A[i][j] = 1;
      B[i][j] = 2;
      BruteForceMatrix[i][j] = 0;
    }
  }

  std::function<void(int**, int**, int, int**)> straight_multiplication =
      [&](int** A, int** B, int nb_elements, int** C) { squareMatrixMultiply(A, B, nb_elements, C); };

  std::cout << "Straight Matrix Multiplication: "
            << utils::runWithTimeMeasure(straight_multiplication, A, B, size, BruteForceMatrix).count()
            << " milliseconds" << std::endl;
  for (int i = 0; i < size; ++i) {
    std::cout << BruteForceMatrix[0][i] << ": ";
  }
  std::cout << std::endl;

  for (int i = 0; i < size; ++i) {
    delete[] A[i];
    delete[] B[i];
    delete[] BruteForceMatrix[i];
  }
  delete[] A;
  delete[] B;
  delete[] BruteForceMatrix;
}

void squareMatrixMultiply(int** A, int** B, int n, int** C)
{
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}
} // namespace matrix