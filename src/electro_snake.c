#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **_matritsa_, int m, int n, int **result_matrix);
void sort_horizontal(int **_matritsa_, int m, int n, int **result_matrix);
void input(int **_matritsa_, int *m, int *n);
void output(int **_matritsa_, int m, int n);

int normalize_separator(char ch);

int *convert_matrix_to_vector(int **_matritsa_, int m, int n);

void sort(int *array, int size);

void run();

int main() {
  run();

  return 0;
}

void run() {
  int **_matritsa_, **result;
  int m, n;

  _matritsa_ = malloc(sizeof(int *));
  input(_matritsa_, &m, &n);
  int bad_output_m = m;

  if (n > 0 || n > 0) {

    result = malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i)
      result[i] = malloc(n * sizeof(int));

    sort_vertical(_matritsa_, m, n, result);
    output(result, m, n);

    printf("\n\n");

    sort_horizontal(_matritsa_, m, n, result);
    output(result, m, n);
    for (int i = 0; i < m; ++i)
      free(result[i]);
    free(result);
  } else
    printf("n/a");

  if (n > -1 && m > -1) {

    for (int i = 0; i < bad_output_m; ++i)
      free(_matritsa_[i]);
    free(_matritsa_);
  }
}

int normalize_separator(char ch) { return ch == ' ' || ch == '\n'; }

void input(int **_matritsa_, int *m, int *n) {
  int is_success = 1;
  if (!(scanf("%d", m) == 1 && getchar() == ' ' && scanf("%d", n) == 1 &&
        getchar() == '\n'))
    is_success = 0;
  if (!is_success) {
    *n = *m = 0;
    return;
  }

  _matritsa_ = realloc(_matritsa_, *m * sizeof(int *));
  for (int i = 0; i < *m; ++i)
    _matritsa_[i] = malloc(*n * sizeof(int));

  for (int i = 0; i < *m; ++i) {
    for (int j = 0; j < *n; ++j) {
      if (!(scanf("%d", &_matritsa_[i][j]) == 1 &&
            normalize_separator(getchar()))) {
        for (int i = 0; i < *m; ++i)
          free(_matritsa_[i]);
        free(_matritsa_);
        *n = *m = 0;
        return;
      }
    }
  }
}

void output(int **_matritsa_, int m, int n) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == m - 1 && j == n - 1)
        printf("%d", _matritsa_[i][j]);
      else if (j == n - 1)
        printf("%d\n", _matritsa_[i][j]);
      else
        printf("%d ", _matritsa_[i][j]);
    }
  }
}

void sort_vertical(int **_matritsa_, int m, int n, int **result_matrix) {
  int *vec = convert_matrix_to_vector(_matritsa_, m, n);
  sort(vec, m * n);
  int k = 0;
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < m; ++i) {
      if (j % 2 == 0)
        result_matrix[i][j] = vec[k++];
      else
        result_matrix[m - 1 - i][j] = vec[k++];
    }
  }
  free(vec);
}

void sort_horizontal(int **_matritsa_, int m, int n, int **result_matrix) {
  int *vec = convert_matrix_to_vector(_matritsa_, m, n);
  sort(vec, m * n);
  int k = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i % 2 == 0)
        result_matrix[i][j] = vec[k++];
      else
        result_matrix[i][n - j - 1] = vec[k++];
    }
  }
  free(vec);
}

int *convert_matrix_to_vector(int **_matritsa_, int m, int n) {

  int *vec = (int *)malloc(n * m * sizeof(int));

  int k = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      vec[k++] = _matritsa_[i][j];
    }
  }

  return vec;
}

void sort(int *array, int size) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - i - 1; ++j) {
      if (array[j] > array[j + 1]) {
        int tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
    }
  }
}