/**
 * USB VCP for STM32F4xx example.
 *    
 * @author     Tilen Majerle
 * @email        tilen@majerle.eu
 * @website    http://stm32f4-discovery.com
 * @ide        Keil uVision
 *
 * Add line below to use this example with F429 Discovery board (in defines.h file)
 *
 * #define USE_USB_OTG_HS
 **/
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stdlib.h"
#include "string.h"

#include "tm_stm32f4_usb_vcp.h"
#include "tm_stm32f4_disco.h"
#include "defines.h"

#define NB_BOUGIES 6

void Configure_interrupt_rotary2(void);
void EXTI0_IRQHandler(void);
void Configure_interrupt_ignition(void);
void EXTI15_10_IRQHandler(void);

uint32_t TIME_IGNITION[NB_BOUGIES];

/*  Le baudrate de l'UART se change dans le fichier 
 *  lib/src/peripherals/stm32f4xx_usart.c
 *  ligne 343
 */

/* Timer
 * Carte stm32f407VGT6 --> 168MHz
 *
 * TIM2
 *
 */

int main(void) {
    uint8_t c;
    /* System Init -- UART */
    SystemInit();
    
    /* Initialize LED's. Make sure to check settings for your board in tm_stm32f4_disco.h file */
    //TM_DISCO_LedInit();
   
    /* Initiallize Counter */
    InitializeTimer();
 
    /* Initialize USB VCP */    
    TM_USB_VCP_Init();

    /* Configure PD0 as interrupt */
    Configure_interrupt_rotary2();
    Configure_interrupt_ignition();
    
    while (1) {
/*
        // USB configured OK, drivers OK
        if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) {
            // Turn on GREEN led
            TM_DISCO_LedOn(LED_GREEN);
            TM_DISCO_LedOff(LED_RED);
            // If something arrived at VCP
            if (TM_USB_VCP_Getc(&c) == TM_USB_VCP_DATA_OK) {
                // Return data back
                TM_USB_VCP_Putc('0');
            }
        } else {
            // USB not OK
            TM_DISCO_LedOff(LED_GREEN);
            TM_DISCO_LedOn(LED_RED);
        }
*/
    }
}

/* Set interrupt handlers */
/* Handle PD0 interrupt */
void EXTI0_IRQHandler(void) {

    int timerValue = 0;
    char val[11];
    //char buffer[10];

    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        /* Do your stuff when PD0 is changed */
        timerValue = TIM_GetCounter(TIM2); /* Recup temps total cycle moteur */
        itoa(timerValue, val, 10);
            
        /* remise a zero du compteur et start */
        //TIM_Cmd(TIM2, DISABLE);
        TIM_SetCounter(TIM2, (uint32_t) 0);
        TIM_Cmd(TIM2, ENABLE);

        TM_USB_VCP_Puts(val);
        
        for (int i = 0 ; i < NB_BOUGIES; i++)
        {
            itoa(TIME_IGNITION[i], val, 10);
            TM_USB_VCP_Putc(';');
            TM_USB_VCP_Puts(val);
            TIME_IGNITION[i] = 0;
        }
    
        TM_USB_VCP_Puts("\r\n");

        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void InitializeTimer()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    TIM_TimeBaseInitTypeDef timerInitStructure; 
    //timerInitStructure.TIM_Prescaler = 40000;
    /* Prescaller = 167 ==> 168Mh soit 168 ticks pour 1 us (prescaller_set + 1) */
    timerInitStructure.TIM_Prescaler = 83;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //timerInitStructure.TIM_Period = 500;
    /* Periode maximum */
    timerInitStructure.TIM_Period = 0xFFFFFFFF;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    //TIM_Cmd(TIM2, ENABLE);
}

/* Configure pins to be interrupts */
void Configure_interrupt_rotary2(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Enable clock for SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    /* Tell system that you will use PD0 for EXTI_Line0 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
    //SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
    
    /* PD0 is connected to EXTI_Line0 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
} 

void Configure_interrupt_ignition(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    /* Enable clock for GPIOB */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    /* Enable clock for SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
   
    /* ################
     * #    EXTI      #
     * ################ */

    /* ### PIN 10 ### */
 
    /* Tell system that you will use PB10 for EXTI_Line10 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);
    
    /* PB10 is connected to EXTI_Line10 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line10;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);

    /* ### PIN 11 ### */

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource11);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line11;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    /* ### PIN 12 ### */

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line12;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    /* ### PIN 13 ### */

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource13);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line13;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    /* ### PIN 14 ### */

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource14);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line14;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    /* ### PIN 15 ### */

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource15);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line15;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    /* ################
     * #  FIN  EXTI   #
     * ################ */


    /* Add IRQ vector to NVIC */
    /* PB12 is connected to EXTI_Line12, which has EXTI15_10_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

/* Handle PB12 interrupt */
void EXTI15_10_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line10) != RESET) {
        /* Do your stuff when PB10 is changed */
        TIME_IGNITION[0] = TIM_GetCounter(TIM2); /* recuperation temps */

        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line10);
    }
    else if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
        TIME_IGNITION[1] = TIM_GetCounter(TIM2);
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    else if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
        TIME_IGNITION[2] = TIM_GetCounter(TIM2);
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    else if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
        TIME_IGNITION[3] = TIM_GetCounter(TIM2);
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    else if (EXTI_GetITStatus(EXTI_Line14) != RESET) {
        TIME_IGNITION[4] = TIM_GetCounter(TIM2);
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    else if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
        TIME_IGNITION[5] = TIM_GetCounter(TIM2);
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
    
}
