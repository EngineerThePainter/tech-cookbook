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

int* addMatrixes(int* A, int* B, int size)
{
  int* C = new int[size * size];
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      C[size * i + j] = A[size * i + j] + B[size * i + j];
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

void addMatrixes(int* A, int* B, int size, int* C)
{
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      C[size * i + j] = A[size * i + j] + B[size * i + j];
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

void printMatrix(int* M, unsigned int size)
{
  for (unsigned int i = 0; i < size; ++i) {
    std::cout << "[";
    for (unsigned int j = 0; j < size; ++j) {
      std::cout << M[size * i + j] << " ";
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

void demoSimpleLinear()
{
  int* A = new int[4];
  int* B = new int[4];
  int* BruteForceMatrix = new int[4];
  int* RecursiveMatrix = new int[4];
  int* StrassenMatrix = new int[4];
  for (int i = 0; i < 4; ++i) {
    BruteForceMatrix[i] = 0;
    RecursiveMatrix[i] = 0;
    StrassenMatrix[i] = 0;
  }

  A[0] = 1;
  A[1] = 3;
  A[2] = 7;
  A[3] = 5;

  B[0] = 6;
  B[1] = 8;
  B[2] = 4;
  B[3] = 2;

  std::cout << "Normal multiplication\n";
  squareMatrixMultiply(A, B, 2, BruteForceMatrix);
  printMatrix(BruteForceMatrix, 2);

  std::cout << "Recursive multiplication\n";
  RecursiveMatrix = squareMatrixMultiplyRecursive(A, B, 2);
  printMatrix(RecursiveMatrix, 2);

  // std::cout << "Strassen multiplication\n";
  // RecursiveMatrix = strassenMultiplication(A, B, 2);
  // printMatrix(RecursiveMatrix, 2);
  delete[] A;
  delete[] B;
  delete[] BruteForceMatrix;
  delete[] RecursiveMatrix;
  delete[] StrassenMatrix;
}

void demoTimed()
{
  const int size = 16; // using power of 2 for convienience of recursive approach
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

void demoMatrixMultiplicationLinearMatrixes() { demoSimpleLinear(); }

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

void squareMatrixMultiply(int* A, int* B, int n, int* C)
{
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        C[n * i + j] += A[n * i + k] * B[n * k + j];
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
    int** A11 = new int*[new_n];
    int** A12 = new int*[new_n];
    int** A21 = new int*[new_n];
    int** A22 = new int*[new_n];
    int** B11 = new int*[new_n];
    int** B12 = new int*[new_n];
    int** B21 = new int*[new_n];
    int** B22 = new int*[new_n];
    int** C11 = new int*[new_n];
    int** C12 = new int*[new_n];
    int** C21 = new int*[new_n];
    int** C22 = new int*[new_n];

    for (int i = 0; i < new_n; ++i) {
      A11[i] = new int[new_n];
      A12[i] = new int[new_n];
      A21[i] = new int[new_n];
      A22[i] = new int[new_n];
      B11[i] = new int[new_n];
      B12[i] = new int[new_n];
      B21[i] = new int[new_n];
      B22[i] = new int[new_n];
      C11[i] = new int[new_n];
      C12[i] = new int[new_n];
      C21[i] = new int[new_n];
      C22[i] = new int[new_n];
      for (int j = 0; j < new_n; ++j) {
        A11[i][j] = 0;
        A12[i][j] = 0;
        A21[i][j] = 0;
        A22[i][j] = 0;
        B11[i][j] = 0;
        B12[i][j] = 0;
        B21[i][j] = 0;
        B22[i][j] = 0;
        C11[i][j] = 0;
        C12[i][j] = 0;
        C21[i][j] = 0;
        C22[i][j] = 0;
      }
    }

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        A11[i][j] = A[i][j];
        A12[i][j] = A[i][new_n + j];
        A21[i][j] = A[new_n + i][j];
        A22[i][j] = A[new_n + i][new_n + j];

        B11[i][j] = B[i][j];
        B12[i][j] = B[i][new_n + j];
        B21[i][j] = B[new_n + i][j];
        B22[i][j] = B[new_n + i][new_n + j];
      }
    }

    addMatrixes(squareMatrixMultiplyRecursive(A11, B11, new_n), squareMatrixMultiplyRecursive(A12, B21, new_n), new_n,
                C11);
    addMatrixes(squareMatrixMultiplyRecursive(A11, B12, new_n), squareMatrixMultiplyRecursive(A12, B22, new_n), new_n,
                C12);
    addMatrixes(squareMatrixMultiplyRecursive(A21, B11, new_n), squareMatrixMultiplyRecursive(A22, B21, new_n), new_n,
                C21);
    addMatrixes(squareMatrixMultiplyRecursive(A21, B12, new_n), squareMatrixMultiplyRecursive(A22, B22, new_n), new_n,
                C22);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        C[i][j] = C11[i][j];
        C[i][new_n + j] = C12[i][j];
        C[new_n + i][j] = C21[i][j];
        C[new_n + i][new_n + j] = C22[i][j];
      }
    }

    for (int i = 0; i < new_n; ++i) {
      delete[] A11[i];
      delete[] A12[i];
      delete[] A21[i];
      delete[] A22[i];
      delete[] B11[i];
      delete[] B12[i];
      delete[] B21[i];
      delete[] B22[i];
      delete[] C11[i];
      delete[] C12[i];
      delete[] C21[i];
      delete[] C22[i];
    }
    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
  }
  return C;
}

void squareMatrixMultiplyRecursive(int* A, int* B, int n, int* C) { C = squareMatrixMultiplyRecursive(A, B, n); }

int* squareMatrixMultiplyRecursive(int* A, int* B, int n)
{
  int squared_n = n * n;
  int* C = new int[squared_n];
  if (n == 1) {
    C[0] = A[0] * B[0];
  } else {
    int new_n = n / 2;
    int new_size = new_n * new_n;
    int* A11 = new int[new_size];
    int* A12 = new int[new_size];
    int* A21 = new int[new_size];
    int* A22 = new int[new_size];
    int* B11 = new int[new_size];
    int* B12 = new int[new_size];
    int* B21 = new int[new_size];
    int* B22 = new int[new_size];
    int* C11 = new int[new_size];
    int* C12 = new int[new_size];
    int* C21 = new int[new_size];
    int* C22 = new int[new_size];

    for (int i = 0; i < new_size; ++i) {
      A11[i] = 0;
      A12[i] = 0;
      A21[i] = 0;
      A22[i] = 0;
      B11[i] = 0;
      B12[i] = 0;
      B21[i] = 0;
      B22[i] = 0;
      C11[i] = 0;
      C12[i] = 0;
      C21[i] = 0;
      C22[i] = 0;
    }

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        unsigned int up_left_quarter = (n * i) + j;
        unsigned int up_right_quarter = (n * i) + j + new_n;
        unsigned int down_left_quarter = (n * n / 2) + (n * i + j);
        unsigned int down_right_quarter = (n * n / 2) + (n * i) + (j + new_n);
        A11[i * new_n + j] = A[up_left_quarter];
        A12[i * new_n + j] = A[up_right_quarter];
        A21[i * new_n + j] = A[down_left_quarter];
        A22[i * new_n + j] = A[down_right_quarter];

        B11[i * new_n + j] = B[up_left_quarter];
        B12[i * new_n + j] = B[up_right_quarter];
        B21[i * new_n + j] = B[down_left_quarter];
        B22[i * new_n + j] = B[down_right_quarter];
      }
    }

    addMatrixes(squareMatrixMultiplyRecursive(A11, B11, new_n), squareMatrixMultiplyRecursive(A12, B21, new_n), new_n,
                C11);
    addMatrixes(squareMatrixMultiplyRecursive(A11, B12, new_n), squareMatrixMultiplyRecursive(A12, B22, new_n), new_n,
                C12);
    addMatrixes(squareMatrixMultiplyRecursive(A21, B11, new_n), squareMatrixMultiplyRecursive(A22, B21, new_n), new_n,
                C21);
    addMatrixes(squareMatrixMultiplyRecursive(A21, B12, new_n), squareMatrixMultiplyRecursive(A22, B22, new_n), new_n,
                C22);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        unsigned int up_left_quarter = (n * i) + j;
        unsigned int up_right_quarter = (n * i) + j + new_n;
        unsigned int down_left_quarter = (n * n / 2) + (n * i + j);
        unsigned int down_right_quarter = (n * n / 2) + (n * i) + (j + new_n);
        C[up_left_quarter] = C11[new_n * i + j];
        C[up_right_quarter] = C12[new_n * i + j];
        C[down_left_quarter] = C21[new_n * i + j];
        C[down_right_quarter] = C22[new_n * i + j];
      }
    }

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
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
    int** A11 = new int*[new_n];
    int** A12 = new int*[new_n];
    int** A21 = new int*[new_n];
    int** A22 = new int*[new_n];
    int** B11 = new int*[new_n];
    int** B12 = new int*[new_n];
    int** B21 = new int*[new_n];
    int** B22 = new int*[new_n];
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
      A11[i] = new int[new_n];
      A12[i] = new int[new_n];
      A21[i] = new int[new_n];
      A22[i] = new int[new_n];
      B11[i] = new int[new_n];
      B12[i] = new int[new_n];
      B21[i] = new int[new_n];
      B22[i] = new int[new_n];
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
        A11[i][j] = 0;
        A12[i][j] = 0;
        A21[i][j] = 0;
        A22[i][j] = 0;
        B11[i][j] = 0;
        B12[i][j] = 0;
        B21[i][j] = 0;
        B22[i][j] = 0;
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
        A11[i][j] = A[i][j];
        A12[i][j] = A[i][new_n + j];
        A21[i][j] = A[new_n + i][j];
        A22[i][j] = A[new_n + i][new_n + j];

        B11[i][j] = B[i][j];
        B12[i][j] = B[i][new_n + j];
        B21[i][j] = B[new_n + i][j];
        B22[i][j] = B[new_n + i][new_n + j];
      }
    }

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        S1[i][j] = B12[i][j] - B22[i][j];
        S2[i][j] = A11[i][j] + A12[i][j];
        S3[i][j] = A21[i][j] + A22[i][j];
        S4[i][j] = B21[i][j] - B11[i][j];
        S5[i][j] = A11[i][j] + A22[i][j];
        S6[i][j] = B11[i][j] + B22[i][j];
        S7[i][j] = A12[i][j] - A22[i][j];
        S8[i][j] = B21[i][j] + B22[i][j];
        S9[i][j] = A11[i][j] - A21[i][j];
        S10[i][j] = B11[i][j] + B12[i][j];
      }
    }

    int** P1 = strassenMultiplication(A11, S1, new_n);
    int** P2 = strassenMultiplication(S2, B22, new_n);
    int** P3 = strassenMultiplication(S3, B11, new_n);
    int** P4 = strassenMultiplication(A22, S4, new_n);
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
      delete[] A11[i];
      delete[] A12[i];
      delete[] A21[i];
      delete[] A22[i];
      delete[] B11[i];
      delete[] B12[i];
      delete[] B21[i];
      delete[] B22[i];
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
    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
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
