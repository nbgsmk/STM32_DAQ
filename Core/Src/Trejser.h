/*
 * Trejser.h
 *
 *  Created on: May 10, 2026
 *      Author: peca
 */

#ifndef SRC_TREJSER_H_
#define SRC_TREJSER_H_

#include "main.h"

#define MAX_TRACE_MSG_LEN 128						// maksimalna duzina moruke u msgQueue

typedef enum {
	dbg_0 = 0,
	dbg_1,
	dbg_2,
	dbg_3,
	dbg_4,
	dbg_5,
	dbg_6,
	dbg_7,
} DbgLev_t;

typedef struct {
	DbgLev_t debugLevel;
	char txt[MAX_TRACE_MSG_LEN];
} TraceMessage_t;

int getTraceLevel();
void setTraceLevel(int level);

void   tracePrint1s(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt[]);
void   tracePrint1s1u(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt[], uint32_t argu1);
void   tracePrint1s2u(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt[], uint32_t argu1, uint32_t argu2);
void tracePrint2s2u(osMessageQueueId_t queueHandle, DbgLev_t debugVerbosity, const char txt1[], const char txt2[], uint32_t argu1, uint32_t argu2);


#endif /* SRC_TREJSER_H_ */
