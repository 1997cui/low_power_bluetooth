/**************************************************************************
 功    能: Cortex-M0上跑V2.86版的ucosii         						 
 编译环境: MDKV4.12                                                    
 时    钟: 外部12Mhz      										     
 日    期: 11/03/14                                                           
 by      : AVR_DIY(苹果另一半)                                                   
 QQ      : 165292803(欢迎交流)										 
 email   : syyhcl@163.com												 
**************************************************************************/
#include "LPC11xx.h"                        /* LPC11xx definitions */
#include "gpio.h"
#include "config.h"
#include "device_init.h"
#include "ucos_ii.h"

OS_STK TaskStartStk1[MaxStkSize];	      //定义任务堆栈大小

void TaskLed(void *nouse);
/****************************************
              main
函数功能 : 主函数
参数描述 : 无
返回值   : 无
****************************************/
int main (void) 
{
    CPU_IntDis();					//禁止所有中断
	DeviceInit();					//初始化设备
    OSInit();						//初始化OS
	OSTaskCreate(TaskLed, (void *)0, &TaskStartStk1[MaxStkSize-1],1); 	   //创建Led显示任务
	OSStart();                                                             //启动ucos ii 永远不返回
}

/***************************************
              LED任务
***************************************/
void TaskLed(void *nouse) 
{
    nouse=nouse;									 //防止编译器警告
    CPU_IntEn();                                     //开时钟节拍中断
    while(1)
    {
		LED_TOG;
        OSTimeDlyHMSM(0,0,0,50);
    }    
}
