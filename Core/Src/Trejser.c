/*
 * Trejser.c
 *
 *  Created on: May 10, 2026
 *      Author: peca
 */


#include <stdio.h>
#include "main.h"
#include "cmsis_os2.h"
#include "Trejser.h"

TraceMessage_t tmsg;

static int CUR_VERBOSITY = 100;

int getTraceLevel(){
	return CUR_VERBOSITY;
}
void setTraceLevel(int level){
	CUR_VERBOSITY = level;
}

void tracePrint1s(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt[]){
	if (debugVerbosity <= CUR_VERBOSITY ) {
		tmsg.debugLevel = debugVerbosity;
		snprintf(tmsg.txt, sizeof(tmsg.txt), "%s \n\r", txt);
		osMessageQueuePut(queueHandle, &tmsg, 0U, 10);
	}
}


void tracePrint1u(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt[], uint32_t argu1){
	snprintf(tmsg.txt, sizeof(tmsg.txt), "%s %d", txt, (unsigned int)argu1);
	tracePrint1s(queueHandle, debugVerbosity, tmsg.txt);
}
void tracePrint2u(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt[], uint32_t argu1, uint32_t argu2){
	snprintf(tmsg.txt, sizeof(tmsg.txt), "%s %d %d", txt, (unsigned int)argu1, (unsigned int)argu2);
	tracePrint1s(queueHandle, debugVerbosity, tmsg.txt);
}
void tracePrint2s2u(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt1[], const char txt2[], uint32_t argu1, uint32_t argu2){
	snprintf(tmsg.txt, sizeof(tmsg.txt), "%s: %s %d %d", txt1, txt2, (unsigned int)argu1, (unsigned int)argu2);
	tracePrint1s(queueHandle, debugVerbosity, tmsg.txt);
}

