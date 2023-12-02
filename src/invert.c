#include <stdio.h>
#include <stdlib.h>
void invert(double **matrix, int n, int m);
void input(double **matrix, int *n, int *m);
void output(double **matrix, int n, int m);

int main() {
  int n, m;
  scanf("%d", &n);
  scanf("%d", &m);
  double **matrix = (double **)malloc(sizeof(double *) * n);
  for (int i = 0; i < n; ++i) {
    matrix[i] = (double *)malloc(sizeof(double) * m);
  }
  input(matrix, &n, &m);
  invert(matrix, n, m);

  for (int i = 0; i < n; ++i) {
    free(matrix[i]);
  }

  free(matrix);
}

void invert(double **matrix, int n, int m) {
  float augmentedMatrix[n][2 * n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      augmentedMatrix[i][j] = matrix[i][j];
      augmentedMatrix[i][j + n] = (i == j) ? 1.0 : 0.0;
    }
  }

  for (int i = 0; i < n; i++) {
    if (augmentedMatrix[i][i] == 0.0) {

      int j;
      for (j = i + 1; j < n; j++) {
        if (augmentedMatrix[j][i] != 0.0) {

          break;
        }
      }

      if (j == n) {
        printf("n/a");
        return;
      }

      for (int k = 0; k < 2 * n; k++) {
        float temp = augmentedMatrix[i][k];
        augmentedMatrix[i][k] = augmentedMatrix[j][k];
        augmentedMatrix[j][k] = temp;
      }
    }

    float pivot = augmentedMatrix[i][i];
    for (int k = 0; k < 2 * n; k++) {
      augmentedMatrix[i][k] /= pivot;
    }

    for (int j = 0; j < n; j++) {
      if (j != i) {
        float factor = augmentedMatrix[j][i];
        for (int k = 0; k < 2 * n; k++) {
          augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
        }
      }
    }
  }

  double **inverse = (double **)malloc(sizeof(double *) * n);
  for (int i = 0; i < n; ++i) {
    inverse[i] = (double *)malloc(sizeof(double) * m);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      inverse[i][j] = augmentedMatrix[i][j + n];
    }
  }
  output(inverse, n, m);

  for (int i = 0; i < n; ++i) {
    free(inverse[i]);
  }

  free(inverse);
}

void input(double **matrix, int *n, int *m) {
  for (int i = 0; i < *n; ++i) {
    for (int j = 0; j < *m; ++j) {
      scanf("%lf", &matrix[i][j]);
    }
  }
}
void output(double **matrix, int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; j++) {
      if (j != m - 1) {
        printf("%lf ", matrix[i][j]);
      } else {
        printf("%lf", matrix[i][j]);
      }
    }
    if (i != n - 1) {
      printf("\n");
    }
  }
}