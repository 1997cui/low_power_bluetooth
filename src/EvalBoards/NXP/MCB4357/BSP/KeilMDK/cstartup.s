;/***********************************************************************
; * $Id: startup_LPC43xx.s 6473 2011-02-16 17:40:54Z nxp27266 $
; *
; * Project: LPC43xx CMSIS Package
; *
; * Description: Cortex-M3 Core Device Startup File for the NXP LPC43xx
; *              Device Series.
; *
; * Copyright(C) 2011, NXP Semiconductor
; * All rights reserved.
; *
; *                                                      modified by KEIL
; ***********************************************************************
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * products. This software is supplied "AS IS" without any warranties.
; * NXP Semiconductors assumes no responsibility or liability for the
; * use of the software, conveys no license or title under any patent,
; * copyright, or mask work right to the product. NXP Semiconductors
; * reserves the right to make changes in the software without
; * notification. NXP Semiconductors also make no representation or
; * warranty that such application will be suitable for the specified
; * use without further testing or modification.
; **********************************************************************/

;/*
;********************************************************************************************************
;*                                              STACK DEFINITIONS
;*
;* Configuration Wizard Menu:
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;*********************************************************************************************************
;*/

;                IMPORT  CORTEX_M0
;                IMPORT  CORTEX_M4
;                EXTERN  CORTEX_M0_EN
;                EXTERN  CORTEX_M4_EN


Stack_Size      EQU     0x00000300

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


;/*
;********************************************************************************************************
;*                                          HEAP DEFINITIONS
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;*********************************************************************************************************
;*/

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

                                                                ; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                                                                ; BSP Vector Interrupt Functions
                IF      :DEF:CORTEX_M4                          ; Cortex-M4 Interrupts
                IMPORT  BSP_IntHandlerDAC
                IMPORT  BSP_IntHandlerM0CORE              
                IMPORT  BSP_IntHandlerDMA                 
                IMPORT  BSP_IntHandlerFLASHEEPROM         
                IMPORT  BSP_IntHandlerETHERNET            
                IMPORT  BSP_IntHandlerSDIO                
                IMPORT  BSP_IntHandlerLCD                 
                IMPORT  BSP_IntHandlerUSB0                
                IMPORT  BSP_IntHandlerUSB1                
                IMPORT  BSP_IntHandlerSCT                 
                IMPORT  BSP_IntHandlerRITIMER             
                IMPORT  BSP_IntHandlerTIMER0              
                IMPORT  BSP_IntHandlerTIMER1              
                IMPORT  BSP_IntHandlerTIMER2              
                IMPORT  BSP_IntHandlerTIMER3              
                IMPORT  BSP_IntHandlerMCPWM               
                IMPORT  BSP_IntHandlerADC0                
                IMPORT  BSP_IntHandlerI2C0                
                IMPORT  BSP_IntHandlerI2C1                
                IMPORT  BSP_IntHandlerSPI                 
                IMPORT  BSP_IntHandlerADC1                
                IMPORT  BSP_IntHandlerSSP0                
                IMPORT  BSP_IntHandlerSSP1                
                IMPORT  BSP_IntHandlerUSART0              
                IMPORT  BSP_IntHandlerUART1               
                IMPORT  BSP_IntHandlerUSART2              
                IMPORT  BSP_IntHandlerUSART3              
                IMPORT  BSP_IntHandlerI2S0                
                IMPORT  BSP_IntHandlerI2S1                
                IMPORT  BSP_IntHandlerSPIFI               
                IMPORT  BSP_IntHandlerSGPIO               
                IMPORT  BSP_IntHandlerPIN_INT0            
                IMPORT  BSP_IntHandlerPIN_INT1            
                IMPORT  BSP_IntHandlerPIN_INT2            
                IMPORT  BSP_IntHandlerPIN_INT3            
                IMPORT  BSP_IntHandlerPIN_INT4            
                IMPORT  BSP_IntHandlerPIN_INT5            
                IMPORT  BSP_IntHandlerPIN_INT6            
                IMPORT  BSP_IntHandlerPIN_INT7            
                IMPORT  BSP_IntHandlerGINT0               
                IMPORT  BSP_IntHandlerGINT1               
                IMPORT  BSP_IntHandlerEVENTROUTER         
                IMPORT  BSP_IntHandlerC_CAN1              
                IMPORT  BSP_IntHandlerATIMER              
                IMPORT  BSP_IntHandlerRTC                 
                IMPORT  BSP_IntHandlerWWDT                
                IMPORT  BSP_IntHandlerC_CAN0              
                IMPORT  BSP_IntHandlerQEI                 
                
                ENDIF
                
                IF      :DEF:CORTEX_M0                          ; Cortex-M0 Interrupts
                IMPORT  BSP_IntHandlerM0_RTC              
                IMPORT  BSP_IntHandlerM0_M4CORE           
                IMPORT  BSP_IntHandlerM0_DMA              
                IMPORT  BSP_IntHandlerM0_FLASHEEPROMAT    
                IMPORT  BSP_IntHandlerM0_ETHERNET         
                IMPORT  BSP_IntHandlerM0_SDIO             
                IMPORT  BSP_IntHandlerM0_LCD        
                IMPORT  BSP_IntHandlerM0_USB0       
                IMPORT  BSP_IntHandlerM0_USB1       
                IMPORT  BSP_IntHandlerM0_SCT        
                IMPORT  BSP_IntHandlerM0_RITIMER_OR_WWDT  
                IMPORT  BSP_IntHandlerM0_TIMER0           
                IMPORT  BSP_IntHandlerM0_GINT1            
                IMPORT  BSP_IntHandlerM0_PIN_INT4 
                IMPORT  BSP_IntHandlerM0_TIMER3
                IMPORT  BSP_IntHandlerM0_MCPWM
                IMPORT  BSP_IntHandlerM0_ADC0             
                IMPORT  BSP_IntHandlerM0_I2C0_OR_I2C1     
                IMPORT  BSP_IntHandlerM0_SGPIO            
                IMPORT  BSP_IntHandlerM0_SPI_OR_DAC       
                IMPORT  BSP_IntHandlerM0_ADC1             
                IMPORT  BSP_IntHandlerM0_SSP0_OR_SSP1     
                IMPORT  BSP_IntHandlerM0_EVENTROUTER      
                IMPORT  BSP_IntHandlerM0_USART0           
                IMPORT  BSP_IntHandlerM0_UART1            
                IMPORT  BSP_IntHandlerM0_USART_OR_C_CAN   
                IMPORT  BSP_IntHandlerM0_USART3           
                IMPORT  BSP_IntHandlerM0_I2S0_OR_I2S1_QEI 
                IMPORT  BSP_IntHandlerM0_C_CAN0           
                
                ENDIF
                
                IMPORT  OS_CPU_PendSVHandler
                IMPORT  OS_CPU_SysTickHandler

Sign_Value      EQU     0x5A5A5A5A

__Vectors       DCD     __initial_sp                        ; 0 Top of Stack
                DCD     Reset_Handler                       ; 1 Reset Handler
                DCD     App_NMI_ISR                         ; 2 NMI Handler
                DCD     App_HardFault_ISR                   ; 3 Hard Fault Handler
                DCD     App_MemFault_ISR                    ; 4 MPU Fault Handler
                DCD     App_BusFault_ISR                    ; 5 Bus Fault Handler
                DCD     App_UsageFault_ISR                  ; 6 Usage Fault Handler
                DCD     Sign_Value                          ; 7 Reserved
                DCD     App_Spurious_ISR                    ; 8 Reserved
                DCD     App_Spurious_ISR                    ; 9 Reserved
                DCD     App_Spurious_ISR                    ; 10 Reserved
                DCD     App_Spurious_ISR                    ; 11 SVCall Handler
                DCD     App_Spurious_ISR                    ; 12 Debug Monitor Handler
                DCD     App_Spurious_ISR                    ; 13 Reserved
                DCD     OS_CPU_PendSVHandler                ; 14 PendSV Handler
                DCD     OS_CPU_SysTickHandler               ; 15 SysTick Handler

                                                            ; External Interrupts
                IF      :DEF:CORTEX_M4                      ; Cortex-M4 Interrupts
                DCD     BSP_IntHandlerDAC                   ; 16 D/A Converter
                DCD     BSP_IntHandlerM0CORE                ; 17 M0 Core
                DCD     BSP_IntHandlerDMA                   ; 18 General Purpose DMA
                DCD     App_Reserved_ISR                    ; 19 Reserved
                DCD     BSP_IntHandlerFLASHEEPROM           ; 20 Reserved for Typhoon
                DCD     BSP_IntHandlerETHERNET              ; 21 Ethernet
                DCD     BSP_IntHandlerSDIO                  ; 22 SD/MMC
                DCD     BSP_IntHandlerLCD                   ; 23 LCD
                DCD     BSP_IntHandlerUSB0                  ; 24 USB0
                DCD     BSP_IntHandlerUSB1                  ; 25 USB1
                DCD     BSP_IntHandlerSCT                   ; 26 State Configurable Timer
                DCD     BSP_IntHandlerRITIMER               ; 27 Repetitive Interrupt Timer
                DCD     BSP_IntHandlerTIMER0                ; 28 Timer0
                DCD     BSP_IntHandlerTIMER1                ; 29 Timer1
                DCD     BSP_IntHandlerTIMER2                ; 30 Timer2
                DCD     BSP_IntHandlerTIMER3                ; 31 Timer3
                DCD     BSP_IntHandlerMCPWM                 ; 32 Motor Control PWM
                DCD     BSP_IntHandlerADC0                  ; 33 A/D Converter 0
                DCD     BSP_IntHandlerI2C0                  ; 34 I2C0
                DCD     BSP_IntHandlerI2C1                  ; 35 I2C1
                DCD     BSP_IntHandlerSPI                   ; 36 SPI
                DCD     BSP_IntHandlerADC1                  ; 37 A/D Converter 1
                DCD     BSP_IntHandlerSSP0                  ; 38 SSP0
                DCD     BSP_IntHandlerSSP1                  ; 39 SSP1
                DCD     BSP_IntHandlerUSART0                ; 40 UART0
                DCD     BSP_IntHandlerUART1                 ; 41 UART1
                DCD     BSP_IntHandlerUSART2                ; 42 UART2
                DCD     BSP_IntHandlerUSART3                ; 43 UART3
                DCD     BSP_IntHandlerI2S0                  ; 44 I2S0
                DCD     BSP_IntHandlerI2S1                  ; 45 I2S1
                DCD     BSP_IntHandlerSPIFI                 ; 46 SPI Flash Interface
                DCD     BSP_IntHandlerSGPIO                 ; 47 SGPIO
                DCD     BSP_IntHandlerPIN_INT0              ; 48 GPIO0
                DCD     BSP_IntHandlerPIN_INT1              ; 49 GPIO1
                DCD     BSP_IntHandlerPIN_INT2              ; 50 GPIO2
                DCD     BSP_IntHandlerPIN_INT3              ; 51 GPIO3
                DCD     BSP_IntHandlerPIN_INT4              ; 52 GPIO4
                DCD     BSP_IntHandlerPIN_INT5              ; 53 GPIO5
                DCD     BSP_IntHandlerPIN_INT6              ; 54 GPIO6
                DCD     BSP_IntHandlerPIN_INT7              ; 55 GPIO7
                DCD     BSP_IntHandlerGINT0                 ; 56 GINT0
                DCD     BSP_IntHandlerGINT1                 ; 57 GINT1
                DCD     BSP_IntHandlerEVENTROUTER           ; 58 Event Router
                DCD     BSP_IntHandlerC_CAN1                ; 59 C_CAN1
                DCD     App_Reserved_ISR                    ; 60 Reserved
                DCD     App_Reserved_ISR                    ; 61 VADC
                DCD     BSP_IntHandlerATIMER                ; 62 ATIMER
                DCD     BSP_IntHandlerRTC                   ; 63 RTC
                DCD     App_Reserved_ISR                    ; 64 Reserved
                DCD     BSP_IntHandlerWWDT                  ; 65 WDT
                DCD     App_Reserved_ISR                    ; 66 Reserved
                DCD     BSP_IntHandlerC_CAN0                ; 67 C_CAN0
                DCD     BSP_IntHandlerQEI                   ; 68 QEI
                ENDIF
                
                IF      :DEF:CORTEX_M0                      ; Cortex-M0 Interrupts
                DCD     BSP_IntHandlerM0_RTC                ; 16 RTC
                DCD     BSP_IntHandlerM0_M4CORE             ; 17 M4 Core        
                DCD     BSP_IntHandlerM0_DMA                ; 18 General Purpose DMA
                DCD     App_Reserved_ISR                    ; 19 Reserved
                DCD     BSP_IntHandlerM0_FLASHEEPROMAT      ; 20 ORed flash bank A, flash bank B, EEPROM, Atimer
                DCD     BSP_IntHandlerM0_ETHERNET           ; 21 Ethernet
                DCD     BSP_IntHandlerM0_SDIO               ; 22 SD/MMC
                DCD     BSP_IntHandlerM0_LCD                ; 23 LCD
                DCD     BSP_IntHandlerM0_USB0               ; 24 USB0
                DCD     BSP_IntHandlerM0_USB1               ; 25 USB1
                DCD     BSP_IntHandlerM0_SCT                ; 26 State Configurable Timer
                DCD     BSP_IntHandlerM0_RITIMER_OR_WWDT    ; 27 Repetitive Interrupt Timer or WWDT
                DCD     BSP_IntHandlerM0_TIMER0             ; 28 Timer0
                DCD     BSP_IntHandlerM0_GINT1              ; 29 GPIO global interrupt 1
                DCD     BSP_IntHandlerM0_PIN_INT4           ; 30 GPIO pin interrupt 4
                DCD     BSP_IntHandlerM0_TIMER3             ; 31 Timer3
                DCD     BSP_IntHandlerM0_MCPWM              ; 32 Motor control PWM
                DCD     BSP_IntHandlerM0_ADC0               ; 33 ADC0
                DCD     BSP_IntHandlerM0_I2C0_OR_I2C1       ; 34 I2C or I2C1
                DCD     BSP_IntHandlerM0_SGPIO              ; 35 Serial GPIO
                DCD     BSP_IntHandlerM0_SPI_OR_DAC         ; 36 SPI or DAC
                DCD     BSP_IntHandlerM0_ADC1               ; 37 ADC1
                DCD     BSP_IntHandlerM0_SSP0_OR_SSP1       ; 38 SSP0 or SSP1
                DCD     BSP_IntHandlerM0_EVENTROUTER        ; 39 Event router
                DCD     BSP_IntHandlerM0_USART0             ; 40 USART0
                DCD     BSP_IntHandlerM0_UART1              ; 41 UART1/Modem
                DCD     BSP_IntHandlerM0_USART_OR_C_CAN     ; 42 USART2 or C CAN1
                DCD     BSP_IntHandlerM0_USART3             ; 43 USART3
                DCD     BSP_IntHandlerM0_I2S0_OR_I2S1_QEI   ; 44 I2S0 or I2S1 or QEI
                DCD     BSP_IntHandlerM0_C_CAN0             ; 45 C CAN0
                DCD     App_Reserved_ISR                    ; 46 Reserved
                DCD     App_Reserved_ISR                    ; 47 Reserved
                ENDIF
                

;CRP address at offset 0x2FC relative to the BOOT Bank address
                IF      :LNOT::DEF:NO_CRP
                SPACE   (0x2FC - (. - __Vectors))
;                EXPORT  CRP_Key
CRP_Key         DCD     0xFFFFFFFF
;                       0xFFFFFFFF => CRP Disabled
;                       0x12345678 => CRP Level 1
;                       0x87654321 => CRP Level 2
;                       0x43218765 => CRP Level 3 (ARE YOU SURE?)
;                       0x4E697370 => NO ISP      (ARE YOU SURE?)
                ENDIF

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler           [WEAK]
                IMPORT  BSP_LowLevelInit
                IMPORT  __main
                LDR     R0, =BSP_LowLevelInit
                BLX     R0

                                                ; Enable Floating Point Support at reset for FPU
                LDR.W   R0, =0xE000ED88         ; Load address of CPACR register
                LDR     R1, [R0]                ; Read value at CPACR
                ORR     R1,  R1, #(0xF <<20)    ; Set bits 20-23 to enable CP10 and CP11 coprocessors
                                                ; Write back the modified CPACR value
                STR     R1, [R0]                ; Wait for store to complete
                DSB

                                                ; Disable automatic FP register content
                                                ; Disable lazy context switch
                LDR.W   R0, =0xE000EF34         ; Load address to FPCCR register
                LDR     R1, [R0]
                AND     R1,  R1, #(0x3FFFFFFF)  ; Clear the LSPEN and ASPEN bits
                STR     R1, [R0]
                ISB                             ; Reset pipeline now the FPU is enabled

                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

App_NMI_ISR     PROC
                EXPORT  App_NMI_ISR             [WEAK]
                B       .
                ENDP
App_HardFault_ISR\
                PROC
                EXPORT  App_HardFault_ISR       [WEAK]
                B       .
                ENDP
App_MemFault_ISR\
                PROC
                EXPORT  App_MemFault_ISR        [WEAK]
                B       .
                ENDP
App_BusFault_ISR\
                PROC
                EXPORT  App_BusFault_ISR        [WEAK]
                B       .
                ENDP
App_UsageFault_ISR\
                PROC
                EXPORT  App_UsageFault_ISR      [WEAK]
                B       .
                ENDP
App_Spurious_ISR\
                PROC
                EXPORT  App_Spurious_ISR        [WEAK]
                B       .
                ENDP
App_Reserved_ISR\
                PROC
                EXPORT  App_Reserved_ISR        [WEAK]
                B       .
                ENDP



                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
