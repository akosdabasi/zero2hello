#pragma once

#include "gpio_driver.h"
#include "exti_driver.h"
#include "rcc_driver.h"


//global instance
extern AFIO_t *const pAFIO;

typedef enum {
    CAN_REMAP_NO_REMAP = 0,         // No remapping (CAN_RX mapped to PA11, CAN_TX mapped to PA12)
    CAN_REMAP_PB8_PB9 = 2,          // Remap CAN_RX mapped to PB8, CAN_TX mapped to PB9
    CAN_REMAP_PD0_PD1 = 3           // Remap  CAN_RX mapped to PD0, CAN_TX mapped to PD1
} can_remap_t;

typedef enum {
    SWJ_FULL_SWJ = 0,               // Full SWJ (JTAG-DP + SW-DP)
    SWJ_FULL_SWJ_NO_NJTRST = 1,     // Full SWJ but without NJTRST
    SWJ_SW_ONLY = 2,                // JTAG-DP disabled, SW-DP enabled
    SWJ_DISABLED = 4                // JTAG-DP and SW-DP disabled (RESET only)
} swj_cfg_t;

typedef enum {
    USART3_NO_REMAP = 0,           // No remap  (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14)
    USART3_PARTIAL_REMAP = 1,      // Partial remap  (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14)
    USART3_FULL_REMAP = 3          // Full remap  (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12)
} usart3_remap_t;

typedef enum {
    TIM1_NO_REMAP = 0,             // No remap  (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12,CH1N/PB13, CH2N/PB14, CH3N/PB15)
    TIM1_PARTIAL_REMAP = 1,        // Partial remap  (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6,CH1N/PA7, CH2N/PB0, CH3N/PB1)
    TIM1_FULL_REMAP = 3            // Full remap  (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15,CH1N/PE8, CH2N/PE10, CH3N/PE12)
} tim1_remap_t;

typedef enum {
    TIM2_NO_REMAP = 0,             // No remap  (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
    TIM2_PARTIAL_REMAP1 = 1,       // Partial remap 1  (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
    TIM2_PARTIAL_REMAP2 = 2,       // Partial remap 2  (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
    TIM2_FULL_REMAP = 3            // Full remap  (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)
} tim2_remap_t;

typedef enum {
    TIM3_NO_REMAP = 0,             // No remap  (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
    TIM3_PARTIAL_REMAP = 2,        // Partial remap  (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
    TIM3_FULL_REMAP = 3            // Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)
} tim3_remap_t;

//basic control functions
static inline void afio_clk_enable(){RCC_APB2ENR_AFIO_CLK_ENABLE();}
static inline void afio_clk_disable(){RCC_APB2ENR_AFIO_CLK_DISABLE();}
static inline void afio_clk_reset(){RCC_APB2RSTR_AFIO_RESET();}

//EVENTOUT signal configuration
static inline void afio_en_EVENTOUT(){SET_BIT(pAFIO->EVCR, AFIO_EVCR_EVOE_Pos);}
static inline void afio_dis_EVENTOUT(){CLEAR_BIT(pAFIO->EVCR, AFIO_EVCR_EVOE_Pos);}
void afio_sel_EVENTOUT_pin(gpio_port_t port ,gpio_pin_t pin);

//remapping
/**
 * @brief  Remap SPI1 pins to an alternate location.
 * @param  enable: Set to 1 to remap SPI1 pins; 0 to disable remapping.
 *         - 0: No remap (NSS/PA4, SCK/PA5, MISO/PA6, MOSI/PA7)
 *         - 1: Remap (NSS/PA15, SCK/PB3, MISO/PB4, MOSI/PB5)
 */
static inline void afio_spi1_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR,AFIO_MAPR_SPI1_REMAP_Pos, enable);
}

/**
 * @brief  Remap I2C1 pins.
 * @param  enable: Set to 1 to remap I2C1 pins; 0 to disable remapping.
 *         - 0: No remap (SCL/PB6, SDA/PB7)
 *         - 1: Remap (SCL/PB8, SDA/PB9)
 */
static inline void afio_i2c1_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR,AFIO_MAPR_I2C1_REMAP_Pos, enable);
}

/**
 * @brief  Remap USART1 pins.
 * @param  enable: Set to 1 to remap USART1 pins; 0 to disable remapping.
 *         - 0: No remap (TX/PA9, RX/PA10)
 *         - 1: Remap (TX/PB6, RX/PB7)
 */
static inline void afio_usart1_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR,AFIO_MAPR_USART1_REMAP_Pos, enable);
}

/**
 * @brief  Remap USART2 pins.
 * @param  enable: Set to 1 to remap USART2 pins; 0 to disable remapping.
 *         - 0: No remap (CTS/PA0, RTS/PA1, TX/PA2, RX/PA3, CK/PA4)
 *         - 1:  Remap (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)
 */
static inline void afio_usart2_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR,AFIO_MAPR_USART2_REMAP_Pos, enable);
}

/**
 * @brief  Remap USART3 pins.
 * @param  remap: Remap option to select USART3 pin configuration.
 *         - USART3_NO_REMAP: No remap (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14)
 *         - USART3_PARTIAL_REMAP: Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14)
 *         - USART3_FULL_REMAP: Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12)
 */
static inline void afio_usart3_remap(usart3_remap_t remap) {
    // Clear USART3_REMAP field
    CLEAR_BITFIELD(pAFIO->MAPR, AFIO_MAPR_USART3_REMAP_Msk);
    // Set the remap value if within range
    pAFIO->MAPR |= ((uint32_t)remap << AFIO_MAPR_USART3_REMAP_Pos);
}

/**
 * @brief  Remap TIM1 pins.
 * @param  remap: Remap option to select TIM1 pin configuration.
 *         - TIM1_NO_REMAP: No remap (default TIM1 pins)
 *         - TIM1_PARTIAL_REMAP: Partial remap for TIM1
 *         - TIM1_FULL_REMAP: Full remap for TIM1
 */
static inline void afio_tim1_remap(tim1_remap_t remap) {
    // Clear TIM1_REMAP field
    CLEAR_BITFIELD(pAFIO->MAPR, AFIO_MAPR_TIM1_REMAP_Msk);
    // Set the remap value if within range
    pAFIO->MAPR |= ((uint32_t)remap << AFIO_MAPR_TIM1_REMAP_Pos);
}

/**
 * @brief  Remap TIM2 pins.
 * @param  remap: Remap option to select TIM2 pin configuration.
 *         - TIM2_NO_REMAP: No remap (default TIM2 pins)
 *         - TIM2_PARTIAL_REMAP1: Partial remap 1
 *         - TIM2_PARTIAL_REMAP2: Partial remap 2
 *         - TIM2_FULL_REMAP: Full remap for TIM2
 */
static inline void afio_tim2_remap(tim2_remap_t remap) {
    // Clear TIM2_REMAP field
    CLEAR_BITFIELD(pAFIO->MAPR, AFIO_MAPR_TIM2_REMAP_Msk);
    // Set the remap value if within range
    pAFIO->MAPR |= ((uint32_t)remap << AFIO_MAPR_TIM2_REMAP_Pos);
}

/**
 * @brief  Remap TIM3 pins.
 * @param  remap: Remap option to select TIM3 pin configuration.
 *         - TIM3_NO_REMAP: No remap (default TIM3 pins)
 *         - TIM3_PARTIAL_REMAP: Partial remap for TIM3
 *         - TIM3_FULL_REMAP: Full remap for TIM3
 */
static inline void afio_tim3_remap(tim3_remap_t remap) {
    // Clear TIM3_REMAP field
    CLEAR_BITFIELD(pAFIO->MAPR, AFIO_MAPR_TIM3_REMAP_Msk);
    // Set the remap value if within range
    pAFIO->MAPR |= ((uint32_t)remap << AFIO_MAPR_TIM3_REMAP_Pos);
}

/**
 * @brief  Remap TIM4 pins.
 * @param  enable: Set to 1 to remap TIM4 pins; 0 to disable remapping.
 *         - 0: No remap (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
 *         - 1:  Remap (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)
 */
static inline void afio_tim4_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR,AFIO_MAPR_TIM4_REMAP_Pos, enable);
}

/**
 * @brief  Remap CAN pins.
 * @param  remap: Remap option to select CAN RX/TX pin configuration.
 *         - CAN_REMAP_NO_REMAP: No remap (CAN RX on PA11, CAN TX on PA12)
 *         - CAN_REMAP_PB8_PB9: Remap CAN RX to PB8, CAN TX to PB9
 *         - CAN_REMAP_PD0_PD1: Remap CAN RX to PD0, CAN TX to PD1
 */
static inline void afio_can_remap(can_remap_t remap) {
    // Clear CAN_REMAP field
    CLEAR_BITFIELD(pAFIO->MAPR, AFIO_MAPR_CAN_REMAP_Msk);
    // Set the remap value
    pAFIO->MAPR |= ((uint32_t)remap << AFIO_MAPR_CAN_REMAP_Pos);
}

/**
 * @brief  Remap Port D0/Port D1 to OSC_IN/OSC_OUT.
 * @param  enable: Set to 1 to remap PD0/PD1; 0 to disable remapping.
 *         - 0: No remapping 
 *         - 1: PD0 remapped to OSC_IN, PD1 remapped to OSC_OUT
 */
static inline void afio_pd01_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR,AFIO_MAPR_PD01_REMAP_Pos, enable);
}

/**
 * @brief  Remap ADC1 and ADC2 External Trigger Injected/Regular Conversion.
 * @param  enable: Set to 1 to remap ADC1 or ADC2; 0 to disable remapping.
 *         - 0: No remapping (ADCxreg/EXTI11, ADCxinj/EXTI15)
 *         - 1: Remap (ADCxreg/TIM8TRGO, ADCxinj/TIM8CH4)
 */
static inline void afio_adc2_etrgreg_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR, AFIO_MAPR_ADC2_ETRGREG_REMAP_Pos, enable);
}

static inline void afio_adc2_etrginj_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR, AFIO_MAPR_ADC2_ETRGINJ_REMAP_Pos, enable);
}

static inline void afio_adc1_etrgreg_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR, AFIO_MAPR_ADC1_ETRGREG_REMAP_Pos, enable);
}

static inline void afio_adc1_etrginj_remap(uint8_t enable) {
    EN_DIS_BIT(pAFIO->MAPR, AFIO_MAPR_ADC1_ETRGINJ_REMAP_Pos, enable);
}

/**
 * @brief  Configure SWJ (Serial Wire JTAG) mode.
 * @param  swj_cfg: Configuration option to set the SWJ debug port.
 *         - SWJ_FULL_SWJ: Full SWJ (JTAG-DP + SW-DP)
 *         - SWJ_FULL_SWJ_NO_NJTRST: Full SWJ (JTAG-DP + SW-DP), without NJTRST
 *         - SWJ_SW_ONLY: JTAG-DP disabled, SW-DP enabled
 *         - SWJ_DISABLED: JTAG-DP and SW-DP disabled (RESET only)
 */
static inline void afio_swj_cfg(swj_cfg_t swj_cfg) {
    // Clear CAN_REMAP field
    CLEAR_BITFIELD(pAFIO->MAPR, AFIO_MAPR_SWJ_CFG_Msk);
    // Set the remap value
    pAFIO->MAPR |= ((uint32_t)swj_cfg << AFIO_MAPR_SWJ_CFG_Pos);
}

//EXTI configuration
//There are 16 lines corresponding to 16pins. On each line the gpio port can be selected
void afio_attach_port_to_exti_line(gpio_port_t port, exti_line_t line); 
