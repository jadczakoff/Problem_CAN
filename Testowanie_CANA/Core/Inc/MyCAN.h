/*
 * MyCAN.h
 *
 *  Created on: Feb 17, 2021
 *      Author: domin
 */

#ifndef INC_MYCAN_H_
#define INC_MYCAN_H_

#include "main.h"
#include "Addresses.h"
#include "uartdma.h"

#define Command_ResetWatchDog 0
#define Command_Write 1
#define Command_Read 2
#define Command_SendFrameToDynamixel 3
#define Command_WriteFromRAMToFLASH 20
#define Command_WriteFromFLASHToRAM 21
#define Command_ResetuC 30
#define Command_BackToDefault 31


typedef struct {

	//////Handlers//////
	CAN_HandleTypeDef* hcan;

	CAN_RxHeaderTypeDef* RxHeader;
	CAN_FilterTypeDef* FilterConfig;
	CAN_TxHeaderTypeDef* TxHeader;
	//uint32_t MyDLC;

	AddressLIST* AL;

	uint32_t Mailbox;




}MyCAN_CAN_HandleTypeDef;

void MyCAN_Init(MyCAN_CAN_HandleTypeDef* Myhcan, AddressLIST* AL ,  CAN_HandleTypeDef* hcan, CAN_FilterTypeDef* FilterConfig, CAN_TxHeaderTypeDef* TxHeader,  CAN_RxHeaderTypeDef* RxHeader);
void MyCAN_IrqHandler(MyCAN_CAN_HandleTypeDef* Myhcan);
void MyCAN_SendMessage(MyCAN_CAN_HandleTypeDef* Myhcan, uint8_t Command, uint8_t Lenght, uint8_t Address, uint8_t *Data);
void MyCAN_ReceiveMessage(MyCAN_CAN_HandleTypeDef* Myhcan);



#endif /* INC_MYCAN_H_ */
