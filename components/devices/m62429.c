/*
 * m62429.c
 *
 *  Created on: Aug 8, 2019
 *      Author: wt
 */
#include "m62429.h"
#include "cmd.h"

/* 0  : 声音最大
 * 84 : 声音最小
 * 50 : 实测，大于50就没声音了
 */
uint16_t Volume_L[] = {0x0003,0x0001,0x0002,0x0000};
				/*D7~D8 :  0dB,   -1dB,  -2dB,  -3dB	*/

uint16_t Volume_H[] = {	/*D2~D6 */
								0x0015,0x0005,0x0019,0x0009,
							/*	  0db,  -4db,  -8db,  -12db	*/
								0x0011,0x0001,0x001e,0x000e,
							/*   -16db, -20db, -24db, -28db	*/
								0x0016,0x0006,0x001a,0x000a,
							/*   -32db, -36db, -40db, -44db	*/
								0x0012,0x0002,0x001c,0x000c,
							/*   -48db, -52db, -56db, -60db	*/
								0x0014,0x0004,0x0018,0x0008,
							/*   -64db, -68db, -72db, -76db	*/
								0x0010,0x0000};
							/*   -80db, -84db	*/

void m62429_init(void)
{
	uint8_t init_vol = 0;
	m62429_control(&init_vol,1);
	protocol_rcv_cmd_register(SET_VOLUME,m62429_control);
}

int8_t m62429_control(uint8_t *volume_data,uint16_t len)  //Vol_dat = 0->84: 0db -> -∞
{
	uint16_t D_a=0;
	uint8_t  Send_bit;
	uint16_t channel_value = 0x4000;  // Both_Channel_Value	:0x0000	 ,  One_Channel_Value	:0x4000	 ,  Two_Channel_Value	:0xc000
	uint16_t volume_temp1,volume_temp2;
	uint16_t M62429_VolumeDATA;

	volume_temp1 = Volume_H[volume_data[0] / 4];	//D2~D6
	volume_temp2 = Volume_L[volume_data[0] % 4];	//D7~D8

	M62429_VolumeDATA = (volume_temp1 << 9) + (volume_temp2 << 7) + channel_value + CONTROL_D9D10;		//count the 11bits volume data

	for(Send_bit = 0;Send_bit < 11;Send_bit++)
	{
		DAT_L;
		for(D_a=0;D_a<20;D_a++){;}
		CLK_L;
		for(D_a=0;D_a<20;D_a++){;}
		if((M62429_VolumeDATA & 0x8000) == 0x8000)
		{
			DAT_H;
		}
		else
		{
			DAT_L;
		}
		for(D_a=0;D_a<20;D_a++){;}
		CLK_H;
		for(D_a=0;D_a<20;D_a++){;}
		M62429_VolumeDATA <<= 1;
	}

	DAT_H;
	for(D_a=0;D_a<20;D_a++){;}
	CLK_L;
	for(D_a=0;D_a<20;D_a++){;}
	CLK_H;

	return 0;
}



