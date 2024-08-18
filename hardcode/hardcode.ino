typedef enum {
  RED, BLUE, GREEN, YELLOW, WHITE, BLACK, MAGENTA, CYAN
} Color;

const Color INSTRUCTIONS[] = {RED, WHITE, RED, WHITE, RED, WHITE, RED, WHITE, RED, CYAN, RED, WHITE, RED, WHITE, RED, CYAN, RED, WHITE, RED, GREEN, YELLOW, BLUE, WHITE, BLUE, YELLOW, CYAN, WHITE, CYAN, MAGENTA, BLUE, GREEN, YELLOW, BLUE, YELLOW, CYAN, MAGENTA, BLACK};

int i = 0;

void setup() {
  init_movement();
}

void loop() {
  Color color = INSTRUCTIONS[i];
  if (color == BLACK) {
    if (aaaaaaaaa()) {
      step();
    }
    return;
  }

  execute_instruction(color);
  i++;
  step();
}
