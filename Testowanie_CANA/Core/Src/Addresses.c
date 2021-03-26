/*
 * Addresses.c
 *
 *  Created on: Feb 24, 2021
 *      Author: domin
 */
#include "Addresses.h"



void MemTable_Init(AddressLIST *AL){
//Wartości domyślne -----------
AL->MEM[MEM_ID] = 1;
AL->MEM[ MEM_HARD_VER ] = 10;
AL->MEM[ MEM_SOFT_VER ] = 10;
AL->MEM[ MEM_LOCK ] = 0;
AL->MEM[ MEM_ANS_MODE ] = 0b00000001;
AL->MEM[ MEM_ANS ] = 0b00000001;
AL->MEM[ MEM_UC_TEMP ] = 0;
AL->MEM[ MEM_UC_MAX_TEMP ] = 50;

}

void MemWriteTable(AddressLIST *AL, uint8_t Address ,uint8_t Lenght,  uint8_t *Value){
    uint8_t *TmpPointer;
    TmpPointer = (uint8_t *)Value;
    for(uint8_t cnt = 0; cnt < Lenght; cnt++){

    AL->MEM[Address++] = *TmpPointer;

    TmpPointer++;
    }


}

void MemReadTable(AddressLIST *AL, uint8_t Address, uint8_t Lenght, const uint8_t *OutBuffer){

    uint8_t *TmpPointer;

    TmpPointer = (uint8_t *)OutBuffer;

    for(uint8_t cnt = 0; cnt <= Lenght; cnt++){
    *TmpPointer = AL->MEM[Address++];
    TmpPointer++;
    }
}
