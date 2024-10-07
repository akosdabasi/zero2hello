#pragma once

#include "gpio_driver.h"

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

inline void afio_clk_enable();
inline void afio_en_EVENTOUT();
inline void afio_dis_EVENTOUT();

void afio_sel_EVENTOUT_pin(gpio_port_t port ,gpio_pin_t pin);

inline void afio_spi1_remap(uint8_t enable);
inline void afio_i2c1_remap(uint8_t enable);
inline void afio_usart1_remap(uint8_t enable);
inline void afio_usart2_remap(uint8_t enable);
inline void afio_usart3_remap(usart3_remap_t remap);
inline void afio_tim1_remap(tim1_remap_t remap);
inline void afio_tim2_remap(tim2_remap_t remap);
inline void afio_tim3_remap(tim3_remap_t remap);
inline void afio_tim4_remap(uint8_t enable);
inline void afio_can_remap(can_remap_t remap);
inline void afio_pd01_remap(uint8_t enable);
inline void afio_adc2_etrgreg_remap(uint8_t enable);
inline void afio_adc2_etrginj_remap(uint8_t enable);
inline void afio_adc1_etrgreg_remap(uint8_t enable);
inline void afio_adc1_etrginj_remap(uint8_t enable);
inline void afio_swj_cfg(swj_cfg_t swj_cfg);

