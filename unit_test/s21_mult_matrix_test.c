#include "s21_test_matrix.h"

START_TEST(simple_mult) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t matr01, matr02, matr_mult1;
  int row = 3;
  int col = 2;
  s21_create_matrix(row, col, &matr01);
  s21_create_matrix(col, row, &matr02);
  if (matr01.matrix != NULL && matr02.matrix != NULL) {
    matr02.matrix[0][0] = 2.0;
    matr02.matrix[0][1] = 2.0;
    matr02.matrix[0][2] = 2.0;

    matr02.matrix[1][0] = 2.0;
    matr02.matrix[1][1] = 2.0;
    matr02.matrix[1][2] = 2.0;

    matr01.matrix[0][0] = 2.0;
    matr01.matrix[0][1] = 2.0;

    matr01.matrix[1][0] = 2.0;
    matr01.matrix[1][1] = 2.0;

    matr01.matrix[2][0] = 2.0;
    matr01.matrix[2][1] = 2.0;
    int res = s21_mult_matrix(&matr01, &matr02, &matr_mult1);
    int res_o = 0;
    double n = 8.0;
    ck_assert_int_eq(res, res_o);
    ck_assert_double_eq(matr_mult1.matrix[0][0], n);
    ck_assert_double_eq(matr_mult1.matrix[0][1], n);
    ck_assert_double_eq(matr_mult1.matrix[0][2], n);

    ck_assert_double_eq(matr_mult1.matrix[1][0], n);
    ck_assert_double_eq(matr_mult1.matrix[1][1], n);
    ck_assert_double_eq(matr_mult1.matrix[1][2], n);

    ck_assert_double_eq(matr_mult1.matrix[2][0], n);
    ck_assert_double_eq(matr_mult1.matrix[2][1], n);
    ck_assert_double_eq(matr_mult1.matrix[2][2], n);

    s21_remove_matrix(&matr01);
    s21_remove_matrix(&matr02);
    s21_remove_matrix(&matr_mult1);
  }
}
END_TEST

START_TEST(mult_matrix_2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);
  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  if (m.matrix != NULL && mtx.matrix != NULL && check.matrix != NULL) {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++) m.matrix[i][j] = get_rand(-10e10, 10e10);

    for (int i = 0; i < cols; i++)
      for (int j = 0; j < rows; j++) mtx.matrix[i][j] = get_rand(-10e10, 10e10);

    for (int i = 0; i < m.rows; i++) {
      for (int j = 0; j < mtx.columns; j++) {
        check.matrix[i][j] = 0;
        for (int k = 0; k < m.columns; k++)
          check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
      }
    }

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t matr1, matr2, matr_mult;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  s21_create_matrix(row, col, &matr2);
  if (matr1.matrix != NULL && matr2.matrix != NULL) {
    matr1.matrix[0][0] = 1.0;
    matr1.matrix[0][1] = 1.0;
    matr1.matrix[1][0] = 1.0;
    matr1.matrix[1][1] = 1.0;
    matr2.matrix[0][0] = 1.0;
    matr2.matrix[0][1] = 1.0;
    matr2.matrix[1][0] = 1.0;
    matr2.matrix[1][1] = 1.0;
    int res = s21_mult_matrix(&matr1, &matr2, &matr_mult);
    int res_o = OK;
    ck_assert_int_eq(res, res_o);
    s21_remove_matrix(&matr1);
    s21_remove_matrix(&matr2);
    s21_remove_matrix(&matr_mult);
  }
}
END_TEST

START_TEST(mult_matrix_4) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  if (m.matrix != NULL && mtx.matrix != NULL && check.matrix != NULL) {
    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), ERROR);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

START_TEST(mult_matrix_5) {
  int rows = 2;
  int cols = 3;
  int rows1 = 4;
  int cols1 = 5;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);

  matrix_t mtx = {0};
  s21_create_matrix(rows1, cols1, &mtx);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  if (m.matrix != NULL && mtx.matrix != NULL && check.matrix != NULL) {
    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), CALCULATION_ERROR);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

START_TEST(mult_matrix_6) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  if (m.matrix != NULL && mtx.matrix != NULL && check.matrix != NULL) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 3;
    m.matrix[0][2] = 4;
    m.matrix[1][0] = 5;
    m.matrix[1][1] = 6;
    m.matrix[1][2] = 7;

    mtx.matrix[0][0] = 6;
    mtx.matrix[1][0] = 7;
    mtx.matrix[2][0] = 8;
    check.matrix[0][0] = 65;
    check.matrix[1][0] = 128;

    matrix_t res = {0};
    int result = s21_mult_matrix(&m, &mtx, &res);
    printf("%d", result);
    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("\033[10;35;40m MULT MATRIX \033[0;0;0m\n");
  TCase *tc = tcase_create("mult_matrix");

  tcase_add_loop_test(tc, simple_mult, 0, 100);
  tcase_add_test(tc, mult_matrix_1);
  tcase_add_test(tc, mult_matrix_2);
  tcase_add_test(tc, mult_matrix_3);
  tcase_add_test(tc, mult_matrix_4);
  tcase_add_test(tc, mult_matrix_5);
  tcase_add_test(tc, mult_matrix_6);

  suite_add_tcase(s, tc);
  return s;
}
