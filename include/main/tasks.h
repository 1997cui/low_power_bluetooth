
#include <stddef.h>
#include "ucos_ii.h"

#define MaxStkSize 64

void init_task(void *);
extern OS_STK init_stack[MaxStkSize];

void lcd_show_task(void *);
extern OS_STK lcd_show_stack[MaxStkSize];

void led_blink_task(void *);
extern OS_STK led_blink_stack[MaxStkSize];
