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

void addMatrixes(int** A, int** B, int size, int** C)
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

void deallocateMatrix(int** M, int size)
{
  for (int i = 0; i < size; ++i) {
    delete[] M[i];
  }
  delete[] M;
}

void printMatrix(int** M, unsigned int size)
{
  for (unsigned int i = 0; i < size; ++i) {
    std::cout << "[";
    for (unsigned int j = 0; j < size; ++j) {
      std::cout << M[i][j] << " ";
    }
    std::cout << "]\n";
  }
}

void demoSimple()
{
  int** A = initializeMatrixOfSize(2);
  int** B = initializeMatrixOfSize(2);
  int** BruteForceMatrix = initializeMatrixOfSize(2);
  int** RecursiveMatrix = initializeMatrixOfSize(2);

  A[0][0] = 1;
  A[0][1] = 3;
  A[1][0] = 7;
  A[1][1] = 5;

  B[0][0] = 6;
  B[0][1] = 8;
  B[1][0] = 4;
  B[1][1] = 2;

  std::cout << "Normal multiplication\n";
  squareMatrixMultiply(A, B, 2, BruteForceMatrix);
  printMatrix(BruteForceMatrix, 2);

  std::cout << "Recursive multiplication\n";
  RecursiveMatrix = squareMatrixMultiplyRecursive(A, B, 2);
  printMatrix(RecursiveMatrix, 2);

  deallocateMatrix(A, 2);
  deallocateMatrix(B, 2);
  deallocateMatrix(BruteForceMatrix, 2);
  deallocateMatrix(RecursiveMatrix, 2);
}

void demoTimed()
{
  const int size = 32; // using power of 2 for convienience of recursive approach
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

  std::function<void(int**, int**, int, int**)> recursive_multiplication =
      [&](int** A, int** B, int nb_elements, int** C) { squareMatrixMultiplyRecursive(A, B, nb_elements, C); };

  std::cout << "Recursive Matrix Multiplication: "
            << utils::runWithTimeMeasure(recursive_multiplication, A, B, size, RecursiveMatrix).count()
            << " milliseconds" << std::endl;

  deallocateMatrix(A, size);
  deallocateMatrix(B, size);
  deallocateMatrix(BruteForceMatrix, size);
  deallocateMatrix(RecursiveMatrix, size);
}

} // namespace

void demoMatrixMultiplication()
{
  demoSimple();
  demoTimed();
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

void squareMatrixMultiplyRecursive(int** A, int** B, int n, int** C) { C = squareMatrixMultiplyRecursive(A, B, n); }

int** squareMatrixMultiplyRecursive(int** A, int** B, int n)
{
  int** C = initializeMatrixOfSize(n);
  if (n == 1) {
    C[0][0] = A[0][0] * B[0][0];
  } else {
    int new_n = n / 2;
    int** A1 = new int*[new_n];
    int** A2 = new int*[new_n];
    int** A3 = new int*[new_n];
    int** A4 = new int*[new_n];
    int** B1 = new int*[new_n];
    int** B2 = new int*[new_n];
    int** B3 = new int*[new_n];
    int** B4 = new int*[new_n];
    int** C1 = new int*[new_n];
    int** C2 = new int*[new_n];
    int** C3 = new int*[new_n];
    int** C4 = new int*[new_n];

    for (int i = 0; i < new_n; ++i) {
      A1[i] = new int[new_n];
      A2[i] = new int[new_n];
      A3[i] = new int[new_n];
      A4[i] = new int[new_n];
      B1[i] = new int[new_n];
      B2[i] = new int[new_n];
      B3[i] = new int[new_n];
      B4[i] = new int[new_n];
      C1[i] = new int[new_n];
      C2[i] = new int[new_n];
      C3[i] = new int[new_n];
      C4[i] = new int[new_n];
      for (int j = 0; j < new_n; ++j) {
        A1[i][j] = 0;
        A2[i][j] = 0;
        A3[i][j] = 0;
        A4[i][j] = 0;
        B1[i][j] = 0;
        B2[i][j] = 0;
        B3[i][j] = 0;
        B4[i][j] = 0;
        C1[i][j] = 0;
        C2[i][j] = 0;
        C3[i][j] = 0;
        C4[i][j] = 0;
      }
    }

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

    addMatrixes(squareMatrixMultiplyRecursive(A1, B1, new_n), squareMatrixMultiplyRecursive(A2, B3, new_n), new_n, C1);
    addMatrixes(squareMatrixMultiplyRecursive(A1, B2, new_n), squareMatrixMultiplyRecursive(A2, B4, new_n), new_n, C2);
    addMatrixes(squareMatrixMultiplyRecursive(A3, B1, new_n), squareMatrixMultiplyRecursive(A4, B3, new_n), new_n, C3);
    addMatrixes(squareMatrixMultiplyRecursive(A3, B2, new_n), squareMatrixMultiplyRecursive(A4, B4, new_n), new_n, C4);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        C[i][j] = C1[i][j];
        C[i][new_n + j] = C2[i][j];
        C[new_n + i][j] = C3[i][j];
        C[new_n + i][new_n + j] = C4[i][j];
      }
    }

    for (int i = 0; i < new_n; ++i) {
      delete[] A1[i];
      delete[] A2[i];
      delete[] A3[i];
      delete[] A4[i];
      delete[] B1[i];
      delete[] B2[i];
      delete[] B3[i];
      delete[] B4[i];
      delete[] C1[i];
      delete[] C2[i];
      delete[] C3[i];
      delete[] C4[i];
    }
    delete[] A1;
    delete[] A2;
    delete[] A3;
    delete[] A4;
    delete[] B1;
    delete[] B2;
    delete[] B3;
    delete[] B4;
    delete[] C1;
    delete[] C2;
    delete[] C3;
    delete[] C4;
  }
  return C;
}

} // namespace matrix