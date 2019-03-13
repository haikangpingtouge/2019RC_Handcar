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
	|--FileName    : auto_chassis.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
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
#define X 0
#define Y 1
int16_t wheel_speed[3];
	 postionPidStruct  x_postionPid_t;
	 postionPidStruct  y_postionPid_t;
	 postionPidStruct  w_postionPid_t;
	 			  uint32_t __sin[300] = {0};
    	int16_t i = 0;
        int16_t x_i = 0;
	int16_t q1[2] ={0};
		int16_t q2[2] = {0};
   int16_t xer=0;
   int16_t yer=0;
    int16_t wer=0;
   int16_t ler=0;
    int16_t flag =1;
		/**
* @Data    2019-02-24 12:02
* @brief   自动底盘初始化
* @param   void
* @retval  void
*/
 void AutoChassisInit(void)
{

  x_postionPid_t.kp = 9;
  x_postionPid_t.kd = 0;
  x_postionPid_t.ki = 0;
  x_postionPid_t.error = 0;
  x_postionPid_t.last_error = 0;//上次误差
  x_postionPid_t.integral_er = 0;//误差积分
  x_postionPid_t.pout = 0;//p输出
  x_postionPid_t.iout = 0;//i输出
  x_postionPid_t.dout = 0;//k输出
  x_postionPid_t.pid_out = 0;//pid输出

	y_postionPid_t.kp = -9;
  y_postionPid_t.kd = 0;
  y_postionPid_t.ki = 0;
  y_postionPid_t.error = 0;
  y_postionPid_t.last_error = 0;//上次误差
  y_postionPid_t.integral_er = 0;//误差积分
  y_postionPid_t.pout = 0;//p输出
  y_postionPid_t.iout = 0;//i输出
  y_postionPid_t.dout = 0;//k输出
  y_postionPid_t.pid_out = 0;//pid输出

	w_postionPid_t.kp = 11;
  w_postionPid_t.kd = 0;
  w_postionPid_t.ki = 0;
  w_postionPid_t.error = 0;
  w_postionPid_t.last_error = 0;//上次误差
  w_postionPid_t.integral_er = 0;//误差积分
  w_postionPid_t.pout = 0;//p输出
  w_postionPid_t.iout = 0;//i输出
  w_postionPid_t.dout = 0;//k输出
  w_postionPid_t.pid_out = 0;//pid输出
  CreateSinCurve(__sin,300,75,0.021,0,75);//正弦
		
}
 /**
	* @Data    2019-02-16 09:53
	* @brief   自动底盘控制服务函数
	* @param   void
	* @retval  void
	*/
	void AutoChassisControl(const dbusStruct* rc)
	{
	const chassisStruct* as= GetChassisStructAdd();
int16_t x_out = 0;
	 int16_t y_out = 0;
	 int16_t w_out = 0;
//  
//#ifdef DEBUG_BY_KEIL
//	  if(i<300)
//      Debug_t.uint32(&huart2,s[i]);
//    i++;
//#endif

					q1[X] = (int16_t)(as->pwholePosition_t->x_coordinate );
		      q1[Y] = (int16_t)(as->pwholePosition_t->y_coordinate );
    			if(as->pwholePosition_t->x_coordinate < -100)
						q1[X] = 0;
					if(q1[Y] < -100)
						q1[Y] = 0;
          do{
            q2[Y] = x_i*10;
					q2[X] = __sin[x_i]*10;
         yer = (int16_t)(q2[Y] - q1[Y]);
					xer = (int16_t)(q2[X] -q1[X]);
	        wer = 0-(int16_t)(as->pwholePosition_t->z_angle);
         
          if(yer < 25)
          {
            if(x_i < 300)
             x_i++;
          }
          else flag = 0;
     
          }while(flag);
        if(x_i < 300)
				{
					x_out = PostionPid(&x_postionPid_t,xer);
					y_out = PostionPid(&y_postionPid_t,yer);
					w_out = PostionPid(&w_postionPid_t,wer);
          x_out = MAX(x_out,3000);
          x_out = MIN(x_out,-3000);
          y_out = MAX(y_out,3000);
          y_out = MIN(y_out,-3000);
          w_out = MAX(w_out,3000);
          w_out = MIN(w_out,-3000);
//          ThreeWheelMotionModel(wheel_speed,as->rc->ch1,as->rc->ch2,as->rc->ch3);
	  			ThreeWheelMotionModel(wheel_speed,x_out,y_out,w_out);
          MotorCanTx(wheel_speed[0],wheel_speed[1],wheel_speed[2]);
//          CanTxMsg();
				}
				else
				{
//					ThreeWheelMotionModel(wheel_speed,as->rc->ch1,as->rc->ch2,as->rc->ch3);
          MotorCanTx(0,0,0);
				}
		// ThreeWheelMotionModel(wheel_speed,400,0,0);
    // MotorCanTx(wheel_speed[0],wheel_speed[1],wheel_speed[2]);
	}
/*-----------------------------------file of end------------------------------*/


