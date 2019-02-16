/**
	|----------------------------- Copyright ------------------------------------|
	|                                                                            |
	|                     (C) Copyright 2018,����ƽͷ��,                          |
	|         1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China        |
	|                  -       All Rights Reserved                               |
	|                                                                            |
	|          By(GCU The wold of team | ����������ѧ����ѧԺ������Ұ�Ƕ�)          |
	|                  https://github.com/GCUWildwolfteam                        |
	|----------------------------------------------------------------------------|
	|--FileName    : counters.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
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

/* ===================== Bezier(���ױ���������) of begin ===================== */
	/* -------------------------------- begin  -------------------------------- */
		/**
		* @author  ����ƽͷ�� 
		* @Data    2018-12-10 19:53
		* @brief   
		* @param   int x
		* @param 	 int	y;  //��ǰ����
		* @retval  float t;  //���߱仯
		*/
	/* -------------------------------- end ----------------------------------- */
//		float Bezier(int x,int y)
//		{
//			float t;  //���߱仯
//			int x0,x1,y0,y1,x2,y2;  //P0,P1,P3��
//			int A ,B,C;//���׷���  At^2+Bt+C=0
//			int temp=0;  //��ʱ���� //ȷ�������㣬Ԥ�����temp
//			A = x2-x0-x1;
//			B = 2*x1;
//			C = x0-x;
//            temp = sqrt(B^2-4*A*C);  //ȷ�������㣬Ԥ�����temp
//			t = (-B + temp)/(2*A);

//			return t;
//		}
		
   
/* ====================== Bezier(���ױ���������) of end ====================== */
/* =========================== PID������ of begin =========================== */
/**
	* @Data    2019-01-26 16:55
	* @brief   λ��pid������
	* @param  postionPidStruct λ��pid�ṹ��ָ��
	* @param  ��ǰ���
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
	* @brief   �ٶ�pid������
	* @param  speedPidStruct �ٶ�pid�ṹ��ָ��
	* @param  ��ǰ���
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
/* ============================ PID������ of end ============================ */
/*--------------------------------file of end---------------------------------*/

