#pragma once

#include "read_w.h"

typedef struct        // определяем общую сборку каждой функции
{
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
    char argument;
}Command;

enum Argument 
{                              //показываем количество аргументов
    NO_ARGUMENTS = 0,
    HAS_SS = 1,
    HAS_DD = 1 << 1
};