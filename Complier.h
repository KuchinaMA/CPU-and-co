#ifndef COMPLIER_H_INCLUDED
#define COMPLIER_H_INCLUDED

#include <stdio.h>

const int MAX_LINE_LEN = 256;

enum ComplierErrors {

    //NoErrors         = 0,
    IncorrectInput   = 1,
    IncorrectOutput  = 1 << 1,
    IncorrectCommand = 1 << 2
};

int complier(FILE* input, FILE* output);

#endif // COMPLIER_H_INCLUDED
