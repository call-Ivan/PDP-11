#include <stdio.h>
#include <stdlib.h>

#include "read_w.h"
#include "commands.h"
#include "logging.h"

extern int is_byte_op;

SSDD get_modereg(word w)
{
    SSDD res;
    int r = (w & 7); // слово - последние три бита, значит все остальное нужно зануллить, где r - номер регистра
    int mode = (w >> 3) & 7; // мода - первые три цифры считая слева

    int step = 0; // изменение регистра 1 или 2;  

    if (is_byte_op && r < 6)
        step = 1; // байты и первые регистры
    else
        step = 2; // слова и регистры R6-R7

    switch(mode) 
    {
        case 0:          // нулевая мода, Rn
            logging(TRACE, "R%d ", r);    
            res.adr = r;
            if(is_byte_op)
            {
                byte b = (byte)(reg[r] & 0xFF); // оставляем младшие 8 бит и приводим к типу байт
                res.val = (word)(signed char)b; // явно к знаковому привел
            }
            else
            {
                res.val = reg[r];
            }
            res.val = reg[r];
            break;
        case 1:         // первая мода, (Rn)
            logging(TRACE, "(R%d) ", r);    
            res.adr = reg[r];
            if(is_byte_op)
            {
                byte b = b_read(res.adr);       // аналогично предыдщему
                res.val = (word)(signed char)b;
            }
            else
            {
                res.val = w_read(res.adr);
            }
            break;
        case 2:        // вторая мода, (Rn)+ или #n
            res.adr = reg[r];
            if (is_byte_op) 
            {
                byte b = b_read(res.adr);
                res.val = (word)(signed char)b;
            }
            else 
            {
                res.val = w_read(res.adr);
            }
            reg[r] += step; // меняем регистр после использования
            
            if(r == 7)
            {
                logging(TRACE, "#%o ", res.val);
            }
            else
            {   
                logging(TRACE, "(R%d)+ ", r);
            }
            break;
        case 3:        // третья мода, @(Rn)+ - косвенный автоинкремент
            res.adr = w_read(reg[r]);
            reg[r] += step;
            if (is_byte_op) 
            {
                byte b = b_read(res.adr);
                res.val = (word)(signed char)b;
            } 
            else 
            {
                res.val = w_read(res.adr);
            }
            break;
        case 4:         // четвертая мода, -(Rn) - автодекрементный режим
            reg[r] -= step;    
            res.adr = reg[r];
            if (is_byte_op) 
            {
                byte b = b_read(res.adr);
                res.val = (word)(signed char)b;
            } 
            else 
            {
                res.val = w_read(res.adr);
            }
            // if(r == 7)
            // {
            //     logging(TRACE, "#%o ", res.val);
            // }
            
            // else
            // {   
            //     logging(TRACE, "(R%d)+ ", r);
            // }                              // разве здесь не нужна проверка на R7 ?
            break;
        case 5:         // пятая мода, @-(Rn) - косвенный автодекрементный режим адресации
            reg[r] -= step;
            res.adr = w_read(reg[r]);
            if(is_byte_op) 
            {
                byte b = b_read(res.adr);
                res.val = (word)(signed char)b;
            } 
            else 
            {
                res.val = w_read(res.adr);
            }
            break;

        default:
            logging(ERROR,"\nMode %d not implemented yet!(\n", mode);
            exit(1);
    }
    return res;
}