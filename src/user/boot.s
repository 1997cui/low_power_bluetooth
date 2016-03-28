Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit						
				PRESERVE8			 ;8字节对齐
                THUMB				 ;下面指令为32位THUMB指令
 ;定义中断向量表
;ENTRY
		        AREA RESET,data,READONLY

				EXPORT  Reset_Handler           
                IMPORT  __main
				EXPORT  __initial_sp


                EXPORT __Vectors
__Vectors       DCD	    __initial_sp
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler
           

                AREA    |.text|, CODE, READONLY
Reset_Handler   
                LDR     R0, =__main
                BX      R0


; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler          B       .
HardFault_Handler	 B		 .
MemManage_Handler	 B       .
BusFault_Handler	 B       .
UsageFault_Handler	 B       .
SVC_Handler     	 B       .
DebugMon_Handler	 B       .
PendSV_Handler  	 B       .
SysTick_Handler 
               EXPORT  SysTick_Handler           [WEAK]	 
               B       .
            

			    ALIGN
				END

