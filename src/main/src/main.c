
#include "arch_main.h"
#include "tasks.h"

OS_STK init_stack[MaxStkSize];

void main_func(void)
{
    //global initialise
    system_init();
	
	OSInit();
	OSTaskCreate(init_task, NULL, &init_stack[MaxStkSize - 1], INIT_TASK_PRIO);
	OSStart();
}
