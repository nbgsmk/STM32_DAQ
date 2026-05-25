/*
 * Trejser.h
 *
 *  Created on: May 10, 2026
 *      Author: peca
 */

#ifndef SRC_RADIO_H_
#define SRC_RADIO_H_


#define MAX_RADIO_MSG_LEN 128						// maksimalna duzina moruke u msgQueue


typedef struct {
	uint64_t tick;
	uint32_t deviceId;
	char txt[MAX_RADIO_MSG_LEN];
} RadioMessage_t;

int getTraceLevel();
void setTraceLevel(int level);

void radioTx1s(osMessageQueueId_t queueHandle, const char txt[]);
void radioTx1s1u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1);
void radioTx1s2u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1, uint32_t argu2);
void radioTx1s3u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1, uint32_t argu2, uint32_t argu3);

void radioTx2s2u(osMessageQueueId_t queueHandle, const char txt1[], const char txt2[], uint32_t aa1, uint32_t argu2);

#endif /* SRC_RADIO_H_ */
