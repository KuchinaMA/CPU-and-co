//#include "ReadCommands.h"
//#define TX_USE_SPEAK
//#include"TXLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "Types.h"
#include "Logfile.h"
#include "Stack.h"
#include "Protection.h"
#include "ReadCommands.h"
#include "Processor.h"


int processor_ctor(struct Processor *proc, const char *file_name) {

    STACK_CONSTRUCT(stk, StackDefaultCapacity);
    proc->stack = stk;

    for (int i = 0; i < NumRegs; i++) {
        proc->registers[i] = 0;
    }

    proc->output = fopen(file_name, "rb");

    return NoErrors;
}

int processor_dtor(struct Processor *proc) {

    fclose(proc->output);

    for (int i = 0; i < NumRegs; i++) {
        proc->registers[i] = 0;
    }

    stack_dtor(&proc->stack);

    return NoErrors;
}

int processor_verify(struct Processor *proc) {


    STACK_VERIFY(&proc->stack);

    if (proc == NULL) {
        fprintf(LOG_FILE, "ERROR! Pointer to processor is NULL\n\n");
        return ProcessorNull;
    }

    if (proc->output == NULL) {
        fprintf(LOG_FILE, "ERROR! Pointer to output file is NULL\n\n");
        return OutputNull;
    }

    return NoErrors;
}

int processor_dump(struct Processor *proc, const char *file, int line, const char *function, FILE* fp) {

    stack_dump(&proc->stack, file, line, function, fp);

    for (int i = 0; i < NumRegs; i++) {
        fprintf(stdout, "rax = %d\n", proc->registers[i]);
    }
}


int cpu(struct Processor *proc) {

    processor_verify(proc);

    int ncommands = 0;
    fread(&ncommands, sizeof(int), 1, proc->output);
    //printf("%d\n", ncommands);

    int* codeArr = (int*)calloc(ncommands, sizeof(int));
    int f = fread(codeArr, sizeof(int), ncommands, proc->output);
    //printf("%d\n", f);

    int current = 0;

    /*for (size_t i = 0; i < ncommands; i++) {
        printf("%d\n", codeArr[i]);
    } */

    for (size_t i = 0; i < ncommands; i++) {

        current = codeArr[i];

        switch(current) {

            case PUSH: {

                elem_t number = codeArr[i+1];
                i++;
                stack_push(&proc->stack, number);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case PUSH_R: {

                elem_t number = codeArr[i+1];
                if (number == RAX || number == RBX || number == RCX) {
                    stack_push(&proc->stack, proc->registers[number]);
                    i++;
                }
                else
                    printf("Incorrect register\n");

                break;
            }

            case POP: {

                elem_t number = codeArr[i+1];
                if (number == RAX || number == RBX || number == RCX) {
                    stack_pop(&proc->stack, &proc->registers[number]);
                    i++;
                }
                else
                    printf("Incorrect register\n");

                break;
            }

            case ADD: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first + second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case SUB: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first - second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case MUL: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first * second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case DIV: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first / second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case POW: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = pow(first,second);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }


            case SQRT: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = sqrt(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }



            case SIN: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = sin(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case COS: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = cos(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case TAN: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = tan(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case CTG: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = 1 / tan(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }


            case MEOW: {

                print_cat();
                break;
            }

            case BARK: {

                print_dog();
                break;
            }

            case DUCK: {

                print_duck();
                break;
            }

            case BOO: {

                print_boo();
                break;
            }


            /*case SOLVE: {

                txSpeak("ура! я умею считать дискриминант!");
                break;
            }

            case SLEEP: {

                txSpeak("хватит ботать, пора спать");
                break;
            }

            case MATAN: {

                txSpeak("сегодня не спим, матан сам себя не заботает");
                break;
            }*/



            case OUT: {

                elem_t answer = 0;
                stack_pop(&proc->stack, &answer);
                printf("\n Answer: "ELEMF"\n", answer);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case IN: {

                elem_t number = 0;
                scanf(ELEMF, &number);
                stack_push(&proc->stack, number);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case HLT: {
                return NoErrors;
            }
        }
        processor_verify(proc);

    }

    free(codeArr);
}


int print_cat() {

    printf(" /\\_/\\ \n( o.o )\n > ^ < \n");
    return 0;
}

int print_dog() {

    printf("           __\n      (___()'`;\n      /,    /`\n      \\\\\"--\\\n\n");
    return 0;
}

int print_duck() {

    printf("    __\n___( o)>\n\\ <_. )\n `---\'\n\n");
    return 0;
}

int print_boo() {

    printf(" .-.\n(o o) boo!\n| O \\\n \\   \\\n  `~~~'\n\n");
    return 0;
}



/*int cpu(struct Processor *proc) {

    processor_verify(proc);

    int ncommands = 0;
    fread(&ncommands, sizeof(int), 1, proc->output);
    //printf("%d\n", ncommands);

    int* codeArr = (int*)calloc(ncommands, sizeof(int));
    int f = fread(codeArr, sizeof(int), ncommands, proc->output);
    //printf("%d\n", f);

    int current = 0;

    /*for (size_t i = 0; i < ncommands; i++) {
        printf("%d\n", codeArr[i]);
    } */

    /*for (size_t i = 0; i < ncommands; i++) {

        current = codeArr[i];

        if (9 < current && current < 16) arithmetic(current, proc);

        else {

        switch(current) {

            case PUSH: {

                elem_t number = codeArr[i+1];
                i++;
                stack_push(&proc->stack, number);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case PUSH_R: {

                elem_t number = codeArr[i+1];
                if (number == RAX || number == RBX || number == RCX) {
                    stack_push(&proc->stack, proc->registers[number]);
                    i++;
                }
                else
                    printf("Incorrect register\n");

                break;
            }

            case POP: {

                elem_t number = codeArr[i+1];
                if (number == RAX || number == RBX || number == RCX) {
                    stack_pop(&proc->stack, &proc->registers[number]);
                    i++;
                }
                else
                    printf("Incorrect register\n");

                break;
            }

            case ADD: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first + second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case SUB: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first - second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case MUL: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first * second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case DIV: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first / second;
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case POW: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = pow(first,second);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }


            case SQRT: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = sqrt(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }



            case SIN: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = sin(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case COS: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = cos(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case TAN: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = tan(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case CTG: {

                elem_t number = 0;
                stack_pop(&proc->stack, &number);

                elem_t newel = 1 / tan(number);
                stack_push(&proc->stack, newel);

                //PRINT_STACK(&proc->stack);
                break;
            }


            case OUT: {

                elem_t answer = 0;
                stack_pop(&proc->stack, &answer);
                printf("\n Answer: "ELEMF"\n", answer);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case IN: {

                elem_t number = 0;
                scanf(ELEMF, &number);
                stack_push(&proc->stack, number);

                //PRINT_STACK(&proc->stack);
                break;
            }

            case HLT: {
                return NoErrors;
            }
            }
        }
        processor_verify(proc);

    }

    free(codeArr);
} */



/*int arithmetic(int current, struct Processor *proc) {

    elem_t second = 0;
    stack_pop(&proc->stack, &second);

    elem_t first = 0;
    stack_pop(&proc->stack, &first);

    elem_t newel = 0;

    switch(current) {

            case ADD:

                newel = first + second;
                break;

            case SUB:

                newel = first - second;
                break;

            case MUL:

                newel = first * second;
                break;

            case DIV:

                newel = first / second;
                break;

            case POW:

                newel = pow(first,second);
                break;
        }

    stack_push(&proc->stack, newel);
    return 0;
}*/
