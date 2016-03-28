#ifndef __TIMER_H 
#define __TIMER_H 

#define   TIMER0_MAT_10MS   20000
#define   TIMER0_CNT_3S     200
#define   TIMER0_CNT_20S    2000
#define   TIMER0_CNT_30S    3000
#define   STOP_3S_COUNT     {Count_3S=0;	     \
				             FlagStart3S=RESET;  \
                            }

#define   START_3S_COUNT  	FlagStart3S=SET; 
#define   STOP_20S_COUNT     {Count_20S=0;	     \
				              FlagStart20S=RESET;\
                             }

#define   START_20S_COUNT  	{FlagStart20S=SET;	 \
                             Count_20S=0; 	     \
							}	 


#define   BEEP_LED_3S      {Count_3S=0;	        \
				            FlagStart3S=RESET;  \
                           }                            

extern volatile uint16_t Cnt_80Ms;
extern volatile uint8_t  SPK_LONG;
extern volatile uint8_t  FlagOver_20S;
extern volatile uint8_t  FlagChekUnPin;	 
extern volatile uint8_t  Count500Ms;  

void timer0Init (uint32_t Interval);  

										 
#endif 

