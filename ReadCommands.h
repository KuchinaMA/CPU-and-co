#ifndef READCOMMANDS_H_INCLUDED
#define READCOMMANDS_H_INCLUDED

#include <stdio.h>

const int MAX_LINE_LEN = 256;

enum COMMANDS {
    PUSH = 1,
    ADD  = 2,
    SUB  = 3,
    MUL  = 4,
    DIV  = 5,
    OUT  = 6,
    HLT  = 7
};

struct Processor {
    struct Stack stack;
    FILE* input;
    FILE* output;
    FILE* dcoutput;
};

int read_commands(FILE *fp, Stack *stk); //интерпретатор
//int complier(FILE *input, FILE *output);
int complier(struct Processor *proc);
//int decomplier(FILE *input, FILE *output);
int decomplier(struct Processor *proc);
//int cpu(FILE *input, Stack *stk);
int cpu(struct Processor *proc);

#endif // READCOMMANDS_H_INCLUDED
