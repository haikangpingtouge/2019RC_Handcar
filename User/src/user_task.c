/**
	|------------------------------ Copyright -----------------------------------|
	|                                                                            |
	|                       (C) Copyright 2019,海康平头哥,                        |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                             |
	|                                                                            |
	|          By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)          |
	|                     https://github.com/GCUWildwolfteam                     |
	|----------------------------------------------------------------------------|
	|--FileName    : user_task.c                                                
	|--Version     : v2.0                                                            
	|--Author      : 海康平头哥                                                       
	|--Date        : 2019-01-15               
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
#include "user_task.h"
dbusStruct dbus_t; //大疆遥控
/* -------------- 外部链接 ----------------- */
extern UART_HandleTypeDef huart1;//串口1
extern CAN_HandleTypeDef hcan1;
/* ----------------- 任务句柄 -------------------- */
	osThreadId startSysInitTaskHandle; 
	osThreadId startParseTaskHandle;
	osThreadId startLedTaskHandle;
	osThreadId startChassisTaskHandle;
	osThreadId startGimbalTaskHandle;
	osThreadId startRcChassisTaskHandle; //遥控模式
/* ----------------- 任务钩子函数 -------------------- */
	void StartSysInitTask(void const *argument);
	void StartParseTask(void const *argument);
	void StartLedTask(void const *argument);
	void StartChassisTask(void const *argument);
	void StartRcChassisTask(void const *argument);//遥控模式
	// void StartGimbalTask(void const *argument);
/* ----------------- 任务信号量 -------------------- */
static uint8_t parse_task_status = 0;//数据解析任务工作状态标志
uint8_t task_on_off = 0;
/**
	* @Data    2019-01-16 18:30
	* @brief   系统初始化任务
	* @param   void
	* @retval  void
	*/
	void SysInitCreate(void)
	{
		/* -------- 系统初始化任务创建 --------- */
		osThreadDef(sysInitTask, StartSysInitTask, osPriorityNormal, 0, 512);
		startSysInitTaskHandle = osThreadCreate(osThread(sysInitTask), NULL);
	}
/**
	* @Data    2019-01-16 18:27
	* @brief   系统初始化钩子函数
	* @param   argument: Not used 
	* @retval  void
	*/
	void StartSysInitTask(void const * argument)
	{
    for(;;)
    {
      task_on_off = DISABLE;
			/* -------- 数据分析任务 --------- */
      osThreadDef(parseTask, StartParseTask, osPriorityRealtime, 0, 512);
      startParseTaskHandle = osThreadCreate(osThread(parseTask), NULL);	
			/* -------- led灯提示任务 --------- */
			osThreadDef(ledTask, StartLedTask, osPriorityNormal, 0,128);
      startLedTaskHandle = osThreadCreate(osThread(ledTask), NULL);
			/* ------ 底盘自动模式任务 ------- */
			osThreadDef(chassisTask, StartChassisTask, osPriorityNormal, 0, 1024);
     startChassisTaskHandle = osThreadCreate(osThread(chassisTask), NULL);
		 /* ------ 底盘遥控模式任务 ------- */
		 	osThreadDef(rcChassisTask, StartrcChassisTask, osPriorityNormal, 0, 1024);
     startRcChassisTaskHandle = osThreadCreate(osThread(rcChassisTask), NULL);
			// /* ------ 云台任务 ------- */
			// osThreadDef(gimbalTask, StartGimbalTask, osPriorityNormal, 0, 640);
      // startGimbalTaskHandle = osThreadCreate(osThread(gimbalTask), NULL);
			ProgressBarLed(LED_GPIO, 500);
      task_on_off = ENABLE;
			/* -------- 删除系统任务 --------- */
			vTaskDelete(startSysInitTaskHandle);
    }
	}
	/**
	* @Data    2019-01-16 18:27
	* @brief   解析任务
	* @param   argument: Not used
	* @retval  void
	*/
	void StartParseTask(void const *argument)
	{
    DJIDbusInit(&dbus_t,&huart1);//大疆遥控初始化
		for(;;)
		{
      if(task_on_off == ENABLE)
      {
				ParseData();
				DbusParseData(&dbus_t);//遥控解析
				parse_task_status = ENABLE;
				osDelay(1);
      }
      else osDelay(1);
		}
	}
	/**
	* @Data    2019-01-18 11:31
	* @brief   led灯提示任务钩子函数
	* @param   argument: Not used
	* @retval  void
	*/
	void StartLedTask(void const *argument)
	{
		for(;;)
		{
      if(task_on_off == ENABLE)
      {
         FlashingLed(LED_GPIO,LED_7,2,100);
        if(parse_task_status == ENABLE)
        {
          FlashingLed(LED_GPIO, LED_1, 2, 100);
        }
        else osDelay(1);
      }
      else osDelay(1);
		}
    
	}
/**
	* @Data    2019-01-27 17:54
	* @brief   自动底盘任务钩子函数
	* @param   argument: Not used
	* @retval  void
	*/
	void StartChassisTask(void const *argument)
	{
		/* ------ 底盘初始化 ------- */
		ChassisInit();
 		for (;;)
		{  
			if(task_on_off == ENABLE)
      {
        ChassisControl(&dbus_t);
				osDelay(2);
			}
			else osDelay(1);
		}
	}
/**
	* @Data    2019-01-27 17:54
	* @brief   自动底盘任务钩子函数
	* @param   argument: Not used
	* @retval  void
	*/
	void StartRcChassisTask(void const *argument)
	{
 		for (;;)
		{  
			if(task_on_off == ENABLE)
      {
        RcChassisControl(&dbus_t);
				osDelay(2);
			}
			else osDelay(1);
		}
	}
// /**
// 	* @Data    2019-01-27 17:55
// 	* @brief   云台任务钩子函数
// 	* @param   argument: Not used
// 	* @retval  void
// 	*/
// 	void StartGimbalTask(void const *argument)
// 	{
// 		for (;;)
// 		{  
// 			if(task_on_off == ENABLE)
//       {
// 				osDelay(2);
// 			}
// 			else osDelay(1);
// 		}
// 	}
/*----------------------------------file of end-------------------------------*/
  
