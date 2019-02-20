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
	|--FileName    : auto_chassis.c                                              
	|--Version     : v1.0                                                          
	|--Author      : ����ƽͷ��                                                     
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
#include "auto_chassis.h" 
int16_t wheel_speed[3];
 /**
	* @Data    2019-02-16 09:53
	* @brief   �Զ����̿��Ʒ�����
	* @param   void
	* @retval  void
	*/
	void AutoChassisControl(const dbusStruct* rc)
	{
		ThreeWheelMotionModel(wheel_speed,400,0,0);
    MotorCanTx(wheel_speed[0],wheel_speed[1],wheel_speed[2]);
	}
/*-----------------------------------file of end------------------------------*/


