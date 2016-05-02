
#include "arch_main.h"
#include "tasks.h"

int main_func(void)
{
    //global initialise
    system_init();
	
	OSInit();
	OSTaskCreate(init_task, NULL, &init_stack[MaxStkSize - 1], INIT_TASK_PRIO);
	OSStart();
}
