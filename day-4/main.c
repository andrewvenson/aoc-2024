#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 140
#define FILE_BUFFER_READ 1
#define XMAS_SIZE 4

int is_xmas_horiz(char *x, int *occ_found) {
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

int main() {
  printf("Hello AoC - Day 4\n\n");
  char buffer[BUFFER_SIZE][BUFFER_SIZE];
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

  for (int x = 0; x < BUFFER_SIZE; x++) {
    for (int y = 0; y < BUFFER_SIZE; y++) {
      memset(file_buffer_read, 0, sizeof(file_buffer_read));

      size_t ret =
          fread(file_buffer_read, sizeof(*file_buffer_read),
                sizeof(file_buffer_read) / sizeof(*file_buffer_read), file);

      if (ret != FILE_BUFFER_READ) {
        exit(EXIT_FAILURE);
      }
      buffer[x][y] = file_buffer_read[0];
    }
  }

  for (int x = 0; x < BUFFER_SIZE; x++) {
    for (int y = 0; y < BUFFER_SIZE; y++) {
      is_xmas_horiz(&buffer[x][y], &occ_found);
    }
  }

  printf("Found: %d\n\n", occ_found);

  fclose(file);
  exit(EXIT_SUCCESS);
}
