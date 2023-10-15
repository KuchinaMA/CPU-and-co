#ifndef READCOMMANDS_H_INCLUDED
#define READCOMMANDS_H_INCLUDED

#include <stdio.h>

const int MAX_LINE_LEN = 256;
const int MAX_ARR_LEN = 200;

enum COMMANDS {

    PUSH   = 1,
    PUSH_R = 2,
    POP    = 3,
    IN     = 4,
    OUT    = 5,

    ADD    = 10,
    SUB    = 11,
    MUL    = 12,
    DIV    = 13,
    SQRT   = 14,
    POW    = 15,

    SIN    = 20,
    COS    = 21,
    TAN    = 22,
    CTG    = 23,

    MEOW   = 30,
    BARK   = 31,
    DUCK   = 32,
    BOO    = 33,

    SOLVE  = 40,
    SLEEP  = 41,
    MATAN  = 42,

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
