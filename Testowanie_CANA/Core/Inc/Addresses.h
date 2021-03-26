/*
 * Addresses.h
 *
 *  Created on: Feb 24, 2021
 *      Author: domin
 */

#ifndef INC_ADDRESSES_H_
#define INC_ADDRESSES_H_

#include "main.h"

//Adresy w tablicy zapisu do FLASH
#define FLASH_ID 0 //Ustawienia płytki
#define FLASH_HARD_VER 1
#define FLASH_SOFT_VER 2
#define FLASH_LOCK 3
#define FLASH_ANS_MODE 4
#define FLASH_UC_MAX_TEMP 5


//Adresy w tablicy zapisu do RAM
#define MEM_ID 0 //Ustawienia płytki
#define MEM_HARD_VER 1
#define MEM_SOFT_VER 2
#define MEM_LOCK 3
#define MEM_ANS_MODE 4 //bit 0 - włącz automatyczne wysyłanie
//bit 1 - włącz wysyłanie po każdym odpytaniu
#define MEM_ANS 5
#define MEM_UC_TEMP 6
#define MEM_UC_MAX_TEMP 7



typedef struct{

	uint8_t MEM[141];

}AddressLIST;

void MemTable_Init(AddressLIST *AL);
void MemWriteTable(AddressLIST *AL, uint8_t Address ,uint8_t Lenght,  uint8_t *Value);
void MemReadTable(AddressLIST *AL, uint8_t Address, uint8_t Lenght, const uint8_t *OutBuffer);

#endif /* INC_ADDRESSES_H_ */
