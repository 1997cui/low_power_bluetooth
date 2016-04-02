
#include "oled.h"

#include "tasks.h"

OS_STK lcd_show_stack[MaxStkSize];

void lcd_show_task(void * p)
{
    p = p;

    while (1)
    {
        LCD_CLS();
        LCD_PrintStr_6_8(0, 0, "Test1");
        OSTimeDlyHMSM(0, 0, 1, 0);
        LCD_CLS();
        LCD_PrintStr_6_8(0, 0, "Test2");
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
