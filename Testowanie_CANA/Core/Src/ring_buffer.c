/*
 * ring_buffer.c
 *
 *  Created on: Jan 18, 2021
 *      Author: domin
 */
#include "main.h"
#include "ring_buffer.h"


Rb_Status Rb_Read(RingBuffer *rb, uint8_t *Value){

	if(rb->Head == rb->Tail){

		return Rb_ERROR;
	}

	*Value = rb->Buffer[rb->Tail];

	rb->Tail = (rb->Tail + 1) % RING_BUFFER_SIZE;

	return Rb_OK;
}

Rb_Status Rb_Write(RingBuffer *rb, uint8_t Value){

	uint8_t TmpHead = (rb->Head + 1) % RING_BUFFER_SIZE;

	if(TmpHead == rb->Tail){
		return Rb_ERROR;
	}

	rb->Buffer[rb->Head] = Value;
	rb->Head = TmpHead;

	return Rb_OK;
}
