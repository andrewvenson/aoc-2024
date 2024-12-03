#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_array(int *list, int list_size) {
  int sorted = 0;
  while (sorted == 0) {
    int shifted = 0;
    for (int x = 0; x < list_size; x++) {
      if ((x + 1) < list_size) {
        if (list[x] == 0) {
          int num0 = list[x];
          int num1 = list[x + 1];
          list[x] = num1;
          list[x + 1] = num0;
          shifted = 1;
        }
      }
      if (x == list_size - 1) {
        shifted = 0;
      }
    }
    if (shifted == 0) {
      sorted = 1;
    }
  }
}

void check_report(int *report, int report_size, int *report_unsafe) {
  int last_level = 0;
  int direction_set = 0;
  for (int y = 0; y < report_size; y++) {
    int level = report[y];
    if (level == 0) {
      break;
    }
    if (last_level == 0) {
      last_level = level;
      continue;
    }
    if (direction_set == 0) {
      if (level > last_level) {
        direction_set = 1;
      } else {
        direction_set = -1;
      }
    }
    if ((level < last_level && direction_set == 1) ||
        (level > last_level && direction_set == -1) ||
        abs(last_level - level) == 0 || abs(last_level - level) > 3) {
      *report_unsafe = 1;
      break;
    }
    last_level = level;
  }
}

void aoc(int reports[][10], int reports_size, int *safe_reports) {
  for (int x = 0; x < reports_size; x++) {
    int *report = reports[x];
    int report_size = 0;
    int report_unsafe = 0;
    int _report_size = sizeof(reports[x]) / sizeof(reports[x][0]);
    for (int y = 0; y < _report_size; y++) {
      if (report[y] == 0) {
        break;
      }
      report_size += 1;
    }
    check_report(report, report_size, &report_unsafe);
    if (report_unsafe == 0) {
      *safe_reports += 1;
      printf("\n\n");
    } else {
      int array[report_size][report_size];
      for (int level = 0; level < report_size; level++) {
        memset(array[level], 0, sizeof(array[level]));
        if (report[level] == 0) {
          break;
        }
        for (int y = 0; y < report_size; y++) {
          if (level == y) {
            continue;
          }
          if (report[y] == 0) {
            break;
          }
          array[level][y] = report[y];
        }
      }
      for (int z = 0; z < report_size; z++) {
        sort_array(array[z], report_size);
      }
      for (int test = 0; test < report_size; test++) {
        report_unsafe = 0;
        check_report(array[test], report_size, &report_unsafe);
        if (report_unsafe == 0) {
          *safe_reports += 1;
          break;
        }
      }
    }
  }
}

int main() {
  printf("Hello AoC - day 2\n\n");
  int reports[][10] = {{1, 2, 3}};
  int reports_size = sizeof(reports) / sizeof(reports[0]);
  int safe_reports = 0;
  aoc(reports, reports_size, &safe_reports);
  printf("safe_reports: %d\n\n", safe_reports);

  return 0;
}
