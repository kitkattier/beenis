#include <stdio.h>

#define MEMORY_SIZE 200
#define NUM_PRINTABLE_CHARACTERS 38
#define OUTPUT_WINDOW 9 // for debug

int8_t memory[MEMORY_SIZE] = {0};
int data_pointer = 0;

void move_to_matching_close() {
  int opens = 1;
  do {
    step();
    i++;
    if (INSTRUCTIONS[i] == GREEN) {
        opens++;
    } else if (INSTRUCTIONS[i] == MAGENTA) {
        opens--;
    }
  } while (opens > 0);
}

void move_to_matching_open() {
  int closes = 1;
  do {
    step();
    i--;
    if (INSTRUCTIONS[i] == MAGENTA) {
      closes++;
    } else if (INSTRUCTIONS[i] == GREEN) {
      closes--;
    }
  } while (closes > 0);
}

bool execute_instruction(Color color) {
  switch (color) {
    case RED:
      memory[data_pointer]++;
      break;
    case YELLOW:
      memory[data_pointer]--;
      break;
    case CYAN:
      data_pointer = (data_pointer + 1) % MEMORY_SIZE;
      break;
    case BLUE:
      data_pointer = (data_pointer - 1) % MEMORY_SIZE;
      break;
    case GREEN:
      if (memory[data_pointer] == 0) {
        move_to_matching_close();
      }
      break;
    case MAGENTA:
      if (memory[data_pointer] != 0) {
        move_to_matching_open();
      }
      break;
    case BLACK:
      return true;
  }

  return false;
}

bool aaaaaaaaa() {
  return memory[0] == 0;
}


