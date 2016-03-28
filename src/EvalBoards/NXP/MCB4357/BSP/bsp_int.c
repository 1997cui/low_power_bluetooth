/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2007-2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       BOARD SUPPORT PACKAGE
*                                        INTERRUPT CONTROLLER
*
*                                            NXP LPC4357
*                                               on the
*                                            Keil MCB4357
*
* Filename      : bsp.c
* Version       : V1.00.00
* Programmer(s) : MD
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_INT_MODULE
#include  <bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

static CPU_FNCT_VOID BSP_IntVectTbl[BSP_INT_ID_MAX];


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_IntHandlerDummy (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          BSP_IntClr()
*
* Description : This function clears an interrupt
*
* Argument(s) : int_id        Interrupt to clear.
*
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) An interrupt does not need to be cleared within the interrupt controller.
*********************************************************************************************************
*/

void  BSP_IntClr (CPU_INT08U  int_id)
{

}


/*
*********************************************************************************************************
*                                             BSP_IntDis()
*
* Description : This function disables an interrupt.
*
* Argument(s) : int_id        Interrupt to clear.
*
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : Disable the specified interrupt by writing a 1 to the Interrupt
*               Mask Flag Register.
*********************************************************************************************************
*/

void  BSP_IntDis (CPU_INT08U  int_id)
{
                                                                /* -------------- ARGUMENTS CHECKING ---------------- */
    if (int_id > BSP_INT_ID_MAX) {
        CPU_IntSrcDis(int_id + 16);
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntDisAll()
*
* Description : Disable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    CPU_IntDis();
}

/*
*********************************************************************************************************
*                                          BSP_IntEn()
*
* Description : This function enables an interrupt.
*
* Argument(s) : int_id        Interrupt to clear.
*
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : Enable interrupt by setting a 1 to the Interrupt Mask
*               Flag Register.
*********************************************************************************************************
*/

void  BSP_IntEn (CPU_INT08U  int_id)
{
    if (int_id > BSP_INT_ID_MAX) {
        CPU_IntSrcEn(int_id + 16);
    }
}


/*
*********************************************************************************************************
*                                            BSP_IntVectSet()
*
* Description : Assign ISR handler.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*               prio        Interrupt priority level. 0(Highest) - 3(Lowest)
*
*               isr         Handler to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntVectSet (CPU_INT08U     int_id,
                      CPU_FNCT_VOID  isr)
{
    CPU_SR_ALLOC();
    

    if (int_id < BSP_INT_ID_MAX) {
        CPU_CRITICAL_ENTER();
        BSP_IntVectTbl[int_id]   = isr;                         /* Setup interrupt specified in the vector table        */
        CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           INTERNAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              BSP_IntInit()
*
* Description : Initialize interrupts:
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntInit (void)
{
    CPU_INT32U  int_id;


    BSP_IntDisAll();

    for (int_id = 0; int_id < BSP_INT_ID_MAX; int_id++) {       /* Initialize each interrupt with Dummy Handler         */
        BSP_IntVectSet((CPU_INT08U   )int_id,
                       (CPU_FNCT_VOID)BSP_IntHandlerDummy);
    }
}

/*
*********************************************************************************************************
*                                        BSP_IntHandler####()
*
* Description : Handle an interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntHandlerDAC                 (void)  { BSP_IntHandler(BSP_INT_ID_DAC);                   }
void  BSP_IntHandlerM0CORE              (void)  { BSP_IntHandler(BSP_INT_ID_M0CORE);                }
void  BSP_IntHandlerDMA                 (void)  { BSP_IntHandler(BSP_INT_ID_DMA);                   }
void  BSP_IntHandlerFLASHEEPROM         (void)  { BSP_IntHandler(BSP_INT_ID_FLASHEEPROM);           }
void  BSP_IntHandlerETHERNET            (void)  { BSP_IntHandler(BSP_INT_ID_ETHERNET);              }
void  BSP_IntHandlerSDIO                (void)  { BSP_IntHandler(BSP_INT_ID_SDIO);                  }
void  BSP_IntHandlerLCD                 (void)  { BSP_IntHandler(BSP_INT_ID_LCD);                   }
void  BSP_IntHandlerUSB0                (void)  { BSP_IntHandler(BSP_INT_ID_USB0);                  }
void  BSP_IntHandlerUSB1                (void)  { BSP_IntHandler(BSP_INT_ID_USB1);                  }
void  BSP_IntHandlerSCT                 (void)  { BSP_IntHandler(BSP_INT_ID_SCT);                   }
void  BSP_IntHandlerRITIMER             (void)  { BSP_IntHandler(BSP_INT_ID_RITIMER);               }
void  BSP_IntHandlerTIMER0              (void)  { BSP_IntHandler(BSP_INT_ID_TIMER0);                }
void  BSP_IntHandlerTIMER1              (void)  { BSP_IntHandler(BSP_INT_ID_TIMER1);                }
void  BSP_IntHandlerTIMER2              (void)  { BSP_IntHandler(BSP_INT_ID_TIMER2);                }
void  BSP_IntHandlerTIMER3              (void)  { BSP_IntHandler(BSP_INT_ID_TIMER3);                }
void  BSP_IntHandlerMCPWM               (void)  { BSP_IntHandler(BSP_INT_ID_MCPWM);                 }
void  BSP_IntHandlerADC0                (void)  { BSP_IntHandler(BSP_INT_ID_ADC0);                  }
void  BSP_IntHandlerI2C0                (void)  { BSP_IntHandler(BSP_INT_ID_I2C0);                  }
void  BSP_IntHandlerI2C1                (void)  { BSP_IntHandler(BSP_INT_ID_I2C1);                  }
void  BSP_IntHandlerSPI                 (void)  { BSP_IntHandler(BSP_INT_ID_SPI);                   }
void  BSP_IntHandlerADC1                (void)  { BSP_IntHandler(BSP_INT_ID_ADC1);                  }
void  BSP_IntHandlerSSP0                (void)  { BSP_IntHandler(BSP_INT_ID_SSP0);                  }
void  BSP_IntHandlerSSP1                (void)  { BSP_IntHandler(BSP_INT_ID_SSP1);                  }
void  BSP_IntHandlerUSART0              (void)  { BSP_IntHandler(BSP_INT_ID_USART0);                }
void  BSP_IntHandlerUART1               (void)  { BSP_IntHandler(BSP_INT_ID_UART1);                 }
void  BSP_IntHandlerUSART2              (void)  { BSP_IntHandler(BSP_INT_ID_USART2);                }
void  BSP_IntHandlerUSART3              (void)  { BSP_IntHandler(BSP_INT_ID_USART3);                }
void  BSP_IntHandlerI2S0                (void)  { BSP_IntHandler(BSP_INT_ID_I2S0);                  }
void  BSP_IntHandlerI2S1                (void)  { BSP_IntHandler(BSP_INT_ID_I2S1);                  }
void  BSP_IntHandlerSPIFI               (void)  { BSP_IntHandler(BSP_INT_ID_SPIFI);                 }
void  BSP_IntHandlerSGPIO               (void)  { BSP_IntHandler(BSP_INT_ID_SGPIO);                 }
void  BSP_IntHandlerPIN_INT0            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT0);              }
void  BSP_IntHandlerPIN_INT1            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT1);              }
void  BSP_IntHandlerPIN_INT2            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT2);              }
void  BSP_IntHandlerPIN_INT3            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT3);              }
void  BSP_IntHandlerPIN_INT4            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT4);              }
void  BSP_IntHandlerPIN_INT5            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT5);              }
void  BSP_IntHandlerPIN_INT6            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT6);              }
void  BSP_IntHandlerPIN_INT7            (void)  { BSP_IntHandler(BSP_INT_ID_PIN_INT7);              }
void  BSP_IntHandlerGINT0               (void)  { BSP_IntHandler(BSP_INT_ID_GINT0);                 }
void  BSP_IntHandlerGINT1               (void)  { BSP_IntHandler(BSP_INT_ID_GINT1);                 }
void  BSP_IntHandlerEVENTROUTER         (void)  { BSP_IntHandler(BSP_INT_ID_EVENTROUTER);           }
void  BSP_IntHandlerC_CAN1              (void)  { BSP_IntHandler(BSP_INT_ID_C_CAN1);                }
void  BSP_IntHandlerATIMER              (void)  { BSP_IntHandler(BSP_INT_ID_ATIMER);                }
void  BSP_IntHandlerRTC                 (void)  { BSP_IntHandler(BSP_INT_ID_RTC);                   }
void  BSP_IntHandlerWWDT                (void)  { BSP_IntHandler(BSP_INT_ID_WWDT);                  }
void  BSP_IntHandlerC_CAN0              (void)  { BSP_IntHandler(BSP_INT_ID_C_CAN0);                }
void  BSP_IntHandlerQEI                 (void)  { BSP_IntHandler(BSP_INT_ID_QEI);                   }

void  BSP_IntHandlerM0_RTC              (void)  { BSP_IntHandler(BSP_INT_ID_M0_RTC);                }
void  BSP_IntHandlerM0_M4CORE           (void)  { BSP_IntHandler(BSP_INT_ID_M0_M4CORE);             }
void  BSP_IntHandlerM0_DMA              (void)  { BSP_IntHandler(BSP_INT_ID_M0_DMA);                }
void  BSP_IntHandlerM0_FLASHEEPROMAT    (void)  { BSP_IntHandler(BSP_INT_ID_M0_FLASHEEPROMAT);      }
void  BSP_IntHandlerM0_ETHERNET         (void)  { BSP_IntHandler(BSP_INT_ID_M0_ETHERNET);           }
void  BSP_IntHandlerM0_SDIO             (void)  { BSP_IntHandler(BSP_INT_ID_M0_SDIO);               }
void  BSP_IntHandlerM0_LCD              (void)  { BSP_IntHandler(BSP_INT_ID_M0_LCD);                }
void  BSP_IntHandlerM0_USB0             (void)  { BSP_IntHandler(BSP_INT_ID_M0_USB0);               }
void  BSP_IntHandlerM0_USB1             (void)  { BSP_IntHandler(BSP_INT_ID_M0_USB1);               }
void  BSP_IntHandlerM0_SCT              (void)  { BSP_IntHandler(BSP_INT_ID_M0_SCT);                }
void  BSP_IntHandlerM0_RITIMER_OR_WWDT  (void)  { BSP_IntHandler(BSP_INT_ID_M0_RITIMER_OR_WWDT);    }
void  BSP_IntHandlerM0_TIMER0           (void)  { BSP_IntHandler(BSP_INT_ID_M0_TIMER0);             }
void  BSP_IntHandlerM0_GINT1            (void)  { BSP_IntHandler(BSP_INT_ID_M0_GINT1);              }
void  BSP_IntHandlerM0_PIN_INT4         (void)  { BSP_IntHandler(BSP_INT_ID_M0_PIN_INT4);           }
void  BSP_IntHandlerM0_TIMER3           (void)  { BSP_IntHandler(BSP_INT_ID_M0_TIMER3);             }
void  BSP_IntHandlerM0_MCPWM            (void)  { BSP_IntHandler(BSP_INT_ID_M0_MCPWM);              }
void  BSP_IntHandlerM0_ADC0             (void)  { BSP_IntHandler(BSP_INT_ID_M0_ADC0);               }
void  BSP_IntHandlerM0_I2C0_OR_I2C1     (void)  { BSP_IntHandler(BSP_INT_ID_M0_I2C0_OR_I2C1);       }
void  BSP_IntHandlerM0_SGPIO            (void)  { BSP_IntHandler(BSP_INT_ID_M0_SGPIO);              }
void  BSP_IntHandlerM0_SPI_OR_DAC       (void)  { BSP_IntHandler(BSP_INT_ID_M0_SPI_OR_DAC);         }
void  BSP_IntHandlerM0_ADC1             (void)  { BSP_IntHandler(BSP_INT_ID_M0_ADC1);               }
void  BSP_IntHandlerM0_SSP0_OR_SSP1     (void)  { BSP_IntHandler(BSP_INT_ID_M0_SSP0_OR_SSP1);       }
void  BSP_IntHandlerM0_EVENTROUTER      (void)  { BSP_IntHandler(BSP_INT_ID_M0_EVENTROUTER);        }
void  BSP_IntHandlerM0_USART0           (void)  { BSP_IntHandler(BSP_INT_ID_M0_USART0);             }
void  BSP_IntHandlerM0_UART1            (void)  { BSP_IntHandler(BSP_INT_ID_M0_UART1);              }
void  BSP_IntHandlerM0_USART_OR_C_CAN   (void)  { BSP_IntHandler(BSP_INT_ID_M0_USART_OR_C_CAN);     }
void  BSP_IntHandlerM0_USART3           (void)  { BSP_IntHandler(BSP_INT_ID_M0_USART3);             }
void  BSP_IntHandlerM0_I2S0_OR_I2S1_QEI (void)  { BSP_IntHandler(BSP_INT_ID_M0_I2S0_OR_I2S1_QEI);   }
void  BSP_IntHandlerM0_C_CAN0           (void)  { BSP_IntHandler(BSP_INT_ID_M0_C_CAN0);             }


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        BSP_IntHandlerDummy()
*
* Description : Dummy interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void  BSP_IntHandlerDummy (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*****************************************s****************************************************************
*                                        BSP_IntHandler()
*
* Description : General Maskable Interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntHandler (CPU_INT16U  src_nbr)
{
    CPU_FNCT_VOID  isr;

    if (src_nbr < BSP_INT_ID_MAX) {
        isr = BSP_IntVectTbl[src_nbr];
        if (isr != (CPU_FNCT_VOID)0) {
            isr();
        }
    }
}
