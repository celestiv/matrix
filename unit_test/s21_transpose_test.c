#include "s21_test_matrix.h"

START_TEST(transpose_matrix_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);

  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(-10e10, 10e10);
      m.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &check), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix_2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);

  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), ERROR);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix_3) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[0][2] = 3.0;
  matr1.matrix[1][0] = 4.0;
  matr1.matrix[1][1] = 5.0;
  matr1.matrix[1][2] = 6.0;

  int res = s21_transpose(&matr1, &matr2);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr1.matrix[0][0], matr2.matrix[0][0]);
  ck_assert_double_eq(matr1.matrix[0][1], matr2.matrix[1][0]);
  ck_assert_double_eq(matr1.matrix[0][2], matr2.matrix[2][0]);
  ck_assert_double_eq(matr1.matrix[1][0], matr2.matrix[0][1]);
  ck_assert_double_eq(matr1.matrix[1][1], matr2.matrix[1][1]);
  ck_assert_double_eq(matr1.matrix[1][2], matr2.matrix[2][1]);
  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

START_TEST(transpose_matrix_4) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  if (matr1.matrix != NULL) {
    matr1.matrix[0][0] = 1.0;
    matr1.matrix[0][1] = 2.0;
    matr1.matrix[0][2] = 3.0;
    matr1.matrix[1][0] = 4.0;
    matr1.matrix[1][1] = 5.0;
    matr1.matrix[1][2] = NAN;
    int res = s21_transpose(&matr1, &matr2);
    int res_o = OK;
    ck_assert_int_eq(res, res_o);
    s21_remove_matrix(&matr1);
    s21_remove_matrix(&matr2);
  }
}
END_TEST

START_TEST(transpose_matrix_5) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  if (matr1.matrix != NULL) {
    matr1.matrix[0][0] = 1.0;
    matr1.matrix[0][1] = 2.0;
    matr1.matrix[0][2] = 3.0;
    matr1.matrix[1][0] = 4.0;
    matr1.matrix[1][1] = 5.0;
    matr1.matrix[1][2] = 6.0;
    int res = s21_transpose(&matr1, &matr2);
    int res_o = 0;
    ck_assert_int_eq(res, res_o);
    s21_remove_matrix(&matr1);
    s21_remove_matrix(&matr2);
  }
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("\033[10;35;40m TRANSPOSE MATRIX \033[0;0;0m\n");
  TCase *tc = tcase_create("transpose_matrix");

  tcase_add_loop_test(tc, transpose_matrix_1, 0, 50);
  tcase_add_loop_test(tc, transpose_matrix_2, 0, 50);
  tcase_add_loop_test(tc, transpose_matrix_3, 0, 50);
  tcase_add_loop_test(tc, transpose_matrix_4, 0, 50);
  tcase_add_loop_test(tc, transpose_matrix_5, 0, 50);

  suite_add_tcase(s, tc);
  return s;
}
