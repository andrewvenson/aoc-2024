#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MULTIPLIER_SIZE 12

int main() {
  printf("Hello aoc - Day 3\n\n");

  int char_count = 0;
  char buffer[BUFFER_SIZE];
  size_t buffer_size = sizeof(buffer) / sizeof(*buffer);

  memset(buffer, 0, sizeof(buffer));

  FILE *file = fopen("multiplier.txt", "r");

  if (!file) {
    perror("An error occurred during opening file");
    return EXIT_FAILURE;
  }

  while (char_count < 19928) {
    if (char_count + BUFFER_SIZE <= 19928 - BUFFER_SIZE) {
      size_t ret = fread(buffer, sizeof(*buffer), buffer_size, file);

      if (ret != buffer_size) {
        fprintf(stderr, "fread failed: %zu\n", ret);
        exit(EXIT_FAILURE);
      }

      int buffer_char_count = 0;

      char mul[MULTIPLIER_SIZE];
      int run_started = 0;

      while (buffer_char_count != BUFFER_SIZE) {
        if (buffer[buffer_char_count] == 'm' && run_started == 0) {
          mul[0] = 'm';
          run_started += 1;
          buffer_char_count += 1;
          continue;
        }

        if (run_started > 0) {
          switch (run_started) {
          case 1:
            if (buffer[buffer_char_count] != 'u') {
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              mul[1] = 'u';
              run_started += 1;
            }
            break;
          case 2:
            if (buffer[buffer_char_count] != 'l') {
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              mul[2] = 'l';
              run_started += 1;
            }
            break;
          case 3:
            if (buffer[buffer_char_count] != '(') {
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              mul[4] = '(';
              run_started += 1;
              for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                printf("%c", mul[x]);
              }
            }
            printf("\n\n");
            break;
          case 4:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 5:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 6:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 7:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 8:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 9:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 10:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 11:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          case 12:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
            break;
          default:
            run_started = 0;
            memset(mul, 0, sizeof(mul));
          }
        }

        buffer_char_count += 1;
      }

      memset(buffer, 0, sizeof(buffer));
      char_count += 1024;
    } else {
      break;
    }
  }

  fclose(file);

  exit(EXIT_SUCCESS);
}
