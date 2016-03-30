
#include <stddef.h>

#include "ucos_ii.h"

#include "global_io.h"
#include "user_periph_setup.h"
#include "gpio.h"
#include "systick.h"
#include "oled.h"

#define MaxStkSize 64

void system_init(void);
void SysTickISR(void);

void lcd_show(void*);
OS_STK lcd_show_stack[MaxStkSize];

void led_blink(void*);
OS_STK led_blink_stack[MaxStkSize];

int main (void)
{
    __disable_irq();
    system_init();
    periph_init();
    LCD_Init();
    systick_register_callback(OS_CPU_SysTickHandler);
    systick_start(1000, 1);
    
    OSInit();
    OSTaskCreate(lcd_show, NULL, &lcd_show_stack[MaxStkSize - 1], 1);
    OSTaskCreate(led_blink, NULL, &led_blink_stack[MaxStkSize - 1], 2);
    OSStart();
}

void system_init(void)
{
    SetWord16(CLK_AMBA_REG, 0x00);                 // set clocks (hclk and pclk ) 16MHz
    SetWord16(SET_FREEZE_REG,FRZ_WDOG);            // stop watch dog    
    SetBits16(SYS_CTRL_REG,PAD_LATCH_EN,1);        // open pads
    SetBits16(SYS_CTRL_REG,DEBUGGER_ENABLE,1);     // open debugger
    SetBits16(PMU_CTRL_REG, PERIPH_SLEEP,0);       // exit peripheral power down
}

void lcd_show(void * p)
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

void led_blink(void * p)
{
    p = p;
	
	OSTimeDlyHMSM(0, 0, 0, 500);

    while (1)
    {
        GPIO_SetActive(LED_PORT, LED_PIN);
        OSTimeDlyHMSM(0, 0, 1, 0);
        GPIO_SetInactive(LED_PORT, LED_PIN);
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
