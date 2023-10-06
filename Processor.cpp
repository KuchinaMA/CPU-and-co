#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Types.h"
#include "Stack.h"
#include "Protection.h"
#include "ReadCommands.h"
#include "Processor.h"


int cpu(struct Processor *proc) {

    assert(proc != 0);

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
    }
}
