/**
	|----------------------------- Copyright ------------------------------------|
	|                                                                            |
	|                     (C) Copyright 2018,����ƽͷ��,       --                 |
	|        1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China         |
	|                            All Rights Reserved                             |
	|                                                                            |
	|        By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)            |
	|                  https://github.com/GCUWildwolfteam                        |
	|----------------------------------------------------------------------------|
	|--FileName    : counters.h                                                
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
	|------------------------------declaration of end----------------------------|
 **/
#ifndef __COUNTERS_H 
#define __COUNTERS_H 
	#include "baseclass.h"

  #define LOCATION_MODE        0  //λ��ʽ
  #define INCREMENTAL_MODE     1  //����ʽ
  #define ER    										0x00U  		//���
  #define LAST_ER 									0x01U  		//�ϴ����
  #define BEFORE_LAST_ER   					0x02U  		//���ϴ����
	#define INTEGRAL_ER								0x03U     //����
  #define KP  											0x04U  		//����p
  #define KI 												0x05U  		//����i
  #define KD  											0x06U  		//����d
	#define TARGET 										0x07U			//Ŀ��ֵ
	#define REAL											0x08U			//��ʵֵ
	#define P_OUT											0x09U			//p���
	#define I_OUT											0x0AU			//i���
	#define D_OUT											0x0BU			//d���
	#define PID_OUT										0x0CU			//pid���
	#define LIMIT_MAX									0x0DU     //����޷�
	#define LIMIT_MIN									0x0EU     //��С�޷�
	float Bezier(int x,int y);
	int16_t GetLengthForTwopoint(const int16_t *Q1,const int16_t *Q2);
/* -------------- λ��ʽpid ----------------- */
	typedef struct postionPidStruct
	{
		float kp;
		float kd;
		float ki;
		int16_t error;
		int16_t last_error;//�ϴ����
		int16_t integral_er;//������
		float pout;//p���
		float iout;//i���
		float dout;//k���
		float pid_out;//pid���
	}postionPidStruct;
	int16_t PostionPid(postionPidStruct *pps, int16_t error);
/* -------------- �ٶ�ʽpid ----------------- */
	typedef struct speedPidStruct
	{
		float kp;
		float kd;
		float ki;
		int16_t error;
		int16_t last_error;//�ϴ����
		int16_t before_last_error;//���ϴ����
		int16_t integral_er;//������
		float pout;//p���
		float iout;//i���
		float dout;//k���
		float pid_out;//pid���
}speedPidStruct;
int16_t SpeedPid(speedPidStruct *sps, int16_t error);
/* =========================== ���������� of begin =========================== */
	typedef struct BezierStruct
	{
		uint32_t *coordinate_x;
		uint32_t *coordinate_y;
		uint8_t n;
		uint32_t point_x[8];
		uint32_t point_y[8];
		uint32_t precision;
		// void(*SetPoint)(uint32_t x,uint32_t y);//���ÿ��Ƶ�
		// void(*SetPrecision)(uint32_t precision);//�������߾���
		// void(*SetPow)(uint8_t n);//���ñ���������
	}bezierStruct;
	HAL_StatusTypeDef CreateDataSpace(bezierStruct* bs);
	uint32_t QuadTo(const uint8_t n,const uint32_t *point,float t);
/* =========================== ���������� of end =========================== */


#endif	// __COUNTERS_H
	
/*--------------------------------file of end---------------------------------*/


