#ifndef __OLED_H
#define __OLED_H

#include "u_cc.h"

void OLED_Init(void);
void OLED_Clear(void);
void OLED_Clearrow(uint8_t i);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2);
void OLED_ShowFloatNum(u16 x,u16 y,float num,u8 len,u8 sizey);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);

#endif
