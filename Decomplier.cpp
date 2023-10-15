#include <stdio.h>
#include <stdlib.h>
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

    int ncommands = 0;
    fread(&ncommands, sizeof(int), 1, input);
    fprintf(output, "Number of commands is %d\n\n", ncommands);

    //printf("%d\n", ncommands);
    int* codeArr = (int*)calloc(ncommands, sizeof(int));
    int f = fread(codeArr, sizeof(int), ncommands, input);

    int current = 0;

    for (size_t i = 0; i < ncommands; i++) {

        current = codeArr[i];

        //printf("%d\n", current);

        switch(current) {

            case PUSH: {

                fprintf(output, "push ");
                elem_t number = codeArr[i+1];
                i++;

                fprintf(output, ELEMF"\n", number);

                break;
            }

            case PUSH_R: {

                fprintf(output, "push_r ");
                elem_t number = codeArr[i+1];
                i++;

                print_reg(number, output);

                break;
            }

            case POP: {

                fprintf(output, "pop ");
                elem_t number = codeArr[i+1];
                i++;

                print_reg(number, output);

                break;
            }

            case ADD:  fprintf(output, "add\n");
                       break;


            case SUB:  fprintf(output, "sub\n");
                       break;


            case MUL:  fprintf(output, "mul\n");
                       break;


            case DIV:  fprintf(output, "div\n");
                       break;


            case SQRT: fprintf(output, "sqrt\n");
                       break;


            case POW:  fprintf(output, "pow\n");
                       break;




            case SIN:  fprintf(output, "sin\n");
                       break;


            case COS:  fprintf(output, "cos\n");
                       break;


            case TAN:  fprintf(output, "tan\n");
                       break;


            case CTG:  fprintf(output, "ctg\n");
                       break;




            case MEOW: fprintf(output, "meow\n");
                       break;


            case BARK: fprintf(output, "bark\n");
                       break;


            case DUCK: fprintf(output, "duck\n");
                       break;


            case BOO:  fprintf(output, "boo\n");
                       break;



            case SOLVE: fprintf(output, "solve\n");
                        break;


            case SLEEP: fprintf(output, "sleep\n");
                        break;


            case MATAN: fprintf(output, "matan\n");
                        break;



            case OUT:  fprintf(output, "out\n");
                       break;


            case IN:   fprintf(output, "in\n");
                       break;


            case HLT:  fprintf(output, "hlt\n");
                       break;


            default: {
                printf("Decompilation failed: incorrect command\n");
                return IncorrectCommand;
            }
        }
    }
    free(codeArr);
    return NoErrors;
}



int print_reg(int number, FILE* output) {
    if (number == RAX) fprintf(output,"rax \n");
    else if (number == RBX) fprintf(output, "rbx \n");
    else if (number == RCX) fprintf(output, "rcx \n");
    else {
        printf("Incorrect register");
        return IncorrectRegister;
    }
    return NoErrors;
}






















