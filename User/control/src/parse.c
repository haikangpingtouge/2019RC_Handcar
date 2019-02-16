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
	|--FileName    : parse.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
	|--Date        : 2019-02-02             
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
#include "parse.h" 
/* -------------- 外部链接 ----------------- */
 extern uint8_t can1_rx[12];
	/**
		* @Data    2019-02-14 14:36
		* @brief   数据解析
		* @param   void
		* @retval  void
		*/
		void ParseData(void)
		{
			uint32_t can_id = 0;
//	  	ByleToMultibyte(&can1_rx[8],&can_id);
			ChassisParseDate(can_id,can1_rx);
//			UserCanQueueRX(&hcan1,can1_rx);//cam1接收
			// ByleToMultibyte(&can1_rx[8],&can_id)
		}
/*-----------------------------------file of end------------------------------*/


