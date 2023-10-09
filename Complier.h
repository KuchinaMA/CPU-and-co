#ifndef COMPLIER_H_INCLUDED
#define COMPLIER_H_INCLUDED

#include <stdio.h>

//static const int MAX_LINE_LEN = 256;

const int ComplierVersion = 2;
static const char *Signature = "mipt";

enum ComplierErrors {

    //NoErrors         = 0,
    IncorrectInput   = 1,
    IncorrectOutput  = 1 << 1,
    IncorrectCommand = 1 << 2
};

int complier(FILE* input, FILE* output);
int print_reg(char* line, FILE* output);
int check_file(FILE* input, FILE* output);

#endif // COMPLIER_H_INCLUDED
