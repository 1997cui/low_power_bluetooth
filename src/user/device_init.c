#include "LPC11xx.h"
#include "gpio.h" 
#include "config.h"
#include "device_init.h"
#include "systick.h"

#define CLKOUT_DIV_Val       1			//CLKOUT时钟分频系数
/****************************************
              系统初始化
函数功能 : 初始化系统所有模块
参数描述 : 无
返回值   : 无
****************************************/	  
void DeviceInit(void) 
{
    SystemInit();						       //时钟初始化
	UserGpioInit();							   //GPIO初始化	
	SysTick_Config(SYSTICK_RELOAD);            //配置系统滴答计数器,10MS中断一次				   	
}
/****************************************
              GPIO初始化
函数功能 : 初始化IO口
参数描述 : 无
返回值   : 无
****************************************/	  
void UserGpioInit(void) 
{
    GPIOInit(); 
    #ifdef __JTAG_DISABLED  				       //禁止JTAG功能
    LPC_IOCON->R_PIO1_0  &= ~0x07;	               //先清掉为初始复位状态
    LPC_IOCON->R_PIO1_0  |=  0x01;		           //禁止TMS
    LPC_IOCON->R_PIO1_1  &= ~0x07;	               //先清掉为初始复位状态
    LPC_IOCON->R_PIO1_1  |=  0x01;		           //禁止TDO 再设置所需要的模式
    LPC_IOCON->R_PIO1_2  &= ~0x07;	               //先清掉为初始复位状态
    LPC_IOCON->R_PIO1_2 |=  0x01;		           //禁止TRST 再设置所需要的模式
    LPC_IOCON->R_PIO0_11 &= ~0x07;	   
    LPC_IOCON->R_PIO0_11 |=  0x01;		           //禁止TDI 设置为普通GPIO
    #endif	  							    
    /*使能CLKOUT管脚输出脉冲测试*/
    //LPC_IOCON->PIO0_1  &= ~0x07;
    //LPC_IOCON->PIO0_1  |=  0x01;
    /*为CLKOUT管脚输出设置脉冲源*/
    //LPC_SYSCON->CLKOUTCLKSEL = 0x03;		     //CLKOUT输出系统主时钟(PIO0_1)
    //LPC_SYSCON->CLKOUTUEN    = 0x01;		
    //LPC_SYSCON->CLKOUTUEN    = 0x00;		
    //LPC_SYSCON->CLKOUTUEN    = 0x01;
    //while ( !(LPC_SYSCON->CLKOUTUEN & 0x01) );	//Wait until updated 
    //LPC_SYSCON->CLKOUTDIV = CLKOUT_DIV_Val;	    //CLKOUT分频系数 1
	LED_DIR_OUT;								    //LED管脚配置
}

