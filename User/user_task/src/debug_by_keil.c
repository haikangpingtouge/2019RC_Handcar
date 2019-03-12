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
	|--FileName    : debug_by_keil.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
	|--Date        : 2019-02-23             
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
#include "debug_by_keil.h" 
#ifdef DEBUG_BY_KEIL
#define PRINTFTASKSTATUS 
 extern UART_HandleTypeDef huart2;//串口1
 extern UART_HandleTypeDef huart7;
debugByKeilStruct pdebug_t;
osThreadId startDebugByKeilTaskHandle; 
void StartDebugByKeilTask(void const *argument);
	/**
		* @Data    2019-02-23 15:46
		* @brief   获取局部变量的地址，用于keil硬件仿真
		* @param   void
		* @retval  void
		*/
		void DebugByKeilInit(void)
		{
			/* -------- keil硬件仿真任务示任务 --------- */
			 osThreadDef(debugByKeilTask, StartDebugByKeilTask, osPriorityBelowNormal, 0,1024);
       startDebugByKeilTaskHandle = osThreadCreate(osThread(debugByKeilTask), NULL); 
//			 DebugClassInit();      
       pdebug_t.d_rc = GetRcStructAdd();
       pdebug_t.d_chassis_t = GetChassisStructAdd();
      
		}
/**
  * @Data    2019-02-23 15:46
  * @brief   keil硬件仿真任务钩子函数
  * @param   void
  * @retval  void
  */
void StartDebugByKeilTask(void const *argument)
{
#ifdef PRINTFTASKSTATUS
     uint8_t pcWriteBuffer[500];
#endif
  uint8_t aa=1;
		for(;;)
		{
#ifdef PRINTFTASKSTATUS
        vTaskList((char *)&pcWriteBuffer);
        printf("任务名称\t运行状态\t优先级\t剩余堆栈\t任务序号\r\n");
        printf("-------------------------------------------------\r\n");
        printf("%s\r\n", pcWriteBuffer); 
        printf("-------------------------------------------------\r\n");
        printf("B : 阻塞, R : 就绪, D : 删除, S : 暂停\r\n");
//        memset(pcWriteBuffer, 0, 500);
//        printf("任务名称\t运行计数\t使用率\r\n");
//        printf("-------------------------------------------------\r\n");
//        vTaskGetRunTimeStats((char *)&pcWriteBuffer);
//        printf("%s\r\n", pcWriteBuffer);
         osDelay(500);      
#endif
//      HAL_UART_Transmit(&huart7,&aa,1,0);
//      osDelay(5);
      
		}
}
//	/**
//	* @Data    2019-01-18 11:31
//	* @brief   led灯提示任务钩子函数
//	* @param   argument: Not used
//	* @retval  void
//	*/
//	void StartLedTask(void const *argument)
//	{
//    uint16_t i=0;
////uint32_t s[1000] = {0};

//    //    printf("led灯提示任务初始化完毕\r\n");
////     uint8_t pcWriteBuffer[500];
//		for(;;)
//		{
////      if(task_on_off == ENABLE)
////      {
//  #if BINGE_BOARD
//        if(parse_task_status == 1)
//          FlashingLed(LED_GPIO, LED_1, 2, 100);
//				else if(rc_chassis_task_status == 1)
//				  FlashingLed(LED_GPIO, LED_2, 2, 50);
//			  else if(auto_chassis_task_status == 1)
//				  FlashingLed(LED_GPIO, LED_3, 2, 50);
//        else osDelay(1);
//  #elif RM_OLD_BOARD
//        (void)parse_task_status;
//  #endif 
////        vTaskList((char *)&pcWriteBuffer);
////        printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
////        printf("%s\r\n", pcWriteBuffer); 
////        osDelay(500);
//        if(i<4500)
//        {
//					
//					;
//           Debug_t.uint32(&huart2,((uint32_t)((1500*sin(0.00419*i))+1500)));
//          i++;
//        }
//        osDelay(10);
////      }
////      else osDelay(1);
//		}
//    
//	}
#endif
/*-----------------------------------file of end------------------------------*/


