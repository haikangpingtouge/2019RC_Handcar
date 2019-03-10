/**
	|------------------------------- Copyright ----------------------------------|
	|                                                                            |
	|                       (C) Copyright 2019,海康平头哥,                        |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                          All Rights Reserved                               |
	|                                                                            |
	|           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
	|                   https://github.com/GCUWildwolfteam                       |
	|----------------------------------------------------------------------------|
	|--FileName    : chassis.h                                                
	|--Version     : v1.0                                                            
	|--Author      : 海康平头哥                                                       
	|--Date        : 2019-01-19               
	|--Libsupports : 
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|------------------------------declaration of end----------------------------|
 **/
#ifndef __CHASSIS_H 
#define __CHASSIS_H 
#include "motor.h" 
#include "DJI_dbus.h" 
#include "wholepositioning.h"
#include "motion_model.h"
#include "usart_debug.h"
typedef struct chassisStruct
{
	 maxionStruct *pmaxion1_t;
   maxionStruct *pmaxion2_t;
	 maxionStruct *pmaxion3_t;
	 wholePositionStruct *pwholePosition_t;
	 CAN_HandleTypeDef* pmoter_can;

} chassisStruct;
void ChassisInit(void);
HAL_StatusTypeDef ChassisParseDate(uint32_t id,uint8_t *data);
HAL_StatusTypeDef MotorParseDate(uint32_t id,uint8_t *data);
void MotorCanTx(int16_t w1,int16_t w2,int16_t w3);
void ChassisMotorInit(uint8_t mode);
const chassisStruct* GetChassisStructAdd(void);
#endif	// __CHASSIS_H
	
/*-----------------------------------file of end------------------------------*/


