#ifndef READCOMMANDS_H_INCLUDED
#define READCOMMANDS_H_INCLUDED

#include <stdio.h>

const int MAX_LINE_LEN = 256;
const int MAX_ARR_LEN = 200;

enum COMMANDS {
    PUSH   = 1,
    ADD    = 2,
    SUB    = 3,
    MUL    = 4,
    DIV    = 5,
    OUT    = 6,
    IN     = 7,
    POP    = 8,
    PUSH_R = 9,
    HLT    = -1,
};

enum Regs {
    RAX = 0,
    RBX = 1,
    RCX = 2
};

/*struct Processor {
    struct Stack stack;
    FILE* input;
    FILE* output;
    FILE* dcoutput;
};*/

//int read_commands(FILE *fp, Stack *stk); //интерпретатор
//int complier(FILE *input, FILE *output);
//int complier(struct Processor *proc);
//int decomplier(FILE *input, FILE *output);
//int decomplier(struct Processor *proc);
//int cpu(FILE *input, Stack *stk);
//int cpu(struct Processor *proc);

#endif // READCOMMANDS_H_INCLUDED
