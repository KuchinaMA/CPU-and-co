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

    check_file(input, output);

    char line[MAX_LINE_LEN] = "";

    while (fscanf(input, "%s", line) > 0) {   //макс длина сканфа!!!

        if (strcmp(line, "push") == 0) {

            fprintf(output, "%d ", PUSH);

            elem_t number = 0;
            fscanf(input, ELEMF, &number);

            fprintf(output, ELEMF"\n", number);

        }


        else if (strcmp(line, "push_r") == 0) {

            fprintf(output, "%d ", PUSH_R);

            char reg[MAX_LINE_LEN] = "";
            fscanf(input, "%s", reg);

            print_reg(reg, output);

        }

        else if (strcmp(line, "pop") == 0) {

            fprintf(output, "%d ", POP);

            char reg[MAX_LINE_LEN] = "";
            fscanf(input, "%s", reg);

            print_reg(reg, output);

        }

        else if (strcmp(line, "add") == 0)    fprintf(output, "%d \n", ADD);

        else if (strcmp(line, "sub") == 0)    fprintf(output, "%d \n", SUB);

        else if (strcmp(line, "mul") == 0)    fprintf(output, "%d \n", MUL);

        else if (strcmp(line, "div") == 0)    fprintf(output, "%d \n", DIV);

        else if (strcmp(line, "out") == 0)    fprintf(output, "%d \n", OUT);

        else if (strcmp(line, "in")  == 0)    fprintf(output, "%d \n", IN);

        else if (strcmp(line, "hlt") == 0)    fprintf(output, "%d \n", HLT);

        else {
            printf("Compilation failed: incorrect command\n"); //fprintf stderr
            return IncorrectCommand;
        }
    }

    return NoErrors;
}


int check_file(FILE* input, FILE* output) {

    int version = 0;
    fscanf(input, "%d", &version);

    char sign[MAX_LINE_LEN] = "";
    fscanf(input, "%s", sign);


    if (version != ComplierVersion) {
        printf("Сompiler and data versions do not match\n");
        return 1;
    }

    else if (strcmp(sign, Signature) != 0) {
        printf("Incorrect signature\n");
        return 1;
    }

    else {
        fprintf(output, "%d\n", version);
        fprintf(output, Signature);
        fprintf(output, "\n");
        return NoErrors;
    }
}




int print_reg(char* line, FILE* output) {
    if (strcmp(line, "rax") == 0) fprintf(output, "%d \n", RAX);
    else if (strcmp(line, "rbx") == 0) fprintf(output, "%d \n", RBX);
    else if (strcmp(line, "rcx") == 0) fprintf(output, "%d \n", RCX);
    else printf("Incorrect register");
    return NoErrors;
}
