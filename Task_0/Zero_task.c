#include <stdio.h>

int main()
{
    int number = 1;
    int registr = 0;
    
    int reg[9] = {0};
    while(number != 0)
    {
        scanf("%d", &number);
        if(number == 0)
        {
            break;
        }
        if(number == 3)
        {
            scanf("%d", &registr);
            if(registr == 5)
            {
                scanf("%d", &reg[registr]);
            }
            else if(registr == 6)
            {
                scanf("%d", &reg[registr]);
            }
            else if(registr == 7)
            {
                scanf("%d", &reg[registr]);
            }
            else
            {
                scanf("%d", &reg[registr]);
            }
        }
        
        int reg1 = 0, reg2 = 0;

        if(number == 1)       //подразумеваем что сначала присылаются числа, а потом уже операции с ними
        {
            scanf("%d", &reg1);
            scanf("%d", &reg2);
            reg[reg1] = (reg[reg1] + reg[reg2]) & 255;
        }
        
        if(number == 2)      
        {
            scanf("%d", &reg1);
            scanf("%d", &reg2);
            reg[reg1] = (reg[reg1] - reg[reg2]) & 255;
        }

        if(number == 4)
        {
            int j = 9;
            printf("\n");
            for(j = 5; j < 9; j++)
            {
                printf("%d ", reg[j]);
            }
        }
    }

    return 0;
}