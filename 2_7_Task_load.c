#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

#define MEMSIZE (64*1024)
byte mem[MEMSIZE]; 

void b_write (Adress adr, byte val); // пишем значение (байт) val по адресу adr;
byte b_read (Adress adr); // читаем байт по адресу adr и возвращаем его;
void w_write (Adress adr, word val); // пишем значение (слово) val по адресу adr;
word w_read (Adress adr); // читаем слово по адресу adr и возвращаем его;
void load_data();
void mem_dump(Adress adr, int size);

void test_mem();

int main()
{
    load_data();

    mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);

    return 0;
}

void b_write (Adress adr, byte val)
{
    mem[adr] = val;
}

byte b_read(Adress adr)
{
    return mem[adr];
}

void w_write (Adress adr, word val)
{
    assert(adr % 2 == 0);
    assert(adr + 1 < MEMSIZE);
    byte low_byte = val & 0xFF;
    byte up_byte = (val >> 8) & 0xFF;
    mem[adr] = low_byte;
    mem[adr+1] = up_byte;
}

word w_read (Adress adr)
{
    word w = mem[adr+1];
    w = w << 8;
    w = w | mem[adr];
    return w & 0xFFFF;
}


void test_mem()
{
    Adress a;
    byte b0, b1, bres, bres_up, bres_down;
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
    // тесты на границу массива, в функции w_write можно выйти за границу(написал assert внутри функции)
    
    
    //тест пишем 1 слово, читаем 2 байта
    fprintf(stderr, "Пишем слово, читаем два байта:\n");
    a = 6;        // другой адрес
    w = 0xa3b4;
    w_write(a, w);
    bres_down = b_read(a);
    bres_up = b_read(a+1);
    fprintf(stderr, "a = %06o, bres_down = %hhx, bres_up = %hhx\n", a, bres_down, bres_up);
    assert(bres_down == 0xb4);
    assert(bres_up == 0xa3);

    // еще тесты
}

// void load_file(const char * filename)
// {
//     FILE * file = fopen(filename, "r");
//     if (file == NULL) {
//         perror(filename);
//         exit(1);
//     }
//     load_data(file);
//     fclose(file);
// }

// "%06o: %06o %04x" - адрес: восьмеричное_слово шестнадцатеричное_слово
void load_data()
{
    
    int N = 0;
    Adress adr = 0;
    
    // здесь я так понимаю в общем случае file откуда мы считываем значения
    // а в нашем из-за тестировочной системы - stdin
    while(2 == fscanf(stdin, "%hx%hx", &adr, &N))
    {
        int i = 0;
        for(i = 0; i < N; i++)
        {
            byte element = 0;
            fscanf(stdin, "%hhx", &element);
            b_write(adr + i, element);
        }
    }
}

// "%06o: %06o %04x" - адрес: восьмеричное_слово шестнадцатеричное_слово
void mem_dump(Adress adr, int size)
{
    int i = 0;
    int words = size/2;
    for(i = 0; i < words; i++)
    {
        word w = w_read(adr);
        printf("%06o: %06o %04x\n", adr, w, w);
        adr+= 2;
    }
}