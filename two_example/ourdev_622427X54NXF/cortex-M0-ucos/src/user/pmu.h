#ifndef __PMU_H 
#define __PMU_H

#define TEST_POWERDOWN      0

#define MCU_SLEEP           0
#define MCU_DEEP_SLEEP      1

/* System Low Power ----------------------------------------------------------*/
#define NVIC_LP_SEVONPEND   (0x10)
#define NVIC_LP_SLEEPDEEP   (0x04)
#define NVIC_LP_SLEEPONEXIT (0x02)

#define NUM_OF_WAKESOURCE	40
#define IRC_OUT_PD          (0x1<<0)
#define IRC_PD              (0x1<<1)
#define FLASH_PD            (0x1<<2)
#define BOD_PD              (0x1<<3)
#define ADC_PD              (0x1<<4)
#define SYS_OSC_PD          (0x1<<5)
#define WDT_OSC_PD          (0x1<<6)
#define SYS_PLL_PD          (0x1<<7)
#define USB_PLL_PD          (0x1<<8)
#define MAIN_REGUL_PD		(0x1<<9)
#define USB_PHY_PD			(0x1<<10)
#define LP_REGUL_PD			(0x1<<12)

/*充电相关引脚*/
#define PWCK_PIN            PIN_0
#define PWCK_PORT           PORT2
#define PWCK_DIR_IN         GPIOSetDir(PWCK_PORT,PWCK_PIN,IN)
#define RD_PWCK_MASK	    0
#define	READ_PWCK_STATE		READ_GPIOBIT(PWCK_PORT,RD_PWCK_MASK)

#define CHOFF_PIN           PIN_5
#define CHOFF_PORT          PORT1
#define CHOFF_DIR_IN        GPIOSetDir(CHOFF_PORT,CHOFF_PIN,IN)
#define RD_CHOFF_MASK	    5
#define	READ_CHOFF_STATE	READ_GPIOBIT(CHOFF_PORT,RD_CHOFF_MASK)


#define SLEEP_MASK          0x18f7	  //睡眠模式BOD打开
//#define SLEEP_MASK          0x18ff
#define	ENTER_SLEEP         PMU_Sleep(MCU_DEEP_SLEEP,SLEEP_MASK)

extern volatile uint8_t FlagChekPower;

void WAKEUP_IRQHandler( void );
void PMU_Init( void );
void PMU_Sleep( uint32_t SleepMode, uint32_t SleepCtrl );
void PMU_PowerDown( void );

#endif 
