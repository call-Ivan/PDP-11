#include <stdio.h>
#include <assert.h>

#include "read_w.h"
#include "logging.h"

static byte mem[MEMSIZE]; 
word reg[REGSIZE];

void test_mem();

void reg_dump()
{
    logging(TRACE, "-------------------------------\n");
    logging(TRACE, "r0=%06o ", reg[0]);
    logging(TRACE, "r2=%06o ", reg[2]);
    logging(TRACE, "r4=%06o ", reg[4]);
    logging(TRACE, "sp=%06o ", reg[6]);
    logging(TRACE, "\n");
    logging(TRACE, "r1=%06o ", reg[1]);
    logging(TRACE, "r3=%06o ", reg[3]);
    logging(TRACE, "r5=%06o ", reg[5]);
    logging(TRACE, "pc=%06o ", reg[7]);
    logging(TRACE, "\n");
}

// int main()
// {
//     test_mem();
//     return 0;
// }

void b_write (Adress adr, byte val)
{
    if (adr < 8) 
    {
        // знаковое расширение
        byte sign_bit = (val >> 7) & 1;
        if (sign_bit == 0) {
            reg[adr] = val & 0xFF;
        } else {
            reg[adr] = ~0xFF | val;
        }
    }
    mem[adr] = val; 
}

byte b_read(Adress adr)
{
    if (adr < 8) {
        return reg[adr] & 0xFF;
    }
    return mem[adr];
}

void w_write (Adress adr, word val)
{
    if (adr < 8) {
        reg[adr] = val;
        return;
    }
    assert(adr % 2 == 0);
    assert(adr + 1 < MEMSIZE);
    byte low_byte = val & 0xFF;
    byte up_byte = (val >> 8) & 0xFF;
    mem[adr] = low_byte;
    mem[adr+1] = up_byte;
}

word w_read (Adress adr)
{
    if (adr < 8) {
        return reg[adr];          // читаем из регистрового массива
    }
    word w = mem[adr+1];
    w = w << 8;
    w = w | mem[adr];
    return w & 0xFFFF;
}


void test_mem()
{
    Adress a;
    byte b0, b1, bres;
    word w, wres;


    // пишем байт, читаем байт
    fprintf(stderr, "Пишем и читаем байт по четному адресу\n");
    a = 0;
    b0 = 0x12;
    b_write(a, b0);
    bres = b_read(a);
    printf("%hu",a);
    // тут полезно написать отладочную печать a, b0, bres
    fprintf(stderr, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);
    // аналогично стоит проверить чтение и запись по нечетному адресу
    fprintf(stderr, "Пишем и читаем байт по нечетному адресу\n");
    a = 1;
    b0 = 0x35;
    b_write(a, b0);
    bres = b_read(a);
    printf("%hu",a);
    // тут полезно написать отладочную печать a, b0, bres
    fprintf(stderr, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);


    // пишем слово, читаем слово
    fprintf(stderr, "Пишем и читаем слово\n");
    a = 2;        // другой адрес
    w = 0x3456;
    w_write(a, w);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);


    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Пишем 2 байта, читаем слово\n");
    a = 4;        // другой адрес
    w = 0xa1b2;
    // little-endian, младшие разряды по меньшему адресу
    b0 = 0xb2;
    b1 = 0xa1;
    b_write(a, b0);
    b_write(a+1, b1);
    wres = w_read(a);
    // тут полезно написать отладочную печать a, w, wres
    fprintf(stderr, "a=%06o b1=%02hhx b0=%02hhx wres=%04x\n", a, b1, b0, wres);
    assert(w == wres);
    // тесты на границу массива, в функции w_write можно выйти за границу

    // еще тесты
}
