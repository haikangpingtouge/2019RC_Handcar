/**
	|------------------------------- Copyright ----------------------------------|
	|                                                                            |
	|                       (C) Copyright 2019,����ƽͷ��,                        |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                             |
	|                                                                            |
	|          By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)          |
	|                     https://github.com/GCUWildwolfteam                     |
	|----------------------------------------------------------------------------|
	|--FileName    : DJI_dbus.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-01-15               
	|--Libsupports : 
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|-------------------------------declaration of end---------------------------|
 **/
#include "DJI_dbus.h" 
uint8_t databuff[21];//���ݽ���
/**
	* @Data    2019-01-15 20:24
	* @brief   ��ң�س�ʼ��
	* @param   dbusStruct* dbs ң�ؽṹ��ָ��
	* @param   huartx(x=1,2,3,6)
	* @retval  HAL Status
	*/
	HAL_StatusTypeDef DJIDbusInit(dbusStruct* dbs,UART_HandleTypeDef *huartx)
	{
	// DBUSConnectStatus = Lost;
		if(dbs == NULL)
		{
			return HAL_ERROR;
			//���huart�����ж�
		}
		dbs->ch1 = 0;
		dbs->ch2 = 0;
		dbs->ch3 = 0;
		dbs->ch4 = 0;
		dbs->switch_left = 0;
		dbs->switch_right = 0;
		dbs->mouse.x = 0;
		dbs->mouse.y=0;
		dbs->mouse.z=0;
		dbs->mouse.press_left=0;
		dbs->mouse.press_right=0;
		dbs->mouse.jumppress_left=0;
		dbs->mouse.jumppress_right=0;
		dbs->keyBoard.key_code = 0;
		dbs->keyBoard.jumpkey_code = 0;
		dbs->state_flag = 0;//״̬��־λ
		dbs->a_frame_len = 21;//һ֡���ݳ���  18��һ֡���ݣ�+3��У�飩
		dbs->check_byte = 0x55;//֡βУ��
		dbs->huartx = huartx;
		/* -------- ��ʼ�������������ݽ��� --------- */
		if(UsartAndDMAInit(huartx, dbs->a_frame_len,ENABLE) != HAL_OK)
		{
			return HAL_ERROR;
		}
		return HAL_OK;
	}
/**
	* @Data    2019-01-16 15:07
	* @brief   ���ݽ���
	* @param   void
	* @retval  void
	*/
	void DbusParseData(dbusStruct* dbs)
	{
//    &&RCRDecryption\
//		(databuff,dbs->a_frame_len) == HAL_OK
		if(UserUsartQueueRX(dbs->huartx,databuff) == HAL_OK)
		{
		dbs->ch1 = (databuff[0] | databuff[1]<<8) & 0x07FF;
		dbs->ch1 -= 1024;
    dbs->ch1 = DbusAntiShake(20,dbs->ch1);
		dbs->ch2 = (databuff[1]>>3 | databuff[2]<<5 ) & 0x07FF;
		dbs->ch2 -= 1024;
    dbs->ch2 = DbusAntiShake(20,dbs->ch2);
		dbs->ch3 = (databuff[2]>>6 | databuff[3]<<2 | databuff[4]<<10) & 0x07FF;
		dbs->ch3 -= 1024;
    dbs->ch3 = DbusAntiShake(20,dbs->ch3);
		dbs->ch4 = (databuff[4]>>1 | databuff[5]<<7) & 0x07FF;		
		dbs->ch4 -= 1024;
    dbs->ch4 = DbusAntiShake(20,dbs->ch4);
		
		dbs->switch_left = ( (databuff[5] >> 4)& 0x000C ) >> 2;
		dbs->switch_right =  (databuff[5] >> 4)& 0x0003 ;
		
		dbs->mouse.x = databuff[6] | (databuff[7] << 8);	//x axis
		dbs->mouse.y = databuff[8] | (databuff[9] << 8);
		dbs->mouse.z = databuff[10]| (databuff[11] << 8);
		
		dbs->mouse.press_left 	= databuff[12];	// is pressed?
		dbs->mouse.press_right 	= databuff[13];
		
		dbs->keyBoard.key_code 	= databuff[14] | databuff[15] << 8; //key broad code
		}
		else
		{
//		dbs->ch1 = 0;
//		dbs->ch2 = 0;
//		dbs->ch3 = 0;
//		dbs->ch4 = 0;
// 
//		dbs->switch_left = 0;
//		dbs->switch_right = 0;
//		
//		dbs->mouse.x = 0;
//		dbs->mouse.y = 0;
//		dbs->mouse.z = 0;
//		
//		dbs->mouse.press_left	= 0;
//		dbs->mouse.press_right	= 0;
//		dbs->keyBoard.key_code	= 0;
		}
	}
	/**
		* @Data    2019-02-14 21:06
		* @brief   ң�ط���
		* @param   int16_t range ������Χ
		* @param 	 int16_t *data ָ�����ݵ�ַ��ָ��
		* @retval  void
		*/
		int16_t DbusAntiShake(int16_t range,int16_t data)
		{
			if(data > -(ABS(range)) && data < (ABS(range)))
				data = 0;
			return data;
		}
	/*----------------------------------file of end-----------------------------*/
