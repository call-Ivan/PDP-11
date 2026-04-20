#include <stdio.h>
#include <stdarg.h>

#include "read_w.h"

int main ()
{
    test_mem();

    load_data();

    // mem_dump(0x40, 20);
    // printf("\n");
    mem_dump(0x200, 0x26);


    return 0;
}