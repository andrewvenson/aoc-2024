#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 19928
#define MULTIPLIER_SIZE 12
#define DO_PROCESS_SIZE 7

int char_is_num(char character) {
  if (character == '1' || character == '2' || character == '3' ||
      character == '4' || character == '5' || character == '6' ||
      character == '7' || character == '8' || character == '9' ||
      character == '0') {
    return 1;
  }
  return 0;
}

int parse_mul(char *mul) {
  char num1[4];
  char num2[4];
  int nums_found = 0;
  int x = 0;
  int last_index = 0;
  // get num1
  while (nums_found != 1) {
    if (mul[x] == ',') {
      nums_found = 1;
      num1[x] = '\0';
      last_index = x + 1;
    } else {
      num1[x] = mul[x];
    }
    x++;
  }
  nums_found = 0;
  x = 0;
  // get num2
  while (nums_found != 1) {
    if (mul[last_index + x] == ')') {
      num2[x] = '\0';
      nums_found = 1;
    } else {
      num2[x] = mul[last_index + x];
    }
    x++;
  }
  int number1 = atoi(num1);
  int number2 = atoi(num2);
  return number1 * number2;
}

int should_process(char *process, int *do_process) {
  for (int x = 0; x < DO_PROCESS_SIZE; x++) {
    switch (x) {
    case 0:
      if (process[x] != 'd') {
        return 1;
      }
      break;
    case 1:
      if (process[x] != 'o') {
        return 1;
      }
      break;
    case 2:
      if (process[x] != 'n' && process[x] != '(') {
        return 1;
      }
      break;
    case 3:
      if (process[x] != '\'' && process[x] != ')') {
        return 1;
      }
      if (process[x] == ')') {
        *do_process = 1;
        return 0;
      }
      break;
    case 4:
      if (process[x] != 't') {
        return 1;
      }
      break;
    case 5:
      if (process[x] != '(') {
        return 1;
      }
      break;
    case 6:
      if (process[x] == ')') {
        *do_process = 0;
        return 0;
      }
      break;
    default:
      return 1;
    }
  }
  return 1;
}

void reset_vals(int *number_set_after_comma, int *comma_set, int *run_started,
                char *mul) {
  *number_set_after_comma = 0;
  *comma_set = 0;
  *run_started = 0;
  memset(mul, 0, sizeof(*mul));
}

void mul_delim_gen(char *buffer, int *buffer_char_count, int *comma_set,
                   int *run_started, char *mul, int *number_set_after_comma,
                   char letter, int index) {
  if (buffer[*buffer_char_count] != letter) {
    reset_vals(number_set_after_comma, comma_set, run_started, mul);
  } else {
    mul[index] = letter;
    *run_started += 1;
  }
}

int ending_delim_check(char *buffer, int *buffer_char_count,
                       int *number_set_after_comma, int *comma_set,
                       int *run_started, char *mul, int *result, int index) {
  if (buffer[*buffer_char_count] == ')') {
    if (*number_set_after_comma == 0) {
      reset_vals(number_set_after_comma, comma_set, run_started, mul);
      *buffer_char_count += 1;
      return 0;
    }
    if (*comma_set == 0) {
      reset_vals(number_set_after_comma, comma_set, run_started, mul);
      *buffer_char_count += 1;
      return 0;
    }
    mul[index] = buffer[*buffer_char_count];
    for (int x = 0; x < MULTIPLIER_SIZE; x++) {
      if (mul[x] == '(') {
        *result += parse_mul(&mul[x + 1]);
      }
    }
    reset_vals(number_set_after_comma, comma_set, run_started, mul);
    *buffer_char_count += 1;
    return 0;
  }
  return 1;
}

int mul_lex_gen(char *buffer, int *buffer_char_count, int *comma_set,
                int *number_set_after_comma, int *run_started, char *mul,
                int *result, int index) {
  if (char_is_num(buffer[*buffer_char_count]) == 1 ||
      buffer[*buffer_char_count] == ')' || buffer[*buffer_char_count] == ',') {
    if (buffer[*buffer_char_count] == ',') {
      if (*comma_set == 1) {
        reset_vals(number_set_after_comma, comma_set, run_started, mul);
        *buffer_char_count += 1;
        return 0;
      }
      *comma_set = 1;
    }
    if (ending_delim_check(buffer, buffer_char_count, number_set_after_comma,
                           comma_set, run_started, mul, result, index) == 0) {
      return 0;
    }
    if ((buffer[*buffer_char_count] != ')' ||
         buffer[*buffer_char_count] != ',') &&
        *comma_set == 1) {
      *number_set_after_comma = 1;
    }
    mul[index] = buffer[*buffer_char_count];
    *run_started += 1;
    return 1;
  }
  reset_vals(number_set_after_comma, comma_set, run_started, mul);
  return 0;
}

int main() {
  printf("Hello aoc - Day 3\n\n");

  int char_count = 0;
  char buffer[BUFFER_SIZE];
  size_t buffer_size = sizeof(buffer) / sizeof(*buffer);
  char mul[MULTIPLIER_SIZE];
  int run_started = 0;
  int comma_set = 0;
  int number_set_after_comma = 0;
  int result = 0;
  int do_process = 1;

  memset(buffer, 0, sizeof(buffer));

  FILE *file = fopen("multiplier.txt", "r");

  if (!file) {
    perror("An error occurred during opening file");
    return EXIT_FAILURE;
  }

  while (char_count < 19928) {
    if (char_count + BUFFER_SIZE <= 19928) {
      size_t ret = fread(buffer, sizeof(*buffer), buffer_size, file);

      if (ret != buffer_size) {
        fprintf(stderr, "fread failed: %zu\n", ret);
        exit(EXIT_FAILURE);
      }

      int buffer_char_count = 0;

      while (buffer_char_count != BUFFER_SIZE) {
        if (buffer[buffer_char_count] == 'd') {
          should_process(&buffer[buffer_char_count], &do_process);
        }

        if (do_process == 0) {
          reset_vals(&number_set_after_comma, &comma_set, &run_started, mul);
          buffer_char_count += 1;
          continue;
        }

        if (buffer[buffer_char_count] == 'm' && run_started == 0) {
          mul[0] = 'm';
          run_started += 1;
          buffer_char_count += 1;
          continue;
        }

        if (run_started > 0) {
          switch (run_started) {
          case 1:
            mul_delim_gen(buffer, &buffer_char_count, &comma_set, &run_started,
                          mul, &number_set_after_comma, 'u', 1);
            break;
          case 2:
            mul_delim_gen(buffer, &buffer_char_count, &comma_set, &run_started,
                          mul, &number_set_after_comma, 'l', 2);
            break;
          case 3:
            mul_delim_gen(buffer, &buffer_char_count, &comma_set, &run_started,
                          mul, &number_set_after_comma, '(', 3);
            break;
          case 4:
            if (char_is_num(buffer[buffer_char_count]) == 1) {
              mul[4] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              reset_vals(&number_set_after_comma, &comma_set, &run_started,
                         mul);
            }
            break;
          case 5:
            if (char_is_num(buffer[buffer_char_count]) == 1 ||
                buffer[buffer_char_count] == ',') {
              if (buffer[buffer_char_count] == ',') {
                comma_set = 1;
              }
              mul[5] = buffer[buffer_char_count];
              run_started += 1;
            } else {
              reset_vals(&number_set_after_comma, &comma_set, &run_started,
                         mul);
            }
            break;
          case 6:
            if (mul_lex_gen(buffer, &buffer_char_count, &comma_set,
                            &number_set_after_comma, &run_started, mul, &result,
                            6) == 0) {
              continue;
            }
            break;
          case 7:
            if (mul_lex_gen(buffer, &buffer_char_count, &comma_set,
                            &number_set_after_comma, &run_started, mul, &result,
                            7) == 0) {
              continue;
            }
            break;
          case 8:
            if (mul_lex_gen(buffer, &buffer_char_count, &comma_set,
                            &number_set_after_comma, &run_started, mul, &result,
                            8) == 0) {
              continue;
            }
            break;
          case 9:
            if (mul_lex_gen(buffer, &buffer_char_count, &comma_set,
                            &number_set_after_comma, &run_started, mul, &result,
                            9) == 0) {
              continue;
            }
            break;
          case 10:
            if (mul_lex_gen(buffer, &buffer_char_count, &comma_set,
                            &number_set_after_comma, &run_started, mul, &result,
                            10) == 0) {
              continue;
            }
            break;
          case 11:
            if (buffer[buffer_char_count] == ')') {
              if (ending_delim_check(buffer, &buffer_char_count,
                                     &number_set_after_comma, &comma_set,
                                     &run_started, mul, &result, 11) == 0) {
                continue;
              }
            } else {
              reset_vals(&number_set_after_comma, &comma_set, &run_started,
                         mul);
            }
            break;
          default:
            reset_vals(&number_set_after_comma, &comma_set, &run_started, mul);
          }
        }
        buffer_char_count += 1;
      }
      memset(buffer, 0, sizeof(buffer));
      char_count += BUFFER_SIZE;
    } else {
      break;
    }
  }

  printf("RESULT: %d\n\n", result);
  fclose(file);
  exit(EXIT_SUCCESS);
}
