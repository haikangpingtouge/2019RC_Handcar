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
	|--FileName    : auto_chassis.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
	|--Date        : 2019-02-20             
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
#include "auto_chassis.h" 
int16_t wheel_speed[3];
 /**
	* @Data    2019-02-16 09:53
	* @brief   自动底盘控制服务函数
	* @param   void
	* @retval  void
	*/
	void AutoChassisControl(const dbusStruct* rc)
	{
		ThreeWheelMotionModel(wheel_speed,400,0,0);
    MotorCanTx(wheel_speed[0],wheel_speed[1],wheel_speed[2]);
	}
/*-----------------------------------file of end------------------------------*/


