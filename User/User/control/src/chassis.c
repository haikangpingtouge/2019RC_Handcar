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
	|--FileName    : chassis.c                                                
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
#include "chassis.h"
  maxionStruct maxion_t1;
	maxionStruct maxion_t2;
	maxionStruct maxion_t3;
	wholePositionStruct wholePosition_t;
	extern CAN_HandleTypeDef hcan1;
	extern UART_HandleTypeDef huart6;//串口1
#define MODILE_ID1 1
#define MODILE_ID2 2
#define MODILE_ID3 3
	/*---------------------------------80字符限制-----------------------------------*/
	/**
	* @Data    2019-01-19 11:45
	* @brief   底盘数据解析
	* @param   chassisStruct* css 底盘结构体指针
	* @retval  void
	*/
	void ChassisInit(chassisStruct* css)
	{
		css->pmaxion_t1 = &maxion_t1;
		css->pmaxion_t2 = &maxion_t2;
		css->pmaxion_t3 = &maxion_t3;
		css->pwholePosition_t = &wholePosition_t;
		/* -------- maxion_t1 --------- */
		maxion_t1.hcanx = &hcan1;
		maxion_t1.real_current = 0;
		maxion_t1.real_velocity = 0;
		maxion_t1.module_id = MODILE_ID1; //驱动编号
		/* -------- maxion_t2 --------- */
			maxion_t2.hcanx = &hcan1;
			maxion_t2.real_current = 0;
			maxion_t2.real_velocity = 0;
			maxion_t2.module_id =MODILE_ID2;//驱动编号
		/* -------- maxion_t3 --------- */
			maxion_t3.hcanx = &hcan1;
			maxion_t3.real_current = 0;
			maxion_t3.real_velocity = 0;
	    maxion_t3.module_id = MODILE_ID3;//驱动编号
			UserCanConfig(&hcan1);

			WholePositioningInit(&wholePosition_t, &huart6);

	}
/*---------------------------------80字符限制-----------------------------------*/
	/**
	* @Data    2019-01-19 12:01
	* @brief   底盘数据解析
	* @param   Peripheral type外设类型,串口CAN_HandleTypeDef,can的CAN_HandleTypeDef
	* @retval  void
	*/
	HAL_StatusTypeDef ChassisParseDate(uint8_t *data)
	{
    uint32_t id =0;
    id = (uint32_t)(data[0]<<24|data[1]<<16|data[2]<<8|data[3]);
    if(id != MODILE_ID1 && id != MODILE_ID2 && id != MODILE_ID3)
      return HAL_BUSY;
		switch (id) 
		{
			case MODILE_ID1:
			MaxionParseData(&maxion_t1,data);
				break;
			case MODILE_ID2:
				MaxionParseData(&maxion_t2,data);
				break;
			case MODILE_ID3:
				MaxionParseData(&maxion_t3,data);
				break;
			default:
				break;
		}
    return HAL_OK;
	}
	/*------------------------------------file of end-------------------------------*/
