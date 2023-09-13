# zero2hello

This project is created to understand all the steps involved in printing "hello" from an MCU via UART. 
The code will be developed outside of any IDE, only using VS Code as a text editor and some command line tools.

hardware used:
- STM32F103RB Nucleo board

  
The steps will include:
1. setting up the MCU by writing the linker script and the startup code
2. setting up a build environment by creating a Makefile
3. writing a GPIO driver
4. writing a UART driver
5. implementing syscalls (_write, _sbrk)
6. implementing printf using UART
7. importing the C standard library


This documentation will be updated as the project progresses and it's main purpose is to document everything I learn and hopefully it will serve as a complete, in-depth guide for others who want to understand how code gets executed on an MCU without hiding any details.


