#include "raylib.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_NUMBERS 150
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

typedef struct Number {
  int number;
  bool changed;
} Number;
Number *num_arr = NULL;

void drawGraphs(const Number *num_arr);
Number *bubbleSort(Number *num_arr);
void quickSort(Number *num_arr, int lo_idx, int hi_idx);

int main(int argc, char **argv) {
  srand(time(0));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World!");
  SetTargetFPS(60);
  num_arr = malloc(NUM_NUMBERS * sizeof(Number));

  for (int i = 0; i < NUM_NUMBERS; i++) {
    num_arr[i].number = rand() % SCREEN_HEIGHT;
  }

  if (argc == 1) {
    char *argument = argv[0];
    printf("argument %s", argument);
    strcmp(argument, "quick") == 0 ? quickSort(num_arr, 0, NUM_NUMBERS - 1)
                                   : bubbleSort(num_arr);

  } else {
    quickSort(num_arr, 0, NUM_NUMBERS - 1);
  }

  CloseWindow(); // Close the window when the loop exits
  return 0;
}

Number *bubbleSort(Number *num_arr) {
  Number curr_num = {};
  Number curr_num_2 = {};
  for (int i = 0; i < NUM_NUMBERS; i++) {
    for (int j = 0; j < NUM_NUMBERS; j++) {
      if (num_arr[j].number > num_arr[i].number) {
        int tmp = num_arr[i].number;
        num_arr[i].number = num_arr[j].number;
        num_arr[j].number = tmp;
        num_arr[i].changed = true;
        num_arr[j].changed = true;
        drawGraphs(num_arr);
        num_arr[i].changed = false;
        num_arr[j].changed = false;
      }
    }
  }
  return num_arr;
}

int quickSort_partition(Number *num_arr, int lo_idx, int hi_idx);
void print_arr(const Number *num_arr);

void quickSort(Number *num_arr, int lo_idx, int hi_idx) {

  if (lo_idx >= hi_idx) {
    return;
  }
  int pivot = quickSort_partition(num_arr, lo_idx, hi_idx);

  quickSort(num_arr, lo_idx, pivot - 1);
  quickSort(num_arr, pivot + 1, hi_idx);
}

int quickSort_partition(Number *num_arr, int lo_idx, int hi_idx) {
  int pivot = num_arr[hi_idx].number;
  int idx = (lo_idx - 1);

  for (int i = lo_idx; i < hi_idx; i++) {
    if (num_arr[i].number <= pivot) {
      idx++;
      int tmp = num_arr[idx].number;
      num_arr[idx].number = num_arr[i].number;
      num_arr[i].number = tmp;

      num_arr[idx].changed = true;
      num_arr[i].changed = true;
      drawGraphs(num_arr);

      num_arr[idx].changed = false;
      num_arr[i].changed = false;
    }
  }

  idx++;
  num_arr[hi_idx].number = num_arr[idx].number;
  num_arr[idx].number = pivot;

  return idx;
}

void print_arr(const Number *num_arr) {
  for (int i = 0; i < NUM_NUMBERS; i++) {
    printf("%d - ", num_arr[i].number);
  }
  printf("\n");
}

void drawGraphs(const Number *num_arr) {
  BeginDrawing();
  ClearBackground(BLUE);

  int width_occupied = 0;
  int block_width = SCREEN_WIDTH / NUM_NUMBERS;
  for (int i = 0; i < NUM_NUMBERS; i++) {
    Rectangle r = {width_occupied, SCREEN_HEIGHT - num_arr[i].number,
                   block_width, num_arr[i].number};
    Color c = num_arr[i].changed ? GREEN : RED;
    DrawRectangleRec(r, c);
    width_occupied += block_width;
  }

  EndDrawing();
}
