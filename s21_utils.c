#include "s21_matrix.h"

int check_matrix(matrix_t *matrix_struct) {
  int result = OK;
  if (matrix_struct->matrix == NULL) result = ERROR;
  if (matrix_struct->rows < 0 || matrix_struct->columns < 0) result = ERROR;
  for (int i = 0; i < matrix_struct->rows && result == OK; i++) {
    for (int j = 0; j < matrix_struct->columns && result == OK; j++) {
      if (matrix_struct->matrix[i][j] == NAN) {
        result = CALCULATION_ERROR;
      }
    }
  }
  return result;
}

int s21_sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
  int final = s21_create_matrix(A->rows, A->columns, result);
  if (final == 0) {
    if (check_matrix(A) == 1 || check_matrix(B) == 1) final = ERROR;
    if (final == 0 && (check_matrix(A) == 2 || check_matrix(B) == 2))
      final = CALCULATION_ERROR;
    if (final == 0 && ((A->rows != B->rows) || (A->columns != B->columns)))
      final = CALCULATION_ERROR;
    if (final == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j] * sign;
        }
      }
    }
  } else {
    s21_remove_matrix(result);
  }
  return final;
}
void s21_get_minor(matrix_t *mat, matrix_t *temp, int ex_row, int ex_col) {
  int i = 0, j = 0;
  for (int row = 0; row < mat->rows; row++) {
    for (int col = 0; col < mat->columns; col++) {
      if (row != ex_row && col != ex_col) {
        temp->matrix[i][j] = mat->matrix[row][col];
        j++;
        if (j == mat->columns - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}
