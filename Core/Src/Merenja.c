//
// Created by peca on 19-Mar-26.
//

#include <stdint.h>
#include "cmsis_os2.h"

#include "Merenja.h"
#include "Kalendar.h"

osMutexId_t mutexMerenjaHandle;
const osMutexAttr_t mutexMerenja_attributes = {
	.name = "mutexMerenja"
};


typedef struct {
	uint32_t UID;
	uint32_t timeStamp;
	uint32_t digitalInputs;			// 32 bita za digitalne ulaze, sto nikada nece biti
	ADinput_t analogInput[32];		// TODO nikad nece biti 32 kanala. ispraviti da bude hadc1.Init.NbrOfConversion
} CurMerenja_t;

CurMerenja_t curMerenja;
const uint32_t 	structTimeout = 100;		// (mS) max cekanje da merenjaStruct postane slobodan



/*
 * UID = Uredjaj ID
 */
void setUID(uint8_t u0, uint8_t u1, uint8_t u2) {
	curMerenja.UID = u0 | (u1 << 8) | (u2 << 16);
}
uint32_t getUID() {
	return curMerenja.UID;
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


