#include <stdio.h>

#define MEMORY_SIZE 200
#define NUM_PRINTABLE_CHARACTERS 38
#define OUTPUT_WINDOW 9

typedef signed char byte;

char bscii_to_char(byte bscii) {
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

int main() {
    byte memory[MEMORY_SIZE] = {0};

    // We would not have this two pass thing because robot can read same thing again
    char instructions[1000]; 
    int num_instructions = fread(instructions, sizeof(char), 1000, stdin);

    int data_pointer = 0;
    int inst_pointer = 0;
    
    while (inst_pointer < num_instructions)  {
        char c = instructions[inst_pointer];
        if (c == '+') {
            memory[data_pointer]++;
        } else if (c == '-') {
            memory[data_pointer]--;
        } else if (c == '>') {
            data_pointer = (data_pointer + 1) % MEMORY_SIZE;
        } else if (c == '<') {
            data_pointer = (data_pointer - 1) % MEMORY_SIZE;
        } else if (c == '[') {
            if (memory[data_pointer] == 0) {
                int opens = 1;
                do {
                    inst_pointer++;
                    if (instructions[inst_pointer] == '[') {
                        opens++;
                    } else if (instructions[inst_pointer] == ']') {
                        opens--;
                    }
                } while (opens > 0);
            }
        } else if (c == ']') {
            if (memory[data_pointer] != 0) {
                int closes = 1;
                do {
                    inst_pointer--;
                    if (instructions[inst_pointer] == ']') {
                        closes++;
                    } else if (instructions[inst_pointer] == '[') {
                        closes--;
                    }
                } while (closes > 0);
            }
        } else if (c == '.') {
            printf("%c", bscii_to_char(memory[data_pointer]));
        } else if (c == ',') {
            printf("NOT IMPLEMENTED"); // Didn't implement because STDIN reached EOF
        }
        inst_pointer++;
    }

    for (int i = 0; i < OUTPUT_WINDOW; i++) {
        putchar(bscii_to_char(memory[i]));
    }

    return 0;
}
