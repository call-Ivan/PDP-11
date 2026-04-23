#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "logging.h" 
#include "read_w.h"
#include "get_mod.h"

SSDD ss, dd;

Command cmd[] =               // аргументы каждой функции
{                     
{0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
{0170000, 010000, "mov",  do_mov, HAS_SS | HAS_DD},
{0177777, 000000, "halt",  do_halt, NO_ARGUMENTS},

{.mask=0, .opcode=0, .name="unknown",  do_unknown, .argument = NO_ARGUMENTS}
};

void do_halt()
{
    logging(TRACE, "THE END!!!\n");
    reg_dump(); // аналог моей функции
    exit(0);
}

void do_add()
{
    w_write(dd.adr, dd.val + ss.val);
}

void do_mov()
{
    w_write(dd.adr, ss.val);
}

void do_unknown()
{
    // exit(1)
}

void run ()
{
    pc = 01000;

    while(1)
    {
        word w = w_read(pc);
        // word current_pc = pc;
        // pc += 2;       // указываем на следующее неразобранное слово

        if(w == 0)
        {
            // logging(TRACE, "halt ");
            logging(TRACE, "%06o %06o : halt", pc, w);
            do_halt();
        }

        else if( (w >> 12) == 001)
        {
            // logging(TRACE, "mov ");
            logging(TRACE, "%06o %06o : mov", pc, w);
            ss = get_modereg(w >> 6);
            dd = get_modereg(w);
            do_mov();
        }

        else if( (w >> 12) == 006)
        {
            // logging(TRACE, "add ");
            logging(TRACE, "%06o %06o : add", pc, w);
            ss = get_modereg(w >> 6);
            dd = get_modereg(w);
            do_add();
        }
        // logging(TRACE, "%06o %06o", pc, w);
        else
        {
            logging(TRACE, "%06o %06o : unknown", pc, w);
            do_unknown();
        }
        pc += 2;   
    }
}