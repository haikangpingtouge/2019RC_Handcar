/**
	|--------------------------------- Copyright --------------------------------|
	|                                                                            |
	|                      (C) Copyright 2019,����ƽͷ��,                         |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                           All Rights Reserved                              |
	|                                                                            |
	|           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : debug_by_keil.h                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-02-23               
	|--Libsupports : 
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|-----------------------------declaration of end-----------------------------|
 **/
#ifndef __DEBUG_BY_KEIL_H 
#define __DEBUG_BY_KEIL_H 
#include "auto_chassis.h" 
#include "rc_chassis.h" 
#include "leds_tip.h" 
#include "parse.h" 
#ifdef DEBUG_BY_KEIL
typedef struct debugByKeilStruct
{
	bezierStruct* pbezier_t;
}debugByKeilStruct;
extern debugByKeilStruct debugByKeil_t;
void DebugByKeilInit(void);
#endif
#endif	// __DEBUG_BY_KEIL_H
/*-----------------------------------file of end------------------------------*/


