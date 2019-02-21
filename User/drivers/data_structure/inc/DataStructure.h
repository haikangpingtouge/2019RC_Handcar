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
	|--FileName    : DataStructure.h                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-02-21               
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
#ifndef __DATASTRUCTURE_H 
#define __DATASTRUCTURE_H 
#include "baseclass.h"
#define MAXSIZE    8
typedef struct SqQueue{
	float data[MAXSIZE];
	unsigned char front;//����ָ��
	unsigned char rear;//��βָ��
}SqQueue;
SqQueue GyinitQueue(void);
float isEmpty(SqQueue qu);
float enQueue(SqQueue *qu,float x,uint8_t size);
float deQueue(SqQueue *qu,float *y,uint8_t size);
#endif	// __DATASTRUCTURE_H
/*-----------------------------------file of end------------------------------*/

