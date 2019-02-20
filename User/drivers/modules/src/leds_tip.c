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
	|--FileName    : leds_tip.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-01-18               
	|--Libsupports : STM32CubeF1 Firmware Package V1.6.0(�ñ�Ŀ�����������)
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end----------------------------|
 **/
#include "leds_tip.h" 
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-18 11:38
		* @brief   ��˸��
		* @param   GPIO LED_GPIO (��ϸ˵����.h�ļ�)
		* @param   ledx led���ź궨��   (��ϸ˵����.h�ļ�)
		* @param   times ��˸����
		* @param   lag  ��˸ʱ���� ��λms
		* @retval  void
		*/
		void FlashingLed(GPIO_TypeDef* GPIO,uint16_t ledx,uint8_t times,uint32_t lag)
		{
		#if RM_OLD_BOARD
		#elif BINGE_BOARD
			UNUSED(GPIO);
			uint8_t i = 0;
			for (i = 0; i < times;i++)
			{
					HAL_GPIO_TogglePin(GPIO, ledx);
          osDelay(lag);
					HAL_GPIO_WritePin(GPIO,ledx,GPIO_PIN_SET);
			}
		#endif
		}
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-18 14:16
		* @brief   ����LED��Ч (�ʺ�LED���������İ���)
		* @param   GPIO LED_GPIO (��ϸ˵����.h�ļ�)
		* @param 	 speed ��������ٶ�
		* @retval  void
		*/
		// void PulsatileLed(GPIO_TypeDef* GPIO,uint8_t speed)
		// {
		// 	uint8_t pulsatiles = 8;//��ԾLED����
		// 	uint8_t i = 0;
		// 	for (i = 0; i < pulsatiles;i++)
		// 	{

		// 	}
		// }
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-18 14:25
	* @brief   ��������Ч
	* @param   GPIO LED_GPIO (��ϸ˵����.h�ļ�)
	* @param   lag  ��˸ʱ���� ��λms
	* @retval  void
	*/
	void ProgressBarLed(GPIO_TypeDef* GPIO,uint32_t lag)
	{
		#if RM_OLD_BOARD
		  UNUSED(GPIO);
		#elif BINGE_BOARD
		uint8_t i = 0;
		uint16_t tem_pin=0;
		for (i = 0; i < LED_TOTAL; i++)
		{
			tem_pin |= 1 << (i+LED_ORIGIN_PIN);
			HAL_GPIO_WritePin(GPIO, tem_pin, GPIO_PIN_RESET);
			osDelay(lag);
		}
		HAL_GPIO_WritePin(GPIO, tem_pin, GPIO_PIN_SET);
	#endif
	}
/*------------------------------------file of end-------------------------------*/


