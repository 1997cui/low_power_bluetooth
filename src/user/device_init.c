#include "LPC11xx.h"
#include "gpio.h" 
#include "config.h"
#include "device_init.h"
#include "systick.h"

#define CLKOUT_DIV_Val       1			//CLKOUTʱ�ӷ�Ƶϵ��
/****************************************
              ϵͳ��ʼ��
�������� : ��ʼ��ϵͳ����ģ��
�������� : ��
����ֵ   : ��
****************************************/	  
void DeviceInit(void) 
{
    SystemInit();						       //ʱ�ӳ�ʼ��
	UserGpioInit();							   //GPIO��ʼ��	
	SysTick_Config(SYSTICK_RELOAD);            //����ϵͳ�δ������,10MS�ж�һ��				   	
}
/****************************************
              GPIO��ʼ��
�������� : ��ʼ��IO��
�������� : ��
����ֵ   : ��
****************************************/	  
void UserGpioInit(void) 
{
    GPIOInit(); 
    #ifdef __JTAG_DISABLED  				       //��ֹJTAG����
    LPC_IOCON->R_PIO1_0  &= ~0x07;	               //�����Ϊ��ʼ��λ״̬
    LPC_IOCON->R_PIO1_0  |=  0x01;		           //��ֹTMS
    LPC_IOCON->R_PIO1_1  &= ~0x07;	               //�����Ϊ��ʼ��λ״̬
    LPC_IOCON->R_PIO1_1  |=  0x01;		           //��ֹTDO ����������Ҫ��ģʽ
    LPC_IOCON->R_PIO1_2  &= ~0x07;	               //�����Ϊ��ʼ��λ״̬
    LPC_IOCON->R_PIO1_2 |=  0x01;		           //��ֹTRST ����������Ҫ��ģʽ
    LPC_IOCON->R_PIO0_11 &= ~0x07;	   
    LPC_IOCON->R_PIO0_11 |=  0x01;		           //��ֹTDI ����Ϊ��ͨGPIO
    #endif	  							    
    /*ʹ��CLKOUT�ܽ�����������*/
    //LPC_IOCON->PIO0_1  &= ~0x07;
    //LPC_IOCON->PIO0_1  |=  0x01;
    /*ΪCLKOUT�ܽ������������Դ*/
    //LPC_SYSCON->CLKOUTCLKSEL = 0x03;		     //CLKOUT���ϵͳ��ʱ��(PIO0_1)
    //LPC_SYSCON->CLKOUTUEN    = 0x01;		
    //LPC_SYSCON->CLKOUTUEN    = 0x00;		
    //LPC_SYSCON->CLKOUTUEN    = 0x01;
    //while ( !(LPC_SYSCON->CLKOUTUEN & 0x01) );	//Wait until updated 
    //LPC_SYSCON->CLKOUTDIV = CLKOUT_DIV_Val;	    //CLKOUT��Ƶϵ�� 1
	LED_DIR_OUT;								    //LED�ܽ�����
}

