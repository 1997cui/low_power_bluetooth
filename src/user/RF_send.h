#ifndef __RF_SEND_H 
#define __RF_SEND_H  

#define RF_PIN          PIN_6
#define RF_PORT         PORT0
#define RF_DIR_OUT      GPIOSetDir(RF_PORT,RF_PIN,OUT)
#define RF_HIGH		    GPIOSetValue(RF_PORT,RF_PIN,SET)
#define RF_LOW		    GPIOSetValue(RF_PORT,RF_PIN,RESET)
#define RF_TOG		    GPIO_TOGGLE(RF_PORT,RF_PIN)

#define FRAME_H         160	
#define FRAME_L         9
#define FRAME_END_H     3
#define HIGH_LEVEL_H    18	
#define HIGH_LEVEL_L    2	
#define LOW_LEVEL_H     6	
#define LOW_LEVEL_L     2

#define RF_CODE_1       {RF_HIGH;                    \
                         delaySysTick(HIGH_LEVEL_H); \
						 RF_LOW;					 \
						 delaySysTick(HIGH_LEVEL_L); \
						}
#define RF_CODE_0       {RF_HIGH;                    \
                         delaySysTick(LOW_LEVEL_H);  \
						 RF_LOW;					 \
						 delaySysTick(LOW_LEVEL_L);  \
						}	
#define FRAME_START     {RF_HIGH;                    \
                         delaySysTick(FRAME_H);      \
						 RF_LOW;					 \
						 delaySysTick(FRAME_L);      \
						}
#define FRAME_END       {RF_HIGH;                    \
                         delaySysTick(FRAME_END_H);  \
						 RF_LOW;					 \
						}

#define CONTROL_ID_ADDR	 0x3ffd 					 //控制器ID在FLASH中的保存地址（16K的最后三个字节）
#define NUM_FRAME        10							 //帧长
#define DEV_CLASS_FIELD	 3
#define DEV_NUM_FIELD	 4
#define CON_CMD_FIELD	 5
#define RELAY_FIELD	     6
#define RESERVED_FIELD	 7
#define CMD_SN_FIELD	 8
#define CHECK_FIELD	     9	

#define   CHECK_SUM_LEN	     0x09
/*类型*/
#define   DEV_SWITCH	     0x01	
#define   DEV_CERTAIN	     0x02
#define   LAP_LOGIN_CMD      0x81
#define   CERTAIN_LOGIN_CMD  0x82
#define   TEST_CMD           0xEE
#define   ALL_DEV_CLASS      0xFF

/*设备号*/
#define   DEV_NUM_S1	     0x01	
#define   DEV_NUM_S2	     0x02
#define   DEV_NUM_S3         0x03
#define   DEV_NUM_S4         0x04
#define   DEV_NUM_S5         0x05
#define   DEV_NUM_S6         0x01
#define   DEV_NUM_S01        0x01
#define   DEV_NUM_S02        0x01
#define   ALL_DEV_NUM        0xFF
/*命令*/
#define   DEL_ID_CMD         0xDD
#define   RESET_CMD          0xDA
#define   CERTAIN_CLOSE_CMD  0x00
#define   PAUSE_CMD          0x80
#define   CERTAIN_OPEN_CMD   0xff
#define	  LAP_DOWN_CMD	     0x10
#define	  LAP_UP_CMD		 0x1f
#define   LAPTOG_CMD         0xEE
#define   ALL_CLOSE_CMD      0x00
#define   ALL_OPEN_CMD       0xff

/*遥控器状态及模式*/
#define   START              1
#define   END                2
#define   NORMAL_MODE        0
#define   LOGIN_MODE         1





				



extern uint8_t SendBuffer[NUM_FRAME];

uint8_t RF_CheckSum(uint8_t *Buff,uint8_t Len);
void RF_SendByte(uint8_t bData);
void RF_DataSend(uint8_t *SendBuf,uint8_t Len);
void RF_LoopSend(void);						
																	 
#endif 

