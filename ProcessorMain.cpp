#include <stdio.h>

#include "Types.h"
#include "Logfile.h"
#include "Stack.h"
#include "Protection.h"

#include "ReadCommands.h"
#include "Processor.h"

int main() {

    open_log("Stackerrors.log", __TIME__);

    struct Processor processor = {};

    STACK_CONSTRUCT(stk, StackDefaultCapacity);

    processor.stack = stk;


    PRINT_STACK(&processor.stack);

    processor.output = fopen("MachineCode1.txt", "r");

    cpu(&processor);


    fclose(processor.output);


    stack_dtor(&processor.stack);

    return 0;
}
