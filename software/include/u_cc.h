#ifndef __U_CC_H
#define __U_CC_H

#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "string.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif


