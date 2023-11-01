#include "s21_test_matrix.h"

START_TEST(sum_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  int status1 = s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  int status2 = s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  int status3 = s21_create_matrix(rows, cols, &check);
  if (status1 == OK && status2 == OK && status3 == OK) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
        mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
        check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
      }
    }
    matrix_t res = {0};

    ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

START_TEST(sum_matrix1) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  int status1 = s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  int status2 = s21_create_matrix(rows1, cols1, &mtx);

  if (status1 == OK && status2 == OK) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
      }
    }
    for (int i = 0; i < rows1; i++) {
      for (int j = 0; j < cols1; j++) {
        mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      }
    }

    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), CALCULATION_ERROR);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
  }
}
END_TEST

START_TEST(sum_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  int status1 = s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  int status2 = s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  int status3 = s21_create_matrix(rows, cols, &check);
  if (status1 == OK && status2 == OK && status3 == OK) {
    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), ERROR);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

Suite *suite_sum_matrix(void) {
  Suite *s = suite_create("\033[10;35;40m SUM MATRIX \033[0;0;0m\n");
  TCase *tc = tcase_create("sum_matrix");

  tcase_add_loop_test(tc, sum_matrix, 0, 50);
  tcase_add_loop_test(tc, sum_matrix1, 0, 50);
  tcase_add_loop_test(tc, sum_matrix2, 0, 50);

  suite_add_tcase(s, tc);
  return s;
}
