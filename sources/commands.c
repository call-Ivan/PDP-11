#include <stdio.h>
#include <stdlib.h>

#include "logging.h" 
#include "read_w.h"

word reg[8];  // регистры 0-7

#define pc reg[7]

typedef struct        // определяем общую сборку каждой функции
{
    word mask;
    word opcode;
    char * name;
    void (*do_command)(void);
}Command;




Command cmd[] =                    // аргументы каждой функции

{0170000, 0060000, "add",  do_add, .argument = NO_ARGUMENTS},
{.mask=0, .opcode=0, .name="mov",  .do_command=do_unknown, .argument = NO_ARGUMENTS},
{.mask=0, .opcode=0, .name="halt",  .do_command=do_unknown, .argument = NO_ARGUMENTS},
{.mask=0, .opcode=0, .name="unknown",  .do_command=do_unknown, .argument = NO_ARGUMENTS}.

void do_halt()
{
    logging(TRACE, "THE END!!!\n");
    reg_dump(); // аналог моей функции
    exit(0);
}

void do_add()
{

}

void do_mov()
{
    
}

void do_nothing()
{
    // exit(1)
    
}

void run ()
{
    pc = 01000;

    while(1)
    {
        word w = w_read(pc);
        logging(TRACE, "%06o %06o", pc, w);
        pc = +2;       // указываем на следующее неразобранное слово

        if(w == 0)
        {
            logging(TRACE, "halt ");
            do_halt();
        }

        else if( (w >> 12) == 001)
        {
            logging(TRACE, "mov ");
            do_mov();
        }

        else if( (w >> 12) == 006)
        {
            logging(TRACE, "add ");
            do_add();
        }


    }

}