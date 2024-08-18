#include <stdio.h>
#include "color_reader.h"
#define SPEED 80

bool finished = false;

Color check_color_but_not_shit() {
    float drake[3];
    for (int i = 0; i < 3; i++) {
        drake[i] = int(g_array[i] * g_SF[i]);
    }
    return check_color(drake);
}

// Move forward until the bot gets to a new colour
Color next_color(Color current_color) {
  Color new_color;
  move_forward(SPEED, SPEED);
  do {
    new_color = check_color_but_not_shit();
  } while (new_color == current_color);
  brake();
  return new_color;
}

// Move backward until the bot gets to a new colour
Color prev_color(Color current_color) {
  Color new_color;
  move_backward(SPEED);
  do {
    new_color = check_color_but_not_shit();
  } while (new_color == current_color);
  brake();
  return new_color;
}

void setup() {
  init_movement();
  init_color_reader();
  Serial.begin(9600); // debug
}

void loop() {
  if (finished) {
    return;
  }

  Color instruction_color = next_color(WHITE);
  finished = execute_instruction(instruction_color);
  if (!finished) {
    next_color(instruction_color); // assume this will return WHITE
  } else {
    debug_print_memory();
  }
}
