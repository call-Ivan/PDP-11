#include <stdarg.h>
#include <stdio.h>
#include "logging.h"

static int current_level = INFO;

int set_log_level(int level)
{
    int old = current_level;
    current_level = level; // так это местячковая переменная, то она как гопник зайдет в любую щель
    return old;
}

void logging(int level, const char * format, ...)
{
    if(level > current_level)
    {
        return;
    }
    va_list ap; // ap - pointer, указывает на следующий после последнего фикс. аргумента
    
    va_start(ap, format);
    vfprintf(stderr ,format, ap);  // почти printf, но работает с va_list(формат с переменным числом аргументов)
    va_end(ap);
}
