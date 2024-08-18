#include <stdio.h>

#define MEMORY_SIZE 200
#define NUM_PRINTABLE_CHARACTERS 38
#define OUTPUT_WINDOW 9 // for debug

int8_t memory[MEMORY_SIZE] = {0};
int data_pointer = 0;

char bscii_to_char(int8_t bscii) {
    bscii %= NUM_PRINTABLE_CHARACTERS;
    if (bscii < 0) {
        bscii += NUM_PRINTABLE_CHARACTERS;
    }
    if (bscii <= 9) {
        return bscii + '0';
    }
    if (bscii == 10) {
        return ':';
    }
    if (bscii == 11) {
        return ' ';
    }
    return bscii - 12 + 'a';
}

void move_to_matching_close() {
  int opens = 1;
  Color color = GREEN;
  do {
    color = next_color(color);
    if (color == GREEN) {
      opens++;
    } else if (color == MAGENTA) {
      opens--;
    }
  } while (opens > 0);
}

void move_to_matching_open() {
  int closes = 1;
  Color color = MAGENTA;
  do {
    color = prev_color(color);
    if (color == MAGENTA) {
      closes++;
    } else if (color == GREEN) {
      closes--;
    }
  } while (closes > 0);
}

bool execute_instruction(Color color) {
  switch (color) {
    case RED:
      memory[data_pointer]++;
      break;
    case YELLOW;
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

void debug_print_memory() {
  for (int i = 0; i < OUTPUT_WINDOW; i++) {
    Serial.print(bscii_to_char(memory[i]));
  }
}
