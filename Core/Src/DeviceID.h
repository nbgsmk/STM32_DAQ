//
// Created by mcu on 25/05/2026.
//

#ifndef STM32_DAQ_DEVICEID_H
#define STM32_DAQ_DEVICEID_H

typedef struct  {
	uint8_t id0;
	uint8_t id1;
	uint8_t id2;
	uint32_t CpuId96bit[3];
	uint32_t UIDbin;
	uint32_t UIDbcd;

} DaqHw_t;


/*
 * UID = Uredjaj ID
 */
void INIT_DEVICE_ID();

DaqHw_t getDaqHw();
uint32_t getUID_bin();
uint32_t getUID_bcd();


#endif //STM32_DAQ_DEVICEID_H
