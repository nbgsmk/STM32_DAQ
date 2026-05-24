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

void sendit(osMessageQueueId_t queue, const char txt[]) {
	snprintf(rmsg.txt, sizeof(rmsg.txt), "%llu %s \n\r", rmsg.msgSequence++, txt);
	osMessageQueuePut(queue, &rmsg, 0U, 100);
}
void radioTx1s(osMessageQueueId_t queueHandle, const char txt[]){
	RadioMessage_t r;
	snprintf(r.txt, sizeof(r.txt), "%s", txt);
	sendit(queueHandle, r.txt);
}
void radioTx1s1u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1){
	RadioMessage_t t;
	snprintf(t.txt, sizeof(t.txt), "%s %d", txt, argu1);
	sendit(queueHandle, t.txt);
}
void radioTx1s2u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1, uint32_t argu2){
	RadioMessage_t t;
	snprintf(t.txt, sizeof(t.txt), "%s %d %d", txt, argu1, argu2);
	sendit(queueHandle, t.txt);
}
void radioTx1s3u(osMessageQueueId_t queueHandle, const char txt[], uint32_t argu1, uint32_t argu2, uint32_t argu3){
	RadioMessage_t t;
	snprintf(t.txt, sizeof(t.txt), "%s %d %d %d", txt, argu1, argu2, argu3);
	sendit(queueHandle, t.txt);
}

void radioTx2s2u(osMessageQueueId_t queueHandle, const char txt1[], const char txt2[], uint32_t argu1, uint32_t argu2){
	RadioMessage_t t;
	snprintf(t.txt, sizeof(t.txt), "%s %s %d %d", txt1, txt2, argu1, argu2);
	sendit(queueHandle, t.txt);
}

