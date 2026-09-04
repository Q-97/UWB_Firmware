/******************************************************************************
*
* @file      startup_zn2014.s
* @author    ultraception FW team
* @brief     zn2014 device vector table for GCC based toolchains. 
*            This module performs:
*                - Set the initial SP
*                - Set the initial PC == Reset_Handler,
*                - Set the vector table entries with the exceptions ISR address
*                - Branches to main in the C library (which eventually
*                  calls main()).
*            After Reset the Cortex-M33 processor is in Thread mode,
*            priority is Privileged, and the Stack is set to Main.
******************************************************************************/

    
.syntax unified
.cpu cortex-m33
.fpu softvfp
.thumb

.global  __Vectors
.global  Default_Handler

.section  .text.Reset_Handler
.weak  Reset_Handler
.type  Reset_Handler, %function
Reset_Handler:
    ldr  sp, = __initial_sp
    bl   SystemInit
    movs r1, #0
    b    LoopCopyRamTextInit

CopyRamTextInit:
    ldr  r3, =_siramtext
    ldr  r3, [r3, r1]
    str  r3, [r0, r1]
    adds r1, r1, #4
    
LoopCopyRamTextInit:
    ldr  r0, =_sramtext
    ldr  r3, =_eramtext
    adds r2, r0, r1
    cmp  r2, r3
    bcc  CopyRamTextInit
    movs r1, #0
    b    LoopCopyDataInit

CopyDataInit:
    ldr  r3, =_sidata
    ldr  r3, [r3, r1]
    str  r3, [r0, r1]
    adds r1, r1, #4
    
LoopCopyDataInit:
    ldr  r0, =_sdata
    ldr  r3, =_edata
    adds r2, r0, r1
    cmp  r2, r3
    bcc  CopyDataInit
    ldr  r2, =_sbss
    b    LoopFillZerobss
 
FillZerobss:
    movs r3, #0
    str  r3, [r2], #4
    
LoopFillZerobss:
    ldr  r3, = _ebss
    cmp  r2, r3
    bcc  FillZerobss

    bl   main
    bx   lr
.size  Reset_Handler, .-Reset_Handler


.section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b    Infinite_Loop
.size  Default_Handler, .-Default_Handler


.section  .isr_vector,"a",%progbits
.type  __Vectors, %object
.size  __Vectors, .-__Vectors

__Vectors:
    .word  __initial_sp
    .word  Reset_Handler
    .word  NMI_Handler
    .word  HardFault_Handler
    .word  MemManage_Handler
    .word  BusFault_Handler
    .word  UsageFault_Handler
    .word  SecureFault_Handler
    .word  0
    .word  0
    .word  0
    .word  SVC_Handler
    .word  DebugMon_Handler
    .word  0
    .word  PendSV_Handler
    .word  SysTick_Handler
    
    /* External Interrupts */
    .word  WDT_IRQHandler                      /* Watch Dog   */                                        
    .word  UART0_IRQHandler                    /* Uart0       */                        
    .word  I2C0_IRQHandler                     /* I2C0        */            
    .word  SPI0_IRQHandler                     /* Spi0        */                      
    .word  SPI1_IRQHandler                     /* Spi1        */                                          
    .word  CAN_IRQHandler                      /* Can         */                                            
    .word  TIMER0_IRQHandler                   /* Timer0      */                        
    .word  TIMER1_IRQHandler                   /* Timer1      */                          
    .word  TIMER2_IRQHandler                   /* Timer2      */                          
    .word  GPIO_IRQHandler                     /* GPIO        */                          
    .word  DMA0_IRQHandler                     /* Dma0        */                          
    .word  SE_IRQHandler                       /* Se          */                  
    .word  UWB_IRQHandler                      /* Uwb         */                   


    .weak      NMI_Handler
    .thumb_set NMI_Handler,Default_Handler
   
    .weak      HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler
   
    .weak      MemManage_Handler
    .thumb_set MemManage_Handler,Default_Handler
   
    .weak      BusFault_Handler
    .thumb_set BusFault_Handler,Default_Handler
 
    .weak      UsageFault_Handler
    .thumb_set UsageFault_Handler,Default_Handler
 
    .weak      SecureFault_Handler
    .thumb_set SecureFault_Handler,Default_Handler
 
    .weak      SVC_Handler
    .thumb_set SVC_Handler,Default_Handler
 
    .weak      DebugMon_Handler
    .thumb_set DebugMon_Handler,Default_Handler
 
    .weak      PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler
 
    .weak      SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler              
   
    .weak      WDT_IRQHandler                   
    .thumb_set WDT_IRQHandler,Default_Handler      
                   
    .weak      UART0_IRQHandler      
    .thumb_set UART0_IRQHandler,Default_Handler
                
    .weak      I2C0_IRQHandler            
    .thumb_set I2C0_IRQHandler,Default_Handler
             
    .weak      SPI0_IRQHandler                  
    .thumb_set SPI0_IRQHandler,Default_Handler
             
    .weak      SPI1_IRQHandler         
    .thumb_set SPI1_IRQHandler,Default_Handler
                   
    .weak      CAN_IRQHandler      
    .thumb_set CAN_IRQHandler,Default_Handler
                   
    .weak      TIMER0_IRQHandler         
    .thumb_set TIMER0_IRQHandler,Default_Handler
                   
    .weak      TIMER1_IRQHandler         
    .thumb_set TIMER1_IRQHandler,Default_Handler
                      
    .weak      TIMER2_IRQHandler         
    .thumb_set TIMER2_IRQHandler,Default_Handler 
                  
    .weak      GPIO_IRQHandler         
    .thumb_set GPIO_IRQHandler,Default_Handler
                         
    .weak      DMA0_IRQHandler         
    .thumb_set DMA0_IRQHandler,Default_Handler
                   
    .weak      SE_IRQHandler               
    .thumb_set SE_IRQHandler,Default_Handler
          
    .weak      UWB_IRQHandler               
    .thumb_set UWB_IRQHandler,Default_Handler
