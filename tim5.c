///////////////////////////////////////////////////////////////////////////////
/// @file     tim5.c
/// @author   AE TEAM
/// @brief    Using timer to generate delays.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////
// Define to prevent recursive inclusion
#define _TIM5_C_

// Files includes
#include "tim5.h"
#include "uart.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief  Waiting for the timer to overflow and interrupt
/// @note   Pay attention to clearing interruption marks.
/// @param  TxMessage:Sent message.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////


void TIM5_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    GeCi_pointer=(char*)UART_SendRow(UART1,(u8*)GeCi_pointer,32);
	  if(*(GeCi_pointer+1)!=0)GeCi_pointer++;
	 LED3_TOGGLE();
	  
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  time initialization configuration
/// @note    It must be careful of the Chip Version.
/// @param  Prescaler: Clock frequency division value.
/// @param  Period: Preloading value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM5_UPCount_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    NVIC_InitTypeDef NVIC_StructInit;

    //Enable TIM1 clock, default clock source is PCLK2,Alternative Clock Sources
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM5, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Period = psc;
    TIM_TimeBaseStruct.TIM_Prescaler = arr;
    //Sampling frequency of digital filter does not affect timer clock
    //Sampling Frequency Dividing Value
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);

    // interrupt priority configuration

    NVIC_StructInit.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_StructInit.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_StructInit.NVIC_IRQChannelSubPriority = 0;
    NVIC_StructInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_StructInit);


    TIM_ClearFlag(TIM5, TIM_FLAG_Update);

    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM5, ENABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  TIM5_UPStatusOVCheck_test1(void)
/// @note
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM5_UPStatusOVCheck(void)
{
    //Waiting for Event Update Flag Bit
    while(TIM_GetFlagStatus(TIM5, TIM_FLAG_Update) == RESET);
    //Clear the marker
    TIM_ClearFlag(TIM5, TIM_FLAG_Update);
}
/// @}

/// @}

/// @}
