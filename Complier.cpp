#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Types.h"
#include "Stack.h"
#include "Protection.h"
#include "ReadCommands.h"
#include "Complier.h"

int complier(FILE* input, FILE* output) {

    assert(input != NULL);
    assert(output != NULL);

    char line[MAX_LINE_LEN] = "";

    while (fscanf(input, "%s", line) > 0) {

        if (strcmp(line, "push") == 0) {

            fprintf(output, "%d ", PUSH);

            elem_t number = 0;
            fscanf(input, ELEMF, &number);

            fprintf(output, ELEMF"\n", number);

        }

        else if (strcmp(line, "add") == 0)    fprintf(output, "%d \n", ADD);

        else if (strcmp(line, "sub") == 0)    fprintf(output, "%d \n", SUB);

        else if (strcmp(line, "mul") == 0)    fprintf(output, "%d \n", MUL);

        else if (strcmp(line, "div") == 0)    fprintf(output, "%d \n", DIV);

        else if (strcmp(line, "out") == 0)    fprintf(output, "%d \n", OUT);

        else if (strcmp(line, "in")  == 0)    fprintf(output, "%d \n", IN);

        else if (strcmp(line, "hlt") == 0)    fprintf(output, "%d \n", HLT);

        else {
            printf("Compilation failled: incorrect command\n");
            return IncorrectCommand;
        }
    }

    return NoErrors;
}
