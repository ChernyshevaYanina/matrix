#include "test_matrix.h"

TEST(Allocate, Invalid_alloc) { ASSERT_ANY_THROW(Matrix matrix(-2, 2)); }

TEST(Copy, copy_true) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;
  Matrix matrix2(matrix1);
  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(Move, move_true) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(matrix1);
  Matrix result(std::move(matrix1));

  ASSERT_TRUE(result == matrix2);
  ASSERT_FALSE(result == matrix1);
}

TEST(Eq, eq_test_true) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.2;
  matrix2(0, 1) = 2.2;
  matrix2(1, 0) = 3.3;
  matrix2(1, 1) = 4.4;

  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Eq, eq_test_false) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.2;
  matrix2(0, 1) = 2.3;
  matrix2(1, 0) = 3.3;
  matrix2(1, 1) = 4.4;

  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Sum, sum_test_true) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  Matrix matrix3(2, 2);
  matrix3(0, 0) = 3.4;
  matrix3(0, 1) = 5.5;
  matrix3(1, 0) = 7.7;
  matrix3(1, 1) = 9.9;

  matrix1.SumMatrix(matrix2);

  ASSERT_TRUE(matrix1 == matrix3);
}

TEST(Sum, sum_test_option1) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  Matrix matrix3(2, 2);
  matrix3(0, 0) = 3.4;
  matrix3(0, 1) = 5.5;
  matrix3(1, 0) = 7.7;
  matrix3(1, 1) = 9.9;

  matrix1 += matrix2;

  ASSERT_TRUE(matrix1 == matrix3);
}

TEST(Sum, sum_test_option2) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  Matrix matrix3(2, 2);
  matrix3(0, 0) = 3.4;
  matrix3(0, 1) = 5.5;
  matrix3(1, 0) = 7.7;
  matrix3(1, 1) = 9.9;

  Matrix result = matrix1 + matrix2;

  ASSERT_TRUE(result == matrix3);
}

TEST(Sum, sum_test_error) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(1, 1);
  matrix2(0, 0) = 2.2;

  ASSERT_ANY_THROW(matrix1.SumMatrix(matrix2));
}

TEST(Sum, sum_test_eq) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  matrix1.SumMatrix(matrix2);

  ASSERT_NEAR(matrix1(0, 0), 3.4, 1e-07);
  ASSERT_NEAR(matrix1(0, 1), 5.5, 1e-07);
  ASSERT_NEAR(matrix1(1, 0), 7.7, 1e-07);
  ASSERT_NEAR(matrix1(1, 1), 9.9, 1e-07);
}

TEST(Sub, sub_test_true) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.4;
  matrix1(0, 1) = 5.5;
  matrix1(1, 0) = 7.7;
  matrix1(1, 1) = 9.9;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  Matrix matrix3(2, 2);
  matrix3(0, 0) = 1.2;
  matrix3(0, 1) = 2.2;
  matrix3(1, 0) = 3.3;
  matrix3(1, 1) = 4.4;

  matrix1.SubMatrix(matrix2);

  ASSERT_TRUE(matrix1 == matrix3);
}

TEST(Sub, sub_test_error) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.4;
  matrix1(0, 1) = 5.5;
  matrix1(1, 0) = 7.7;
  matrix1(1, 1) = 9.9;

  Matrix matrix2(1, 1);
  matrix2(0, 0) = 2.2;

  ASSERT_ANY_THROW(matrix1.SubMatrix(matrix2));
}

TEST(Sub, sub_test_eq) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.4;
  matrix1(0, 1) = 5.5;
  matrix1(1, 0) = 7.7;
  matrix1(1, 1) = 9.9;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  matrix1.SubMatrix(matrix2);

  ASSERT_NEAR(matrix1(0, 0), 1.2, 1e-07);
  ASSERT_NEAR(matrix1(0, 1), 2.2, 1e-07);
  ASSERT_NEAR(matrix1(1, 0), 3.3, 1e-07);
  ASSERT_NEAR(matrix1(1, 1), 4.4, 1e-07);
}

TEST(Sub, sub_test_option1) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.4;
  matrix1(0, 1) = 5.5;
  matrix1(1, 0) = 7.7;
  matrix1(1, 1) = 9.9;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  Matrix matrix3(2, 2);
  matrix3(0, 0) = 1.2;
  matrix3(0, 1) = 2.2;
  matrix3(1, 0) = 3.3;
  matrix3(1, 1) = 4.4;

  matrix1 -= matrix2;

  ASSERT_TRUE(matrix1 == matrix3);
}

TEST(Sub, sub_test_option2) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 3.4;
  matrix1(0, 1) = 5.5;
  matrix1(1, 0) = 7.7;
  matrix1(1, 1) = 9.9;

  Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.2;
  matrix2(0, 1) = 3.3;
  matrix2(1, 0) = 4.4;
  matrix2(1, 1) = 5.5;

  Matrix matrix3(2, 2);
  matrix3(0, 0) = 1.2;
  matrix3(0, 1) = 2.2;
  matrix3(1, 0) = 3.3;
  matrix3(1, 1) = 4.4;

  Matrix result = matrix1 - matrix2;

  ASSERT_TRUE(result == matrix3);
}

TEST(MulNumber, mul_number_eq) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  matrix1.MulNumber(10);

  ASSERT_NEAR(matrix1(0, 0), 12, 1e-07);
  ASSERT_NEAR(matrix1(0, 1), 22, 1e-07);
  ASSERT_NEAR(matrix1(1, 0), 33, 1e-07);
  ASSERT_NEAR(matrix1(1, 1), 44, 1e-07);
}

TEST(MulNumber, mul_number_option1) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  matrix1 *= 10;

  ASSERT_NEAR(matrix1(0, 0), 12, 1e-07);
  ASSERT_NEAR(matrix1(0, 1), 22, 1e-07);
  ASSERT_NEAR(matrix1(1, 0), 33, 1e-07);
  ASSERT_NEAR(matrix1(1, 1), 44, 1e-07);
}

TEST(MulNumber, mul_number_option2) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix result = matrix1 * 10;

  ASSERT_NEAR(result(0, 0), 12, 1e-07);
  ASSERT_NEAR(result(0, 1), 22, 1e-07);
  ASSERT_NEAR(result(1, 0), 33, 1e-07);
  ASSERT_NEAR(result(1, 1), 44, 1e-07);
}

TEST(MulNumber, mul_number_option3) {
  Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.2;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  Matrix result = 10 * matrix1;

  ASSERT_NEAR(result(0, 0), 12, 1e-07);
  ASSERT_NEAR(result(0, 1), 22, 1e-07);
  ASSERT_NEAR(result(1, 0), 33, 1e-07);
  ASSERT_NEAR(result(1, 1), 44, 1e-07);
}

TEST(MulMatrix, mul_matrix_tests) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  Matrix matrix3(3, 3);
  matrix3(0, 0) = 9;
  matrix3(0, 1) = 12;
  matrix3(0, 2) = 15;
  matrix3(1, 0) = 19;
  matrix3(1, 1) = 26;
  matrix3(1, 2) = 33;
  matrix3(2, 0) = 29;
  matrix3(2, 1) = 40;
  matrix3(2, 2) = 51;

  matrix1.MulMatrix(matrix2);
  ASSERT_TRUE(matrix1 == matrix3);
}

TEST(MulMatrix, mul_matrix_option1) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  Matrix matrix3(3, 3);
  matrix3(0, 0) = 9;
  matrix3(0, 1) = 12;
  matrix3(0, 2) = 15;
  matrix3(1, 0) = 19;
  matrix3(1, 1) = 26;
  matrix3(1, 2) = 33;
  matrix3(2, 0) = 29;
  matrix3(2, 1) = 40;
  matrix3(2, 2) = 51;

  matrix1 *= matrix2;
  ASSERT_TRUE(matrix1 == matrix3);
}

TEST(MulMatrix, mul_matrix_option2) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  Matrix matrix3(3, 3);
  matrix3(0, 0) = 9;
  matrix3(0, 1) = 12;
  matrix3(0, 2) = 15;
  matrix3(1, 0) = 19;
  matrix3(1, 1) = 26;
  matrix3(1, 2) = 33;
  matrix3(2, 0) = 29;
  matrix3(2, 1) = 40;
  matrix3(2, 2) = 51;

  Matrix result = matrix1 * matrix2;
  ASSERT_TRUE(result == matrix3);
}

TEST(MulMatrix, mul_matrix_error) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  Matrix matrix2(1, 1);
  matrix2(0, 0) = 4;

  ASSERT_ANY_THROW(matrix1.MulMatrix(matrix2));
}

TEST(MulMatrix, mul_matrix_eq) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  Matrix matrix2(2, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  matrix1.MulMatrix(matrix2);

  ASSERT_NEAR(matrix1(0, 0), 9, 1e-07);
  ASSERT_NEAR(matrix1(0, 1), 12, 1e-07);
  ASSERT_NEAR(matrix1(0, 2), 15, 1e-07);
  ASSERT_NEAR(matrix1(1, 0), 19, 1e-07);
  ASSERT_NEAR(matrix1(1, 1), 26, 1e-07);
  ASSERT_NEAR(matrix1(1, 2), 33, 1e-07);
  ASSERT_NEAR(matrix1(2, 0), 29, 1e-07);
  ASSERT_NEAR(matrix1(2, 1), 40, 1e-07);
  ASSERT_NEAR(matrix1(2, 2), 51, 1e-07);
}

TEST(Transpose, transpose_tests) {
  Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  Matrix matrix2(2, 3);

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 3;
  matrix2(0, 2) = 5;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 4;
  matrix2(1, 2) = 6;

  Matrix matrix3 = matrix1.Transpose();

  ASSERT_TRUE(matrix3 == matrix2);
}

TEST(Determinant, determ_test_true) {
  Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(1, 2) = 1;
  matrix(2, 0) = 3;
  matrix(2, 1) = 2;
  matrix(2, 2) = 3;

  double det = matrix.Determinant();

  ASSERT_TRUE(det == -8);
}

TEST(Determinant, determ_test_false) {
  Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(1, 2) = 1;

  ASSERT_ANY_THROW(matrix.Determinant());
}

TEST(Determinant, determ_test_true_one) {
  Matrix matrix(1, 1);
  matrix(0, 0) = 1;

  ASSERT_TRUE(matrix.Determinant() == 1);
}

TEST(CalcComplements, calc_c_test_true) {
  Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(1, 2) = 1;
  matrix(2, 0) = 3;
  matrix(2, 1) = 2;
  matrix(2, 2) = 3;

  Matrix result = matrix.CalcComplements();

  Matrix matrix1(3, 3);
  matrix1(0, 0) = 4;
  matrix1(0, 1) = -6;
  matrix1(0, 2) = 0;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = -6;
  matrix1(1, 2) = 4;
  matrix1(2, 0) = -4;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = -4;

  ASSERT_TRUE(matrix1 == result);
}

TEST(CalcComplements, calc_c_test_false) {
  Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(2, 0) = 3;
  matrix(2, 1) = 2;

  ASSERT_ANY_THROW(matrix.CalcComplements());
}

TEST(CalcComplements, calc_c_test_true_one) {
  Matrix matrix(1, 1);
  matrix(0, 0) = 2;
  Matrix matrix2 = matrix.CalcComplements();
  ASSERT_TRUE(matrix2(0, 0) == 4);
}

TEST(Inverse, inverse_test_false_det) {
  Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(1, 2) = 1;
  matrix(2, 0) = 3;
  matrix(2, 1) = 3;
  matrix(2, 2) = 3;

  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

TEST(Inverse, inverse_test_true) {
  Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(1, 2) = 1;
  matrix(2, 0) = 3;
  matrix(2, 1) = 2;
  matrix(2, 2) = 3;

  Matrix matrix2(3, 3);
  matrix2(0, 0) = -0.5;
  matrix2(0, 1) = 0;
  matrix2(0, 2) = 0.5;
  matrix2(1, 0) = 0.75;
  matrix2(1, 1) = 0.75;
  matrix2(1, 2) = -1;
  matrix2(2, 0) = 0;
  matrix2(2, 1) = -0.5;
  matrix2(2, 2) = 0.5;

  Matrix result = matrix.InverseMatrix();

  ASSERT_TRUE(matrix2 == result);
}

TEST(Inverse, inverse_test_true_one) {
  Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  Matrix result = matrix.InverseMatrix();
  ASSERT_NEAR(result(0, 0), 0.2, 1e-07);
}

TEST(Inverse, inverse_test_false) {
  Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 2;
  matrix(2, 0) = 3;
  matrix(2, 1) = 2;

  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

TEST(SetAndGet, get_test) {
  Matrix matrix(2, 2);
  int row = matrix.getRows();
  int col = matrix.getCols();

  ASSERT_TRUE(row == 2);
  ASSERT_TRUE(col == 2);
}

TEST(SetAndGet, set_test) {
  Matrix matrix(2, 2);
  matrix.setRows(3);
  matrix.setCols(4);

  ASSERT_TRUE(matrix.getRows() == 3);
  ASSERT_TRUE(matrix.getCols() == 4);
}

TEST(SetAndGet, set_test_1) {
  Matrix matrix(3, 3);
  matrix.setRows(2);
  matrix.setCols(2);

  ASSERT_TRUE(matrix.getRows() == 2);
  ASSERT_TRUE(matrix.getCols() == 2);
}

int main() {
  ::testing::InitGoogleTest();
#ifdef __APPLE__
  free(__cxxabiv1::__cxa_get_globals());
#endif
  return RUN_ALL_TESTS();
}