/**
	|--------------------------------- Copyright --------------------------------|
	|                                                                            |
	|                      (C) Copyright 2019,����ƽͷ��,                         |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                           All Rights Reserved                              |
	|                                                                            |
	|           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : rc_chassis.c                                              
	|--Version     : v1.0                                                          
	|--Author      : ���                                                     
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
		* @brief   �ֶ����̿��Ʒ�����
		* @param   void
		* @retval  void
		*/
		void RcChassisControl(const dbusStruct* rc)
		{
			int16_t temp_wheel_speed[3];
			/* ------ �˶�ģ�� ------- */
			ThreeWheelMotionModel(temp_wheel_speed,rc->ch1,rc->ch2,rc->ch3);
			/* ------ �ٶȷֽ��can���� ------- */		
   	  MotorCanTx(temp_wheel_speed[0],temp_wheel_speed[1],temp_wheel_speed[2]);
		}
	
/*-----------------------------------file of end------------------------------*/


