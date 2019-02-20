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
	|--FileName    : rc_chassis.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 桂灿                                                     
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
#include "rc_chassis.h" 
	/**
		* @Data    2019-02-20 13:31
		* @brief   手动底盘控制服务函数
		* @param   void
		* @retval  void
		*/
		void RcChassisControl(const dbusStruct* rc)
		{
			int16_t temp_wheel_speed[3];
			/* ------ 运动模型 ------- */
			ThreeWheelMotionModel(temp_wheel_speed,-4*rc->ch1,-4*rc->ch2,-4*rc->ch3);
			/* ------ 速度分解后can发送 ------- */		
   	  MotorCanTx(temp_wheel_speed[0],temp_wheel_speed[1],temp_wheel_speed[2]);
		}
	
/*-----------------------------------file of end------------------------------*/


