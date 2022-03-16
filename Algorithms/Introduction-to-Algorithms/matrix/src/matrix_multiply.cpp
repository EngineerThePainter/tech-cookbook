#include "matrix_multiply.hpp"

#include <functional>
#include <iostream>

#include "time_tracker.hpp"

namespace matrix
{
namespace
{

std::vector<int> addMatrixes(const std::vector<int>& A, const std::vector<int>& B)
{
  std::vector<int> C{};
  C.resize(A.size());
  for (int i = 0; i < A.size(); ++i) {
    C[i] = A[i] + B[i];
  }
  return C;
}

void addMatrixes(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C)
{
  for (int i = 0; i < A.size(); ++i) {
    C[i] = A[i] + B[i];
  }
}

void substractMatrixes(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C)
{
  for (int i = 0; i < A.size(); ++i) {
    C[i] = A[i] - B[i];
  }
}

void printMatrix(const std::vector<int>& M, unsigned int size)
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
  std::vector<int> A = {1, 3, 7, 5};
  std::vector<int> B = {6, 8, 4, 2};
  std::vector<int> BruteForceMatrix (4);
  std::vector<int> RecursiveMatrix (4);
  std::vector<int> StrassenMatrix (4);

  std::cout << "Normal multiplication\n";
  squareMatrixMultiply(A, B, BruteForceMatrix, 2);
  printMatrix(BruteForceMatrix, 2);

  std::cout << "Recursive multiplication\n";
  RecursiveMatrix = squareMatrixMultiplyRecursive(A, B, 2);
  printMatrix(RecursiveMatrix, 2);

  std::cout << "Strassen multiplication\n";
  StrassenMatrix = strassenMultiplication(A, B, 2);
  printMatrix(StrassenMatrix, 2);
}

void demoTimed()
{
  const int size = 32; // using power of 2 for convienience of recursive approach
  std::vector<int> A(size * size, 1);
  std::vector<int> B(size * size, 2);
  std::vector<int> BruteForceMatrix(size * size);
  std::vector<int> RecursiveMatrix(size * size);
  std::vector<int> StrassenMatrix(size * size);

  std::function<void(const std::vector<int>&, const std::vector<int>&, std::vector<int>&, const int)>
      straight_multiplication = [&](const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n) {
        squareMatrixMultiply(A, B, C, n);
      };

  std::cout << "Straight Matrix Multiplication: "
            << utils::runWithTimeMeasure(straight_multiplication, A, B, BruteForceMatrix, size).count()
            << " milliseconds" << std::endl;

  std::function<void(const std::vector<int>&, const std::vector<int>&, std::vector<int>&, const int)>
      recursive_multiplication = [&](const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n) {
        squareMatrixMultiplyRecursive(A, B, C, n);
      };

  // The result will be generally worse due to overhead of matrix initializations, but in general
  // it is still the same computational effort
  std::cout << "Recursive Matrix Multiplication: "
            << utils::runWithTimeMeasure(recursive_multiplication, A, B, RecursiveMatrix, size).count()
            << " milliseconds" << std::endl;

  std::function<void(const std::vector<int>&, const std::vector<int>&, std::vector<int>&, const int)>
      strassen_multiplication = [&](const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n) {
        strassenMultiplication(A, B, C, n);
      };

  std::cout << "Strassen Matrix Multiplication: "
            << utils::runWithTimeMeasure(strassen_multiplication, A, B, StrassenMatrix, size).count() << " milliseconds"
            << std::endl;
}

} // namespace

void demoMatrixMultiplication()
{
  demoSimple();
  demoTimed();
}

void squareMatrixMultiply(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n)
{
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        C[n * i + j] += A[n * i + k] * B[n * k + j];
      }
    }
  }
}

void squareMatrixMultiplyRecursive(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C,
                                   const int n)
{
  C = squareMatrixMultiplyRecursive(A, B, n);
}

std::vector<int> squareMatrixMultiplyRecursive(const std::vector<int>& A, const std::vector<int>& B, const int n)
{
  int squared_n = n * n;
  std::vector<int> C(squared_n);
  if (n == 1) {
    C[0] = A[0] * B[0];
  } else {
    int new_n = n / 2;
    int new_size = new_n * new_n;
    std::vector<int> A11(new_size, 0);
    std::vector<int> A12(new_size, 0);
    std::vector<int> A21(new_size, 0);
    std::vector<int> A22(new_size, 0);
    std::vector<int> B11(new_size, 0);
    std::vector<int> B12(new_size, 0);
    std::vector<int> B21(new_size, 0);
    std::vector<int> B22(new_size, 0);
    std::vector<int> C11(new_size, 0);
    std::vector<int> C12(new_size, 0);
    std::vector<int> C21(new_size, 0);
    std::vector<int> C22(new_size, 0);

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

    addMatrixes(squareMatrixMultiplyRecursive(A11, B11, new_n), squareMatrixMultiplyRecursive(A12, B21, new_n), C11);
    addMatrixes(squareMatrixMultiplyRecursive(A11, B12, new_n), squareMatrixMultiplyRecursive(A12, B22, new_n), C12);
    addMatrixes(squareMatrixMultiplyRecursive(A21, B11, new_n), squareMatrixMultiplyRecursive(A22, B21, new_n), C21);
    addMatrixes(squareMatrixMultiplyRecursive(A21, B12, new_n), squareMatrixMultiplyRecursive(A22, B22, new_n), C22);

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
  }
  return C;
}

void strassenMultiplication(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, const int n)
{
  C = strassenMultiplication(A, B, n);
}

std::vector<int> strassenMultiplication(const std::vector<int>& A, const std::vector<int>& B, const int n)
{
  std::vector<int> C(n * n, 0);
  if (n == 1) {
    C[0] = A[0] * B[0];
  } else {
    int new_n = n / 2;
    int new_size = new_n * new_n;
    std::vector<int> A11(new_size, 0);
    std::vector<int> A12(new_size, 0);
    std::vector<int> A21(new_size, 0);
    std::vector<int> A22(new_size, 0);
    std::vector<int> B11(new_size, 0);
    std::vector<int> B12(new_size, 0);
    std::vector<int> B21(new_size, 0);
    std::vector<int> B22(new_size, 0);
    std::vector<int> S1(new_size, 0);
    std::vector<int> S2(new_size, 0);
    std::vector<int> S3(new_size, 0);
    std::vector<int> S4(new_size, 0);
    std::vector<int> S5(new_size, 0);
    std::vector<int> S6(new_size, 0);
    std::vector<int> S7(new_size, 0);
    std::vector<int> S8(new_size, 0);
    std::vector<int> S9(new_size, 0);
    std::vector<int> S10(new_size, 0);

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

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        S1[new_n * i + j] = B12[new_n * i + j] - B22[new_n * i + j];
        S2[new_n * i + j] = A11[new_n * i + j] + A12[new_n * i + j];
        S3[new_n * i + j] = A21[new_n * i + j] + A22[new_n * i + j];
        S4[new_n * i + j] = B21[new_n * i + j] - B11[new_n * i + j];
        S5[new_n * i + j] = A11[new_n * i + j] + A22[new_n * i + j];
        S6[new_n * i + j] = B11[new_n * i + j] + B22[new_n * i + j];
        S7[new_n * i + j] = A12[new_n * i + j] - A22[new_n * i + j];
        S8[new_n * i + j] = B21[new_n * i + j] + B22[new_n * i + j];
        S9[new_n * i + j] = A11[new_n * i + j] - A21[new_n * i + j];
        S10[new_n * i + j] = B11[new_n * i + j] + B12[new_n * i + j];
      }
    }

    std::vector<int> P1 = strassenMultiplication(A11, S1, new_n);
    std::vector<int> P2 = strassenMultiplication(S2, B22, new_n);
    std::vector<int> P3 = strassenMultiplication(S3, B11, new_n);
    std::vector<int> P4 = strassenMultiplication(A22, S4, new_n);
    std::vector<int> P5 = strassenMultiplication(S5, S6, new_n);
    std::vector<int> P6 = strassenMultiplication(S7, S8, new_n);
    std::vector<int> P7 = strassenMultiplication(S9, S10, new_n);

    for (int i = 0; i < new_n; ++i) {
      for (int j = 0; j < new_n; ++j) {
        unsigned int up_left_quarter = (n * i) + j;
        unsigned int up_right_quarter = (n * i) + j + new_n;
        unsigned int down_left_quarter = (n * n / 2) + (n * i + j);
        unsigned int down_right_quarter = (n * n / 2) + (n * i) + (j + new_n);
        C[up_left_quarter] = P5[new_n * i + j] + P4[new_n * i + j] - P2[new_n * i + j] + P6[new_n * i + j];
        C[up_right_quarter] = P1[new_n * i + j] + P2[new_n * i + j];
        C[down_left_quarter] = P3[new_n * i + j] + P4[new_n * i + j];
        C[down_right_quarter] = P5[new_n * i + j] + P1[new_n * i + j] - P3[new_n * i + j] - P7[new_n * i + j];
      }
    }
  }
  return C;
}

} // namespace matrix
