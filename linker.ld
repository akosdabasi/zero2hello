ENTRY(Reset_Handler); /*so that the debugger and other tools know*/

MEMORY {
  sram(rwx) : ORIGIN = 0x20000000, LENGTH = 20k  
  flash(rx) : ORIGIN = 0x08000000, LENGTH = 128k
}

/* Full-descending stack start at the end of SRAM*/
_sstack = ORIGIN(sram) + LENGTH(sram); 


/*
VMA: the address the section will have when the output file is run
LMA: the address at which the section will be loaded
-> data section is loaded into ROM(LMA) and copied into RAM(VMA) whe the program starts up
*/

SECTIONS{

    .vectors : 
    { 
      KEEP(*(.vectors)) /*Otherwise it would get garbage collected by the linker, since it's not referenced in the code*/
    } > flash
    
    .text : 
    {
      *(.text*) 
    } > flash
    
    .rodata :
    {
      *(.rodata*) 
    } > flash

    .data : 
    {
      _sdata = .;             /* .data section start */
      *(.data SORT(.data.*))  /*sections will be placed in memory in a stable order*/
      _edata = .;             /* .data section end */
    } > sram AT > flash

    _sidata = LOADADDR(.data);

    .bss : 
    {
      _sbss = .;                    /* .bss section start */
      *(.bss SORT(.bss.*) COMMON)   /*sections will be placed in memory in a stable order*/
      _ebss = .;                    /* .bss section end */
    } > sram
}