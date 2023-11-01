#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0) return ERROR;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  int final = OK;
  if (final == OK) {
    for (int i = 0; i < rows && final == OK; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        s21_remove_matrix(result);
        final = ERROR;
      }
    }
    result->rows = rows;
    result->columns = columns;
  }
  return final;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    A->rows = 0;
    A->columns = 0;
    free(A->matrix);
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int final = SUCCESS;
  if ((A->rows == 0 && B->rows == 0) || (A->columns == 0 && B->columns == 0))
    final = SUCCESS;
  if ((A->rows != B->rows) || (A->columns != B->columns)) final = FAILURE;
  for (int i = 0; i < A->rows && final == SUCCESS; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) final = FAILURE;
    }
  }
  return final;
}
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sum_sub_matrix(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sum_sub_matrix(A, B, result, -1);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int final = s21_create_matrix(A->rows, A->columns, result);
  if (final == 0) {
    final = check_matrix(A);
    if ((A->rows != result->rows) || (A->columns != result->columns)) {
      final = ERROR;
    }
    if (final == OK) {
      for (int i = 0; i < A->rows && final == OK; i++) {
        for (int j = 0; j < A->columns && final == OK; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return final;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int final = 0;
  if (check_matrix(A) == 1 || check_matrix(B) == 1)
    final = ERROR;
  else if (check_matrix(A) == 2 || check_matrix(B) == 2)
    final = CALCULATION_ERROR;
  if (A->columns != B->rows) final = CALCULATION_ERROR;
  s21_create_matrix(A->rows, B->columns, result);
  if (result->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
        }
      }
    }
  }
  return final;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int final = OK;
  if (check_matrix(A) == OK &&
      s21_create_matrix(A->columns, A->rows, result) == OK) {
    if ((A->rows != result->columns) || (A->columns != result->rows))
      final = CALCULATION_ERROR;
    else if (final == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    final = check_matrix(A);
  }
  return final;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A->rows != A->columns) return CALCULATION_ERROR;
  int final = OK;
  if (check_matrix(A) == OK) {
    double det_result = 0.;
    s21_determinant(A, &det_result);
    if (det_result != 0.) {
      final = s21_create_matrix(A->rows, A->columns, result);
      if (A->rows == 1 && A->columns == 1 && result->matrix != NULL) {
        result->matrix[0][0] = det_result;
      } else if (result->matrix != NULL) {
        matrix_t temp = {0};
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
            s21_get_minor(A, &temp, i, j);
            s21_determinant(&temp, &det_result);
            result->matrix[i][j] = pow(-1, i + j) * det_result;
            s21_remove_matrix(&temp);
          }
        }
      }
    } else
      final = CALCULATION_ERROR;
  } else {
    final = check_matrix(A);
  }
  return final;
}

int s21_determinant(matrix_t *A, double *result) {
  int final = OK;
  final = check_matrix(A);
  if (final == OK && A->columns != A->rows) final = CALCULATION_ERROR;
  double det = 0.0;
  if (final == OK) {
    if (A->rows == 1) {
      det = A->matrix[0][0];
    } else {
      matrix_t minor = {0};
      for (int j = 0; j < A->columns; j++) {
        final = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        if (final == OK) {
          s21_get_minor(A, &minor, 0, j);
          double temp_det = 0.0;
          s21_determinant(&minor, &temp_det);
          int sign = ((j + 1) % 2 == 0) ? -1 : 1;
          det += sign * A->matrix[0][j] * temp_det;
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  *result = det;
  return final;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int final = OK;
  if (check_matrix(A) == OK) {
    double temp_determinant = 0;
    if (result != NULL && A->rows == A->columns &&
        s21_determinant(A, &temp_determinant) == OK && temp_determinant != 0) {
      matrix_t temp;
      final = s21_calc_complements(A, &temp);
      if (final == OK) {
        matrix_t transpose_t;
        final = s21_transpose(&temp, &transpose_t);
        s21_remove_matrix(&temp);
        if (final == OK) {
          s21_mult_number(&transpose_t, (1. / temp_determinant), result);
          s21_remove_matrix(&transpose_t);
        }
      }
    } else
      final = CALCULATION_ERROR;
  } else
    final = check_matrix(A);

  return final;
}
