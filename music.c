////////////////////////////////////////////////////////////////////////////////
/// @file    music.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
#define _MUSIC_C_

// Files includes
#include "music.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DELAY
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DELAY_Exported_Functions
/// @{





////////////////////////////////////////////////////////////////////////////////
/// @brief  给出一个由音符到频率的映射
/// @note   
/// @param  music:音符,包括：1:do 2:Re 3:Mi 4:Fa 5:So 6:La 7:Si 
/// @retval frequency.
u16 music2freq(u8 music)
{
	u16 freq;
	u8 degree=((music&0xf0)>>4);
	music&=0x0f;
	switch(music)
	{
		case 1:freq=262;break;
		case 2:freq=294;break;
		case 3:freq=330;break;
		case 4:freq=349;break;
		case 5:freq=392;break;
		case 6:freq=440;break;
		case 7:freq=494;break;
		default:freq=0;
	}
	switch(degree)
	{
		case 0:break;
		case 1:freq*=2;break;
		case 0xf:freq/=2;break;
		default:freq=0;
	}
	return freq;
}




/// @}

/// @}

/// @}
