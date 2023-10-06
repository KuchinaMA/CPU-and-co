#include <stdio.h>

#include "Types.h"
#include "Stack.h"
#include "Logfile.h"
#include "Protection.h"

#include "ReadCommands.h"
#include "Complier.h"

int main() {

    FILE* input = fopen("Source2.txt", "r");
    FILE* output = fopen("MachineCode2.txt", "w");

    complier(input, output);

    fclose(input);
    fclose(output);

    printf("Compilation was successful\n");

    return 0;
}
