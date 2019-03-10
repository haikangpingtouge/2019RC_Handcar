/**
	|------------------------------ Copyright -----------------------------------|
	|                                                                            |
	|                       (C) Copyright 2019,����ƽͷ��,                        |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                             |
	|                                                                            |
	|          By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)          |
	|                     https://github.com/GCUWildwolfteam                     |
	|----------------------------------------------------------------------------|
	|--FileName    : sys_task.c                                                
	|--Version     : v2.0                                                            
	|--Author      : ����ƽͷ��                                                       
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
#include "sys_task.h"
#include <Math.h>
/* -------------- �ⲿ���� ----------------- */
extern UART_HandleTypeDef huart2;//����2
extern UART_HandleTypeDef huart3;//����3
extern CAN_HandleTypeDef hcan2;
/* ----------------- ������ -------------------- */
	osThreadId startSysInitTaskHandle; 
	osThreadId startParseTaskHandle;
	osThreadId startChassisTaskHandle;
//	osThreadId startGimbalTaskHandle;
	osThreadId startRcChassisTaskHandle; //ң��ģʽ
	osThreadId startAutoChassisTaskHandle; //�Զ�ģʽ

/* ----------------- �����Ӻ��� -------------------- */
	void StartSysInitTask(void const *argument);
	void StartParseTask(void const *argument);
	void StartChassisTask(void const *argument);
	void StartRcChassisTask(void const *argument);//ң��ģʽ
	void StartAutoChassisTask(void const *argument);//�Զ�ģʽ
//	void StartBezierTask(void const *argument);//������������������
  // void StartGimbalTask(void const *argument);
/* -------------- ˽�к� ----------------- */
	#define RC_MODE 2 //ң��ģʽ
	#define AUTO_MODE 1 //�Զ�ģʽ
/* ----------------- �����ź��� -------------------- */
uint8_t task_on_off = 0;
 uint8_t auto_chassis_task_status = 0;
 uint8_t rc_chassis_task_status = 0;
/**
	* @Data    2019-01-16 18:30
	* @brief   ϵͳ��ʼ������
	* @param   void
	* @retval  void
	*/
	void SysInitCreate(void)
	{
		/* -------- ϵͳ��ʼ�����񴴽� --------- */
		osThreadDef(sysInitTask, StartSysInitTask, osPriorityNormal, 0, 256);
		startSysInitTaskHandle = osThreadCreate(osThread(sysInitTask), NULL);
	}
/**
	* @Data    2019-01-16 18:27
	* @brief   ϵͳ��ʼ�����Ӻ���
	* @param   argument: Not used 
	* @retval  void
	*/
	void StartSysInitTask(void const * argument)
	{
//    printf("ϵͳ���񴴽��ɹ�����ȴ������񴴽�����������\r\n");
    for(;;)
    {
      task_on_off = DISABLE;
			/* -------- ���ݷ������� --------- */
      osThreadDef(parseTask, StartParseTask, osPriorityRealtime, 0, 256);
      startParseTaskHandle = osThreadCreate(osThread(parseTask), NULL);	
			/* ------ ����ģʽ���� ------- */
			osThreadDef(chassisTask, StartChassisTask, osPriorityHigh, 0, 512);
      startChassisTaskHandle = osThreadCreate(osThread(chassisTask),NULL);
//			/* ------ ��̨���� ------- */
//			osThreadDef(gimbalTask, StartGimbalTask, osPriorityNormal, 0, 128);
//      startGimbalTaskHandle = osThreadCreate(osThread(gimbalTask), NULL);
		#if BINGE_BOARD
			ProgressBarLed(LED_GPIO, 300);
		#elif RM_OLD_BOARD
    osDelay(20);
		#endif
      task_on_off = ENABLE;
			/* -------- ɾ��ϵͳ���� --------- */
//     printf("�������������񴴽����\r\n");
			vTaskDelete(startSysInitTaskHandle);
    }
	}
	/**
	* @Data    2019-01-16 18:27
	* @brief   ��������
	* @param   argument: Not used
	* @retval  void
	*/
	void StartParseTask(void const *argument)
	{
    ParseInit();
		for(;;)
		{
      if(task_on_off == ENABLE)
      {
				ParseData();
				osDelay(2);
      }
      else osDelay(1);
		}
	}
/**
* @Data    2019-01-27 17:54
* @brief   ���������Ӻ���
* @param   argument: Not used   //���̸�����ģʽ�������ö�ֵ�ź��������ܵ�������ʱ�л�������
* @retval  void
*/
void StartChassisTask(void const *argument)
{
 	const dbusStruct* pRc_t;
  pRc_t = GetRcStructAdd();
/* ------ �������� ------- */
	uint8_t flag = 0;//�����ź�������
/* ------ �������ݳ�ʼ�� ------- */
	ChassisInit();
/* ------ Ĭ�ϵ�������Ϊ�Զ�ģʽ ------- */
	osThreadDef(autoChassisTask,StartAutoChassisTask,osPriorityNormal,0,512);
	startAutoChassisTaskHandle=osThreadCreate(osThread(autoChassisTask),NULL);
	flag = AUTO_MODE;
//  printf("���������ʼ�����\r\n");
	for(;;)
	{
		switch (pRc_t->switch_left) 
		{
		/* ------ �Զ��������񴴽� ------- */
		case AUTO_MODE:
		if(flag == RC_MODE)
		{
			/* -------- ɾ���ֶ��������� --------- */ 
			vTaskDelete(startRcChassisTaskHandle);
			rc_chassis_task_status = 0;
			osThreadDef(autoChassisTask,StartAutoChassisTask,osPriorityNormal,0,512);
			startAutoChassisTaskHandle=osThreadCreate(osThread(autoChassisTask),NULL);
			flag = AUTO_MODE;
		}
			break;
		/* ------ �ֶ��������񴴽� ------- */
		case RC_MODE:
		if(flag == AUTO_MODE)
		{
			/* -------- ɾ���Զ��������� --------- */
			vTaskDelete(startAutoChassisTaskHandle);
			auto_chassis_task_status = 0;
			osThreadDef(rcChassisTask, StartRcChassisTask, osPriorityNormal, 0, 512);
			startRcChassisTaskHandle = osThreadCreate(osThread(rcChassisTask), NULL);
      flag = RC_MODE;
		}
			break;
		default:
			break;
		}
		osDelay(1);
	}
}
	/**
	* @Data    2019-01-27 17:54
	* @brief   ң�ص��������Ӻ���
	* @param   argument: Not used
	* @retval  void
	*/
	void StartRcChassisTask(void const *argument)
	{
  	const dbusStruct* pRc_t;
    pRc_t = GetRcStructAdd();
		for (;;)
		{  
			if(task_on_off == ENABLE)
      {
				RcChassisControl(pRc_t);
				rc_chassis_task_status = 1;
				osDelay(2);
			}
			else osDelay(1);
		}
	}
	/**
	* @Data    2019-02-20 16:48
	* @brief   �Զ����������Ӻ���
	* @param   void
	* @retval  void
	*/
	void StartAutoChassisTask(void const *argument)
	{
   const dbusStruct* pRc_t;
    pRc_t = GetRcStructAdd();
//    printf("�Զ����������ʼ�����\r\n");
		for (;;)
		{  
			if(task_on_off == ENABLE)
      {
				AutoChassisControl(pRc_t);
				auto_chassis_task_status = 1;
				osDelay(2);
			}
			else osDelay(1);
		}

	}
///**
//	* @Data    2019-01-27 17:55
//	* @brief   ��̨�����Ӻ���
//	* @param   argument: Not used
//	* @retval  void
//	*/
//	void StartGimbalTask(void const *argument)
//	{

////    int i =0;
//		for (;;)
//		{  
////      (void)a;
//			if(task_on_off == ENABLE)
//       {
////        for(i=0;i<100;i++)
////         {
////           a[i] = 99;
////         }
//			 	 osDelay(500);

//			 }
//			 else 
//       {
//         osDelay(1);
//       }
//		}
//	}
 /**
	* @Data    2019-02-22 14:44
	* @brief   �������������������Ӻ���
	* @param   argument: Not used
	* @retval  void
	*/
//	void StartBezierTask(void const *argument)
//	{
//// 		bezierStruct bezier_t; //���������߽ṹ��
//// 		bezier_t.coordinate_x = NULL;
//// 		bezier_t.coordinate_y = NULL;
//// 		bezier_t.n = 4;
//// 		bezier_t.precision = 1000;
//// 		bezier_t.point_x[0] = 0;
//// 		bezier_t.point_y[0] = 0;
//// 		bezier_t.point_x[1] = 1500; //mm
//// 		bezier_t.point_y[1] = 1500;
//// 		bezier_t.point_x[2] = 0;
//// 		bezier_t.point_y[2] = 3000;
//// 		bezier_t.point_x[3] = 1500;
//// 		bezier_t.point_y[3] = 4500;
//// 		bezier_t.point_x[4] = 750;
//// 		bezier_t.point_y[4] = 5250;
//// 		bezier_t.point_x[5] = 0;
//// 		bezier_t.point_y[5] = 0;
//// 		bezier_t.point_x[6] = 0;
//// 		bezier_t.point_y[6] = 0;
//// 		bezier_t.point_x[7] = 0;
//// 		bezier_t.point_y[7] = 0;
//// 		/* ------ �Ľױ������������� ------- */
//// 			CreateDataSpace(&bezier_t);
//// #ifdef DEBUG_BY_KEIL
//// 		debugByKeil_t.pbezier_t = &bezier_t;
//// #endif
//	  for (;;)
//		{  
//			if(task_on_off == ENABLE)
//      {

//				osDelay(1);
//			}
//			else osDelay(1);
//		}
//	}
/*----------------------------------file of end-------------------------------*/
  
