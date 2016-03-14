#ifndef __KEY_H 
#define __KEY_H 

#define KEY_KX1_PIN     PIN_11
#define KEY_KX2_PIN     PIN_2
#define KEY_K1_PIN      PIN_0
#define KEY_K2_PIN      PIN_1
#define KEY_K3_PIN      PIN_2
#define KEY_K4_PIN      PIN_10

#define KEY_KX1_PORT    PORT1
#define KEY_KX2_PORT    PORT3
#define KEY_K1_PORT     PORT1
#define KEY_K2_PORT     PORT1
#define KEY_K3_PORT     PORT1
#define KEY_K4_PORT     PORT1
#define KEY_LINE_PORT	PORT1

#define KEY_PORT_INIT   {GPIOSetDir(KEY_K1_PORT,KEY_K1_PIN,OUT);  \
                         GPIOSetDir(KEY_K2_PORT,KEY_K2_PIN,OUT);  \
						 GPIOSetDir(KEY_K3_PORT,KEY_K3_PIN,OUT);  \
						 GPIOSetDir(KEY_K4_PORT,KEY_K4_PIN,OUT);  \
						 GPIOSetDir(KEY_KX1_PORT,KEY_KX1_PIN,IN); \
						 GPIOSetDir(KEY_KX2_PORT,KEY_KX2_PIN,IN); \
						}
#define ALL_LINE_LOW_MASK      0x0bf8                                    //1011 1111 1000
#define FIRST_LINE_LOW_MASK    0x0bff                                    //1011 1111 1111
#define SECOND_LINE_LOW_MASK   0x0ffe                                    //1111 1111 1110
#define THIRD_LINE_LOW_MASK    0x0ffb                                    //1111 1111 1011
#define FOURTH_LINE_LOW_MASK   0x0ffd                                    //1111 1111 1101
#define WR_KEY_MASK			   0x0407									 //0100 0000 0111
#define RD_KX1_MASK			   11
#define RD_KX2_MASK			   2
#define SET_LINE1_LOW          SET_GPIO(KEY_LINE_PORT,WR_KEY_MASK, FIRST_LINE_LOW_MASK )			   
#define SET_LINE2_LOW          SET_GPIO(KEY_LINE_PORT,WR_KEY_MASK, SECOND_LINE_LOW_MASK)
#define SET_LINE3_LOW          SET_GPIO(KEY_LINE_PORT,WR_KEY_MASK, THIRD_LINE_LOW_MASK)
#define SET_LINE4_LOW          SET_GPIO(KEY_LINE_PORT,WR_KEY_MASK, FOURTH_LINE_LOW_MASK)	
#define SET_All_LINE_LOW 	   SET_GPIO(KEY_LINE_PORT,WR_KEY_MASK, ALL_LINE_LOW_MASK)
#define	READ_KEY_STATE		   ((READ_GPIOBIT(KEY_KX1_PORT,RD_KX1_MASK)<<1)|(READ_GPIOBIT(KEY_KX2_PORT,RD_KX2_MASK)))
#define NO_KEY_DOWN            0x0003
#define ALL_ROW_KEY_DOWN       0x0000

#define KEY_STATE_START         0
#define KEY_STATE_PRESS         1 
#define KEY_STATE_RELEASE       2

#define S01_KEY_CODE            0x1bff              //0001 1011 1111 1111
#define S02_KEY_CODE            0x2bff              //0010 1011 1111 1111
#define S1_KEY_CODE             0x1ffe             	//0001 1111 1111 1110
#define S4_KEY_CODE             0x2ffe              //0010 1111 1111 1110
#define S2_KEY_CODE             0x1ffb              //0001 1111 1111 1011
#define S5_KEY_CODE             0x2ffb             	//0010 1111 1111 1011
#define S3_KEY_CODE             0x1ffd             	//0001 1111 1111 1101
#define S6_KEY_CODE             0x2ffd             	//0010 1111 1111 1101
#define S01_S02_CODE            0x0bff             	//0000 1011 1111 1111

#define NO_RETURN           	255
#define NO_KEY_RETURN           0
#define S01_KEY_RETURN          1              
#define S02_KEY_RETURN          2              
#define S1_KEY_RETURN           3             	
#define S2_KEY_RETURN           4              
#define S3_KEY_RETURN           5              
#define S4_KEY_RETURN           6             	
#define S5_KEY_RETURN           7             	
#define S6_KEY_RETURN           8             	
#define S01_S02_RETURN          9 
#define S01_DOWN_RETURN         10 			   //³¤°´
#define S02_DOWN_RETURN         11 
#define S0102_DOWN_RETURN       12   
          	


extern volatile uint8_t FlagStart3S;
extern volatile uint16_t Count_3S;
extern volatile uint8_t Flag3S_Over;
extern volatile uint8_t FlagStart20S;	  
extern volatile uint16_t Count_20S;	
extern volatile uint16_t Count_30S;		  
extern volatile uint8_t LoginEnter;

uint8_t ScanKey (void);
void KeyDispose(void);


#endif



