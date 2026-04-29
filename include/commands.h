#pragma once

#include "read_w.h"

enum Argument 
{                              //показываем количество аргументов
    NO_ARGUMENTS = 0,
    HAS_SS = 1,
    HAS_DD = 1 << 1,
    HAS_NN = 3
};

typedef struct        // определяем общую сборку каждой функции
{
    word shift;
    word opcode;
    char * name;
    void (*do_command)(void);
    char argument;
}Command;

extern Command commands[];

void do_halt(void);
void do_add(void);
void do_mov(void);
// void do_movb(void);
void do_sob(void);
void do_unknown(void);
void reg_dump();
void run();

