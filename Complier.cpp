#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Types.h"
#include "Stack.h"
#include "Protection.h"
#include "ReadCommands.h"
#include "Complier.h"


#define DEF_CMD(name, number, argument)          \
    if (strcmp(line, #name) == 0) {              \
        codeArr[position++] = name;              \
        if (argument == NumArg) {                     \
        elem_t num = 0;                          \
            fscanf(input, ELEMF, &num);          \
            codeArr[position++] = num;           \
        }                                        \
        else if (argument == RegArg) {                \
            char reg[MAX_LINE_LEN] = "";         \
            fscanf(input, "%s", reg);            \
            print_reg(reg, codeArr, position++); \
        }                                        \
    }                                            \
    else



int complier(FILE* input, FILE* output) {

    assert(input != NULL);
    assert(output != NULL);

    check_file(input, output);

    int *codeArr = (int*)calloc(MAX_ARR_LEN, sizeof(int));
    int position = 0;

    char line[MAX_LINE_LEN] = "";

    while (fscanf(input, "%s", line) > 0) {   //макс длина сканфа!!!

        #include "Commands.h"

        /*else*/ {

            printf("Compilation failed: incorrect command\n"); //fprintf stderr
            return IncorrectCommand;
        }
    }

    fwrite(&position, sizeof(int), 1, output);
    fwrite(codeArr, sizeof(int), position, output);

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


