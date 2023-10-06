#ifndef DECOMPLIER_H_INCLUDED
#define DECOMPLIER_H_INCLUDED

#include <stdio.h>

const int DecomplierVersion = 2;
static const char *Signature = "mipt";

enum DecomplierErrors {

    //NoErrors         = 0,
    IncorrectInput   = 1,
    IncorrectOutput  = 1 << 1,
    IncorrectCommand = 1 << 2
};

int decomplier(FILE* input, FILE* output);

#endif // DECOMPLIER_H_INCLUDED
