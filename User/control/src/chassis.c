/**
	|------------------------------- Copyright ----------------------------------|
	|                                                                            |
	|                        (C) Copyright 2019,海康平头哥,                       |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                             |
	|                                                                            |
	|           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : chassis.c                                                
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
	|-------------------------------declaration of end---------------------------|
 **/
#include "chassis.h"
/* -------------- 结构体声明 ----------------- */
  chassisStruct chassis_t;//底盘
  maxionStruct maxion1_t;
	maxionStruct maxion2_t;
	maxionStruct maxion3_t;
	wholePositionStruct wholePosition_t;
/* -------------- 外部链接 ----------------- */
	extern CAN_HandleTypeDef hcan1;
	extern UART_HandleTypeDef huart6;//串口1
/* -------------- 私有宏 ----------------- */
#define MODILE_ID1 1
#define MODILE_ID2 2
#define MODILE_ID3 3
#define SPEED_LOOP_PWM			0//速度模式电流限值
/*   Group   取值范围 0-7
    Number  取值范围 0-15
	其中Number==0时，为广播发送*/
#define MOTOR1_GROUP				0//电机1的组号
#define MOTOR1_NUMBER				1//电机1的成员号
#define MOTOR2_GROUP				0//电机2的组号
#define MOTOR2_NUMBER				2//电机2的成员号
#define MOTOR3_GROUP				0//电机3的组号
#define MOTOR3_NUMBER				3//电机3的成员号
	/**
	* @Data    2019-01-19 11:45
	* @brief   底盘数据解析
	* @param   chassisStruct* css 底盘结构体指针
	* @retval  void
	*/
	void ChassisInit(void)
	{
		chassis_t.pmaxion1_t = &maxion1_t;
		chassis_t.pmaxion2_t = &maxion2_t;
		chassis_t.pmaxion3_t = &maxion3_t;
		chassis_t.pwholePosition_t = &wholePosition_t;
		chassis_t.pmoter_can = &hcan1;
		/* -------- maxion_t1 --------- */
			maxion1_t.hcanx = NULL;
			maxion1_t.real_current = 0;
			maxion1_t.real_velocity = 0;
			maxion1_t.module_id =        \
		  MOTOR_CAN_ID_CAL(MOTOR1_GROUP,MOTOR1_NUMBER); //电机1发送id
		/* -------- maxion_t2 --------- */
			maxion2_t.hcanx = NULL;
			maxion2_t.real_current = 0;
			maxion2_t.real_velocity = 0;
			maxion2_t.module_id =        \
		  MOTOR_CAN_ID_CAL(MOTOR2_GROUP,MOTOR2_NUMBER); //电机2发送id
		/* -------- maxion_t3 --------- */
			maxion3_t.hcanx = NULL;
			maxion3_t.real_current = 0;
			maxion3_t.real_velocity = 0;
	   	maxion3_t.module_id =        \
		  MOTOR_CAN_ID_CAL(MOTOR3_GROUP,MOTOR3_NUMBER); //电机3发送id
			UserCanConfig(chassis_t.pmoter_can);
			WholePositioningInit(&wholePosition_t, &huart6);//全场定位初始化
      ChassisMotorInit(openloop_mode_e);
	}
	/**
	* @Data    2019-01-19 12:01
	* @brief   底盘数据解析
	* @param   Peripheral type外设类型,串口CAN_HandleTypeDef,can的 CAN_HandleTypeDef
	* @retval  void
	*/
	HAL_StatusTypeDef ChassisParseDate(uint32_t id,uint8_t *data)
	{
   	// MotorParseDate(id,data);//can数据解析
		ParseWholePositioningInfo(chassis_t.pwholePosition_t);//全场定位数据解析
    return HAL_OK;
	}
/**
	* @Data    2019-02-16 10:40
	* @brief   底盘can数据解析 (电机数据)
	* @param   void
	* @retval  void
	*/
	HAL_StatusTypeDef MotorParseDate(uint32_t id,uint8_t *data)
	{
		if(id != MODILE_ID1 && id != MODILE_ID2 && id != MODILE_ID3)
      return HAL_BUSY;
		switch (id) 
		{
			case MODILE_ID1:
			  MaxionParseData(&maxion1_t,data);
				break;
			case MODILE_ID2:
				MaxionParseData(&maxion2_t,data);
				break;
			case MODILE_ID3:
				MaxionParseData(&maxion3_t,data);
				break;
			default:
				break;
		}
    return HAL_OK;
	}
/**
	* @Data    2019-02-16 09:53
	* @brief   底盘控制服务函数
	* @param   void
	* @retval  void
	*/
	void ChassisControl(dbusStruct* rc)
	{
//		MotorCanTx(20,20,20);
	}
	/**
	* @Data    2019-02-15 14:15
	* @brief   速度环数据发送
	* @param   void
	* @retval  void
	*/
	void MotorCanTx(int16_t w1,int16_t w2,int16_t w3)
	{
		uint8_t s[8]={0};
    SpeedLoopMode(SPEED_LOOP_PWM,w1,s);
		CanTxMsg(chassis_t.pmoter_can,maxion1_t.module_id,s);
		DataFilling(s,0,8);
		SpeedLoopMode(SPEED_LOOP_PWM,w2,s);
		CanTxMsg(chassis_t.pmoter_can,maxion2_t.module_id,s);
		DataFilling(s,0,8);
		SpeedLoopMode(SPEED_LOOP_PWM,w2,s);
		CanTxMsg(chassis_t.pmoter_can,maxion3_t.module_id,s);
		DataFilling(s,0,8);
	}
 /**
	 * @Data    2019-02-16 16:52 
	 * @brief   底盘电机初始化
	 * @param   void
	 * @retval  void
	 */
	 void ChassisMotorInit(uint8_t mode)
	 {
		 	 ResetMode(chassis_t.pmoter_can,maxion1_t.module_id);//发送复位指令
		  ResetMode(chassis_t.pmoter_can,maxion2_t.module_id);//发送复位指令
		  ResetMode(chassis_t.pmoter_can,maxion3_t.module_id);//发送复位指令
			osDelay(500);//等待500ms
			ModeSelectionMode(chassis_t.pmoter_can,maxion1_t.module_id,mode);
			ModeSelectionMode(chassis_t.pmoter_can,maxion2_t.module_id,mode);
			ModeSelectionMode(chassis_t.pmoter_can,maxion3_t.module_id,mode);
			osDelay(500);//等待500ms
		 	// MotorInit(chassis_t.pmoter_can,maxion1_t.module_id,mode);//电机1初始化
			// MotorInit(chassis_t.pmoter_can,maxion2_t.module_id,mode);//电机2初始化
			// MotorInit(chassis_t.pmoter_can,maxion3_t.module_id,mode);//电机3初始化
	 }
/*----------------------------------file of end-------------------------------*/
