#include "LPC11xx.h"			
#include "systick.h"
#include "gpio.h" 
#include "ucos_ii.h"
#include "config.h"		
/*******************************************************
          systick�жϷ������
��������:systick����������ж�
��������:��
����ֵ  :��
********************************************************/
void SysTick_Handler(void)
{
	OSIntEnter();					// Must be called first at every hardware interrupt entry point 
   	OSTimeTick();					// Must be called during tick isr 
   	OSIntExit();
}

