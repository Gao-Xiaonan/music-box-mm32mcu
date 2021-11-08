////////////////////////////////////////////////////////////////////////////////
/// @file     beeper.c
/// @author   AE TEAM
/// @brief    configure the beeper
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
#define _TIM2_C_

// Files includes
#include "beeper.h"
#include "tim2.h"
#include "delay.h"
#include "led.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief  Waiting for the timer to overflow and interrupt
/// @note   Pay attention to clearing interruption marks.
/// @param  TxMessage:Sent message.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////

extern u32 ucTim2Flag;
extern u32 SystemCoreClock;



////////////////////////////////////////////////////////////////////////////////
/// @brief  time initialization configuration
/// @note    It must be careful of the Chip Version.
/// @param  Prescaler: Clock frequency division value.
/// @param  Period: Preloading value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////

void beeper_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
                     
 
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void beep_on(void)
{
	  TIM_Cmd(TIM2,ENABLE);
}

void beep_off(void)
{
	  TIM_Cmd(TIM2,DISABLE);
}

/// @brief  发出一定频率和时间的声音
/// @note    It must be careful of the Chip Version.
/// @param  freq:频率(Hz)
/// @param  time：时间（单位：ms）
/// @retval None.
void play_tunes(u16 freq,u16 time)
{
  beep_off();
	if(freq!=0)
	{
		WRITE_REG(TIM2->ARR, 1000000/freq/2-1);
		WRITE_REG(TIM2->PSC, SystemCoreClock/2/1000000-1);//1MHz时钟
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		ucTim2Flag=0;
		beep_on();
		while(ucTim2Flag!=(time*freq*2)/1000)
		{}
			
	}
	else
	{
		DELAY_Ms(time);
	}
	
}


/// @}

/// @}

/// @}



