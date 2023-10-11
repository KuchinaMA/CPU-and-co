#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

    proc->output = fopen(file_name, "r");

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


/*int cpu(struct Processor *proc) {

    processor_verify(proc);

    int version = 0;
    fscanf(proc->output, "%d", &version);

    char sign[MAX_LINE_LEN] = "";
    fscanf(proc->output, "%s", sign);


    if (version != ProcessorVersion) printf("Processor and data versions do not match\n");

    else if (strcmp(sign, Signature) != 0) printf("Incorrect signature\n");

    else {

        int commands = 0;
        fscanf(proc->output, "%d", &commands);

        int current = 0;

        while (fscanf(proc->output, "%d", &current) > 0) {

            switch(current) {

                case PUSH: {

                    elem_t number = 0;
                    fscanf(proc->output, ELEMF, &number);
                    stack_push(&proc->stack, number);

                    //PRINT_STACK(&proc->stack);
                    break;
                }

                case PUSH_R: {

                    elem_t number = 0;
                    fscanf(proc->output, ELEMF, &number);
                    if (number == RAX || number == RBX || number == RCX)
                        stack_push(&proc->stack, proc->registers[number]);

                    else
                        printf("Incorrect register");

                    break;
                }

                case POP: {

                    elem_t number = 0;
                    fscanf(proc->output, ELEMF, &number);
                    if (number == RAX || number == RBX || number == RCX)
                        stack_pop(&proc->stack, &proc->registers[number]);

                    else
                        printf("Incorrect register");

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
    }
} */


int cpu(struct Processor *proc) {

    processor_verify(proc);

    int ncommands = 0;
    fscanf(proc->output, "%d", &ncommands);
    printf("%d\n", ncommands);

    //int* codeArr = (int*)calloc(ncommands, sizeof(int));
    //int f = fread(codeArr, ncommands, sizeof(int), proc->output);
    //printf("%d\n", f);
    //int codeArr[25] = {};

    int current = 0;

    /*for (size_t i = 0; i < ncommands; i++) {
        fscanf(proc->output, "%d", &codeArr[i]);
    }

    for (size_t i = 0; i < ncommands; i++) {
        printf("%d\n", codeArr[i]);
    }*/

    for (size_t i = 0; i < ncommands; i++) {

        fscanf(proc->output, "%d", &current);
        //current = codeArr[i];
        //printf("%d\n", current);

        switch(current) {

            case PUSH: {

                elem_t number = 0;
                fscanf(proc->output, ELEMF, &number);
                stack_push(&proc->stack, number);

                PRINT_STACK(&proc->stack);
                break;
            }

            case PUSH_R: {

                elem_t number = 0;
                fscanf(proc->output, ELEMF, &number);
                if (number == RAX || number == RBX || number == RCX)
                    stack_push(&proc->stack, proc->registers[number]);

                else
                    printf("Incorrect register\n");

                break;
            }

            case POP: {

                elem_t number = 0;
                fscanf(proc->output, ELEMF, &number);
                if (number == RAX || number == RBX || number == RCX)
                    stack_pop(&proc->stack, &proc->registers[number]);

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

                PRINT_STACK(&proc->stack);
                break;
            }

            case SUB: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first - second;
                stack_push(&proc->stack, newel);

                PRINT_STACK(&proc->stack);
                break;
            }

            case MUL: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first * second;
                stack_push(&proc->stack, newel);

                PRINT_STACK(&proc->stack);
                break;
            }

            case DIV: {

                elem_t second = 0;
                stack_pop(&proc->stack, &second);

                elem_t first = 0;
                stack_pop(&proc->stack, &first);

                elem_t newel = first / second;
                stack_push(&proc->stack, newel);

                PRINT_STACK(&proc->stack);
                break;
            }

            case OUT: {

                elem_t answer = 0;
                stack_pop(&proc->stack, &answer);
                printf("\n Answer: "ELEMF"\n", answer);

                PRINT_STACK(&proc->stack);
                break;
            }

            case IN: {

                elem_t number = 0;
                scanf(ELEMF, &number);
                stack_push(&proc->stack, number);

                PRINT_STACK(&proc->stack);
                break;
            }

            case HLT: {
                return NoErrors;
            }
        }
        processor_verify(proc);

    }

    //free(codeArr);
}
