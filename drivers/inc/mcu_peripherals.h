/* 
* file: STM32F103RB device header 
* description: contains memory, bus domain and perihperal base address definitions 
*/

#include "utils.h"

//memory base addresses
#define SRAM_BASE_ADDR    0x20000000U
#define FLASH_BASE_ADDR   0x08000000U


//bus domain base addresses
#define APB1_BASE_ADDR    0x40000000U
#define APB2_BASE_ADDR    0x40010000U
#define AHB_BASE_ADDR     0x40018000U



//peripheral base addresses
//APB2
#define GPIOA_BASE_ADDR   (APB2_BASE_ADDR + 0x0800U)
#define GPIOB_BASE_ADDR   (APB2_BASE_ADDR + 0x0C00U)
#define GPIOC_BASE_ADDR   (APB2_BASE_ADDR + 0x1000U)
#define GPIOD_BASE_ADDR   (APB2_BASE_ADDR + 0x1400U)

//AHB
#define RCC_BASE_ADDR      (AHB_BASE_ADDR + 0x9000U)



//peripheral register definitions
typedef struct{
    __vo uint32_t CR[2];
    __vo uint32_t IDR;
    __vo uint32_t ODR;
    __vo uint32_t BSRR;
    __vo uint32_t BRR;
    __vo uint32_t LCKR;

} GPIO_t;

typedef struct{
    __vo uint32_t CR;
    __vo uint32_t CFGR;
    __vo uint32_t CIR;
    __vo uint32_t APB2RSTR;
    __vo uint32_t APB1RSTR;
    __vo uint32_t AHBENR;
    __vo uint32_t APB2ENR;
    __vo uint32_t APB1ENR;
    __vo uint32_t BDCR;
    __vo uint32_t CSR;

} RCC_t;



//peripherals
#define GPIOA   ((GPIO_t*)GPIOA_BASE_ADDR) 
#define GPIOB   ((GPIO_t*)GPIOB_BASE_ADDR) 
#define GPIOC   ((GPIO_t*)GPIOC_BASE_ADDR) 
#define GPIOD   ((GPIO_t*)GPIOD_BASE_ADDR)

#define RCC     ((RCC_t*)RCC_BASE_ADDR)
