/**
	|-------------------------------- Copyright -----------------------------------|
	|                                                                              |
	|                        (C) Copyright 2019,����ƽͷ��,                         |
	|            1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                               |
	|                                                                              |
	|            By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)          |
	|                     https://github.com/GCUWildwolfteam                       |
	|------------------------------------------------------------------------------|
	|--FileName    : leds_tip.h                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-01-18               
	|--Libsupports : STM32CubeF4 Firmware Package V1.6.0(�ñ�Ŀ�����������)
	|--Description : �޸����ŵĺ�,��ͬ������Ų�һ��
	|--							 1��RM_NEW_BOARD
	|--							 2��RM_OLD_BOARD                                                      
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end----------------------------|
 **/
#ifndef __LEDS_TIP_H 
#define __LEDS_TIP_H 
#include "baseclass.h"
/* ----------------- �������ѡ�� -------------------- */
#define RM_NEW_BOARD 0
#define RM_OLD_BOARD 0
#define BINGE_BOARD 1 //���İ���
/* ----------------- led���ź궨�嶨�� -------------------- */
#if RM_NEW_BOARD //�°����ź궨��
	#define LED_1 GPIO_PIN_1
	#define LED_2 GPIO_PIN_2
	#define LED_3 GPIO_PIN_3
	#define LED_4 GPIO_PIN_4
	#define LED_5 GPIO_PIN_5
	#define LED_6 GPIO_PIN_6
	#define LED_7 GPIO_PIN_7
	#define LED_8 GPIO_PIN_8
	#define LED_GPIO GPIOG
#elif BINGE_BOARD
	#define LED_1 GPIO_PIN_9
	#define LED_2 GPIO_PIN_10
	#define LED_3 GPIO_PIN_11
	#define LED_4 GPIO_PIN_12
	#define LED_5 GPIO_PIN_13
	#define LED_6 GPIO_PIN_14
	#define LED_7 GPIO_PIN_15
	#define LED_GPIO GPIOE
  #define LED_TOTAL 7 //led�ȸ���
  #define LED_ORIGIN_PIN 9  //��GPIO�������
#elif RM_OLD_BOARD
	#define LED_1 0
	#define LED_2 0
	#define LED_3 0
	#define LED_4 0
	#define LED_5 0
	#define LED_6 0
	#define LED_7 0
	#define LED_GPIO0G  0
  #define LED_TOTAL 0 //led�ȸ���
  #define LED_ORIGIN_PIN 0  //��GPIO�������
#endif
	void FlashingLed(GPIO_TypeDef *GPIO, uint16_t ledx, uint8_t times, uint32_t lag);
	void ProgressBarLed(GPIO_TypeDef *GPIO, uint32_t lag);
#endif // __LEDS_TIP_H

/*------------------------------------file of end-------------------------------*/


