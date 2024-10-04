#pragma once

/* 
* file: utility macros and definitions
* description: contains often used utility functions and definitions for embedded systems 
*/

//stdint typedefs
typedef signed char int8_t;             // Signed 8-bit integer
typedef unsigned char uint8_t;          // Unsigned 8-bit integer

typedef short int int16_t;              // Signed 16-bit integer
typedef unsigned short int uint16_t;    // Unsigned 16-bit integer

typedef int int32_t;                    // Signed 32-bit integer
typedef unsigned int uint32_t;          // Unsigned 32-bit integer

typedef long long int int64_t;          // Signed 64-bit integer
typedef unsigned long long int uint64_t;// Unsigned 64-bit integer

//defines
#define __vo volatile
#define __IO volatile
#define __I const volatile
#define __O volatile

#define TRUE    1
#define FALSE   0
#define SET     TRUE
#define UNSET   FALSE
#define ENABLE  TRUE
#define DISABLE FALSE

//bit manipulations
#define BIT(x)                  (1u << x)

#define SETBIT(word, bit)       (word |= (1u << bit))
#define GETBIT(word, bit)       (((word) >> (bit)) & 1u)
#define CLEARBIT(word, bit)     (word &= ~(1u << bit))
#define TOGGLEBIT(word, bit)    (word ^= (1u << bit))

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,     /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,     /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,     /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,     /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  Interrupt0_IRQn               =   0,
  Interrupt1_IRQn               =   1,
  Interrupt2_IRQn               =   2,
  Interrupt3_IRQn               =   3,
  Interrupt4_IRQn               =   4,
  Interrupt5_IRQn               =   5,
  Interrupt6_IRQn               =   6,
  Interrupt7_IRQn               =   7,
  Interrupt8_IRQn               =   8,
  Interrupt9_IRQn               =   9,
  /* Interrupts 10 .. 223 are left out */
  Interrupt224_IRQn             =   224
} IRQn_t;
