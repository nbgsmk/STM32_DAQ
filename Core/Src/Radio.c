/*
 * Trejser.c
 *
 *  Created on: May 10, 2026
 *      Author: peca
 */


#include <stdio.h>
#include "main.h"
#include "cmsis_os2.h"
#include "Radio.h"

RadioMessage_t rmsg;
//
//static int CUR_VERBOSITY = 100;
//
//int getTraceLevel(){
//	return CUR_VERBOSITY;
//}
//void setTraceLevel(int level){
//	CUR_VERBOSITY = level;
//}
//
//void tracePrint(osMessageQueueId_t queue, DbgLev_t debugVerbosity, const char *txt){
//	if (debugVerbosity <= CUR_VERBOSITY ) {
//		tmsg.debugLevel = debugVerbosity;
//		snprintf(tmsg.txt, sizeof(tmsg.txt), "%s \n\r", txt);
//		osMessageQueuePut(queue, &tmsg, 0U, 10);
//	}
//}

void radioTx1s(osMessageQueueId_t queueHandle, const char txt[]){
	;
}
void radioTx1s1u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1){
	;
}
void radioTx1s2u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1, uint32_t argu2){
	;
}
void radioTx1s3u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1, uint32_t argu2, uint32_t argu3){
	;
}



void radioTx2s2u(osMessageQueueId_t queueHandle, const char txt1[], const char txt2[], uint32_t aa1, uint32_t argu2){
	;
}


