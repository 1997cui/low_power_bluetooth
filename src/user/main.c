/**************************************************************************
 ��    ��: Cortex-M0����V2.86���ucosii         						 
 ���뻷��: MDKV4.12                                                    
 ʱ    ��: �ⲿ12Mhz      										     
 ��    ��: 11/03/14                                                           
 by      : AVR_DIY(ƻ����һ��)                                                   
 QQ      : 165292803(��ӭ����)										 
 email   : syyhcl@163.com												 
**************************************************************************/
#include "LPC11xx.h"                        /* LPC11xx definitions */
#include "gpio.h"
#include "config.h"
#include "device_init.h"
#include "ucos_ii.h"

OS_STK TaskStartStk1[MaxStkSize];	      //���������ջ��С

void TaskLed(void *nouse);
/****************************************
              main
�������� : ������
�������� : ��
����ֵ   : ��
****************************************/
int main (void) 
{
    CPU_IntDis();					//��ֹ�����ж�
	DeviceInit();					//��ʼ���豸
    OSInit();						//��ʼ��OS
	OSTaskCreate(TaskLed, (void *)0, &TaskStartStk1[MaxStkSize-1],1); 	   //����Led��ʾ����
	OSStart();                                                             //����ucos ii ��Զ������
}

/***************************************
              LED����
***************************************/
void TaskLed(void *nouse) 
{
    nouse=nouse;									 //��ֹ����������
    CPU_IntEn();                                     //��ʱ�ӽ����ж�
    while(1)
    {
		LED_TOG;
        OSTimeDlyHMSM(0,0,0,50);
    }    
}
