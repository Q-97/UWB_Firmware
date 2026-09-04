/*****************************************************************************
*
*  File        : ZN2014_FLASH.ld
*  Author	   : ultraception FW team
*  Abstract    : Linker script for ZN2014 series
*                192Kbytes FLASH and 256Kbytes RAM
*
*                Set heap size, stack size and stack location according
*                to application requirements.
*
*                Set memory bank area and size if external memory is used.
*
*  Target      : ultraception ZN
*****************************************************************************/

__initial_sp = 0x20020000;

_Min_Heap_Size = 0xc00;      /* required amount of heap  */
_Min_Stack_Size = 0x1000;    /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
    FLASH (rx)     : ORIGIN = 0x8000000, LENGTH = 192K
    RAMTEXT (xrw)  : ORIGIN = 0x1FFE0000, LENGTH = 128K
    RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Entry Point */
ENTRY(Reset_Handler)

/* Define output sections */
SECTIONS
{
    /* The startup code goes first into FLASH */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) /* Startup code */
        . = ALIGN(4);
    } > FLASH

    _siramtext = LOADADDR(.ramtext);
    .ramtext : 
	{
        . = ALIGN(4);
        _sramtext = .;
		*zn_qspi.o(.text* .rodata*)
        *zn_qspi_gd25q40.o(.text* .rodata*)
        *.o (.ramtext*)
        . = ALIGN(4);
        _eramtext = .;
    } > RAMTEXT AT > FLASH

    /* The program code and other data goes into FLASH */
    .text :
    {
        . = ALIGN(4);
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        . = ALIGN(4);
        _etext = .;        /* define a global symbols at end of code */
    } > FLASH

    /* Constant data goes into FLASH */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
		*(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(4);
    } > FLASH

    /* used by the startup to initialize data */
    _sidata = LOADADDR(.data);
    /* Initialized data sections goes into RAM, load LMA copy after code */
    .data : 
    {
        . = ALIGN(4);
        _sdata = .;        /* create a global symbol at data start */
        *(.data)           /* .data sections */
        *(.data*)          /* .data* sections */
        . = ALIGN(4);
        _edata = .;        /* define a global symbol at data end */
    } > RAM AT > FLASH
  
    /* Uninitialized data section */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;         /* define a global symbol at bss start */
        __bss_start__ = _sbss;
        *(.bss)
		*(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;         /* define a global symbol at bss end */
        __bss_end__ = _ebss;
    } > RAM

    /* User_heap_stack section, used to check that there is enough RAM left */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } > RAM

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }
}
