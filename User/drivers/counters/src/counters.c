/**
	|----------------------------- Copyright ------------------------------------|
	|                                                                            |
	|                     (C) Copyright 2018,海康平头哥,                          |
	|         1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China        |
	|                  -       All Rights Reserved                               |
	|                                                                            |
	|          By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)          |
	|                  https://github.com/GCUWildwolfteam                        |
	|----------------------------------------------------------------------------|
	|--FileName    : counters.c                                                
	|--Version     : v1.0                                                            
	|--Author      : 海康平头哥                                                       
	|--Date        : 2018-11-27               
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
#include "counters.h" 
#include <Math.h>
/* ===================== Bezier(二阶贝塞尔曲线) of begin ===================== */
/* -------------- 私有宏 ----------------- */
	#define X 0
	#define Y 1
	/**
		* @Data    2019-02-19 18:37
		* @brief   二阶贝塞尔曲线生成
		* @param   起点p1，控制点p2，终点p3
		* @retval  void
		*/
		void CreateBezierCurve(int16_t *p1,int16_t *p2,int16_t *p3)
		{
			
		}
	/** 
	* @author  海康平头哥 
	* @Data    2018-12-10 19:53
	* @brief   
	* @param   int x
	* @param 	 int	y;  //当前坐标
	* @retval  float t;  //曲线变化
	*/
	float Bezier(int x,int y)
	{
//		GetLengthForTwopoint();
		float t;  //曲线变化
//		int x0,x1,y0,y1,x2,y2;  //P0,P1,P3点
		int A ,B,C;//二阶方程  At^2+Bt+C=0
		int temp=0;  //临时数据 //确定三个点，预先算出temp
//		A = x2-x0-x1;
//		B = 2*x1;
//		C = x0-x;
		temp = sqrt(B^2-4*A*C);  //确定三个点，预先算出temp
		t = (-B + temp)/(2*A);
		return t;
	}
	/**
		* @Data    2019-02-19 11:40
		* @brief   平面两点间长度计算
		* @param   点Q1(x,y) = (Q1[0],Q1[1])
		* @param	 点Q2(x,y) = (Q2[0],Q2[1])
		* @retval  int16_t 长度 单位mm
		*/
		int16_t GetLengthForTwopoint(const int16_t *Q1,const int16_t *Q2)
		{
			return (int16_t)(sqrt(pow((Q1[X] + Q2[X]),2) + pow((Q1[Y] + Q2[Y]),2)));
		}
/* ====================== Bezier(二阶贝塞尔曲线) of end ====================== */
/* =========================== PID控制器 of begin =========================== */
/**
	* @Data    2019-01-26 16:55
	* @brief   位置pid控制器
	* @param  postionPidStruct 位置pid结构体指针
	* @param  当前误差
	* @retval  int16_t
	*/
	int16_t PostionPid(postionPidStruct *pps,int16_t error)
	{
	  pps->error	= error;
		pps->integral_er += pps->error;
		pps->pout = pps->kp * pps->error;
		pps->iout = pps->ki * pps->integral_er;
		pps->dout = pps->kd * (pps->error - pps->last_error);
		pps->pid_out = pps->pout + pps->iout + pps->dout;
		pps->last_error = pps->error;
		return pps->pid_out;
	}
/**
	* @Data    2019-01-26 16:55
	* @brief   速度pid控制器
	* @param  speedPidStruct 速度pid结构体指针
	* @param  当前误差
	* @retval  int16_t
	*/
	int16_t SpeedPid(speedPidStruct *sps,int16_t error)
	{
		sps->error = error;
		if((ABS(sps->error)) < (ABS(sps->last_error)))
			sps->last_error = sps->error;
		if((ABS(sps->last_error)) < (ABS(sps->before_last_error)))
			sps->before_last_error = sps->last_error;
		sps->pout = sps->kp * (sps->error - sps->last_error);
		sps->iout = sps->ki * sps->error;
		sps->dout = sps->kd * (sps->error - 2*sps->last_error + \
													 sps->before_last_error);
		sps->pid_out += (int16_t)(sps->pout + sps->iout + sps->dout);
    sps->pid_out = MAX(sps->pid_out,32766);
    sps->pid_out = MIN(sps->pid_out,-32766);
		sps->last_error = sps->error;
		sps->before_last_error = sps->last_error;
		return (int16_t)(sps->pid_out);
	}
/* ============================ PID控制器 of end ============================ */
/*--------------------------------file of end---------------------------------*/


