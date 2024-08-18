#include <stdio.h>

bool finished = false;

// Move forward until the bot gets to a new colour
Color next_color(Color current_color) {
  Color new_color;
  do {
    step();
    new_color = check_color();
  } while (new_color == current_color);
  return new_color;
}

// Move backward until the bot gets to a new colour
Color prev_color(Color current_color) {
  Color new_color;
  do {
    step_back();
    new_color = check_color();
  } while (new_color == current_color);
  return new_color;
}

void setup() {
  init_motors();
  init_colour_sensor();
  Serial.begin(9600); // debug
}

void loop() {
  if (finished) {
    return;
  }

  Color instruction_color = next_color(WHITE);
  finished = execute_instruction(instruction_color)
  if (!finished) {
    next_color(instruction_color); // assume this will return WHITE
  } else {
    debug_print_memory();
  }
}
