#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Types.h"
#include "Stack.h"
#include "Protection.h"
#include "ReadCommands.h"
#include "Decomplier.h"

#define DEF_CMD(name, number, argument, code)   \
    case name:                                  \
    fprintf(output, #name"\n");                 \
    if (argument > 0) {                         \
        elem_t num = codeArr[i+1];              \
        i++;                                    \
        if (argument == NumArg)                 \
            fprintf(output, ELEMF"\n", num);    \
        if (argument == RegArg)                 \
            print_reg(num, output);             \
        if (argument == JmpArg)                 \
            fprintf(output, ELEMF"\n", num);    \
    }                                           \
    break;


int decomplier(FILE* input, FILE* output) {

    assert(input != NULL);
    assert(output != NULL);

    int ncommands = 0;
    fread(&ncommands, sizeof(int), 1, input);
    fprintf(output, "Number of commands is %d\n\n", ncommands);

    //printf("%d\n", ncommands);
    int* codeArr = (int*)calloc(ncommands, sizeof(int));
    int f = fread(codeArr, sizeof(int), ncommands, input);

    int current = 0;

    for (size_t i = 0; i < ncommands; i++) {

        current = codeArr[i];

        switch(current) {

            #include "Commands.h"

            default: {
                printf("Decompilation failed: incorrect command\n");
                return IncorrectCommand;
            }
        }
    }
    free(codeArr);
    return NoErrors;
}

#undef DEF_CMD


int print_reg(int number, FILE* output) {
    if (number == RAX) fprintf(output,"rax \n");
    else if (number == RBX) fprintf(output, "rbx \n");
    else if (number == RCX) fprintf(output, "rcx \n");
    else if (number == RDX) fprintf(output, "rdx \n");
    else {
        printf("Incorrect register");
        return IncorrectRegister;
    }
    return NoErrors;
}






















