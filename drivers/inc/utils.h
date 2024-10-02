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

