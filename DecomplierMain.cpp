#include <stdio.h>

#include "Types.h"
#include "Stack.h"
#include "Logfile.h"
#include "Protection.h"

#include "ReadCommands.h"
#include "Decomplier.h"

int main() {

    FILE* input = fopen("MachineCode3.bin", "rb");
    FILE* output = fopen("DecomplierOutput3.txt", "w");

    decomplier(input, output);

    fclose(input);
    fclose(output);

    printf("Decompilation was successful\n");

    return 0;
}
