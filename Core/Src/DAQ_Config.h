//
// Created by peca on 19-Mar-26.
//

#ifndef ETVDAQ_DAQ_CONFIG_H
#define ETVDAQ_DAQ_CONFIG_H


#include <stdint.h>
#include "main.h"
#include "cmsis_os2.h"

// default vrednosti treba pregaziti u .c fajlu
static uint32_t HW_HEARTBEAT_TICKS = 	1000U * 10;		// period blinkanja led diode
static uint32_t ADC_NUMof_INPUTS = 		15;
static uint32_t ADC_PERIOD_TICKS = 		1000U *3;		// period izmedju dva ADC merenja



osStatus_t INIT_DAQ_HW();
osStatus_t INIT_ADC();
osStatus_t INIT_DIGITAL_INPUTS();
osStatus_t INIT_RADIO();


/////////////
// HARDWARE
////////////

uint32_t cfg_GetHeartbeatPeriod();
void cfg_SetHeartbeatPeriod(uint32_t period_mS);

//////////////////////
// ADC CONFIGURATION
//////////////////////

uint32_t getAdcPeriodTicks();
void setAdcPeriodTicks(uint32_t adcPeriodTicks);

int getADC_RESULT(uint32_t inputNumber);
void setADC_RESULT(uint32_t inputNumber, int thresholdValue);


int getADC_THRESHOLD(uint32_t inputNumber);
void setADC_THRESHOLD(uint32_t inputNumber, int thresholdValue);
void setADC_ALL_THRESHOLDS(int thresholdValue);

uint32_t getAD_HYSTR(uint32_t inputNumber);
void setAD_HYSTR(uint32_t inputNumber, uint32_t hysteresisValue);


#endif //ETVDAQ_DAQ_CONFIG_H


