#include "matrix_oop.h"

void Matrix::Allocate() noexcept {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void Matrix::Deallocate() noexcept {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range("Invalid value rows or/and cols");
  }
  Allocate();
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  Allocate();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix &&other)
    : matrix_(other.matrix_), rows_(other.rows_), cols_(other.cols_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix::~Matrix() { Deallocate(); }

bool Matrix::equalMatrixSize(const Matrix &other) noexcept {
  return rows_ == other.rows_ && cols_ == other.cols_;
}

bool Matrix::isSquare() noexcept { return rows_ == cols_; }

bool Matrix::equalRowsAndCols(const Matrix &other) noexcept {
  return this->cols_ == other.rows_;
}

void Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    Deallocate();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->Allocate();
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  // return *this;
}

bool Matrix::operator==(const Matrix &other) { return EqMatrix(other); }
Matrix Matrix::operator+(const Matrix &other) {
  Matrix result = *this;
  result.SumMatrix(other);
  return result;
}
Matrix Matrix::operator-(const Matrix &other) {
  Matrix result = *this;
  result.SubMatrix(other);
  return result;
}
Matrix Matrix::operator*(const double num) {
  Matrix result = *this;
  result.MulNumber(num);
  return result;
}

Matrix operator*(const double num, const Matrix &matrix) {
  Matrix result = matrix;
  result.MulNumber(num);
  return result;
}

Matrix Matrix::operator*(const Matrix &other) {
  Matrix result = *this;
  result.MulMatrix(other);
  return result;
}
void Matrix::operator-=(const Matrix &other) { this->SubMatrix(other); }

void Matrix::operator+=(const Matrix &other) { this->SumMatrix(other); }

void Matrix::operator*=(const Matrix &other) { this->MulMatrix(other); }
void Matrix::operator*=(double num) { this->MulNumber(num); };

double &Matrix::operator()(int index, int index2) {
  return matrix_[index][index2];
}
bool Matrix::EqMatrix(const Matrix &other) {
  if (!this->equalMatrixSize(other)) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::sumAndSubMatrix(const Matrix &other, double sign) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j] * sign;
    }
  }
}

void Matrix::SumMatrix(const Matrix &other) {
  if (!equalMatrixSize(other)) {
    throw std::invalid_argument("Invalid size of matrix");
  }
  sumAndSubMatrix(other, 1.0);
}

void Matrix::SubMatrix(const Matrix &other) {
  if (!equalMatrixSize(other)) {
    throw std::invalid_argument("Invalid size of matrix");
  }
  sumAndSubMatrix(other, -1.0);
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (!this->equalRowsAndCols(other)) {
    throw std::invalid_argument("Rows and cols not equal");
  }
  Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = temp;
}

Matrix Matrix::Transpose() {
  Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

Matrix Matrix::Minor(int rows, int cols) {
  Matrix result(rows_ - 1, cols_ - 1);
  int c = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i == rows) {
      continue;
    } else {
      int k = 0;
      for (int j = 0; j < cols_; ++j) {
        if (j == cols) {
          continue;
        } else {
          result.matrix_[c][k] = matrix_[i][j];
          ++k;
        }
      }
      ++c;
    }
  }
  return result;
}

double Matrix::Determinant() {
  double result = 0.0;
  if (!this->isSquare()) {
    throw std::invalid_argument("Matrix need to be squere");
  }
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    double determinant = 0.0;
    int sign = 1;
    for (int i = 0; i < cols_; ++i) {
      Matrix temp = this->Minor(0, i);
      determinant = temp.Determinant();
      result += matrix_[0][i] * determinant * sign;
      sign = -sign;
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  if (!this->isSquare()) {
    throw std::invalid_argument("Matrix need to be squere");
  }
  Matrix result(rows_, cols_);
  double determinant = 0;
  if (rows_ == 1) {
    result.matrix_[0][0] = pow(matrix_[0][0], 2);
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        Matrix temp;
        temp = this->Minor(i, j);
        determinant = temp.Determinant();
        result.matrix_[i][j] = (determinant * pow(-1, (i + j)));
      }
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  if (!this->isSquare()) {
    throw std::invalid_argument("Matrix need to be squere");
  }
  double determinant = this->Determinant();
  Matrix temp(rows_, cols_);
  if (rows_ == 1) {
    temp.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else if (determinant != 0) {
    temp = *this;
    temp = temp.CalcComplements();
    temp = temp.Transpose();
    double num = 1 / determinant;
    temp.MulNumber(num);
  } else {
    throw std::invalid_argument("Determinant is zero, calc error");
  }
  return temp;
}

void Matrix::setRows(int rows) {
  Matrix result(rows, cols_);
  for (int i = 0; i < std::min(rows, rows_); ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = result;
}

void Matrix::setCols(int cols) {
  Matrix result(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < std::min(cols, cols_); ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = result;
}

int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }
