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
	|--FileName    : motion_model.c                                              
	|--Version     : v1.0                                                          
	|--Author      : 海康平头哥                                                     
	|--Date        : 2019-02-17             
	|--Libsupports : 
	|--Description :各种运动模型算法                                                     
	|--FunctionList                                                     
	|-------1. ....                                                     
	|          <version>:                                                     
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|-----------------------------declaration of end-----------------------------|
 **/
#include "motion_model.h" 
#include "Math.h"
/* ======================== 全向轮三轮运动模型 of begin ======================= */
//	static float value[3] = {0};
#define VX_VALUE           (0.5f)
#define VY_VALUE           (sqrt(3)/2.f)      
#define L_value            (350*0.01f)  
	// /**
	// 	* @Data    2019-02-17 21:24
	// 	* @brief  获取轮子半径长度，场地坐标和机器人坐标角度误差
	// 	* @param   void
	// 	* @retval  void
	// 	*/
	// 	void GetRadiusAndTheta(uint8_t radius,char theta)
	// 	{
	// 		value[V_X] = (float)(-cos(60+theta));

	// 	}
	/**
		* @Data    2019-02-17 20:17
		* @brief  全向轮三轮底盘运动模型
		* @param   void
		* @retval  void
		*/
		void ThreeWheelMotionModel(int16_t motorspeed[],float vx,float vy,float w)
		{
			motorspeed[0] = (int16_t)(-VX_VALUE*vx + VY_VALUE*vy + L_value*w);
			motorspeed[1] = (int16_t)(-VX_VALUE*vx - VY_VALUE*vy + L_value*w);
			motorspeed[2] = (vx + L_value*w);
		}
/* ======================== 全向轮三轮运动模型 of end ======================== */
/*-----------------------------------file of end------------------------------*/


