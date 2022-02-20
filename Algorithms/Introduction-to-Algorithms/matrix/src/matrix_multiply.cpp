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
    M[i] = new int[size];
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
  int** RecursiveMatrix = initializeMatrixOfSize(size);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      A[i][j] = 1;
      B[i][j] = 2;
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
  std::cout << std::endl << std::endl;

  RecursiveMatrix = squareMatrixMultiplyRecursive(A, B, size);
  // std::cout << "Recursive Matrix Multiplication: "
  //           << utils::runWithTimeMeasure(straight_multiplication, A, B, size, BruteForceMatrix).count()
  //           << " milliseconds" << std::endl;
  std::cout << "Results of recursive\n";
  for (int i = 0; i < size; ++i) {
    std::cout << RecursiveMatrix[0][i] << ": ";
  }
  std::cout << std::endl;

  deallocateMatrix(A, size);
  deallocateMatrix(B, size);
  deallocateMatrix(BruteForceMatrix, size);
  deallocateMatrix(RecursiveMatrix, size);
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

int** squareMatrixMultiplyRecursive(int** A, int** B, int n)
{
  int** C = initializeMatrixOfSize(n);
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
      }
    }

    int** C1 =
        addMatrixes(squareMatrixMultiplyRecursive(A1, B1, new_n), squareMatrixMultiplyRecursive(A2, B3, new_n), new_n);
    int** C2 =
        addMatrixes(squareMatrixMultiplyRecursive(A1, B2, new_n), squareMatrixMultiplyRecursive(A2, B4, new_n), new_n);
    int** C3 =
        addMatrixes(squareMatrixMultiplyRecursive(A3, B1, new_n), squareMatrixMultiplyRecursive(A4, B2, new_n), new_n);
    int** C4 =
        addMatrixes(squareMatrixMultiplyRecursive(A3, B2, new_n), squareMatrixMultiplyRecursive(A4, B4, new_n), new_n);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        C[i][j] = C1[i][j];
        C[i][new_n + j] = C2[i][j];
        C[new_n + i][j] = C3[i][j];
        C[new_n + i][new_n + j] = C4[i][j];
      }
    }

    deallocateMatrix(A1, new_n);
    deallocateMatrix(A2, new_n);
    deallocateMatrix(A3, new_n);
    deallocateMatrix(A4, new_n);

    deallocateMatrix(B1, new_n);
    deallocateMatrix(B2, new_n);
    deallocateMatrix(B3, new_n);
    deallocateMatrix(B4, new_n);

    deallocateMatrix(C1, new_n);
    deallocateMatrix(C2, new_n);
    deallocateMatrix(C3, new_n);
    deallocateMatrix(C4, new_n);
  }
  return C;
}

} // namespace matrix