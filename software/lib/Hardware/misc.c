#include "misc.h"


void MiscInit(void)
{
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();      //禁用JTAG，否则PB3,PB4无法使用
    /* LED和蜂鸣器 */
    /*
        LED------PB4
        BEEP------PB2
    */
    GPIO_InitTypeDef GPIO_Initstruct = {0};
    GPIO_Initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstruct.Pull = GPIO_NOPULL;
    GPIO_Initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_Initstruct.Pin = GPIO_PIN_2 | GPIO_PIN_4;

    HAL_GPIO_Init(GPIOB, &GPIO_Initstruct);

    /* 按键 */
    /*
        KEY1------PA15
        KEY2------PB3
    */
    GPIO_Initstruct.Mode = GPIO_MODE_IT_FALLING;;
    GPIO_Initstruct.Pull = GPIO_PULLUP;
    GPIO_Initstruct.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOA, &GPIO_Initstruct);

    GPIO_Initstruct.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &GPIO_Initstruct);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);

    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    LED(0);
    BEEP(0);
}




