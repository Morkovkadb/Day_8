#include <stdio.h>

#define MAX_SIZE 10

double determinant(double matrix[MAX_SIZE][MAX_SIZE]) {
  return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

void solve_cramer(double coefficients[MAX_SIZE][MAX_SIZE], int m, int n) {
  double det_A = determinant(coefficients);

  double x[MAX_SIZE];

  for (int i = 0; i < m; i++) {
    double Ai[MAX_SIZE][MAX_SIZE];

    for (int j = 0; j < m; j++) {
      for (int k = 0; k < n; k++) {
        Ai[j][k] = coefficients[j][k];
      }
    }

    double det_Ai = determinant(Ai);
    x[i] = det_Ai / det_A;
  }

  printf("Решение:\n");
  for (int i = 0; i < m; i++) {
    printf("x%d = %f\n", i + 1, x[i]);
  }
}

int main() {
  int m;
  int n;
  double coefficients[MAX_SIZE][MAX_SIZE];

  scanf("%d", &m);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%lf", &coefficients[i][j]);
    }
  }

  solve_cramer(coefficients, m, n);

  return 0;
}