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
dbusStruct dbus_t; //��ң��
/* -------------- �ⲿ���� ----------------- */
extern UART_HandleTypeDef huart1;//����1
extern CAN_HandleTypeDef hcan1;
/* ----------------- ������ -------------------- */
	osThreadId startSysInitTaskHandle; 
	osThreadId startParseTaskHandle;
	osThreadId startLedTaskHandle;
	osThreadId startChassisTaskHandle;
	osThreadId startGimbalTaskHandle;
	osThreadId startRcChassisTaskHandle; //ң��ģʽ
	osThreadId startAutoChassisTaskHandle; //ң��ģʽ
/* ----------------- �����Ӻ��� -------------------- */
	void StartSysInitTask(void const *argument);
	void StartParseTask(void const *argument);
	void StartLedTask(void const *argument);
	void StartChassisTask(void const *argument);
	void StartRcChassisTask(void const *argument);//ң��ģʽ
	void StartAutoChassisTask(void const *argument);//�Զ�ģʽ
	// void StartGimbalTask(void const *argument);
/* -------------- ˽�к� ----------------- */
	#define RC_MODE 2 //ң��ģʽ
	#define AUTO_MODE 1 //�Զ�ģʽ
/* ----------------- �����ź��� -------------------- */
static uint8_t parse_task_status = 0;//���ݽ���������״̬��־
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
		osThreadDef(sysInitTask, StartSysInitTask, osPriorityNormal, 0, 512);
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
    for(;;)
    {
      task_on_off = DISABLE;
			/* -------- ���ݷ������� --------- */
      osThreadDef(parseTask, StartParseTask, osPriorityRealtime, 0, 512);
      startParseTaskHandle = osThreadCreate(osThread(parseTask), NULL);	
			/* -------- led����ʾ���� --------- */
			osThreadDef(ledTask, StartLedTask, osPriorityAboveNormal, 0,128);
      startLedTaskHandle = osThreadCreate(osThread(ledTask), NULL);
			/* ------ ����ģʽ���� ------- */
			osThreadDef(chassisTask, StartChassisTask, osPriorityHigh, 0, 1024);
      startChassisTaskHandle = osThreadCreate(osThread(chassisTask),&dbus_t);
			// /* ------ ��̨���� ------- */
			// osThreadDef(gimbalTask, StartGimbalTask, osPriorityNormal, 0, 640);
      // startGimbalTaskHandle = osThreadCreate(osThread(gimbalTask), NULL);
		#if BINGE_BOARD
			ProgressBarLed(LED_GPIO, 300);
		#elif RM_OLD_BOARD
		#endif
      task_on_off = ENABLE;
			/* -------- ɾ��ϵͳ���� --------- */
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
    DJIDbusInit(&dbus_t,&huart1);//��ң�س�ʼ��
		for(;;)
		{
      if(task_on_off == ENABLE)
      {
				ParseData();
				DbusParseData(&dbus_t);//ң�ؽ���
				parse_task_status = 1;
				osDelay(1);
      }
      else osDelay(1);
		}
	}
	/**
	* @Data    2019-01-18 11:31
	* @brief   led����ʾ�����Ӻ���
	* @param   argument: Not used
	* @retval  void
	*/
	void StartLedTask(void const *argument)
	{
		for(;;)
		{
      if(task_on_off == ENABLE)
      {
        if(parse_task_status == 1)
          FlashingLed(LED_GPIO, LED_1, 2, 100);
				else if(rc_chassis_task_status == 1)
				  FlashingLed(LED_GPIO, LED_2, 2, 50);
			  else if(auto_chassis_task_status == 1)
				  FlashingLed(LED_GPIO, LED_3, 2, 50);
        else osDelay(1);
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
/* ------ �������� ------- */
	uint8_t flag = 0;//�����ź�������
	dbusStruct* pAutoRc_t;
  pAutoRc_t = (dbusStruct*)argument;//��������ת��
/* ------ �������ݳ�ʼ�� ------- */
	ChassisInit();
/* ------ Ĭ�ϵ�������Ϊ�Զ�ģʽ ------- */
	osThreadDef(autoChassisTask,StartAutoChassisTask,osPriorityNormal,0,512);
	startAutoChassisTaskHandle=osThreadCreate(osThread(autoChassisTask),NULL);
	flag = AUTO_MODE;
	for(;;)
	{
		switch (pAutoRc_t->switch_left) 
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
		for (;;)
		{  
			if(task_on_off == ENABLE)
      {
				RcChassisControl(&dbus_t);
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
		for (;;)
		{  
			if(task_on_off == ENABLE)
      {
				AutoChassisControl(&dbus_t);
				auto_chassis_task_status = 1;
				osDelay(2);
			}
			else osDelay(1);
		}

	}
// /**
// 	* @Data    2019-01-27 17:55
// 	* @brief   ��̨�����Ӻ���
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
  
