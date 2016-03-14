#ifndef __CONFIG_H 
#define __CONFIG_H  

#define SET		        1
#define RESET		    0
//#define LPC1112_board
#define LPC1114_board
/*********************LED*************************/
#ifdef  LPC1112_board
#define LED_PIN         PIN_1
#define LED_PORT        PORT0
#endif

#ifdef  LPC1114_board
#define LED_PIN         PIN_7
#define LED_PORT        PORT2
#endif

#define LED_DIR_OUT     GPIOSetDir(LED_PORT,LED_PIN,OUT)
#define LED_ON		    GPIOSetValue(LED_PORT,LED_PIN,RESET)
#define LED_OFF		    GPIOSetValue(LED_PORT,LED_PIN,SET)
#define LED_TOG		    GPIO_TOGGLE(LED_PORT,LED_PIN)
										 
#endif 

