#pragma once

#ifndef READ_W_H
#define READ_W_H

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

typedef struct{
    Adress adr;    // адрес аргумента
    word val;       // значение аргумента
} SSDD;

extern SSDD ss, dd;

#define MEMSIZE (64*1024) 
#define REGSIZE 8
extern word reg[REGSIZE];
#define pc reg[7]

void b_write (Adress adr, byte val); // пишем значение (байт) val по адресу adr;
byte b_read (Adress adr); // читаем байт по адресу adr и возвращаем его;
void w_write (Adress adr, word val); // пишем значение (слово) val по адресу adr;
word w_read (Adress adr); // читаем слово по адресу adr и возвращаем его;

void load_data();
void mem_dump(Adress adr, int size);
void reg_dump();

void test_mem();

#endif