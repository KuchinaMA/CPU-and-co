#include <stdio.h>

#include "Types.h"
#include "Stack.h"
#include "Logfile.h"
#include "Protection.h"

#include "ReadCommands.h"

int main() {

    open_log("Stackerrors.log", __TIME__);

    struct Processor processor = {};

    STACK_CONSTRUCT(stk, StackDefaultCapacity);

    processor.stack = stk;

    //STACK_CONSTRUCT(processor.stack, StackDefaultCapacity);

    PRINT_STACK(&processor.stack);

    /*FILE *input = fopen("Source.txt", "r");
    FILE *output = fopen("MachineCode.txt", "w+");
    FILE *output1 = fopen("DecomplierTest.txt", "w");*/

    processor.input = fopen("Source1.txt", "r");
    processor.output = fopen("MachineCode1.txt", "w+");
    processor.dcoutput = fopen("DecomplierTest1.txt", "w");

    //complier(input, output);
    complier(&processor);

    fseek(processor.output, 0, SEEK_SET);
    decomplier(&processor);

    /*fseek(input, 0, SEEK_SET);
    read_commands(input, &stk);*/

    fseek(processor.output, 0, SEEK_SET);
    //cpu(processor.output, &processor.stack);
    cpu(&processor);

    fclose(processor.input);
    fclose(processor.output);
    fclose(processor.dcoutput);


    stack_dtor(&processor.stack);

    return 0;
}

