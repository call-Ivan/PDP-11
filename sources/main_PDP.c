#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "read_w.h"
#include "commands.h"
#include "logging.h"


int main ()
{
    // test_mem();

    load_data();
    set_log_level(TRACE);
    run();
    // mem_dump(0x40, 20);
    // printf("\n");
    mem_dump(0x200, 0x15);
    

    return 0;
}