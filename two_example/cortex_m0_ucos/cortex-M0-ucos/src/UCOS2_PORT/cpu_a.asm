       EXPORT  CPU_IntDis
       EXPORT  CPU_IntEn


        AREA |.text|, CODE, READONLY, ALIGN=2
		THUMB
		REQUIRE8
		PRESERVE8


;************************
;�ж�ʹ�ܺ�ʧ�ܶ���
;************************
CPU_IntEn
        CPSIE   I
        BX      LR

CPU_IntDis
        CPSID   I
        BX      LR

        END


