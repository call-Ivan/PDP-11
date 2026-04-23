#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "read_w.h"

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
    unsigned int n = 0;
    Adress adr = 0;
    // здесь я так понимаю в общем случае file откуда мы считываем значения
    // а в нашем из-за тестировочной системы - stdin
    while(2 == fscanf(stdin, "%hx%x", &adr, &n))
    {
        unsigned int i = 0;
        for(i = 0; i < n; i++)
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
    printf("%s %d: adr=%06o %x size=%d\n", __FUNCTION__, __LINE__, adr, adr, size);
    int i = 0;
    int words = size/2;
    for(i = 0; i < words; i++)
    {
        word w = w_read(adr);
        printf("%06o: %06o %04x\n", adr, w, w);
        adr+= 2;
    }
}