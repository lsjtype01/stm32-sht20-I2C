#ifndef __MISC_H
#define __MISC_H

#include "u_cc.h"

#define LED(x)   do{ x ? \
                        (GPIOB->ODR &= ~(1<<4)) : \
                        (GPIOB->ODR |= (1<<4)); \
                  }while(0) 

#define BEEP(x)   do{ x ? \
                        (GPIOB->ODR |= (1<<2)) : \
                        (GPIOB->ODR &= ~(1<<2)); \
                  }while(0) 


void MiscInit(void);



#endif


