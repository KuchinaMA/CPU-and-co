#include <stdio.h>
#include <stdlib.h>
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

    int *codeArr = (int*)calloc(MAX_ARR_LEN, sizeof(int));
    int position = 0;

    char line[MAX_LINE_LEN] = "";

    while (fscanf(input, "%s", line) > 0) {   //макс длина сканфа!!!

        if (strcmp(line, "push") == 0) {

            codeArr[position++] = PUSH;

            elem_t number = 0;
            fscanf(input, ELEMF, &number);

            codeArr[position++] = number;
        }


        else if (strcmp(line, "push_r") == 0) {

            codeArr[position++] = PUSH_R;

            char reg[MAX_LINE_LEN] = "";
            fscanf(input, "%s", reg);

            print_reg(reg, codeArr, position++);
        }

        else if (strcmp(line, "pop") == 0) {

            codeArr[position++] = POP;

            char reg[MAX_LINE_LEN] = "";
            fscanf(input, "%s", reg);

            print_reg(reg, codeArr, position++);
        }

        else if (strcmp(line, "add") == 0)    codeArr[position++] = ADD;

        else if (strcmp(line, "sub") == 0)    codeArr[position++] = SUB;

        else if (strcmp(line, "mul") == 0)    codeArr[position++] = MUL;

        else if (strcmp(line, "div") == 0)    codeArr[position++] = DIV;

        else if (strcmp(line, "out") == 0)    codeArr[position++] = OUT;

        else if (strcmp(line, "in")  == 0)    codeArr[position++] = IN;

        else if (strcmp(line, "hlt") == 0)    codeArr[position++] = HLT;

        else {
            printf("Compilation failed: incorrect command\n"); //fprintf stderr
            return IncorrectCommand;
        }
    }

    fprintf(output, "%d \n", position);
    for (int i = 0; i < position; i++) {
        fprintf(output, "%d \n", codeArr[i]);
    }

    free(codeArr);

    return NoErrors;
}


int check_file(FILE* input, FILE* output) {

    int version = 0;
    fscanf(input, "%d", &version);

    char sign[MAX_LINE_LEN] = "";
    fscanf(input, "%s", sign);


    if (version != ComplierVersion) {
        printf("Сompiler and data versions do not match\n");
        return 1;  //В будущем какая-то ошибка
    }

    else if (strcmp(sign, Signature) != 0) {
        printf("Incorrect signature\n");
        return 1; //тоже должна быть ошибка
    }

    else {
        //fprintf(output, "%d\n", version);
        //fprintf(output, Signature);
        //fprintf(output, "\n");
        return NoErrors;
    }
}




int print_reg(char* line, int* codeArr, int position) {

    if (strcmp(line, "rax") == 0)      codeArr[position] = RAX;

    else if (strcmp(line, "rbx") == 0) codeArr[position] = RBX;

    else if (strcmp(line, "rcx") == 0) codeArr[position] = RCX;

    else printf("Incorrect register");

    return NoErrors;
}


