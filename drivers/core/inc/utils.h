#pragma once

/* 
* file: utils.h
* description: commonly used type definitions and helper functions 
* contains:
*     - stdint like type definitions
*     - type modifier defines for memory mapped peripheral registers
*     - other common defines
*     - utility functions for bit manipulation
*/

//stdint like type definitions
typedef signed char int8_t;             // Signed 8-bit integer
typedef unsigned char uint8_t;          // Unsigned 8-bit integer

typedef short int int16_t;              // Signed 16-bit integer
typedef unsigned short int uint16_t;    // Unsigned 16-bit integer

typedef int int32_t;                    // Signed 32-bit integer
typedef unsigned int uint32_t;          // Unsigned 32-bit integer

typedef long long int int64_t;          // Signed 64-bit integer
typedef unsigned long long int uint64_t;// Unsigned 64-bit integer

//other type definitions
//function pointers
typedef void (*isr_callback_t)(void);

//null pointer
#define NULL (void*)0;

//type modifier defines for memmory mapped peripheral registers
#define __vo volatile
#define __IO volatile
#define __I const volatile
#define __O volatile


//other common defines
#define TRUE    1
#define FALSE   0
#define SET     TRUE
#define UNSET   FALSE
#define ENABLE  TRUE
#define DISABLE FALSE
#define HIGH    TRUE
#define LOW     FALSE

typedef enum {
  disabled = 0,
  enabled  = 1
} state_t;

//utility macros for bit manipulation
#define BIT(x)                            (1u << x)

#define SET_BIT(word, pos)                (word |= (1u << pos))
#define GET_BIT(word, pos)                ((word >> pos) & 1u)
#define CLEAR_BIT(word, pos)              (word &= ~(1u << pos))
#define TOGGLE_BIT(word, pos)             (word ^= (1u << pos))
#define EN_DIS_BIT(word, pos, enable)     ({if (enable) {SET_BIT(word, pos);} else {CLEAR_BIT(word, pos);}})

#define GET_BITFIELD(word, mask, pos)     (((uint32_t)word & mask) >> pos)
#define CLEAR_BITFIELD(word, mask)        (word &= (~(uint32_t)mask))