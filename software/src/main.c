#include "sys_clk.h"
#include "misc.h"
#include "oled.h"
#include "sht20.h"

u8 g_temp_thredhold;    //温度阈值

int main(void){
    float temp, hum;
    g_temp_thredhold = 40;
    HAL_Init();
    SysClockInit();
    delay_init(72);
    MiscInit();
    OLED_Init();
    SHT20Init();
    /* 初始化界面 */
    OLED_ShowCHinese(0, 2, 0);
    OLED_ShowCHinese(16, 2, 1);
    OLED_ShowChar(32, 2, ':', 16);
    OLED_ShowCHinese(88, 2, 4);
    OLED_ShowCHinese(0, 4, 2);
    OLED_ShowCHinese(16, 4, 3);
    OLED_ShowChar(32, 4, ':', 16);
    OLED_ShowCHinese(64, 4, 4);
    OLED_ShowCHinese(0, 0, 5);
    OLED_ShowCHinese(16, 0, 6);
    OLED_ShowChar(32, 0, ':', 16);
    OLED_ShowChar(88, 0, '%', 16);
    OLED_ShowCHinese(16, 6, 7);
    OLED_ShowCHinese(32, 6, 8);
    OLED_ShowString(48, 6, "201", 16);
    OLED_ShowCHinese(80, 6, 9);
    OLED_ShowCHinese(96, 6, 10);
    OLED_ShowCHinese(112, 6, 11);
    while (1)
    {
        hum = SHT20GetHum();
        temp = SHT20GetTemp();
        if(temp > g_temp_thredhold){
            LED(1);
            BEEP(1);
        }else{
            LED(0);
            BEEP(0);
        }
       // OLED_ShowNum(48, 2, temp, 2, 16);
        //OLED_ShowNum(48, 0, hum, 2, 16);
        OLED_ShowFloatNum(48, 2, temp, 4, 16);
        OLED_ShowFloatNum(48, 0, hum, 4, 16);
        OLED_ShowNum(48, 4, g_temp_thredhold, 2, 16);
        delay_ms(100);
    }
}

/* 外部中断处理 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* KEY2按下 */
    if(GPIO_Pin == GPIO_PIN_3){
        delay_ms(20);           //消抖
        if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)){
            if(g_temp_thredhold > 0)
                g_temp_thredhold --;
        }
    }
    /* KEY1按下 */
    if(GPIO_Pin == GPIO_PIN_15){
        delay_ms(20);           //消抖
        if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)){
            if(g_temp_thredhold < 99)
            g_temp_thredhold ++;
        }
    }
}






