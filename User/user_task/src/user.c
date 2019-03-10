/**
	|--------------------------------- Copyright --------------------------------|
	|                                                                            |
	|                      (C) Copyright 2018,海康平头哥,                         |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                           All Rights Reserved                              |
	|                                                                            |
	|           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : user.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
	|--Date        : 2018-11-27             
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
#include "user.h" 
 /**
	* @Data    2019-01-16 19:28
	* @brief  系统初始化
	* @param   void
	* @retval  void
	*/
		void SysInit(void)
		{ 
			SysInitCreate();
#ifdef DEBUG_BY_KEIL //keil调试初始化
			DebugByKeilInit();
#endif
		}
 /**
	* @Data    2019-02-20 21:11
	* @brief   用户IO口设置
	* @param   void
	* @retval  void
	*/
	void UserIOInit(void)
	{
#if RM_OLD_BOARD
		HAL_GPIO_DeInit(GPIOE, LED5_Pin|LED1_Pin|LED3_Pin|LED6_Pin 
																		|LED2_Pin|LED4_Pin|LED7_Pin);
		HAL_GPIO_DeInit(LASER_GPIO_Port,LASER_Pin);
#endif 
	}
/*-----------------------------------file of end------------------------------*/
 



