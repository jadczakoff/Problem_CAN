/*
 * ring_buffer.h
 *
 *  Created on: Jan 18, 2021
 *      Author: domin
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#define RING_BUFFER_SIZE 64

typedef enum {

	Rb_OK = 0,
	Rb_ERROR = 1

}Rb_Status;


typedef struct {

	uint8_t Head;
	uint8_t Tail;
	uint8_t Buffer[RING_BUFFER_SIZE];

}RingBuffer;

Rb_Status Rb_Read(RingBuffer *rb, uint8_t *Value);
Rb_Status Rb_Write(RingBuffer *rb, uint8_t Value);


#endif /* INC_RING_BUFFER_H_ */
