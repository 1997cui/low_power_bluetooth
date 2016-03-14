#ifndef __ADC_H 
#define __ADC_H 

#define   ADC_CLK          1000000
#define   PCLK             12000000
#define   VOLTAGE_1650MV   0x0233       //1000110011
#define   VOLTAGE_1750MV   0x0255       //1001010101
//#define   VOLTAGE_2050MV   0x02c9	    //1010101010

extern volatile uint8_t FlagLowVol;

void ADC_Init(void);
uint32_t ADC_Convert(void);
										 
#endif 


