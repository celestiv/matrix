#include "s21_test_matrix.h"

START_TEST(test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (codec == OK) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(3, 4, &m);
  if (codec == OK) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, CALCULATION_ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_normal) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);
  if (code1 == 0 && code2 == 0) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;

    m.matrix[1][0] = 0;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;

    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;

    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    int code = s21_calc_complements(&m, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
  }
}
END_TEST

START_TEST(calc_complements_1) {
  matrix_t matr1, matr2;
  int row = 3;
  int col = 3;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[0][2] = 3.0;

  matr1.matrix[1][0] = 0.0;
  matr1.matrix[1][1] = 4.0;
  matr1.matrix[1][2] = 2.0;

  matr1.matrix[2][0] = 5.0;
  matr1.matrix[2][1] = 2.0;
  matr1.matrix[2][2] = 1.0;

  int res = s21_calc_complements(&matr1, &matr2);
  int res_o = 0;
  ck_assert_int_eq(res, res_o);
  ck_assert_double_eq(matr2.matrix[0][0], 0.0);
  ck_assert_double_eq(matr2.matrix[0][1], 10.0);
  ck_assert_double_eq(matr2.matrix[0][2], -20.0);

  ck_assert_double_eq(matr2.matrix[1][0], 4.0);
  ck_assert_double_eq(matr2.matrix[1][1], -14.0);
  ck_assert_double_eq(matr2.matrix[1][2], 8.0);

  ck_assert_double_eq(matr2.matrix[2][0], -8.0);
  ck_assert_double_eq(matr2.matrix[2][1], -2.0);
  ck_assert_double_eq(matr2.matrix[2][2], 4.0);

  s21_remove_matrix(&matr1);
  s21_remove_matrix(&matr2);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t matr1, matr2;
  int row = 2;
  int col = 2;
  s21_create_matrix(row, col, &matr1);
  matr1.matrix[0][0] = 1.0;
  matr1.matrix[0][1] = 2.0;
  matr1.matrix[1][0] = 3.0;
  matr1.matrix[1][1] = 4.0;
  int res = s21_calc_complements(&matr1, &matr2);
  int res_o = OK;
  ck_assert_int_eq(res, res_o);
  s21_remove_matrix(&matr2);
  s21_remove_matrix(&matr1);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s =
      suite_create("\033[10;35;40m COMPLEMENT OF A MATRIX \033[0;0;0m\n");
  TCase *tc = tcase_create("calc_complements");

  tcase_add_loop_test(tc, test_normal, 0, 50);
  tcase_add_loop_test(tc, test_not_sqare, 0, 50);
  tcase_add_loop_test(tc, test_incorrect, 0, 50);
  tcase_add_loop_test(tc, test_one_by_one, 0, 50);
  tcase_add_loop_test(tc, calc_complements_1, 0, 50);
  tcase_add_loop_test(tc, calc_complements_2, 0, 50);

  suite_add_tcase(s, tc);
  return s;
}
