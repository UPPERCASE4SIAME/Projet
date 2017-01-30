#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef  GPIO_InitStructure;

void Delay(__IO uint32_t nCount);

int main (void)
{
    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);


    /* Configure PD12, PD13, PD14,PD15 and PD5 in output pushpull mode */
    /* Note that PD12,13,14 and 15 relate to the on board LEDs, pin PD5 maps to the Pin labelled PD5 on the
    * STM board, and this is referrenced in the code below using GPIO_Pin_5 (refering to pin 5). When we actually
    * toggle the pin using GPIO_SetBits is when we specify the D part using GPIOD ie GPIO_SetBits(GPIOD, GPIO_Pin_5);
    **/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
 
    while (1)
    {
        /* PD12 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_12);
 
        /* Insert delay */
        Delay(0x3FFFFF);
 
        /* PD13 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_13);
 
        /* Insert delay */
        Delay(0x3FFFFF);
 
        /* PD14 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_14);
 
        /* Insert delay */
        Delay(0x3FFFFF);
 
        /* PD15 to be toggled */
        GPIO_SetBits(GPIOD, GPIO_Pin_15);
 
        /* Insert delay */
        Delay(0x3FFFFF);
 
    // This line resets the pins, turning off the LED's and setting the voltage on pin PD55 to 0
        GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

        /* Insert delay */
        Delay(0x3FFFFF);
    }
}

void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}
