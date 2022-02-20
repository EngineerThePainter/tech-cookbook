#include "matrix_multiply.hpp"

#include <functional>
#include <iostream>

#include "time_tracker.hpp"

namespace matrix
{
namespace
{
int** initializeMatrixOfSize(int size)
{
  int** M = new int*[size];
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      M[i][j] = 0;
    }
  }
  return M;
}

int** addMatrixes(int** A, int** B, int size)
{
  int** C = initializeMatrixOfSize(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  return C;
}

void deallocateMatrix(int** M, int size)
{
  for (int i = 0; i < size; ++i) {
    delete[] M[i];
  }
  delete[] M;
}

} // namespace

void demoMatrixMultiplication()
{
  const int size = 16; // using power of 2 for convienience of recursive approach
  int** A = initializeMatrixOfSize(size);
  int** B = initializeMatrixOfSize(size);
  int** BruteForceMatrix = initializeMatrixOfSize(size);

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

  deallocateMatrix(A);
  deallocateMatrix(B);
  deallocateMatrix(BruteForceMatrix);
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

void squareMatrixMultiplyRecursive(int** A, int** B, int n, int** C)
{
  if (n == 1) {
    C[0][0] = A[0][0] * B[0][0];
  } else {
    int new_n = n / 2;
    int** A1 = initializeMatrixOfSize(new_n);
    int** A2 = initializeMatrixOfSize(new_n);
    int** A3 = initializeMatrixOfSize(new_n);
    int** A4 = initializeMatrixOfSize(new_n);

    int** B1 = initializeMatrixOfSize(new_n);
    int** B2 = initializeMatrixOfSize(new_n);
    int** B3 = initializeMatrixOfSize(new_n);
    int** B4 = initializeMatrixOfSize(new_n);

    int** C1 = initializeMatrixOfSize(new_n);
    int** C2 = initializeMatrixOfSize(new_n);
    int** C3 = initializeMatrixOfSize(new_n);
    int** C4 = initializeMatrixOfSize(new_n);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        A1[i][j] = A[i][j];
        A2[i][j] = A[i][new_n + j];
        A3[i][j] = A[new_n + i][j];
        A4[i][j] = A[new_n + i][new_n + j];

        B1[i][j] = B[i][j];
        B2[i][j] = B[i][new_n + j];
        B3[i][j] = B[new_n + i][j];
        B4[i][j] = B[new_n + i][new_n + j];

        C1[i][j] = C[i][j];
        C2[i][j] = C[i][new_n + j];
        C3[i][j] = C[new_n + i][j];
        C4[i][j] = C[new_n + i][new_n + j];
      }
    }

    deallocateMatrix(A1);
    deallocateMatrix(A2);
    deallocateMatrix(A3);
    deallocateMatrix(A4);

    deallocateMatrix(B1);
    deallocateMatrix(B2);
    deallocateMatrix(B3);
    deallocateMatrix(B4);

    deallocateMatrix(C1);
    deallocateMatrix(C2);
    deallocateMatrix(C3);
    deallocateMatrix(C4);
  }
}

} // namespace matrix