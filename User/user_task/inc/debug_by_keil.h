/**
	|--------------------------------- Copyright --------------------------------|
	|                                                                            |
	|                      (C) Copyright 2019,海康平头哥,                         |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                           All Rights Reserved                              |
	|                                                                            |
	|           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : debug_by_keil.h                                                
	|--Version     : v1.0                                                            
	|--Author      : 海康平头哥                                                       
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


