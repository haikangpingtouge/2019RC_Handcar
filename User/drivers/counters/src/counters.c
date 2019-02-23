/**
	|----------------------------- Copyright ------------------------------------|
	|                                                                            |
	|                     (C) Copyright 2018,����ƽͷ��,                          |
	|         1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China        |
	|                  -       All Rights Reserved                               |
	|                                                                            |
	|          By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)          |
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
/* ===================== Bezier(����������) of begin ===================== */
//  /**
// 	* @Data    2019-02-23 11:45
// 	* @brief   ���������߽ṹ���ʼ��
// 	* @param   void
// 	* @retval  void
// 	*/
// 	void BezierStructInit(bezierStruct* bs)
// 	{
// 		bs->coordinate_x = NULL;
// 		bs->coordinate_y = NULL;
// 		bs->n = 4;
// 		bs->precision = 1000;
// 	}
	/**
		* @Data    2019-02-21 16:38
		* @brief   ��������㴢��ռ�
		* @param   void
		* @retval  void
		*/
		HAL_StatusTypeDef CreateDataSpace(bezierStruct* bs)
		{
			uint32_t i = 0;
			float t=0;
			bs->coordinate_x	= (uint32_t*)malloc(sizeof(uint32_t)*(bs->precision+3));
			bs->coordinate_y	= (uint32_t*)malloc(sizeof(uint32_t)*(bs->precision+3));
			if(bs->coordinate_x == NULL || bs->coordinate_x == NULL)
			{
				free(bs->coordinate_x);
				free(bs->coordinate_y);
	      return HAL_ERROR;
			}
			
			for(i = 0;i<(bs->precision+1);i++)
			{
				t = i/bs->precision;
				*(bs->coordinate_x+i) = QuadTo(bs->n,bs->point_x,t);
			  *(bs->coordinate_y+i) = QuadTo(bs->n,bs->point_y,t);
			}
			return HAL_OK;
		}
	/**
	* @Data    2019-02-21 14:08
	* @brief   n�ױ����������������� 
							Bn(t) =(1?t)nP0+��i=1n?1nti(1?t)n?iPi+tnPn(n��2,n��Z)
	* @param   n ����������
	* @param   *point  ���Ƶ��ַ
	* @param  t ����ϵ��
	* @retval uint32_t ����ó�����x��y��ֵ
	*/
	uint32_t QuadTo(const uint8_t n,const uint32_t *point,float t)
	{
		if(n < 2 && n < 8)
		{
			return 0;
		}
		uint8_t i = 1;
		float sum_Pi = 0;
		for(i = 1;i < n;i++)
		{
			sum_Pi += n *pow(t,i) * pow((1-t),(n-i)) * (*(point+i));
		}
		return (uint32_t) \
						((pow((1-t),n) * (*(point))) + sum_Pi +( pow(t,n) * (*(point+n))));
	}
//	/**
//		* @Data    2019-02-19 11:40
//		* @brief   ƽ������䳤�ȼ���
//		* @param   ��Q1(x,y) = (Q1[0],Q1[1])
//		* @param	 ��Q2(x,y) = (Q2[0],Q2[1])
//		* @retval  int16_t ���� ��λmm
//		*/
//		int16_t GetLengthForTwopoint(const int16_t *Q1,const int16_t *Q2)
//		{
//			return (int16_t)(sqrt(pow((Q1[X] + Q2[X]),2) + pow((Q1[Y] + Q2[Y]),2)));
//		}
/* ====================== Bezier(����������) of end ====================== */
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


