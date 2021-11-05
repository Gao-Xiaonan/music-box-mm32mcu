////////////////////////////////////////////////////////////////////////////////
/// @file     main.c
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
#define _MAIN_C_

// Files includes
#include "main.h"
#include "uart.h"
#include "beeper.h"
#include "tim2.h"
#include "tim5.h"
#include "delay.h"
#include "music.h"
#include "led.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{
#define BASIC_CLAP 125


extern u32 SystemCoreClock;
char GeCi1[]="东揽钟山紫气\r\n北拥扬子银涛\r\n六朝松下听箫韶\r\n齐梁遗韵在\r\n太学令名标\r\n";
char GeCi2[]="百载文枢江左\r\n东南辈出英豪\r\n";
char GeCi3[]="海涵地负展宏涛\r\n展宏涛\r\n";
char GeCi4[]="日新臻化境\r\n";
char GeCi5[]="四海领风骚\r\n";
char GeCi[384]={0};
char* GeCi_pointer=GeCi;


void play_a_lyric(u8 lyric[],u8 clap[])
{
	u8 k=0;
	while(clap[k]!=0)
	{
		if(lyric[k]!=lyric[k+1])
		{
			play_tunes(music2freq(lyric[k]),clap[k]*BASIC_CLAP);
		}
		else
		{
			play_tunes(music2freq(lyric[k]),clap[k]*BASIC_CLAP-50);
			play_tunes(0,50);
		}
		k++;
		LED1_TOGGLE();
		LED4_TOGGLE();
	}
	LED2_TOGGLE();
}

void play_dongLan_lingMingBiao()
{
	u8 lyric[50]={6,6,0x13,0x13,0x12,0x11,0x13,//东揽钟山紫气
		0x12,0x12,0x13,0x12,0x11,6,5,6,//北拥扬子银涛；
	6,6,0x13,0x13,0x12,0x11,0x12,//六朝松下听箫韶
		0x12,0x13,0x15,0x15,0x13,0x15,//齐梁遗韵在
		0x12,0x11,0x06,5,6,0//太学令名标
		};
	u8 clap[50]={4,4,4,4,6,2,8,
		4,2,2,3,1,2,2,16,
	4,4,4,4,4,4,8,
	6,2,4,4,12,4,
	6,2,4,4,12,4,0};

  play_a_lyric(lyric,clap);
}

void play_baiZai_HuaJing()
{
	u8 lyric[30]={0x13,0x13,0x15,0x15,0x16,0x15,0x13,//百载文枢江左
		0x15,0x15,0x16,0x15,0x13,0x12,0x11,0x13,//东南辈出英豪
		6,6,0x13,0x13,0x12,0x11,0x12,0};//海涵地负展宏涛
	u8 clap[30]={4,4,4,4,6,2,8,
		4,3,1,4,4,6,2,8,
		4,4,4,4,6,2,7,1,0};
	play_a_lyric(lyric,clap);
}

void play_zhanHongTao()
{
	u8 lyric[10]={0x12,0x13,0x12,0x11,0x06,0x15};
	u8 clap[10]={6,2,2,2,4,16,0};
	play_a_lyric(lyric,clap);
}

void play_SiHaiLFengSao()
{
	u8 lyric[10]={0x13,0x15,0x11,6,5,6,0};
	u8 clap[10]={4,4,4,3,1,12,4,0};
	play_a_lyric(lyric,clap);
}

void play_End()
{
	u8 lytic[10]={0x15,0x15,0x15,0x13,0x16,0x00};
	u8 clap[10]={12,4,8,8,32,16,0};
	play_a_lyric(lytic,clap);
}

void play_Start()
{
	u8 lyric[40]={0x16,0x13,0x12,0x11,0x12,0x13,0x15,0x16,0x15,0x13,0x12,0x13,
		6,6,0x13,0x13,0x12,0x11,0x12,0x13,0x15,0x11,6,5,6,6,6,6,3};
	u8 clap[40]={8,8,4,3,1,8,4,4,3,1,4,16,
		4,4,4,4,4,4,8,4,4,3,1,4,4,2,2,6,2,0};
	play_a_lyric(lyric,clap);
}
	

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
s32 main(void)
{
	int i;
    strcat(GeCi,GeCi1);
	for(i=0;i<2;i++)
	{
	  strcat(GeCi,GeCi2);
	  strcat(GeCi,GeCi3);
	  strcat(GeCi,GeCi2);
	  strcat(GeCi,GeCi4);
	  strcat(GeCi,GeCi5);
	}
	strcat(GeCi,GeCi5);
    CONSOLE_Init(115200);
	  DELAY_Init();
	  LED_Init();
    TIM2_UPCount_Init(100 - 1, SystemCoreClock/ 100000 - 1);
	  beeper_Init();
    while(1) {
			TIM5_UPCount_Init(BASIC_CLAP*32-1,60000-1);
			TIM_Cmd(TIM5,DISABLE);
			GeCi_pointer=GeCi;
			play_Start();
			GeCi_pointer=(char*)UART_SendRow(UART1,(u8*)GeCi_pointer,32);
	    if(*(GeCi_pointer+1)!=0)GeCi_pointer++;
			LED1_OFF();
			TIM_Cmd(TIM5,ENABLE);
			LED2_OFF();
			DELAY_Ms(3);
			play_dongLan_lingMingBiao();
			LED3_OFF();
			for(i=0;i<2;i++)
			{
				play_baiZai_HuaJing();
				play_zhanHongTao();
				play_baiZai_HuaJing();
				play_SiHaiLFengSao();
			}
			play_End();
			TIM_Cmd(TIM5,DISABLE);


        
    }
}


/// @}

/// @}

/// @}
