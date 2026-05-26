//
// Created by peca on 19-Mar-26.
//

#ifndef ETVDAQ_MERENJAHOLDER_H
#define ETVDAQ_MERENJAHOLDER_H


#define MAX_DIGITAL_INPUTS 32
#define MAX_ANALOG_INPUTS 32


typedef struct {
	uint32_t measuredValue;

	uint32_t alarmThreshold;
	int32_t alarmPolarity;			// -1=ALARM_ISPOD, 0=NO_ALARM, +1=alarm_IZNAD
	uint32_t hysteresisValue;
} ADinput_t;


void INIT_MERENJA_HOLDER();




/*
 * DIGITALNI ULAZI
 */
uint32_t getDigitalResult();
osStatus_t setDigitalResult(uint32_t arg);

/*
 * ANALOGNI ULAZI
 */
int getAnalogResult(uint32_t inputNumber);
osStatus_t setAnalogResult(uint32_t inputNumber, uint32_t value);


osStatus_t setAnalogInputCfg(uint32_t inputNumber, int alarmThreshold, int alarmPolarity, uint32_t hysteresisValue);
ADinput_t getAnalogInputCfg(uint32_t inputNumber);

#endif //ETVDAQ_MERENJAHOLDER_H
