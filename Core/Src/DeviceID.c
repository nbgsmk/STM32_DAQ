//
// Created by mcu on 25/05/2026.
//

#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"

#include "DeviceID.h"




DaqHw_t hw;

/*
 * UID = Uredjaj ID
 */


void readIDswitches() {
	uint8_t u0 = 0;
	uint8_t u1 = 0;
	uint8_t u2 = 0;

	HAL_GPIO_WritePin(KBD_digit0_GPIO_Port, KBD_digit0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KBD_digit1_GPIO_Port, KBD_digit1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KBD_digit2_GPIO_Port, KBD_digit2_Pin, GPIO_PIN_SET);

	// PRVA cifra
	HAL_GPIO_WritePin(KBD_digit0_GPIO_Port, KBD_digit0_Pin, GPIO_PIN_RESET);
	osDelay(20);
	//i am  1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
	if (HAL_GPIO_ReadPin(KBD_i0_GPIO_Port, KBD_i0_Pin) == GPIO_PIN_SET) { u0 |= (1 << bit0); };
	if (HAL_GPIO_ReadPin(KBD_i1_GPIO_Port, KBD_i1_Pin) == GPIO_PIN_SET) { u0 |= (1 << bit1); };
	if (HAL_GPIO_ReadPin(KBD_i2_GPIO_Port, KBD_i2_Pin) == GPIO_PIN_SET) { u0 |= (1 << bit2); };
	if (HAL_GPIO_ReadPin(KBD_i3_GPIO_Port, KBD_i3_Pin) == GPIO_PIN_SET) { u0 |= (1 << bit3); };

	// DRUGA cifra
	HAL_GPIO_WritePin(KBD_digit0_GPIO_Port, KBD_digit0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KBD_digit1_GPIO_Port, KBD_digit1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KBD_digit2_GPIO_Port, KBD_digit2_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(KBD_digit1_GPIO_Port, KBD_digit1_Pin, GPIO_PIN_RESET);
	osDelay(20);
	//i am  1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
	if (HAL_GPIO_ReadPin(KBD_i0_GPIO_Port, KBD_i0_Pin) == GPIO_PIN_SET) { u1 |= (1 << bit0); };
	if (HAL_GPIO_ReadPin(KBD_i1_GPIO_Port, KBD_i1_Pin) == GPIO_PIN_SET) { u1 |= (1 << bit1); };
	if (HAL_GPIO_ReadPin(KBD_i2_GPIO_Port, KBD_i2_Pin) == GPIO_PIN_SET) { u1 |= (1 << bit2); };
	if (HAL_GPIO_ReadPin(KBD_i3_GPIO_Port, KBD_i3_Pin) == GPIO_PIN_SET) { u1 |= (1 << bit3); };

	// TRECA cifra
	HAL_GPIO_WritePin(KBD_digit0_GPIO_Port, KBD_digit0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KBD_digit1_GPIO_Port, KBD_digit1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KBD_digit2_GPIO_Port, KBD_digit2_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(KBD_digit2_GPIO_Port, KBD_digit2_Pin, GPIO_PIN_RESET);
	osDelay(20);
	//i am  1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
	if (HAL_GPIO_ReadPin(KBD_i0_GPIO_Port, KBD_i0_Pin) == GPIO_PIN_SET) { u2 |= (1 << bit0); };
	if (HAL_GPIO_ReadPin(KBD_i1_GPIO_Port, KBD_i1_Pin) == GPIO_PIN_SET) { u2 |= (1 << bit1); };
	if (HAL_GPIO_ReadPin(KBD_i2_GPIO_Port, KBD_i2_Pin) == GPIO_PIN_SET) { u2 |= (1 << bit2); };
	if (HAL_GPIO_ReadPin(KBD_i3_GPIO_Port, KBD_i3_Pin) == GPIO_PIN_SET) { u2 |= (1 << bit3); };

	hw.UIDbin = (u2 << 8) | (u1 << 4) | u0;
	hw.UIDbcd = (u2 * 10000) + (u1 * 100) + u0;
	hw.id2 = u2;
	hw.id1 = u1;
	hw.id0 = u0;
}


uint32_t getUID_bin() {
	readIDswitches();
	return hw.UIDbin;
}
uint32_t getUID_bcd() {
	readIDswitches();
	return hw.UIDbcd;
}

DaqHw_t getDaqHw() {
	return hw;
}

void INIT_DEVICE_ID() {
	hw.CpuId96bit[0] = HAL_GetUIDw0();
	hw.CpuId96bit[1] = HAL_GetUIDw1();
	hw.CpuId96bit[2] = HAL_GetUIDw2();
	readIDswitches();
}