//
// Created by peca on 19-Mar-26.
//

#include <stdint.h>
#include "DAQ_Config.h"
#include "Merenja.h"

osStatus_t INIT_DAQ_HW(){
	return osOK;
}

osStatus_t INIT_ADC(){

	// init all inputs
	for (int i = 0; i < ADC_NUMof_INPUTS; ++i) {
		setAnalogInputCfg(i, 0, 0, 0);
	}

	setAnalogInputCfg(0, 2000, 1, 50);
	setAnalogInputCfg(1, 2000, 1, 50);
	setAnalogInputCfg(2, 2000, 1, 50);
	setAnalogInputCfg(3, 2000, 1, 50);
	setAnalogInputCfg(4, 2000, 1, 50);
	setAnalogInputCfg(5, 2000, 1, 50);
	setAnalogInputCfg(6, 2000, 1, 50);
	setAnalogInputCfg(7, 2000, 1, 50);
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


