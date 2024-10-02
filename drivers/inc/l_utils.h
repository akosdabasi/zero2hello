/* 
* file: utility functions 
* description: contains often used utility functions for embedded systems 
*/

//bit manipulations
#define BIT(x)                  (1u << x)

#define SETBIT(word, bit)       (word |= (1u << bit))
#define GETBIT(word, bit)       (((word) >> (bit)) & 1u)
#define CLEARBIT(word, bit)     (word &= ~(1u << bit))
#define TOGGLEBIT(word, bit)    (word ^= (1u << bit))

