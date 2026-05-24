//
// Created by peca on 19-Mar-26.
//

#include <stdint.h>
#include "DAQ_Config.h"
#include "MerenjaHolder.h"

osStatus_t INIT_DAQ_HW(){
	INIT_MERENJA_HOLDER();
	return osOK;
}

osStatus_t INIT_ADC(){


	// init all inputs
	for (int i = 0; i < ADC_NUMof_INPUTS; ++i) {
		setAnalogInputCfg(i, 0, 0, 0);
	}

	setAnalogInputCfg(0, 2000, 0, 50);
	setAnalogInputCfg(1, 2001, 1, 51);
	setAnalogInputCfg(2, 2002, 2, 52);
	setAnalogInputCfg(3, 2003, 3, 53);
	setAnalogInputCfg(4, 2004, 4, 54);
	setAnalogInputCfg(5, 2005, 5, 55);
	setAnalogInputCfg(6, 2006, 6, 56);
	setAnalogInputCfg(7, 2007, 7, 57);
	return osOK;
}

osStatus_t INIT_DIGITAL_INPUTS(){
	return osOK;
}


/////////////
// HARDWARE
////////////


uint32_t cfg_GetHeartbeatPeriod() {
	return HW_HEARTBEAT_TICKS;
}
void cfg_SetHeartbeatPeriod(uint32_t periodTicks) {
	HW_HEARTBEAT_TICKS = periodTicks;
	// TODO write to flash
}


//////////////////////
// ADC CONFIGURATION
//////////////////////


uint32_t getAdcPeriodTicks(){
	return ADC_PERIOD_TICKS;
}
void setAdcPeriodTicks(uint32_t adcPeriodTicks){
	ADC_PERIOD_TICKS = adcPeriodTicks;
}


///////////////////////
// RADIO CONFIGURATION
///////////////////////

osStatus_t INIT_RADIO(){
	// TODO radio init
	return osOK;
}


