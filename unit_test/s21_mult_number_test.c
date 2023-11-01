#include "s21_test_matrix.h"

START_TEST(mult_number_1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  if (m.matrix != NULL && check.matrix != NULL) {
    double mult_number = get_rand(-10e5, 10e5);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
        check.matrix[i][j] = m.matrix[i][j] * mult_number;
      }
    }
    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

START_TEST(mult_number_2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  if (m.matrix != NULL && check.matrix != NULL) {
    double mult_number = get_rand(-10e5, 10e5);

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), ERROR);

    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
  }
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t m, matr_mult;
  double num = 2.0;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &m);
  if (m.matrix != NULL) {
    m.matrix[0][0] = 1.0;
    m.matrix[0][1] = 1.0;
    m.matrix[1][0] = 1.0;
    m.matrix[1][1] = 1.0;
    int res = s21_mult_number(&m, num, &matr_mult);
    int res_o = 0;
    ck_assert_int_eq(res, res_o);
    ck_assert_double_eq(matr_mult.matrix[0][0], 2.0);
    ck_assert_double_eq(matr_mult.matrix[0][1], 2.0);
    ck_assert_double_eq(matr_mult.matrix[1][0], 2.0);
    ck_assert_double_eq(matr_mult.matrix[1][1], 2.0);
    s21_remove_matrix(&m);
    s21_remove_matrix(&matr_mult);
  }
}
END_TEST

START_TEST(mult_number_4) {
  matrix_t m, matr_mult;
  double num = 2.0;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &m);
  if (m.matrix != NULL) {
    m.matrix[0][0] = 1.0;
    m.matrix[0][1] = 1.0;
    m.matrix[1][0] = 1.0;
    m.matrix[1][1] = 1.0;
    int res = s21_mult_number(&m, num, &matr_mult);
    int res_o = OK;
    ck_assert_int_eq(res, res_o);
    s21_remove_matrix(&m);
    s21_remove_matrix(&matr_mult);
  }
}
END_TEST

Suite *suite_mult_number_matrix(void) {
  Suite *s = suite_create("\033[10;35;40m MULT NUMBER MATRIX \033[0;0;0m\n");
  TCase *tc = tcase_create("mult_number_matrix");

  tcase_add_loop_test(tc, mult_number_1, 0, 100);
  tcase_add_loop_test(tc, mult_number_2, 0, 100);
  tcase_add_test(tc, mult_number_3);
  tcase_add_test(tc, mult_number_4);

  suite_add_tcase(s, tc);
  return s;
}
