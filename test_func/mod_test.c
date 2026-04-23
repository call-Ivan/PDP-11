#include <assert.h>

#include "commands.h"
#include "read_w.h"
#include "logging.h"

Command cmd;
while(1) 
{
    cmd = parse_cmd(read_cmd()); // читаем слово и разбираем команду
    cmd.do_command();            // выполняем команду
}

// тест, что мы правильно определяем команды mov, add, halt
void test_parse_mov()
{
    logging(TRACE, __FUNCTION__);
    Command cmd = parse_cmd(0017654);
    assert(strcmp(cmd.name, "mov"));
    logging(TRACE, " ... OK\n");
}
// тест, что мы разобрали правильно аргументы ss и dd в mov R5, R3
void test_mode0()
{
    logging(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    assert(ss.val == 34);
    assert(ss.adr == 5);
    assert(dd.val == 12);
    assert(dd.adr == 3);
    logging(TRACE, " ... OK\n");
}
// тест, что mov и мода 0 работают верно в mov R5, R3
void test_mov()
{
    logging(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    cmd.do_command();
    assert(reg[3] = 34);
    assert(reg[5] = 34);
    logging(TRACE, " ... OK\n");
}