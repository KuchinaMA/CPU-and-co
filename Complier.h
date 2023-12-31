#ifndef COMPLIER_H_INCLUDED
#define COMPLIER_H_INCLUDED

#include <stdio.h>

const int ComplierVersion = 3;
static const char *Signature = "mipt";

enum ComplierErrors {
    IncorrectInput   = 1,
    IncorrectOutput  = 1 << 1,
    IncorrectCommand = 1 << 2,
    InvalidVersion   = 1 << 3,
    InvalidSignature = 1 << 4
};

int complier(FILE* input, FILE* output);
//int complier(FILE* input, FILE* output, int *labels);
int print_reg(char* line, int* codeArr, int position);
int check_file(FILE* input, FILE* output);

#endif // COMPLIER_H_INCLUDED
