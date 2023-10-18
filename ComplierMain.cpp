#include <stdio.h>

#include "Types.h"
#include "Stack.h"
#include "Logfile.h"
#include "Protection.h"

#include "Complier.h"

int main() {

    FILE* input = fopen("Source1.txt", "r");
    FILE* output = fopen("MachineCode2.bin", "wb");

    complier(input, output);

    fclose(input);
    fclose(output);

    printf("Compilation was successful\n");

    return 0;
}
