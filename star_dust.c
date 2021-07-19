#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void bytes(int n, int *v) { // extrage biti din numar
  for (int i = 0; i < 4; i++) {
    v[i] = ((n >> (8 * i)) & 0xFF);
  }
}
int closest_multiple(int x) { //
  while (x % 4) {
    x++;
  }
  return x;
}
void number(char **m, int i, int j) { // construieste un numar din biti
  char *v = (char *)malloc(4 * sizeof(char));
  for (int k = 0; k < 4; k++) {
    v[k] = m[i][j + k];
  }
  int *numar = (int *)v;
  printf("%08X ", *numar);
  free(v);
}
double bytes_ext(char **m, int n, int *c) { // calculeaza suma de biti
  double s = 0, nr = 0;
  int *v = (int *)malloc(4 * sizeof(int));
  for (int i = 0; i < c[0] * 4; i++) {
    s = s + m[0][i];
    nr++;
  }
  for (int i = 0; i < c[n - 1] * 4; i++) {
    s = s + m[n - 1][i];
    nr++;
  }
  for (int i = 1; i < n - 1; i++) {
    s = s + m[i][0];
    nr++;
  }
  for (int i = 1; i < n - 1; i++) {
    s = s + m[i][c[i] * 4 - 1];
    nr++;
  }
  free(v);
  return s / nr;
}
void delete(char **m, char x, int lin, int col) { // operatia delete
  int k;
  if (x == 'I') {
    k = 4;
    m[lin][col * k - 1] = 0;
    m[lin][col * k - 2] = 0;
    m[lin][col * k - 3] = 0;
    m[lin][col * k - 4] = 0;
  } else if (x == 'S') {
    k = 2;
    m[lin][col * k - 1] = 0;
    m[lin][col * k - 2] = 0;
  } else if (x == 'C') {
    k = 1;
    m[lin][col * k - 1] = 0;
  }
}
void swap(char **m, char x, int lin, int col) { // operatia swap
  int k;
  if (x == 'I') {
    k = 4;
    int i = col * k;
    char aux = m[lin][i];
    m[lin][i] = m[lin][i + 3];
    m[lin][i + 3] = aux;
    char aux2 = m[lin][i + 1];
    m[lin][i + 1] = m[lin][i + 2];
    m[lin][i + 2] = aux2;
  } else if (x == 'S') {
    k = 2;
    int i = col * k;
    char aux = m[lin][i];
    m[lin][i] = m[lin][i + 1];
    m[lin][i + 1] = aux;
  }
}
void modify(char **m, int *c, char data, int lin, int col, int nr) {
  int v[4] = {0}, k;
  bytes(nr, v);
  if (data == 'I') {
    k = 4;
    if (c[lin] * 4 >= col * k) {
      m[lin][(col - 1) * k + 0] = v[0];
      m[lin][(col - 1) * k + 1] = v[1];
      m[lin][(col - 1) * k + 2] = v[2];
      m[lin][(col - 1) * k + 3] = v[3];
    } else {
      m[lin] = (char *)realloc(m[lin], (col * k) * sizeof(char));
      for (int i = c[lin] * 4; i < col * k; i++) {
        m[lin][i] = 0;
      }
      c[lin] = col;
      m[lin][(col - 1) * k + 0] = v[0];
      m[lin][(col - 1) * k + 1] = v[1];
      m[lin][(col - 1) * k + 2] = v[2];
      m[lin][(col - 1) * k + 3] = v[3];
    }
  } else if (data == 'S') {
    k = 2;
    if (c[lin] * 4 >= col * k) {
      m[lin][col * k - 2] = v[0];
      m[lin][col * k - 1] = v[1];

    } else {
      if (col % 2 == 0) {
        m[lin] = (char *)realloc(m[lin], (col * k) * sizeof(char));
        for (int i = c[lin] * 4; i < col * k; i++) {
          m[lin][i] = 0;
        }
        c[lin] = col * k / 4;
        m[lin][col * k - 2] = v[0];
        m[lin][col * k - 1] = v[1];
      } else {
        m[lin] = (char *)realloc(m[lin], ((col + 1) * k) * sizeof(char));
        for (int i = c[lin] * 4; i < (col + 1) * k; i++) {
          m[lin][i] = 0;
        }
        c[lin] = (col + 1) * 2 / 4;
        m[lin][col * k - 2] = v[0];
        m[lin][col * k - 1] = v[1];
      }
    }

  } else if (data == 'C') {
    k = 1;
    if (c[lin] * 4 >= col) {
      m[lin][col - 1] = v[0];
    } else {
      m[lin] =
          (char *)realloc(m[lin], closest_multiple(col * k) * sizeof(char));
      for (int i = c[lin] * 4; i < closest_multiple(col * k); i++) {
        m[lin][i] = 0;
      }
      c[lin] = closest_multiple(col * k) / 4;
      m[lin][col - 1] = v[0];
    }
  }
} // operatia modify
void black_hole(int i, int j, char **m, int n, int *c, int *z) {
  m[i][j] = 1;
  (*z)++;
  int i2, j2;
  i2 = i + 0;
  j2 = j + 1;
  if ((i2 >= 0) && (i2 < n) && (j2 >= 0) && (j2 < c[i2] * 4) &&
      m[i2][j2] == 0) {
    black_hole(i2, j2, m, n, c, z);
  }
  i2 = i + 0;
  j2 = j - 1;
  if ((i2 >= 0) && (i2 < n) && (j2 >= 0) && (j2 < c[i2] * 4) &&
      m[i2][j2] == 0) {
    black_hole(i2, j2, m, n, c, z);
  }

  i2 = i + 1;
  j2 = j + 0;
  if ((i2 >= 0) && (i2 < n) && (j2 >= 0) && (j2 < c[i2] * 4) &&
      m[i2][j2] == 0) {
    black_hole(i2, j2, m, n, c, z);
  }

  i2 = i - 1;
  j2 = j + 0;
  if ((i2 >= 0) && (i2 < n) && (j2 >= 0) && (j2 < c[i2] * 4) &&
      m[i2][j2] == 0) {
    black_hole(i2, j2, m, n, c, z);
  }
} // calculeza masivitatea gaurilor negre
int main() {
  char **m, u1, u2, operation, data;
  int n, nr, a, k = 0, *v, *c, x, lin, col, nr_op;
  scanf("%d", &n);
  m = (char **)malloc(n * sizeof(char *));
  c = (int *)malloc(n * sizeof(int));
  v = (int *)malloc(4 * sizeof(int));
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    c[k] = x;
    m[i] = (char *)malloc((x * 4) * sizeof(char));
    for (int j = 0; j < x * 4; j += 4) {
      scanf("%X", &a);
      bytes(a, v);
      m[i][j] = v[0];
      m[i][j + 1] = v[1];
      m[i][j + 2] = v[2];
      m[i][j + 3] = v[3];
    }
    k++;
  }
  printf("task 1\n");
  double m_a = bytes_ext(m, n, c);
  printf("%0.8f\n", m_a);
  printf("task 2\n");
  scanf("%d", &nr_op);
  for (int i = 0; i < nr_op; i++) {
    scanf("%c", &u1);
    scanf("%c", &operation);
    if (operation == 'S') {
      scanf("%c", &u2);
      scanf("%c", &data);
      scanf("%d%d", &lin, &col);
      swap(m, data, lin, col);
    } else if (operation == 'D') {
      scanf("%c", &u2);
      scanf("%c", &data);
      scanf("%d%d", &lin, &col);
      delete (m, data, lin, col);
    } else if (operation == 'M') {
      scanf("%c", &u2);
      scanf("%c", &data);
      scanf("%d%d", &lin, &col);
      scanf("%X", &nr);
      modify(m, c, data, lin, col, nr);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < c[i] * 4; j += 4) {
      number(m, i, j);
    }
    printf("\n");
  }
  printf("task 3\n");
  int imin, jmin, masivitate = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < c[i] * 4; j++) {
      if (m[i][j] == 0) {
        int y = 0;
        black_hole(i, j, m, n, c, &y);
        if (y > masivitate) {
          masivitate = y;
          imin = i;
          jmin = j;
        }
      }
    }
  }
  printf("%d %d %d\n", imin, jmin, masivitate);
  for (int i = 0; i < n; i++) {
    free(m[i]);
  }
  free(m);
  free(c);
  free(v);
  return 0;
}
