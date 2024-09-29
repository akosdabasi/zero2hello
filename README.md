# zero2hello

This project is created to understand all the steps involved in printing "hello" from an MCU via UART.
The code will be developed outside of any IDE, only using VS Code as a text editor and some command line tools.

This documentation will be updated as the project progresses and it's main purpose is to document everything I learn and hopefully it will serve as a guide for others who want to understand how code gets executed on an MCU.

## Overview

The following steps will be carried out throughout this project:

1. setting up the MCU by writing the **linker script** and the **startup code**
2. setting up a build environment by creating a **Makefile**
3. writing a **GPIO driver**
4. writing a **UART driver**
5. implementing **syscalls** (\_write, \_sbrk)
6. implementing **printf** using UART
7. importing the **C standard library**

Tools used in this project:

- text editor: [VS Code](https://code.visualstudio.com/download)
- build toolchain: [arm-none-eabi-gcc](https://developer.arm.com/downloads/-/gnu-rm)
- build automation: [Make](https://www.gnu.org/software/make/)
- debugger: [Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/)

## Hardware and Documentation:

The hardware used during this project is an [STM32F103RB Nucleo board](https://www.st.com/en/evaluation-tools/nucleo-f103rb.html). This is a development board with an integrated [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html) debugger/programmer and with the [STM32F103RB MCU](https://www.st.com/en/microcontrollers-microprocessors/stm32f103rb.html) that is based on the [ARM Cortex-M3 processor](https://developer.arm.com/Processors/Cortex-M3).

Documentation is available on these 3 levels:

| Level                      |                                          datasheet                                          |                                                                                    reference manual                                                                                    |                                                                         user manual                                                                          |
| -------------------------- | :-----------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------: |
| Cortex-M3                  | [CortexM3_DS](https://documentation-service.arm.com/static/62053c120ca305732a3a5c14?token=) |                                              [CortexM3_RM](https://documentation-service.arm.com/static/5e8e107f88295d1e18d34714?token=)                                               |                                 [CortexM3_UM](https://documentation-service.arm.com/static/5ea823e69931941038df1af5?token=)                                  |
| STM32F103RB                |            [STM32_DS](https://www.st.com/resource/en/datasheet/stm32f103rb.pdf)             | [STM32_RM](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) | [STM32_CortexM3_UM](https://www.st.com/resource/en/programming_manual/pm0056-stm32f10xxx20xxx21xxxl1xxxx-cortexm3-programming-manual-stmicroelectronics.pdf) |
| Nucleo64 Development Board |         [Nucleo64_DS](https://www.st.com/resource/en/data_brief/nucleo-f103rb.pdf)          |                                                                                           -                                                                                            |                     [Nucleo64_UM](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)                     |

**Datasheets** usually gives a short overview of the funcionalities and electrical characteristics.  
**Reference manuals** go more in depth and explain all the features in detail.  
**User manuals** are similar to reference manuals but usully more geared towards the applicaiton developer.

There might be some overlap between the different levels of documentation but generally on Cortex-M3 level you find information on how the processor works, the instruction set it uses, it's power management and it's core peripherals like NVIC, SCB, SysTick etc.  
The STM32F103RB level is about MCU specific features like MCU periherals(GPIO, UART, SPI, I2C, DMA, Timers etc.), memory map and all other features that are mentioned as `optional` or `implementation-defined` on the Cortex-M3 level.  
In the Nucleo 64 documentation you find information on the hardware layout like the power supply, LEDs, push buttons and clock sources.

## Acronyms

CMSIS - Cortex Microcontroller Sosftware Interface  
AMBA - Advanced Microcontroller Bus Architecture  
AHB - Advanced High-performance Bus  
APB - Advanced Peripheral Bus  
ATB - Advanced Trace Bus
ISA - Instruction Set Architecture  
MPU - Memory Protection Unit  
PPB - Private Peripheral Bus
MCU - Micro Controller Unit
SWD - Serial Wire Debug

## Definitions

Harward architecture - Seperate buses for instruction and data  
AMBA - open standard on how to connect and manage blocks on an SoC

## Getting to know the hardware

Before writing any code we need to understand how exactly our hardware works. This requires some basic familiarity with embedded systems, processors, digital electronics and going through the user manuals. I will assume that the reader is familiar with concepts like memory-map, memory-mapped registers, fetch-decode-execute cycle and core registers.

Normally after reset the processor will initialize some core and peripheral registers and start the execution from the memory address stored in the PC register. This happens automatically by the digital circuits in the processor before any machine code would take over. In our case the SP will be initialized by the first and the PC by the second entry of the vector table, which at startup should be at memory address 0x0000 0000.

The MCU's memory map(which we find in the datasheet and reference manual) tells us at which addresses we can reach the Flash, system memory, SRAM and other memory regions. Flash starts at address 0x08000 0000 and is aliased to the boot space (which starts at 0x0000 0000). BOOT0 and BOOT1 pins of the MCU decide which memory region gets aliased to boot space but by defualt on our board it's the Flash. So by putting some value in 0x0800 0000 and 0x0800 0004 we can initialize the SP and tell the CPU from where it should execute the first instruction, effectively taking control.

We can write C and assembly code, that we can compile with a toolchain to raw binary data, that we then write into the flash memory of the processor via a programmer device. The programmer can flash this raw binary data via directly accessing the SWD interface or if there is already a bootloader running on the hardware we can communicate with that via UART and other interfaces. The exact process depends on the MCU and should be documented. In our case the Nucleo board alraedy contains the ST-Link V2.1 programmer/debugger that handles this operation, powers the MCU and provides the clock signal as well. Meaning, that we can just connect the board to our development machine via the USB port and use a debugging tool that can communicate with the ST-Link like Ozone. (To use Ozone you need to flash the J-Link firmware on the ST-Link hardware first by following the instructions on their website).

So now we know we can write the flash memory with a .bin file which will contain the machine code instructions and global data equivalent of the C program we wrote. We just need to make sure, that all the compiled binaries are placed correctly and that we initialize the SP and PC registers properly.

## Linker Script

## Startup Code

## References

### Reset behaviour

```c
// TakeReset()
// ============
TakeReset()
 CurrentMode = Mode_Thread;
 PRIMASK<0> = '0'; /* priority mask cleared at reset */
 FAULTMASK<0> = '0'; /* fault mask cleared at reset */
 BASEPRI<7:0> = Zeros(8); /* base priority disabled at reset */
 if HaveFPExt() then /* initialize the Floating Point Extn */
    CONTROL<2:0> = '000'; /* FP inactive, stack is Main, thread is privileged */
    CPACR.cp10 = '00';
    CPACR.cp11 = '00';
    FPDSCR.AHP = '0';
    FPDSCR.DN = '0';
    FPDSCR.FZ = '0';
    FPDSCR.RMode = '00';
    FPCCR.ASPEN = '1';
    FPCCR.LSPEN = '1';
    FPCCR.LSPACT = '0';
    FPCAR = bits(32) UNKNOWN;
    FPFSR = bits(32) UNKNOWN;
    for i = 0 to 31
    S[i] = bits(32) UNKNOWN;
 else
    CONTROL<1:0> = '00'; /* current stack is Main, thread is privileged */
 for i = 0 to 511 /* all exceptions Inactive */
    ExceptionActive[i] = '0';
 ResetSCSRegs(); /* catch-all function for System Control Space reset */
 ClearExclusiveLocal(ProcessorID()); /* Synchronization (LDREX* / STREX*) monitor support */
 ClearEventRegister(); /* see WFE instruction for more details */
 for i = 0 to 12
    R[i] = bits(32) UNKNOWN;
 bits(32) vectortable = VTOR<31:7>:'0000000';
 SP_main = MemA_with_priv[vectortable, 4, AccType_VECTABLE] AND 0xFFFFFFFC<31:0>;
 SP_process = ((bits(30) UNKNOWN):'00');
 LR = 0xFFFFFFFF<31:0>; /* preset to an illegal exception return value */
 tmp = MemA_with_priv[vectortable+4, 4, AccType_VECTABLE];
 tbit = tmp<0>;
 APSR = bits(32) UNKNOWN; /* flags UNPREDICTABLE from reset */
 IPSR<8:0> = Zeros(9); /* Exception Number cleared */
 EPSR.T = tbit; /* T bit set from vector */
 EPSR.IT<7:0> = Zeros(8); /* IT/ICI bits cleared */
 BranchTo(tmp AND 0xFFFFFFFE<31:0>); /* address of reset service routine *

```
