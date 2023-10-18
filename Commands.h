
DEF_CMD(PUSH, 1, 1, {
    elem_t number = codeArr[i+1];
    i++;
    stack_push(&proc->stack, number);
    })

DEF_CMD(PUSH_R, 2, 2, {
    elem_t number = codeArr[i+1];
    if (number == RAX || number == RBX || number == RCX) {
        stack_push(&proc->stack, proc->registers[number]);
        i++;
    }
    else
        printf("Incorrect register\n");
    })

DEF_CMD(POP, 3, 2, {
    elem_t number = codeArr[i+1];
    if (number == RAX || number == RBX || number == RCX) {
        stack_pop(&proc->stack, &proc->registers[number]);
        i++;
    }
    else
        printf("Incorrect register\n");
    })

DEF_CMD(IN, 4, 0, {
    elem_t number = 0;
    scanf(ELEMF, &number);
    stack_push(&proc->stack, number);
    })

DEF_CMD(OUT, 5, 0, {
    elem_t answer = 0;
    stack_pop(&proc->stack, &answer);
    printf("\n Answer: "ELEMF"\n", answer);
    })


DEF_CMD(ADD, 10, 0, {
    elem_t second = 0;
    stack_pop(&proc->stack, &second);

    elem_t first = 0;
    stack_pop(&proc->stack, &first);

    elem_t newel = first + second;
    stack_push(&proc->stack, newel);
    })

DEF_CMD(SUB, 11, 0, {
    elem_t second = 0;
    stack_pop(&proc->stack, &second);

    elem_t first = 0;
    stack_pop(&proc->stack, &first);

    elem_t newel = first - second;
    stack_push(&proc->stack, newel);
    })

DEF_CMD(MUL, 12, 0, {
    elem_t second = 0;
    stack_pop(&proc->stack, &second);

    elem_t first = 0;
    stack_pop(&proc->stack, &first);

    elem_t newel = first * second;
    stack_push(&proc->stack, newel);
    })

DEF_CMD(DIV, 13, 0, {
    elem_t second = 0;
    stack_pop(&proc->stack, &second);

    elem_t first = 0;
    stack_pop(&proc->stack, &first);

    elem_t newel = first / second;
    stack_push(&proc->stack, newel);
    })

DEF_CMD(SQRT, 14, 0, {
    elem_t number = 0;
    stack_pop(&proc->stack, &number);

    elem_t newel = sqrt(number);
    stack_push(&proc->stack, newel);
    })

DEF_CMD(POW, 15, 0, {
    elem_t second = 0;
    stack_pop(&proc->stack, &second);

    elem_t first = 0;
    stack_pop(&proc->stack, &first);

    elem_t newel = pow(first,second);
    stack_push(&proc->stack, newel);
    })


DEF_CMD(SIN, 20, 0, {
    elem_t number = 0;
    stack_pop(&proc->stack, &number);

    elem_t newel = sin(number);
    stack_push(&proc->stack, newel);
    })

DEF_CMD(COS, 21, 0, {elem_t number = 0;
    stack_pop(&proc->stack, &number);

    elem_t newel = cos(number);
    stack_push(&proc->stack, newel);
    })

DEF_CMD(TAN, 22, 0, {
    elem_t number = 0;
    stack_pop(&proc->stack, &number);

    elem_t newel = tan(number);
    stack_push(&proc->stack, newel);
    })

DEF_CMD(CTG, 23, 0, {
    elem_t number = 0;
    stack_pop(&proc->stack, &number);

    elem_t newel = 1 / tan(number);
    stack_push(&proc->stack, newel);
    })


DEF_CMD(MEOW, 30, 0, {
    print_cat();
    })

DEF_CMD(BARK, 31, 0, {
    print_dog();
    })

DEF_CMD(DUCK, 32, 0, {
    print_duck();
    })

DEF_CMD(BOO, 33, 0, {
    print_boo();
    })


DEF_CMD(SOLVE, 40, 0, {
    printf("I can count the discriminant!\n");
    })

DEF_CMD(SLEEP, 41, 0, {
    printf("Stop boting, it's time to sleep\n");
    })

DEF_CMD(MATAN, 42, 0, {
    printf("There's no tine to sleep, you need to botat' matan\n");
    })


DEF_CMD(HLT, -1, 0, {
    return NoErrors;
    })
