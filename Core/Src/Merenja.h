//
// Created by peca on 19-Mar-26.
//

#ifndef ETVDAQ_MERENJA_H
#define ETVDAQ_MERENJA_H


typedef struct {
	uint32_t measuredValue;

	uint32_t alarmThreshold;
	int32_t alarmPolarity;			// -1=ALARM_ISPOD, 0=NO_ALARM, +1=alarm_IZNAD
	uint32_t hysteresisValue;
} ADinput_t;

/*
 * UID = Uredjaj ID
 */
void setUID(uint32_t u0, uint32_t u1, uint32_t u2);
uint32_t getUID();


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

#endif //ETVDAQ_MERENJA_H
