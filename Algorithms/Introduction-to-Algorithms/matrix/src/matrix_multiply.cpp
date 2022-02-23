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

void substractMatrixes(int** A, int** B, int size, int** C)
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      C[i][j] = A[i][j] - B[i][j];
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
  int** StrassenMatrix = initializeMatrixOfSize(2);

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

  std::cout << "Strassen multiplication\n";
  RecursiveMatrix = strassenMultiplication(A, B, 2);
  printMatrix(RecursiveMatrix, 2);

  deallocateMatrix(A, 2);
  deallocateMatrix(B, 2);
  deallocateMatrix(BruteForceMatrix, 2);
  deallocateMatrix(RecursiveMatrix, 2);
  deallocateMatrix(StrassenMatrix, 2);
}

void demoTimed()
{
  const int size = 512; // using power of 2 for convienience of recursive approach
  int** A = initializeMatrixOfSize(size);
  int** B = initializeMatrixOfSize(size);
  int** BruteForceMatrix = initializeMatrixOfSize(size);
  int** RecursiveMatrix = initializeMatrixOfSize(size);
  int** StrassenMatrix = initializeMatrixOfSize(size);

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

  // The result will be generally worse due to overhead of matrix initializations, but in general
  // it is still the same computational effort
  std::cout << "Recursive Matrix Multiplication: "
            << utils::runWithTimeMeasure(recursive_multiplication, A, B, size, RecursiveMatrix).count()
            << " milliseconds" << std::endl;

  std::function<void(int**, int**, int, int**)> strassen_multiplication =
      [&](int** A, int** B, int nb_elements, int** C) { strassenMultiplication(A, B, nb_elements, C); };

  std::cout << "Strassen Matrix Multiplication: "
            << utils::runWithTimeMeasure(strassen_multiplication, A, B, size, StrassenMatrix).count() << " milliseconds"
            << std::endl;

  deallocateMatrix(A, size);
  deallocateMatrix(B, size);
  deallocateMatrix(BruteForceMatrix, size);
  deallocateMatrix(RecursiveMatrix, size);
  deallocateMatrix(StrassenMatrix, size);
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

void strassenMultiplication(int** A, int** B, int n, int** C) { C = strassenMultiplication(A, B, n); }

int** strassenMultiplication(int** A, int** B, int n)
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
    int** S1 = new int*[new_n];
    int** S2 = new int*[new_n];
    int** S3 = new int*[new_n];
    int** S4 = new int*[new_n];
    int** S5 = new int*[new_n];
    int** S6 = new int*[new_n];
    int** S7 = new int*[new_n];
    int** S8 = new int*[new_n];
    int** S9 = new int*[new_n];
    int** S10 = new int*[new_n];

    for (int i = 0; i < new_n; ++i) {
      A1[i] = new int[new_n];
      A2[i] = new int[new_n];
      A3[i] = new int[new_n];
      A4[i] = new int[new_n];
      B1[i] = new int[new_n];
      B2[i] = new int[new_n];
      B3[i] = new int[new_n];
      B4[i] = new int[new_n];
      S1[i] = new int[new_n];
      S2[i] = new int[new_n];
      S3[i] = new int[new_n];
      S4[i] = new int[new_n];
      S5[i] = new int[new_n];
      S6[i] = new int[new_n];
      S7[i] = new int[new_n];
      S8[i] = new int[new_n];
      S9[i] = new int[new_n];
      S10[i] = new int[new_n];
      for (int j = 0; j < new_n; ++j) {
        A1[i][j] = 0;
        A2[i][j] = 0;
        A3[i][j] = 0;
        A4[i][j] = 0;
        B1[i][j] = 0;
        B2[i][j] = 0;
        B3[i][j] = 0;
        B4[i][j] = 0;
        S1[i][j] = 0;
        S2[i][j] = 0;
        S3[i][j] = 0;
        S4[i][j] = 0;
        S5[i][j] = 0;
        S6[i][j] = 0;
        S7[i][j] = 0;
        S8[i][j] = 0;
        S9[i][j] = 0;
        S10[i][j] = 0;
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

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        S1[i][j] = B2[i][j] - B4[i][j];
        S2[i][j] = A1[i][j] + A2[i][j];
        S3[i][j] = A3[i][j] + A4[i][j];
        S4[i][j] = B3[i][j] - B1[i][j];
        S5[i][j] = A1[i][j] + A4[i][j];
        S6[i][j] = B1[i][j] + B4[i][j];
        S7[i][j] = A2[i][j] - A4[i][j];
        S8[i][j] = B3[i][j] + B4[i][j];
        S9[i][j] = A1[i][j] - A3[i][j];
        S10[i][j] = B1[i][j] + B2[i][j];
      }
    }

    int** P1 = strassenMultiplication(A1, S1, new_n);
    int** P2 = strassenMultiplication(S2, B4, new_n);
    int** P3 = strassenMultiplication(S3, B1, new_n);
    int** P4 = strassenMultiplication(A4, S4, new_n);
    int** P5 = strassenMultiplication(S5, S6, new_n);
    int** P6 = strassenMultiplication(S7, S8, new_n);
    int** P7 = strassenMultiplication(S9, S10, new_n);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
        C[i][new_n + j] = P1[i][j] + P2[i][j];
        C[new_n + i][j] = P3[i][j] + P4[i][j];
        C[new_n + i][new_n + j] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
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
      delete[] S1[i];
      delete[] S2[i];
      delete[] S3[i];
      delete[] S4[i];
      delete[] S5[i];
      delete[] S6[i];
      delete[] S7[i];
      delete[] S8[i];
      delete[] S9[i];
      delete[] S10[i];
      delete[] P1[i];
      delete[] P2[i];
      delete[] P3[i];
      delete[] P4[i];
      delete[] P5[i];
      delete[] P6[i];
      delete[] P7[i];
    }
    delete[] A1;
    delete[] A2;
    delete[] A3;
    delete[] A4;
    delete[] B1;
    delete[] B2;
    delete[] B3;
    delete[] B4;
    delete[] S1;
    delete[] S2;
    delete[] S3;
    delete[] S4;
    delete[] S5;
    delete[] S6;
    delete[] S7;
    delete[] S8;
    delete[] S9;
    delete[] S10;
    delete[] P1;
    delete[] P2;
    delete[] P3;
    delete[] P4;
    delete[] P5;
    delete[] P6;
    delete[] P7;
  }
  return C;
}

} // namespace matrix