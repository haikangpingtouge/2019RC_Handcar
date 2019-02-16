/**
	|-------------------------------- Copyright -----------------------------------|
	|                                                                              |
	|                        (C) Copyright 2019,海康平头哥,                         |
	|            1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                               |
	|                                                                              |
	|            By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)          |
	|                     https://github.com/GCUWildwolfteam                       |
	|------------------------------------------------------------------------------|
	|--FileName    : chassis.h                                                
	|--Version     : v1.0                                                            
	|--Author      : 海康平头哥                                                       
	|--Date        : 2019-01-19               
	|--Libsupports : STM32CubeF1 Firmware Package V1.6.0(用别的库出问题别问我)
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end----------------------------|
 **/
#ifndef __CHASSIS_H 
#define __CHASSIS_H 
#include "motor.h" 
#include "wholepositioning.h"
typedef struct chassisStruct
{
	 maxionStruct *pmaxion_t1;
	maxionStruct *pmaxion_t2;
	 maxionStruct *pmaxion_t3;
	 wholePositionStruct *pwholePosition_t;
} chassisStruct;
void ChassisInit(chassisStruct* css);
HAL_StatusTypeDef ChassisParseDate(uint8_t *data);
#endif	// __CHASSIS_H
	
 /*------------------------------------file of end-------------------------------*/


