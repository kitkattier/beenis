#include <stdio.h>

#define MEMORY_SIZE 200

typedef signed char byte;

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
            data_pointer++;
        } else if (c == '<') {
            data_pointer--;
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
            printf("%c", memory[data_pointer]);
        } else if (c == ',') {
            printf("NOT IMPLEMENTED"); // Didn't implement because STDIN reached EOF
        }
        inst_pointer++;
    }

    return 0;
}
