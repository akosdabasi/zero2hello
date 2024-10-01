/* 
* file: utility functions 
* description: contains often used utility functions for embedded systems 
*/

//bit manipulations

#define SETBIT(word, bit)     (word |= (1 << bit))
#define GETBIT(word, bit)     ((word & (1 << bit)) >> bit)
#define CLEARBIT(word, bit)   (word &= ~(1 << bit))
#define TOGGLEBIT(word, bit)  (word ^= (1 << bit))

