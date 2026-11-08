 .syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.thumb
	.thumb_func

.global	__delay

//----------------------------------------------
//       Arg: Number of cycles (min 16)
__delay:
        LSRS    R1, R0, #2
        SUBS    R1, R1, #3

L1:     SUBS    R1, R1, #1
        NOP
        BNE     L1
        
        MOVS    R1, #1
        ANDS    R1, R0, R1	//#1
        BNE     L2

L2:     MOVS    R1, #2
        ANDS    R1, R0, R1	//#1
        BNE     L3
L3:     BNE     L4        

L4:     BX      LR
//----------------------------------------------
