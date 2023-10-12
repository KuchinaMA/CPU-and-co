#include <stdio.h>

#include "Types.h"
#include "Logfile.h"
#include "Stack.h"
#include "Protection.h"

//#include "ReadCommands.h"
#include "Processor.h"

int main() {

    open_log("Stackerrors.log", __TIME__);

    struct Processor processor = {};

    processor_ctor(&processor, "MachineCode2.bin");

    processor_dump(&processor, __FILE__, __LINE__, __func__, stdout);
    //PRINT_STACK(&processor.stack);

    cpu(&processor);

    //processor_dump(&processor, __FILE__, __LINE__, __func__, stdout);

    processor_dtor(&processor);

    return 0;
}
