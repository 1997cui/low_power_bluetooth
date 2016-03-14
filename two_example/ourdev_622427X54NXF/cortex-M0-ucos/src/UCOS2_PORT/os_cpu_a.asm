
    EXTERN  OSRunning                                           ; External references
    EXTERN  OSPrioCur
    EXTERN  OSPrioHighRdy
    EXTERN  OSTCBCur
    EXTERN  OSTCBHighRdy
    EXTERN  OSIntNesting
    EXTERN  OSIntExit
    EXTERN  OSTaskSwHook

    
    EXPORT  OS_CPU_SR_Save                                      ; Functions declared in this file
    EXPORT  OS_CPU_SR_Restore
    EXPORT  OSStartHighRdy
    EXPORT  OSCtxSw
    EXPORT  OSIntCtxSw


    AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8
        
;************************************
;保存和恢复中断屏蔽寄存器子函数定义
;************************************

OS_CPU_SR_Save
        MRS     R0, PRIMASK                 ; Set prio int mask to mask all (except faults)
        CPSID   I
        BX      LR


OS_CPU_SR_Restore
        MSR     PRIMASK, R0
        BX      LR


;************************************
;启动多任务
;************************************

OSStartHighRdy
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0

    LDR     R0, __OS_Running                                    ; OSRunning = TRUE;
    MOVS    R1, #1
    STRB    R1, [R0]
    
                                                                ; SWITCH TO HIGHEST PRIORITY TASK:
    LDR     R0, __OS_TCBHighRdy                                 ;   Get highest priority task TCB address,
    LDR     R1, [R0]                                            ;   Get stack pointer,
    LDR     R2, [R1]
    MSR     MSP, R2                                             ;   Switch to the new stack,
    
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3    
        
                                                                ; NORMAL FUNCTION RETURN (see Note #2)
    ADD     SP, #0x10
    POP    {R0-R3}                                              ;   Pop new task's R12, PC, LR, PSR into (R0, R1, R2, R3, respectively)
    MOV     R12, R0
    MOV     LR,  R1
    MSR     PSR, R3
    
    PUSH   {R2}                                                 ;   Save PC
    
    SUB     SP, #0x1C                                           
    POP    {R0-R3}                                              ;   Pop new task's R0-R3
    ADD     SP, #0x0C
    
    CPSIE   I                                                   ;   Enable interrupts
    
    POP    {PC}                                                 ;   Pop new task's PC
    
   
    
;************************************
;任务级别下的任务切换
;************************************

OSCtxSw
	CPSID   I
	SUB     SP,#0x10
	PUSH    {R0-R3}

	ADD     SP,#0x20
	MRS     R3, PSR
	MOV		R2, LR
	MOV		R1, LR
	MOV     R0, R12
	PUSH    {R0-R3}

	SUB     SP, #0x10
	MOV 	R0, R8
	MOV 	R1, R9
	MOV 	R2, R10
	MOV 	R3, R11
	PUSH    {R0-R7}


    MRS     R0, MSP
    LDR     R1, __OS_TCBCur                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]    
 
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0
   
    LDR     R0, __OS_PrioCur                                    ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, __OS_PrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, __OS_TCBCur                                     ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, __OS_TCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]
    
    LDR     R0, [R2]                                            ; SP = OSTCBHighRdy->OSTCBStkPtr;
    MSR     MSP, R0                                             
    
	                                                               ; RESTORE TASK's CONTEXT
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3  
	
	ADD     SP, #0x10
    POP    {R0-R3}                                              ;   Pop new task's R12, PC, LR, PSR into (R0, R1, R2, R3, respectively)
    MOV     R12, R0
    MOV     LR,  R1
    MSR     PSR, R3
    
    PUSH   {R2}                                                 ;   Save PC
    
    SUB     SP, #0x1C                                           
    POP    {R0-R3}                                              ;   Pop new task's R0-R3
    ADD     SP, #0x0C 
    CPSIE   I                                                   ;   Enable interrupts
    POP    {PC}    
    NOP

;************************************
;中断级别下的任务切换
;************************************

OSIntCtxSw
	CPSID   I
	SUB     SP,#0x10
	PUSH    {R0-R3}

	ADD     SP,#0x20
	MRS     R3, PSR
	MOV		R2, LR
	MOV		R1, LR
	MOV     R0, R12
	PUSH    {R0-R3}

	SUB     SP, #0x10
	MOV 	R0, R8
	MOV 	R1, R9
	MOV 	R2, R10
	MOV 	R3, R11
	PUSH    {R0-R7}


    MRS     R0, MSP
    LDR     R1, __OS_TCBCur                                     ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]    
 
    LDR     R0, __OS_TaskSwHook                                 ; OSTaskSwHook();
    BLX     R0
   
    LDR     R0, __OS_PrioCur                                    ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, __OS_PrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, __OS_TCBCur                                     ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, __OS_TCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]
    
    LDR     R0, [R2]                                            ; SP = OSTCBHighRdy->OSTCBStkPtr;
    MSR     MSP, R0                                             
    
	                                                               ; RESTORE TASK's CONTEXT
    POP    {R0-R7}                                              ;   Pop new task's R8-R11 (into R0-R3), R4-R7
    MOV     R8,  R0                                              
    MOV     R9,  R1
    MOV     R10, R2
    MOV     R11, R3  
	
	ADD     SP, #0x10
    POP    {R0-R3}                                              ;   Pop new task's R12, PC, LR, PSR into (R0, R1, R2, R3, respectively)
    MOV     R12, R0
    MOV     LR,  R1
    MSR     PSR, R3
    
    PUSH   {R2}                                                 ;   Save PC
    
    SUB     SP, #0x1C                                           
    POP    {R0-R3}                                              ;   Pop new task's R0-R3
    ADD     SP, #0x0C 
    CPSIE   I                                                   ;   Enable interrupts
    POP    {PC}    
    NOP         

;************************************
;全局变量定义
;************************************
__OS_TaskSwHook
    DCD     OSTaskSwHook

__OS_IntExit
    DCD     OSIntExit

__OS_IntNesting
    DCD     OSIntNesting

__OS_PrioCur
    DCD     OSPrioCur

__OS_PrioHighRdy
    DCD     OSPrioHighRdy

__OS_Running
    DCD     OSRunning

__OS_TCBCur
    DCD     OSTCBCur

__OS_TCBHighRdy
    DCD     OSTCBHighRdy

    END
