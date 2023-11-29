#include "sht20.h"

I2C_HandleTypeDef g_I2C1_Handler;

u8 I2C1Init(void)
{
    /**I2C1 GPIO Configuration    
    PB6    ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
   	GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_RCC_I2C1_CLK_ENABLE();

    g_I2C1_Handler.Instance = I2C1;
    g_I2C1_Handler.Init.ClockSpeed = 100000;
    g_I2C1_Handler.Init.DutyCycle = I2C_DUTYCYCLE_2;
    g_I2C1_Handler.Init.OwnAddress1 = 0;
    g_I2C1_Handler.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    g_I2C1_Handler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    g_I2C1_Handler.Init.OwnAddress2 = 0;
    g_I2C1_Handler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    g_I2C1_Handler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&g_I2C1_Handler) != HAL_OK)
        return 1;
    return 0;
}

/* 发送一次命令 */
void SHT20WriteCmd(u8 cmd)
{
    u8 data = cmd;
    HAL_I2C_Master_Transmit(&g_I2C1_Handler, SHT20_ADDR, &data, 1, 0X1000);
}

/* 初始化DHT20 */
void SHT20Init(void)
{
    I2C1Init();
    SHT20WriteCmd(CMD_RESET);   //软复位
}

/* 获取温度 */
float SHT20GetTemp(void)
{
    u8 ret;
    float data;
    u8 tmpreg[2];           //MSB LSB CRC
    SHT20WriteCmd(CMD_TEMP_MEASURE_HOLD);   //发送温度转化命令，主机模式
    ret = HAL_I2C_Master_Receive(&g_I2C1_Handler, SHT20_ADDR | 0x01, tmpreg, 2, 0xFFFF); //等待温度转化完成读取温度
    if(ret == HAL_OK){
        data = (float)(((u16)tmpreg[0] << 8) + (tmpreg[1] & 0xFC));
    }else {
        return 0;
    }
    return (data * 175.72) / 65536  - 46.85;
}

/* 获取湿度 */
float SHT20GetHum(void)
{
    u8 ret;
    float data;
    u8 tmpreg[2];           //MSB LSB CRC
    SHT20WriteCmd(CMD_HUM_MEASURE_HOLD);   //发送温度转化命令，主机模式
    ret = HAL_I2C_Master_Receive(&g_I2C1_Handler, SHT20_ADDR | 0x01, tmpreg, 2, 0xFFFF); //等待温度转化完成读取温度
    if(ret == HAL_OK){
        data = (float)(((u16)tmpreg[0] << 8) + (tmpreg[1] & 0xFC));
    }else {
        return 0;
    }
    return (data * 125) / 65536  - 6;
}
