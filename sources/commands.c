#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "logging.h" 
#include "read_w.h"
#include "get_mod.h"

SSDD ss, dd;

Command commands[] =               // аргументы каждой функции
{                     
{12, 006, "add", do_add, HAS_SS | HAS_DD},   // я ниче тогда не понял, какое число где
{12, 001, "mov",  do_mov, HAS_SS | HAS_DD},
{0, 000000, "halt",  do_halt, NO_ARGUMENTS},
{9, 077, "sob", do_sob, NO_ARGUMENTS},
// {  ,       , "movb", do_movb, },

{.shift=16, .opcode=0, .name="unknown",  do_unknown, .argument = NO_ARGUMENTS}
};

void do_halt()
{
    logging(TRACE, "\nTHE END!!!\n");
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

void do_sob()
{
    word w = w_read(pc - 2);
    int r = (w >> 6) & 7;  // 8-6 бит
    word offset = w & 077;  // смещение числа 0-5 биты

    reg[r]--;

    if(reg[r] != 0)
    {
        pc = pc - 2*offset;
    }
}


void do_movb()
{



}
void run ()
{
    pc = 01000;

    while(1)
    {
        word w = w_read(pc);
        logging(TRACE, "%06o %06o : ", pc, w);
        pc += 2;       // указываем на следующее неразобранное слово
        for(int i = 0; ; i++) {
            Command cmd = commands[i];
            if ((w >> cmd.shift) == cmd.opcode) {
                logging(TRACE, "%s ", cmd.name);
                if (cmd.argument & HAS_SS)
                    ss = get_modereg(w >> 6);
                if (cmd.argument & HAS_DD)
                    dd = get_modereg(w);

                cmd.do_command();
                break;
            }
        }
        /*
        if((w >> 0) == 0)
        {
            logging(TRACE, "halt ");
            do_halt();
        }

        else if( (w >> 12) == 001)
        {
            logging(TRACE, "mov ");
            ss = get_modereg(w >> 6);
            dd = get_modereg(w);
            do_mov();
        }

        else if( (w >> 12) == 006)
        {
            logging(TRACE, "add ");
            ss = get_modereg(w >> 6);
            dd = get_modereg(w);
            do_add();
        }
        else
        {
            logging(TRACE, "unknown");
            do_unknown();
        }
        */
        logging(TRACE, "\n");
           
    }
}