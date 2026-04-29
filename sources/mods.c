#include <stdio.h>
#include <stdlib.h>

#include "read_w.h"
#include "commands.h"


#include "logging.h"

SSDD get_modereg(word w)
{
    SSDD res;
    int r = (w & 7); // слово - последние три бита, значит все остальное нужно зануллить, где r - номер регистра
    int mode = (w >> 3) & 7; // мода - первые три цифры считая слева

    switch(mode) 
    {
        case 0:          // нулевая мода, Rn
            logging(TRACE, "R%d ", r);    
            res.adr = r;
            res.val = reg[r];
            break;
        case 1:         // первая мода, (Rn)
            logging(TRACE, "(R%d) ", r);    
            res.adr = reg[r];
            res.val = w_read(res.adr);
            break;
        case 2:        // вторая мода, (Rn)+ или #n
            res.adr = reg[r];
            res.val = w_read(res.adr);
            reg[r] += 2;
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
            reg[r] += 2;
            res.val = w_read(res.adr);
            break;

        case 4:         // четвертая мода, -(Rn) - автодекрементный режим
            reg[r] -= 2;    
            res.adr = reg[r];
            res.val = w_read(res.adr);
            
            // if(r == 7)
            // {
            //     logging(TRACE, "#%o ", res.val);
            // }
            
            // else
            // {   
            //     logging(TRACE, "(R%d)+ ", r);
            // }                              // разве здесь не нужна проверка на R7 ?
            break;
        // case 5:         // пятая мода, 
            

        //     break;

        default:
            logging(ERROR,"\nMode %d not implemented yet!(\n", mode);
            exit(1);
    }
    return res;
}