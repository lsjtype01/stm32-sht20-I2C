#ifndef __SHT20_H
#define __SHT20_H

#include "u_cc.h"

#define SHT20_ADDR  0x80

#define CMD_TEMP_MEASURE_HOLD    0xE3
#define CMD_HUM_MEASURE_HOLD     0xE5
#define CMD_TEMP_MEASURE         0xF3
#define CMD_HUM_MEASURE          0xF5
#define CMD_WRITE_USER_REG       0xE6     
#define CMD_READ_USER_REG        0xE7
#define CMD_RESET                0xFE     

void SHT20Init(void);
float SHT20GetTemp(void);
float SHT20GetHum(void);

#endif
