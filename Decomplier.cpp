#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Types.h"
#include "Stack.h"
#include "Protection.h"
#include "ReadCommands.h"
#include "Decomplier.h"

int decomplier(FILE* input, FILE* output) {

    assert(input != NULL);
    assert(output != NULL);

    int current = 0;

    while (fscanf(input, "%d", &current) > 0) {

        switch(current) {

            case PUSH: {

                fprintf(output, "push ");

                elem_t number = 0;
                fscanf(input, ELEMF, &number);

                fprintf(output, ELEMF"\n", number);

                break;
            }

            case ADD: fprintf(output, "add\n");
                      break;


            case SUB: fprintf(output, "sub\n");
                      break;


            case MUL: fprintf(output, "mul\n");
                      break;


            case DIV: fprintf(output, "div\n");
                      break;


            case OUT: fprintf(output, "out\n");
                      break;


            case IN:  fprintf(output, "in\n");
                      break;


            case HLT: fprintf(output, "hlt\n");
                      break;

            default: {
                printf("Decompilation failled: incorrect command\n");
                return IncorrectCommand;
            }

        }
    }
    return NoErrors;
}
