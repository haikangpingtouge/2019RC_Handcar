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
	|--FileName    : rc_gimbal.h                                                
	|--Version     : v1.0                                                            
	|--Author      : 桂灿                                                       
	|--Date        : 2019-02-21               
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
#ifndef __RC_GIMBAL_H 
#define __RC_GIMBAL_H 
#include "gimbal.h" 
#include "DJI_dbus.h" 
void RcGimbalControl(const dbusStruct* rc);
#endif	// __RC_GIMBAL_H
/*-----------------------------------file of end------------------------------*/


