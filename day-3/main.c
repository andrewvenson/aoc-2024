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

  char mul[MULTIPLIER_SIZE];
  int run_started = 0;
  int comma_set = 0;
  int number_set_after_comma = 0;

  while (char_count < 19928) {
    if (char_count + BUFFER_SIZE <= 19928 - BUFFER_SIZE) {
      size_t ret = fread(buffer, sizeof(*buffer), buffer_size, file);

      if (ret != buffer_size) {
        fprintf(stderr, "fread failed: %zu\n", ret);
        exit(EXIT_FAILURE);
      }

      int buffer_char_count = 0;

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
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              mul[1] = 'u';
              run_started += 1;
            }
            break;
          case 2:
            if (buffer[buffer_char_count] != 'l') {
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              mul[2] = 'l';
              run_started += 1;
            }
            break;
          case 3:
            if (buffer[buffer_char_count] != '(') {
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              mul[3] = '(';
              run_started += 1;
            }
            break;
          case 4:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0') {
              mul[4] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 5:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0' ||
                buffer[buffer_char_count] == ',') {
              if (buffer[buffer_char_count] == ',') {
                comma_set = 1;
              }
              mul[5] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 6:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0' ||
                buffer[buffer_char_count] == ')' ||
                buffer[buffer_char_count] == ',') {

              if (buffer[buffer_char_count] == ',') {
                if (comma_set == 1) {
                  run_started = 0;
                  comma_set = 0;
                  number_set_after_comma = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                comma_set = 1;
              }

              if (buffer[buffer_char_count] == ')') {
                if (number_set_after_comma == 0) {
                  comma_set = 0;
                  run_started = 0;
                  number_set_after_comma = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }

                if (comma_set == 0) {
                  comma_set = 0;
                  run_started = 0;
                  number_set_after_comma = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }

                mul[6] = buffer[buffer_char_count];
                for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                  printf("%c", mul[x]);
                }

                printf("\n\n");

                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              if ((buffer[buffer_char_count] != ')' ||
                   buffer[buffer_char_count] != ',') &&
                  comma_set == 1) {
                number_set_after_comma = 1;
              }

              mul[6] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 7:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0' ||
                buffer[buffer_char_count] == ')' ||
                buffer[buffer_char_count] == ',') {

              if (buffer[buffer_char_count] == ',') {
                if (comma_set == 1) {
                  number_set_after_comma = 0;
                  run_started = 0;
                  comma_set = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                comma_set = 1;
              }

              if (buffer[buffer_char_count] == ')') {
                if (number_set_after_comma == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                if (comma_set == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                mul[7] = buffer[buffer_char_count];
                for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                  printf("%c", mul[x]);
                }
                printf("\n\n");
                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              if ((buffer[buffer_char_count] != ')' ||
                   buffer[buffer_char_count] != ',') &&
                  comma_set == 1) {
                number_set_after_comma = 1;
              }

              mul[7] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 8:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0' ||
                buffer[buffer_char_count] == ')' ||
                buffer[buffer_char_count] == ',') {

              if (buffer[buffer_char_count] == ',') {
                if (comma_set == 1) {
                  number_set_after_comma = 0;
                  run_started = 0;
                  comma_set = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                comma_set = 1;
              }

              if (buffer[buffer_char_count] == ')') {
                if (number_set_after_comma == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                if (comma_set == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                mul[8] = buffer[buffer_char_count];
                for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                  printf("%c", mul[x]);
                }
                printf("\n\n");
                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              if ((buffer[buffer_char_count] != ')' ||
                   buffer[buffer_char_count] != ',') &&
                  comma_set == 1) {
                number_set_after_comma = 1;
              }

              mul[8] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 9:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0' ||
                buffer[buffer_char_count] == ')' ||
                buffer[buffer_char_count] == ',') {

              if (buffer[buffer_char_count] == ',') {
                if (comma_set == 1) {
                  number_set_after_comma = 0;
                  run_started = 0;
                  comma_set = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                comma_set = 1;
              }

              if (buffer[buffer_char_count] == ')') {
                if (number_set_after_comma == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                if (comma_set == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                mul[9] = buffer[buffer_char_count];
                for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                  printf("%c", mul[x]);
                }
                printf("\n\n");
                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              if ((buffer[buffer_char_count] != ')' ||
                   buffer[buffer_char_count] != ',') &&
                  comma_set == 1) {
                number_set_after_comma = 1;
              }

              mul[9] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 10:
            if (buffer[buffer_char_count] == '1' ||
                buffer[buffer_char_count] == '2' ||
                buffer[buffer_char_count] == '3' ||
                buffer[buffer_char_count] == '4' ||
                buffer[buffer_char_count] == '5' ||
                buffer[buffer_char_count] == '6' ||
                buffer[buffer_char_count] == '7' ||
                buffer[buffer_char_count] == '8' ||
                buffer[buffer_char_count] == '9' ||
                buffer[buffer_char_count] == '0' ||
                buffer[buffer_char_count] == ')' ||
                buffer[buffer_char_count] == ',') {

              if (buffer[buffer_char_count] == ',') {
                if (comma_set == 1) {
                  number_set_after_comma = 0;
                  run_started = 0;
                  comma_set = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                comma_set = 1;
              }

              if (buffer[buffer_char_count] == ')') {
                if (number_set_after_comma == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                if (comma_set == 0) {
                  number_set_after_comma = 0;
                  comma_set = 0;
                  run_started = 0;
                  memset(mul, 0, sizeof(mul));
                  buffer_char_count += 1;
                  continue;
                }
                mul[10] = buffer[buffer_char_count];
                for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                  printf("%c", mul[x]);
                }
                printf("\n\n");
                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              if ((buffer[buffer_char_count] != ')' ||
                   buffer[buffer_char_count] != ',') &&
                  comma_set == 1) {
                number_set_after_comma = 1;
              }

              mul[10] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          case 11:
            if (buffer[buffer_char_count] == ')') {
              if (number_set_after_comma == 0) {
                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              if (comma_set == 0) {
                number_set_after_comma = 0;
                comma_set = 0;
                run_started = 0;
                memset(mul, 0, sizeof(mul));
                buffer_char_count += 1;
                continue;
              }

              mul[11] = buffer[buffer_char_count];

              for (int x = 0; x < MULTIPLIER_SIZE; x++) {
                printf("%c", mul[x]);
              }

              printf("\n\n");

              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            } else {
              number_set_after_comma = 0;
              comma_set = 0;
              run_started = 0;
              memset(mul, 0, sizeof(mul));
            }
            break;
          default:
            number_set_after_comma = 0;
            comma_set = 0;
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
