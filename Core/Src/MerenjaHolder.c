//
// Created by peca on 19-Mar-26.
//

#include <stdint.h>
#include "cmsis_os2.h"

#include "MerenjaHolder.h"
#include "Kalendar.h"
#include "stm32f4xx_hal.h"


osMutexId_t mutexMerenjaHandle;
const osMutexAttr_t mutexMerenja_attributes = {
	.name = "mutexMerenja"
};


typedef struct {
	uint32_t uid96bit[3];
	uint32_t UID_bin;
	uint32_t UID_bcd;
	uint32_t timeStamp;
	uint32_t digitalInputs;							// 32 bita za digitalne ulaze, sto nikada nece biti
	ADinput_t analogInput[MAX_ANALOG_INPUTS];		// TODO nikad nece biti 32 kanala. ispraviti da bude hadc1.Init.NbrOfConversion
} CurMerenja_t;

CurMerenja_t curMerenja;
const uint32_t 	structTimeout = 100;		// (mS) max cekanje da merenjaStruct postane slobodan

void INIT_MERENJA_HOLDER() {
	mutexMerenjaHandle = osMutexNew(&mutexMerenja_attributes);
	curMerenja.uid96bit[0] = HAL_GetUIDw0();
	curMerenja.uid96bit[1] = HAL_GetUIDw1();
	curMerenja.uid96bit[2] = HAL_GetUIDw2();
}

/*
 * UID = Uredjaj ID
 */
void setUID(uint8_t u0, uint8_t u1, uint8_t u2) {
	curMerenja.UID_bin = (u2 << 8) | (u1 << 4) | u0;
	curMerenja.UID_bcd = (u2 * 10000) + (u1 * 100) + u0;
}
uint32_t getUID_bin() {
	return curMerenja.UID_bin;
}
uint32_t getUID_bcd() {
	return curMerenja.UID_bcd;
}


CurMerenja_t get() {
	return curMerenja;
}

uint32_t getDigitalResult() {
	return curMerenja.digitalInputs;
}
osStatus_t setDigitalResult(uint32_t value) {
	osStatus_t stat = osMutexAcquire(mutexMerenjaHandle, structTimeout);
	if (stat == osOK) {
		curMerenja.timeStamp = getTimestamp();
		curMerenja.digitalInputs = value;
	} else {
		// isteklo vreme, ne upisujem nista ali vraticu osStatus != ok
	}
	osMutexRelease(mutexMerenjaHandle);
	return stat;
}

/**
 *
 */
int getAnalogResult(uint32_t inputNumber){
	return curMerenja.analogInput[inputNumber].measuredValue;
}
osStatus_t setAnalogResult(uint32_t inputNumber, uint32_t value) {
	osStatus_t stat = osMutexAcquire(mutexMerenjaHandle, structTimeout);
	if (stat == osOK) {
		curMerenja.timeStamp = getTimestamp();
		curMerenja.analogInput[inputNumber].measuredValue = value;
	} else {
		// isteklo vreme, ne upisujem nista ali vracam osStatus != ok
	}
	osMutexRelease(mutexMerenjaHandle);
	return stat;
}

/**
 * @retval return struct with adc input config and measured value
 * @see setAnalogInputCfg(...)
 */
ADinput_t getAnalogInputCfg(uint32_t inputNumber){
	return curMerenja.analogInput[inputNumber];
}


/**
 *
 * @param inputNumber which adc input is being configured
 * @param alarmThreshold alarm is signalled if this adc value is crossed
 * @param alarmPolarity -1=alarm_BELOW, 0=NO_ALARM, +1=alarm_ABOVE threshold
 * @param hysteresisValue ensures alarm stability ie prevent flapping
 */
osStatus_t setAnalogInputCfg(uint32_t inputNumber, int alarmThreshold, int alarmPolarity, uint32_t hysteresisValue){
	osStatus_t stat = osMutexAcquire(mutexMerenjaHandle, structTimeout);
	if (stat == osOK) {
		curMerenja.analogInput[inputNumber].alarmThreshold = alarmThreshold;
		curMerenja.analogInput[inputNumber].alarmPolarity = alarmPolarity;
		curMerenja.analogInput[inputNumber].hysteresisValue = hysteresisValue;
	} else {
		// isteklo vreme, ne upisujem nista ali vraticu osStatus != ok
	}
	osMutexRelease(mutexMerenjaHandle);
	return stat;
}


