#include "LPC11xx.h"			
#include "systick.h"
#include "gpio.h" 
#include "ucos_ii.h"
#include "config.h"		
/*******************************************************
          systick中断服务程序
函数功能:systick计数器溢出中断
参数描述:无
返回值  :无
********************************************************/
void SysTick_Handler(void)
{
	OSIntEnter();					// Must be called first at every hardware interrupt entry point 
   	OSTimeTick();					// Must be called during tick isr 
   	OSIntExit();
}

