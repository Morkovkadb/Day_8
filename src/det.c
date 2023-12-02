#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);
void input(double **matrix, int *n, int *m);
void output(double det);

int main() {
  int n, m;
  scanf("%d", &n);
  scanf("%d", &m);
  if (n != m) {
    printf("n/a");
    return 0;
  }
  double **matrix = (double **)malloc(sizeof(double *) * n);
  for (int i = 0; i < n; ++i) {
    matrix[i] = (double *)malloc(sizeof(double) * m);
  }

  input(matrix, &n, &m);
  output(det(matrix, n, m));
  for (int i = 0; i < n; ++i) {
    free(matrix[i]);
  }
  free(matrix);
}

double det(double **matrix, int n, int m) {
  double determinant = 0;

  if (n == 1 && m == 1) {
    return matrix[0][0];
  } else if (n == 2 && m == 2) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  } else if (n == 3 && m == 3) {
    return (matrix[0][0] * matrix[1][1] * matrix[2][2] +
            matrix[0][2] * matrix[1][0] * matrix[2][1] +
            matrix[0][1] * matrix[1][2] * matrix[2][0]) -
           (matrix[0][2] * matrix[1][1] * matrix[2][0] +
            matrix[0][0] * matrix[1][2] * matrix[2][1] +
            matrix[0][1] * matrix[1][0] * matrix[2][2]);
  }

  else {
    double **submatrix = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; ++i) {
      submatrix[i] = (double *)malloc(sizeof(double) * m);
    }

    for (int l = 0; l < n; ++l) {
      int i = 0, j = 0;

      for (int row = 1; row < n; ++row) {
        for (int column = 0; i < m; ++column) {
          if (column != i) {
            submatrix[i][j++] = matrix[row][column];
            if (j == n - 1) {
              j = 0;
              i++;
            }
          }
        }
      }

      determinant +=
          matrix[0][l] * (l % 2 == 0 ? 1 : -1) * det(submatrix, n - 1, m - 1);
    }
    for (int i = 0; i < n; ++i) {
      free(submatrix[i]);
    }

    free(submatrix);
  }
  return determinant;
}

void input(double **matrix, int *n, int *m) {
  for (int i = 0; i < *n; ++i) {
    for (int j = 0; j < *m; ++j) {
      scanf("%lf", &matrix[i][j]);
    }
  }
}

void output(double det) { printf("%.6lf", det); }
