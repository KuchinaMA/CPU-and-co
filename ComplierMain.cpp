#include <stdio.h>

#include "Types.h"
#include "Stack.h"
#include "Logfile.h"
#include "Protection.h"

#include "Complier.h"

int main() {

    FILE* input = fopen("Source3.txt", "r");
    FILE* output = fopen("MachineCode3.bin", "wb");

    int labels[10] = {};
    for (int i = 0; i < 10; i++)
        labels[i] = -1;

    complier(input, output, labels);

    fclose(input);
    fclose(output);

    printf("Compilation was successful\n");

    return 0;
}
