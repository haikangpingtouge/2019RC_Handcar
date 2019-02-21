#ifndef __NIMING_H
#define __NIMING_H
#ifdef DEBUG_BY_KEIL
#include "baseclass.h"

typedef struct 
{
	void(*f)(float,float,UART_HandleTypeDef* huart);
	void(*i16)(int16_t,int16_t,UART_HandleTypeDef* huart);
	void(*uint32)(uint32_t data);
	uint8_t flag;
}Niming_Class;
extern Niming_Class  nimingDebug_t;
#endif
#endif	// __NIMING_H
