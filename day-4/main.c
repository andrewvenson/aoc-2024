#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 141
#define FILE_BUFFER_READ 1
#define XMAS_SIZE 4

int is_pagan_mas(char pagan[BUFFER_SIZE][BUFFER_SIZE], int *occ_found, int x_c,
                 int y_c) {
  if (x_c >= 2 && x_c <= BUFFER_SIZE - 4 && y_c <= BUFFER_SIZE - 4 &&
      y_c >= 2) {
    if (pagan[x_c][y_c] == 'A') {
      int m = 0;
      int s = 0;

      // check upper right
      if (pagan[x_c - 1][y_c + 1] == 'M' || pagan[x_c - 1][y_c + 1] == 'S') {
        if (pagan[x_c - 1][y_c + 1] == 'M') {
          m += 1;
        } else {
          s += 1;
        }
      } else {
        return 1;
      }

      // check bottom left
      if (pagan[x_c + 1][y_c - 1] == 'M' || pagan[x_c + 1][y_c - 1] == 'S') {
        if (pagan[x_c - 1][y_c + 1] == 'M') {
          if (m != 0) {
            return 1;
          }
        }
        if (pagan[x_c - 1][y_c + 1] == 'S') {
          if (s != 0) {
            return 1;
          }
        }
      } else {
        return 1;
      }

      m = 0;
      s = 0;

      // check upper left
      if (pagan[x_c - 1][y_c - 1] == 'M' || pagan[x_c - 1][y_c - 1] == 'S') {
        if (pagan[x_c - 1][y_c - 1] == 'M') {
          m += 1;
        } else {
          s += 1;
        }
      } else {
        return 1;
      }

      // check bottom right
      if (pagan[x_c + 1][y_c + 1] == 'M' || pagan[x_c + 1][y_c + 1] == 'S') {
        if (pagan[x_c + 1][y_c + 1] == 'M') {
          if (m != 0) {
            return 1;
          } else {
            *occ_found += 1;
            return 0;
          }
        }
        if (pagan[x_c + 1][y_c + 1] == 'S') {
          if (s != 0) {
            return 1;
          } else {
            *occ_found += 1;
            return 0;
          }
        }
      }
    }
  }
  return 0;
}

void is_pagan_diag(char pagan[BUFFER_SIZE][BUFFER_SIZE], int *occ_found,
                   int x_c, int y_c) {
  // search diagonal down right
  if (x_c <= BUFFER_SIZE - 5 && y_c <= BUFFER_SIZE - 5) {
    if (pagan[x_c][y_c] == 'X') {
      if (pagan[x_c + 1][y_c + 1] == 'M') {
        if (pagan[x_c + 2][y_c + 2] == 'A') {
          if (pagan[x_c + 3][y_c + 3] == 'S') {
            *occ_found += 1;
          }
        }
      }
    }
  }
  // search diagonal down left
  if (x_c <= BUFFER_SIZE - 5 && y_c >= 3) {
    if (pagan[x_c][y_c] == 'X') {
      if (pagan[x_c + 1][y_c - 1] == 'M') {
        if (pagan[x_c + 2][y_c - 2] == 'A') {
          if (pagan[x_c + 3][y_c - 3] == 'S') {
            *occ_found += 1;
          }
        }
      }
    }
  }
  // search diagonal up left
  if (x_c >= 3 && y_c >= 3) {
    if (pagan[x_c][y_c] == 'X') {
      if (pagan[x_c - 1][y_c - 1] == 'M') {
        if (pagan[x_c - 2][y_c - 2] == 'A') {
          if (pagan[x_c - 3][y_c - 3] == 'S') {
            *occ_found += 1;
          }
        }
      }
    }
  }
  // search diagonal up right
  if (x_c >= 3 && y_c <= BUFFER_SIZE - 5) {
    if (pagan[x_c][y_c] == 'X') {
      if (pagan[x_c - 1][y_c + 1] == 'M') {
        if (pagan[x_c - 2][y_c + 2] == 'A') {
          if (pagan[x_c - 3][y_c + 3] == 'S') {
            *occ_found += 1;
          }
        }
      }
    }
  }
}

int is_pagan_mas_horiz(char *x, int *occ_found) {
  char prev_letter;
  for (int i = 0; i < XMAS_SIZE - 1; i++) {
    switch (i) {
    case 0:
      if (x[i] != 'M' && x[i] != 'S') {
        return 0;
      } else {
        prev_letter = x[i];
      }
      break;
    case 1:
      if (x[i] != 'M' && x[i] != 'A') {
        return 0;
      } else {
        if (prev_letter == 'M' && x[i] == 'A') {
          prev_letter = x[i];
        } else if (prev_letter == 'S' && x[i] == 'A') {
          prev_letter = x[i];
        } else {
          return 0;
        }
      }
      break;
    case 2:
      if (x[i] != 'S' && x[i] != 'M') {
        return 0;
      } else {
        if (prev_letter == 'A' && x[i] == 'S') {
          *occ_found += 1;
        } else if (prev_letter == 'A' && x[i] == 'M') {
          *occ_found += 1;
        }
      }
      return 0;
      break;
    default:
      return 0;
    }
  }
  return 0;
}

int is_pagan_horiz(char *x, int *occ_found) {
  char prev_letter;
  for (int i = 0; i < XMAS_SIZE; i++) {
    switch (i) {
    case 0:
      if (x[i] != 'X' && x[i] != 'S') {
        return 0;
      } else {
        prev_letter = x[i];
      }
      break;
    case 1:
      if (x[i] != 'M' && x[i] != 'A') {
        return 0;
      } else {
        if (prev_letter == 'X' && x[i] == 'M') {
          prev_letter = x[i];
        } else if (prev_letter == 'S' && x[i] == 'A') {
          prev_letter = x[i];
        } else {
          return 0;
        }
      }
      break;
    case 2:
      if (x[i] != 'A' && x[i] != 'M') {
        return 0;
      } else {
        if (prev_letter == 'M' && x[i] == 'A') {
          prev_letter = x[i];
        } else if (prev_letter == 'A' && x[i] == 'M') {
          prev_letter = x[i];
        } else {
          return 0;
        }
      }
      break;
    case 3:
      if (x[i] != 'S' && x[i] != 'X') {
        return 0;
      } else {
        if (prev_letter == 'A' && x[i] == 'S') {
          *occ_found += 1;
        } else if (prev_letter == 'M' && x[i] == 'X') {
          *occ_found += 1;
        }
      }
      return 0;
      break;
    default:
      return 0;
    }
  }
  return 0;
}

void process_pagans(char buffer[BUFFER_SIZE][BUFFER_SIZE], int *occ_found,
                    int diag, int pagan_mas, int pagan_mas_horiz) {
  for (int x = 0; x < BUFFER_SIZE - 1; x++) {
    for (int y = 0; y < BUFFER_SIZE; y++) {
      if (diag == 1) {
        is_pagan_diag(buffer, occ_found, x, y);
      }

      if (pagan_mas == 1) {
        is_pagan_mas(buffer, occ_found, x, y);
      }

      if (pagan_mas_horiz == 1) {
        is_pagan_mas_horiz(&buffer[x][y], occ_found);
      }

      // else {
      //   is_pagan_horiz(&buffer[x][y], occ_found);
      // }
    }
  }
}

void turn_buffer(char buffer[BUFFER_SIZE][BUFFER_SIZE],
                 char turned_buffer[BUFFER_SIZE][BUFFER_SIZE]) {
  for (int x = 0; x < BUFFER_SIZE - 1; x++) {
    for (int y = 0; y < BUFFER_SIZE; y++) {
      if (y == BUFFER_SIZE - 1) {
        turned_buffer[x][y] = '\n';
      } else {
        turned_buffer[x][y] = buffer[BUFFER_SIZE - (2 + y)][x];
      }
    }
  }
}

int main() {
  printf("Hello AoC - Day 4\n\n");
  char buffer[BUFFER_SIZE][BUFFER_SIZE];
  char turned_buffer[BUFFER_SIZE][BUFFER_SIZE];
  char file_buffer_read[FILE_BUFFER_READ];
  int occ_found = 0;

  for (int x = 0; x < BUFFER_SIZE; x++) {
    memset(buffer[x], 0, sizeof(buffer[x]));
  }

  FILE *file = fopen("pagan.txt", "r");

  if (!file) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  for (int x = 0; x < BUFFER_SIZE - 1; x++) {
    for (int y = 0; y < BUFFER_SIZE; y++) {
      memset(file_buffer_read, 0, sizeof(file_buffer_read));
      size_t ret =
          fread(file_buffer_read, sizeof(*file_buffer_read),
                sizeof(file_buffer_read) / sizeof(*file_buffer_read), file);

      if (ret != FILE_BUFFER_READ) {
        printf("fread ERROR!\n");
        exit(EXIT_FAILURE);
      }
      buffer[x][y] = file_buffer_read[0];
    }
  }

  memset(file_buffer_read, 0, sizeof(file_buffer_read));

  process_pagans(buffer, &occ_found, 0, 0, 1);
  turn_buffer(buffer, turned_buffer);
  process_pagans(turned_buffer, &occ_found, 0, 0, 1);
  process_pagans(turned_buffer, &occ_found, 0, 1, 0);

  printf("Found: %d\n\n", occ_found);
  fclose(file);
  exit(EXIT_SUCCESS);
}
