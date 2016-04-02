
#include "tasks.h"

int main(void)
{
	__disable_irq();
    OSInit();
    OSTaskCreate(init_task, NULL, &init_stack[MaxStkSize - 1], 1);
    OSStart();
}
