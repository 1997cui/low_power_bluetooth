
#include "tasks.h"

OS_STK init_stack[MaxStkSize];

void init_task(void * p)
{
	__enable_irq();
	
	int i = 1;
	p = p;
	
	OS_CPU_SysTickInit(1000);
	
    OSTaskCreate(lcd_show_task, NULL, &lcd_show_stack[MaxStkSize - 1], ++i);
	OSTaskCreate(led_blink_task, NULL, &led_blink_stack[MaxStkSize - 1], ++i);
	
	OSTaskDel(OS_PRIO_SELF);
}
