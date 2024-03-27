#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cmath>
#include <iostream>

class Matrix {
 private:
  double** matrix_;
  int rows_, cols_;

  bool equalMatrixSize(const Matrix& other) noexcept;
  bool isSquare() noexcept;
  bool equalRowsAndCols(const Matrix& other) noexcept;
  void sumAndSubMatrix(const Matrix& other, double sign) noexcept;
  void Allocate() noexcept;
  void Deallocate() noexcept;

 public:
  Matrix() : matrix_(nullptr), rows_(0), cols_(0){};
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();
  bool operator==(const Matrix& other);
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const double num);
  friend Matrix operator*(const double num, const Matrix& other);
  void operator-=(const Matrix& other);
  void operator+=(const Matrix& other);
  void operator=(const Matrix& other);
  void operator*=(const Matrix& other);
  void operator*=(double num);
  Matrix operator*(const Matrix& other);
  double& operator()(int index, int index2);
  Matrix Minor(int rows, int cols);
  int getRows() const;
  int getCols() const;
  void setRows(int rows);
  void setCols(int cols);
};

#endif  // SRC_MATRIX_H_
