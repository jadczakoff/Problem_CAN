/*
 * MyCAN.c
 *
 *  Created on: Feb 17, 2021
 *      Author: domin
 */


#include "MyCAN.h"
#include "main.h"
#include "uartdma.h"
#include "Addresses.h"
extern UARTDMA_HandleTypeDef huartdma2;


void MyCAN_Init(MyCAN_CAN_HandleTypeDef* Myhcan,AddressLIST* AL ,  CAN_HandleTypeDef* hcan, CAN_FilterTypeDef* FilterConfig ,  CAN_TxHeaderTypeDef* TxHeader,  CAN_RxHeaderTypeDef* RxHeader){

	Myhcan->hcan = hcan;
	Myhcan->TxHeader = TxHeader;
	Myhcan->RxHeader = RxHeader;
	Myhcan->AL = AL;
	Myhcan->FilterConfig = FilterConfig;


	 FilterConfig->FilterBank = 13;
	  FilterConfig->FilterMode = CAN_FILTERMODE_IDMASK;
	  FilterConfig->FilterScale = CAN_FILTERSCALE_16BIT;
	  FilterConfig->FilterIdHigh = 0x0000;
	  FilterConfig->FilterIdLow = 0x0000;
	  FilterConfig->FilterMaskIdHigh = 0x0000;
	  FilterConfig->FilterMaskIdLow = 0x0000;
	  FilterConfig->FilterFIFOAssignment = CAN_RX_FIFO0;
	  FilterConfig->FilterActivation = CAN_FILTER_ENABLE;


	  if (HAL_CAN_ConfigFilter(hcan, FilterConfig) != HAL_OK)
	  {

	    /* Filter configuration Error */
	    Error_Handler();
	  }



  /* Start the CAN peripheral */
  if (HAL_CAN_Start(hcan) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  /* Activate CAN RX notification */
  if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }

  TxHeader->StdId = AL->MEM[MEM_ID] + 64;
  TxHeader->ExtId = 0x00;
  TxHeader->DLC = 8;
  TxHeader->RTR = CAN_RTR_DATA;
  TxHeader->IDE = CAN_ID_STD;
  TxHeader->TransmitGlobalTime = DISABLE;



}

void MyCAN_IrqHandler(MyCAN_CAN_HandleTypeDef* Myhcan){
	MyCAN_ReceiveMessage(Myhcan);
}

void MyCAN_SendMessage(MyCAN_CAN_HandleTypeDef* Myhcan, uint8_t Command, uint8_t Lenght, uint8_t Address, uint8_t *Data){

		while(HAL_CAN_GetTxMailboxesFreeLevel(Myhcan->hcan)){

				Myhcan->TxHeader->DLC = (uint32_t)Lenght;
				uint8_t Tmp1[Lenght];
				 Tmp1[0] = Command;
				 Tmp1[1] = Lenght;
				 Tmp1[2] = Address;
				for(uint8_t cnt = 3; cnt <= (Lenght - 1); cnt++){
					Tmp1[cnt] = *Data;
					Data++;
				}


				HAL_CAN_AddTxMessage(Myhcan->hcan, Myhcan->TxHeader, Tmp1, &(Myhcan->Mailbox));
		}

}

void MyCAN_ReceiveMessage(MyCAN_CAN_HandleTypeDef* Myhcan){

	uint8_t TmpBuffor[8];

		if(HAL_CAN_GetRxMessage(Myhcan->hcan, CAN_RX_FIFO0, Myhcan->RxHeader, TmpBuffor) == HAL_OK){

			// \/ Lenght of Message without Command, Addresses and DLC
			uint8_t LenghtData = TmpBuffor[1] - 3;
			uint8_t TmpToReceive[LenghtData];
			uint8_t TmpToSend[LenghtData];




			switch(Myhcan->RxHeader->StdId){
			case 66:
				if(TmpBuffor[0] == 1){
					//Writing to private table only Dates then overwrite in MEM Table
					uint8_t anothercnt = 0;
					for(uint8_t cnt = 3; cnt < TmpBuffor[1]; cnt++){
						TmpToSend[anothercnt] = TmpBuffor[cnt];
						anothercnt++;
					}
						MemWriteTable(Myhcan->AL,TmpBuffor[2], LenghtData, TmpToSend);


					}
				else if(TmpBuffor[0] == 2){

						MemReadTable(Myhcan->AL, TmpBuffor[2], LenghtData,  TmpToReceive);
						MyCAN_SendMessage(Myhcan, Command_Write, TmpBuffor[1], TmpBuffor[2], TmpToReceive);

				}
				break;

			default:

				break;
			}

		}

}
