#pragma once
/* 
* file: STM32F103RB device header 
* description: contains memory, bus domain and perihperal base address definitions 
*/

#include "utils.h"

//memory base addresses
#define SRAM_BASE_ADDR    0x20000000u
#define FLASH_BASE_ADDR   0x08000000u


//bus domain base addresses
#define APB1_BASE_ADDR    0x40000000u
#define APB2_BASE_ADDR    0x40010000u
#define AHB_BASE_ADDR     0x40018000u



//peripheral base addresses
//APB1
#define SPI2_BASE_ADDR    0x40003800u
#define SPI3_BASE_ADDR    0x40003C00u
#define USART2_BASE_ADDR  0x40004400u
#define USART3_BASE_ADDR  0x40004800u


//APB2
#define GPIOA_BASE_ADDR   0x40010800u
#define GPIOB_BASE_ADDR   0x40010C00u
#define GPIOC_BASE_ADDR   0x40011000u
#define GPIOD_BASE_ADDR   0x40011400u
#define EXTI_BASE_ADDR    0x40010400u
#define AFIO_BASE_ADDR    0x40010000u
#define SPI1_BASE_ADDR    0x40013000u
#define USART1_BASE_ADDR  0x40013800u

//AHB
#define RCC_BASE_ADDR      0x40021000u



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

typedef struct {
    __vo uint32_t IMR;     // Interrupt Mask Register
    __vo uint32_t EMR;     // Event Mask Register
    __vo uint32_t RTSR;    // Rising Trigger Selection Register
    __vo uint32_t FTSR;    // Falling Trigger Selection Register
    __vo uint32_t SWIER;   // Software Interrupt Event Register
    __vo uint32_t PR;      // Pending Register
} EXTI_t;

typedef struct {
    __vo uint32_t EVCR;        // Event Control Register
    __vo uint32_t MAPR;        // Remap and Debug I/O Configuration Register
    __vo uint32_t EXTICR[4];   // External Interrupt Configuration Registers (EXTICR1 to EXTICR4)
    __vo uint32_t MAPR2;       // Remap and Debug I/O Configuration Register 2 (only available on some devices)
} AFIO_t;

typedef struct {
    __vo uint32_t CR1;        // SPI Control Register 1
    __vo uint32_t CR2;        // SPI Control Register 2
    __vo uint32_t SR;         // SPI Status Register
    __vo uint32_t DR;         // SPI Data Register
    __vo uint32_t CRCPR;      // SPI CRC Polynomial Register
    __vo uint32_t RXCRCR;     // SPI RX CRC Register
    __vo uint32_t TXCRCR;     // SPI TX CRC Register
    __vo uint32_t I2SCFGR;    // SPI_I2S Configuration Register
    __vo uint32_t I2SPR;      // SPI_I2S Prescaler Register
} SPI_t;

typedef struct {
    __vo uint32_t SR;         // Status register
    __vo uint32_t DR;         // Data register
    __vo uint32_t BRR;        // Baud rate register
    __vo uint32_t CR1;        // Control register 1
    __vo uint32_t CR2;        // Control register 2
    __vo uint32_t CR3;        // Control register 3
    __vo uint32_t GTPR;       // Guard time and prescaler register
} USART_t;

//peripherals
#define GPIOA   ((GPIO_t *const)GPIOA_BASE_ADDR) 
#define GPIOB   ((GPIO_t *const)GPIOB_BASE_ADDR) 
#define GPIOC   ((GPIO_t *const)GPIOC_BASE_ADDR) 
#define GPIOD   ((GPIO_t *const)GPIOD_BASE_ADDR)

#define SPI1    ((SPI_t *const)SPI1_BASE_ADDR)
#define SPI2    ((SPI_t *const)SPI2_BASE_ADDR)
#define SPI3    ((SPI_t *const)SPI3_BASE_ADDR)

#define USART1   ((USART_t *const)USART1_BASE_ADDR)
#define USART2   ((USART_t *const)USART2_BASE_ADDR)
#define USART3   ((USART_t *const)USART3_BASE_ADDR)

#define EXTI    ((EXTI_t *const)EXTI_BASE_ADDR)
#define AFIO    ((AFIO_t *const)AFIO_BASE_ADDR)

#define RCC     ((RCC_t *const)RCC_BASE_ADDR)

/*--------------------------USART SR BIT FIELD POSITION AND MASK DEFINITIONS-------------------------------*/
// USART_SR Register Fields
#define USART_SR_PE_Pos            (0U)                           // Parity Error bit position
#define USART_SR_PE_Msk            (1U << USART_SR_PE_Pos)        // Parity Error mask

#define USART_SR_FE_Pos            (1U)                           // Framing Error bit position
#define USART_SR_FE_Msk            (1U << USART_SR_FE_Pos)        // Framing Error mask

#define USART_SR_NE_Pos            (2U)                           // Noise Error Flag bit position
#define USART_SR_NE_Msk            (1U << USART_SR_NE_Pos)        // Noise Error mask

#define USART_SR_ORE_Pos           (3U)                           // Overrun Error bit position
#define USART_SR_ORE_Msk           (1U << USART_SR_ORE_Pos)       // Overrun Error mask

#define USART_SR_IDLE_Pos          (4U)                           // IDLE Line Detected bit position
#define USART_SR_IDLE_Msk          (1U << USART_SR_IDLE_Pos)      // IDLE Line Detected mask

#define USART_SR_RXNE_Pos          (5U)                           // Read Data Register Not Empty bit position
#define USART_SR_RXNE_Msk          (1U << USART_SR_RXNE_Pos)      // Read Data Register Not Empty mask

#define USART_SR_TC_Pos            (6U)                           // Transmission Complete bit position
#define USART_SR_TC_Msk            (1U << USART_SR_TC_Pos)        // Transmission Complete mask

#define USART_SR_TXE_Pos           (7U)                           // Transmit Data Register Empty bit position
#define USART_SR_TXE_Msk           (1U << USART_SR_TXE_Pos)       // Transmit Data Register Empty mask

#define USART_SR_LBD_Pos           (8U)                           // LIN Break Detection Flag bit position
#define USART_SR_LBD_Msk           (1U << USART_SR_LBD_Pos)       // LIN Break Detection Flag mask

#define USART_SR_CTS_Pos           (9U)                           // CTS Flag bit position
#define USART_SR_CTS_Msk           (1U << USART_SR_CTS_Pos)       // CTS Flag mask

// USART_DR Register Fields
#define USART_DR_DR_Pos            (0U)                           // Data value bit position
#define USART_DR_DR_Msk            (0x1FFU << USART_DR_DR_Pos)    // Data value mask (9 bits)

// USART_BRR Register Fields
#define USART_BRR_DIV_Fraction_Pos (0U)                                     // Fraction of USARTDIV bit position
#define USART_BRR_DIV_Fraction_Msk (0xFU << USART_BRR_DIV_Fraction_Pos)     // Fraction of USARTDIV mask (4 bits)

#define USART_BRR_DIV_Mantissa_Pos (4U)                                     // Mantissa of USARTDIV bit position
#define USART_BRR_DIV_Mantissa_Msk (0xFFFU << USART_BRR_DIV_Mantissa_Pos)   // Mantissa of USARTDIV mask (12 bits)

// USART_CR1 Register Fields
#define USART_CR1_SBK_Pos          (0U)                           // Send Break bit position
#define USART_CR1_SBK_Msk          (1U << USART_CR1_SBK_Pos)      // Send Break mask

#define USART_CR1_RWU_Pos          (1U)                           // Receiver Wakeup bit position
#define USART_CR1_RWU_Msk          (1U << USART_CR1_RWU_Pos)      // Receiver Wakeup mask

#define USART_CR1_RE_Pos           (2U)                           // Receiver Enable bit position
#define USART_CR1_RE_Msk           (1U << USART_CR1_RE_Pos)       // Receiver Enable mask

#define USART_CR1_TE_Pos           (3U)                           // Transmitter Enable bit position
#define USART_CR1_TE_Msk           (1U << USART_CR1_TE_Pos)       // Transmitter Enable mask

#define USART_CR1_IDLEIE_Pos       (4U)                           // IDLE Interrupt Enable bit position
#define USART_CR1_IDLEIE_Msk       (1U << USART_CR1_IDLEIE_Pos)   // IDLE Interrupt Enable mask

#define USART_CR1_RXNEIE_Pos       (5U)                           // RXNE Interrupt Enable bit position
#define USART_CR1_RXNEIE_Msk       (1U << USART_CR1_RXNEIE_Pos)   // RXNE Interrupt Enable mask

#define USART_CR1_TCIE_Pos         (6U)                           // Transmission Complete Interrupt Enable bit position
#define USART_CR1_TCIE_Msk         (1U << USART_CR1_TCIE_Pos)     // Transmission Complete Interrupt Enable mask

#define USART_CR1_TXEIE_Pos        (7U)                           // TXE Interrupt Enable bit position
#define USART_CR1_TXEIE_Msk        (1U << USART_CR1_TXEIE_Pos)    // TXE Interrupt Enable mask

#define USART_CR1_PEIE_Pos         (8U)                           // PE Interrupt Enable bit position
#define USART_CR1_PEIE_Msk         (1U << USART_CR1_PEIE_Pos)     // PE Interrupt Enable mask

#define USART_CR1_PS_Pos           (9U)                           // Parity Selection bit position
#define USART_CR1_PS_Msk           (1U << USART_CR1_PS_Pos)       // Parity Selection mask

#define USART_CR1_PCE_Pos          (10U)                          // Parity Control Enable bit position
#define USART_CR1_PCE_Msk          (1U << USART_CR1_PCE_Pos)      // Parity Control Enable mask

#define USART_CR1_WAKE_Pos         (11U)                          // Wakeup method bit position
#define USART_CR1_WAKE_Msk         (1U << USART_CR1_WAKE_Pos)     // Wakeup method mask

#define USART_CR1_M_Pos            (12U)                          // Word length bit position
#define USART_CR1_M_Msk            (1U << USART_CR1_M_Pos)        // Word length mask

#define USART_CR1_UE_Pos           (13U)                          // USART Enable bit position
#define USART_CR1_UE_Msk           (1U << USART_CR1_UE_Pos)       // USART Enable mask

// USART_CR2 Register Fields
#define USART_CR2_ADD_Pos          (0U)                           // Address of the USART node bit position
#define USART_CR2_ADD_Msk          (0xFU << USART_CR2_ADD_Pos)    // Address of the USART node mask (4 bits)

#define USART_CR2_LBDL_Pos         (5U)                           // LIN Break Detection Length bit position
#define USART_CR2_LBDL_Msk         (1U << USART_CR2_LBDL_Pos)     // LIN Break Detection Length mask

#define USART_CR2_LBDIE_Pos        (6U)                           // LIN Break Detection Interrupt Enable bit position
#define USART_CR2_LBDIE_Msk        (1U << USART_CR2_LBDIE_Pos)    // LIN Break Detection Interrupt Enable mask

#define USART_CR2_LBCL_Pos         (8U)                           // Last Bit Clock pulse bit position
#define USART_CR2_LBCL_Msk         (1U << USART_CR2_LBCL_Pos)     // Last Bit Clock pulse mask

#define USART_CR2_CPHA_Pos         (9U)                           // Clock Phase bit position
#define USART_CR2_CPHA_Msk         (1U << USART_CR2_CPHA_Pos)     // Clock Phase mask

#define USART_CR2_CPOL_Pos         (10U)                          // Clock Polarity bit position
#define USART_CR2_CPOL_Msk         (1U << USART_CR2_CPOL_Pos)     // Clock Polarity mask

#define USART_CR2_CLKEN_Pos        (11U)                          // Clock Enable bit position
#define USART_CR2_CLKEN_Msk        (1U << USART_CR2_CLKEN_Pos)    // Clock Enable mask

#define USART_CR2_STOP_Pos         (12U)                          // STOP bits bit position
#define USART_CR2_STOP_Msk         (0x3U << USART_CR2_STOP_Pos)   // STOP bits mask (2 bits)

#define USART_CR2_LINEN_Pos        (14U)                          // LIN mode Enable bit position
#define USART_CR2_LINEN_Msk        (1U << USART_CR2_LINEN_Pos)    // LIN mode Enable mask

// USART_CR3 Register Fields
#define USART_CR3_EIE_Pos          (0U)                           // Error Interrupt Enable bit position
#define USART_CR3_EIE_Msk          (1U << USART_CR3_EIE_Pos)      // Error Interrupt Enable mask

#define USART_CR3_IREN_Pos         (1U)                           // IrDA mode Enable bit position
#define USART_CR3_IREN_Msk         (1U << USART_CR3_IREN_Pos)     // IrDA mode Enable mask

#define USART_CR3_IRLP_Pos         (2U)                           // IrDA Low-Power bit position
#define USART_CR3_IRLP_Msk         (1U << USART_CR3_IRLP_Pos)     // IrDA Low-Power mask

#define USART_CR3_HDSEL_Pos        (3U)                           // Half-Duplex Selection bit position
#define USART_CR3_HDSEL_Msk        (1U << USART_CR3_HDSEL_Pos)    // Half-Duplex Selection mask

#define USART_CR3_NACK_Pos         (4U)                           // Smartcard NACK Enable bit position
#define USART_CR3_NACK_Msk         (1U << USART_CR3_NACK_Pos)     // Smartcard NACK Enable mask

#define USART_CR3_SCEN_Pos         (5U)                           // Smartcard mode Enable bit position
#define USART_CR3_SCEN_Msk         (1U << USART_CR3_SCEN_Pos)     // Smartcard mode Enable mask

#define USART_CR3_DMAR_Pos         (6U)                           // DMA Enable Receiver bit position
#define USART_CR3_DMAR_Msk         (1U << USART_CR3_DMAR_Pos)     // DMA Enable Receiver mask

#define USART_CR3_DMAT_Pos         (7U)                           // DMA Enable Transmitter bit position
#define USART_CR3_DMAT_Msk         (1U << USART_CR3_DMAT_Pos)     // DMA Enable Transmitter mask

#define USART_CR3_RTSE_Pos         (8U)                           // RTS Enable bit position
#define USART_CR3_RTSE_Msk         (1U << USART_CR3_RTSE_Pos)     // RTS Enable mask

#define USART_CR3_CTSE_Pos         (9U)                           // CTS Enable bit position
#define USART_CR3_CTSE_Msk         (1U << USART_CR3_CTSE_Pos)     // CTS Enable mask

#define USART_CR3_CTSIE_Pos        (10U)                          // CTS Interrupt Enable bit position
#define USART_CR3_CTSIE_Msk        (1U << USART_CR3_CTSIE_Pos)    // CTS Interrupt Enable mask

#define USART_CR3_ONEBIT_Pos       (11U)                          // One sample bit method Enable bit position
#define USART_CR3_ONEBIT_Msk       (1U << USART_CR3_ONEBIT_Pos)   // One sample bit method Enable mask

// USART_GTPR Register Fields
#define USART_GTPR_PSC_Pos         (0U)                           // Prescaler value bit position
#define USART_GTPR_PSC_Msk         (0xFFU << USART_GTPR_PSC_Pos)  // Prescaler value mask (8 bits)

#define USART_GTPR_GT_Pos          (8U)                           // Guard time value bit position
#define USART_GTPR_GT_Msk          (0xFFU << USART_GTPR_GT_Pos)   // Guard time value mask (8 bits)

/*--------------------------SPI BIT FIELD POSITION AND MASK DEFINITIONS-------------------------------*/
// SPI_CR1 Register Fields
#define SPI_CR1_CPHA_Pos           (0U)                           // Clock Phase bit position
#define SPI_CR1_CPHA_Msk           (1U << SPI_CR1_CPHA_Pos)       // Clock Phase mask

#define SPI_CR1_CPOL_Pos           (1U)                           // Clock Polarity bit position
#define SPI_CR1_CPOL_Msk           (1U << SPI_CR1_CPOL_Pos)       // Clock Polarity mask

#define SPI_CR1_MSTR_Pos           (2U)                           // Master Selection bit position
#define SPI_CR1_MSTR_Msk           (1U << SPI_CR1_MSTR_Pos)       // Master Selection mask

#define SPI_CR1_BR_Pos             (3U)                           // Baud Rate Control bit position (BR[2:0])
#define SPI_CR1_BR_Msk             (7U << SPI_CR1_BR_Pos)         // Baud Rate Control mask (3 bits)

#define SPI_CR1_SPE_Pos            (6U)                           // SPI Enable bit position
#define SPI_CR1_SPE_Msk            (1U << SPI_CR1_SPE_Pos)        // SPI Enable mask

#define SPI_CR1_LSBFIRST_Pos       (7U)                           // Frame Format (LSB First) bit position
#define SPI_CR1_LSBFIRST_Msk       (1U << SPI_CR1_LSBFIRST_Pos)   // Frame Format mask

#define SPI_CR1_SSI_Pos            (8U)                           // Internal Slave Select bit position
#define SPI_CR1_SSI_Msk            (1U << SPI_CR1_SSI_Pos)        // Internal Slave Select mask

#define SPI_CR1_SSM_Pos            (9U)                           // Software Slave Management bit position
#define SPI_CR1_SSM_Msk            (1U << SPI_CR1_SSM_Pos)        // Software Slave Management mask

#define SPI_CR1_RXONLY_Pos         (10U)                          // Receive Only mode bit position
#define SPI_CR1_RXONLY_Msk         (1U << SPI_CR1_RXONLY_Pos)     // Receive Only mode mask

#define SPI_CR1_DFF_Pos            (11U)                          // Data Frame Format bit position
#define SPI_CR1_DFF_Msk            (1U << SPI_CR1_DFF_Pos)        // Data Frame Format mask

#define SPI_CR1_CRCNEXT_Pos        (12U)                          // CRC Transfer Next bit position
#define SPI_CR1_CRCNEXT_Msk        (1U << SPI_CR1_CRCNEXT_Pos)    // CRC Transfer Next mask

#define SPI_CR1_CRCEN_Pos          (13U)                          // CRC Enable bit position
#define SPI_CR1_CRCEN_Msk          (1U << SPI_CR1_CRCEN_Pos)      // CRC Enable mask

#define SPI_CR1_BIDIOE_Pos         (14U)                          // Output Enable in Bidirectional Mode bit position
#define SPI_CR1_BIDIOE_Msk         (1U << SPI_CR1_BIDIOE_Pos)     // Output Enable in Bidirectional Mode mask

#define SPI_CR1_BIDIMODE_Pos       (15U)                          // Bidirectional Data Mode Enable bit position
#define SPI_CR1_BIDIMODE_Msk       (1U << SPI_CR1_BIDIMODE_Pos)   // Bidirectional Data Mode Enable mask

// SPI_CR2 Register Fields
#define SPI_CR2_RXDMAEN_Pos        (0U)                           // RX Buffer DMA Enable bit position
#define SPI_CR2_RXDMAEN_Msk        (1U << SPI_CR2_RXDMAEN_Pos)    // RX Buffer DMA Enable mask

#define SPI_CR2_TXDMAEN_Pos        (1U)                           // TX Buffer DMA Enable bit position
#define SPI_CR2_TXDMAEN_Msk        (1U << SPI_CR2_TXDMAEN_Pos)    // TX Buffer DMA Enable mask

#define SPI_CR2_SSOE_Pos           (2U)                           // SS Output Enable bit position
#define SPI_CR2_SSOE_Msk           (1U << SPI_CR2_SSOE_Pos)       // SS Output Enable mask

#define SPI_CR2_ERRIE_Pos          (5U)                           // Error Interrupt Enable bit position
#define SPI_CR2_ERRIE_Msk          (1U << SPI_CR2_ERRIE_Pos)      // Error Interrupt Enable mask

#define SPI_CR2_RXNEIE_Pos         (6U)                           // RX Buffer Not Empty Interrupt Enable bit position
#define SPI_CR2_RXNEIE_Msk         (1U << SPI_CR2_RXNEIE_Pos)     // RX Buffer Not Empty Interrupt Enable mask

#define SPI_CR2_TXEIE_Pos          (7U)                           // TX Buffer Empty Interrupt Enable bit position
#define SPI_CR2_TXEIE_Msk          (1U << SPI_CR2_TXEIE_Pos)      // TX Buffer Empty Interrupt Enable mask

// SPI_SR Register Fields
#define SPI_SR_RXNE_Pos            (0U)                           // Receive Buffer Not Empty bit position
#define SPI_SR_RXNE_Msk            (1U << SPI_SR_RXNE_Pos)        // Receive Buffer Not Empty mask

#define SPI_SR_TXE_Pos             (1U)                           // Transmit Buffer Empty bit position
#define SPI_SR_TXE_Msk             (1U << SPI_SR_TXE_Pos)         // Transmit Buffer Empty mask

#define SPI_SR_CHSIDE_Pos          (2U)                           // Channel Side bit position (for I2S)
#define SPI_SR_CHSIDE_Msk          (1U << SPI_SR_CHSIDE_Pos)      // Channel Side mask

#define SPI_SR_UDR_Pos             (3U)                           // Underrun Flag bit position (for I2S)
#define SPI_SR_UDR_Msk             (1U << SPI_SR_UDR_Pos)         // Underrun Flag mask

#define SPI_SR_CRCERR_Pos          (4U)                           // CRC Error Flag bit position
#define SPI_SR_CRCERR_Msk          (1U << SPI_SR_CRCERR_Pos)      // CRC Error Flag mask

#define SPI_SR_MODF_Pos            (5U)                           // Mode Fault Flag bit position
#define SPI_SR_MODF_Msk            (1U << SPI_SR_MODF_Pos)        // Mode Fault Flag mask

#define SPI_SR_OVR_Pos             (6U)                           // Overrun Flag bit position
#define SPI_SR_OVR_Msk             (1U << SPI_SR_OVR_Pos)         // Overrun Flag mask

#define SPI_SR_BSY_Pos             (7U)                           // Busy Flag bit position
#define SPI_SR_BSY_Msk             (1U << SPI_SR_BSY_Pos)         // Busy Flag mask

// SPI_DR Register Fields
#define SPI_DR_DR_Pos              (0U)                           // Data Register bit position
#define SPI_DR_DR_Msk              (0xFFFFU << SPI_DR_DR_Pos)     // Data Register mask (16 bits)

// SPI_CRCPR Register Fields
#define SPI_CRCPR_CRCPOLY_Pos      (0U)                                 // CRC Polynomial bit position
#define SPI_CRCPR_CRCPOLY_Msk      (0xFFFFU << SPI_CRCPR_CRCPOLY_Pos)   // CRC Polynomial mask (16 bits)

// SPI_RXCRCR Register Fields
#define SPI_RXCRCR_RXCRC_Pos       (0U)                                 // RX CRC bit position
#define SPI_RXCRCR_RXCRC_Msk       (0xFFFFU << SPI_RXCRCR_RXCRC_Pos)    // RX CRC mask (16 bits)

// SPI_TXCRCR Register Fields
#define SPI_TXCRCR_TXCRC_Pos       (0U)                                 // TX CRC bit position
#define SPI_TXCRCR_TXCRC_Msk       (0xFFFFU << SPI_TXCRCR_TXCRC_Pos)    // TX CRC mask (16 bits)


/*--------------------------GPIO BIT FIELD POSITION AND MASK DEFINITIONS-------------------------------*/
// GPIOx_LCKR Register Fields
#define GPIOx_LCKR_LCKK_Pos         (16U)  // Position of HSION bit
#define GPIOx_LCKR_LCKK_Msk         (1U << GPIOx_LCKR_LCKK_Pos)  // Mask for HSION bit

/*--------------------------RCC BIT FIELD POSITION AND MASK DEFINITIONS-------------------------------*/
// RCC_CR Register Fields
#define RCC_CR_HSION_Pos         (0U)  // Position of HSION bit
#define RCC_CR_HSION_Msk         (1U << RCC_CR_HSION_Pos)  // Mask for HSION bit

#define RCC_CR_HSIRDY_Pos        (1U)  // Position of HSIRDY bit
#define RCC_CR_HSIRDY_Msk        (1U << RCC_CR_HSIRDY_Pos)  // Mask for HSIRDY bit

#define RCC_CR_HSITRIM_Pos       (3U)  // Position of HSITRIM bits
#define RCC_CR_HSITRIM_Msk       (0x1F << RCC_CR_HSITRIM_Pos)  // Mask for HSITRIM bits

#define RCC_CR_HSICAL_Pos        (8U)  // Position of HSICAL bits
#define RCC_CR_HSICAL_Msk        (0xFF << RCC_CR_HSICAL_Pos)  // Mask for HSICAL bits

#define RCC_CR_HSEON_Pos         (16U) // Position of HSEON bit
#define RCC_CR_HSEON_Msk         (1U << RCC_CR_HSEON_Pos)  // Mask for HSEON bit

#define RCC_CR_HSERDY_Pos        (17U) // Position of HSERDY bit
#define RCC_CR_HSERDY_Msk        (1U << RCC_CR_HSERDY_Pos)  // Mask for HSERDY bit

#define RCC_CR_HSEBYP_Pos        (18U) // Position of HSEBYP bit
#define RCC_CR_HSEBYP_Msk        (1U << RCC_CR_HSEBYP_Pos)  // Mask for HSEBYP bit

#define RCC_CR_CSSON_Pos         (19U) // Position of CSSON bit
#define RCC_CR_CSSON_Msk         (1U << RCC_CR_CSSON_Pos)  // Mask for CSSON bit

#define RCC_CR_PLLON_Pos         (24U) // Position of PLLON bit
#define RCC_CR_PLLON_Msk         (1U << RCC_CR_PLLON_Pos)  // Mask for PLLON bit

#define RCC_CR_PLLRDY_Pos        (25U) // Position of PLLRDY bit
#define RCC_CR_PLLRDY_Msk        (1U << RCC_CR_PLLRDY_Pos)  // Mask for PLLRDY bit

// RCC_CFGR Register Fields
#define RCC_CFGR_SW_Pos          (0U)  // Position of SW bits
#define RCC_CFGR_SW_Msk          (0x3 << RCC_CFGR_SW_Pos)  // Mask for SW bits

#define RCC_CFGR_SWS_Pos         (2U)  // Position of SWS bits
#define RCC_CFGR_SWS_Msk         (0x3 << RCC_CFGR_SWS_Pos)  // Mask for SWS bits

#define RCC_CFGR_HPRE_Pos        (4U)  // Position of HPRE bits
#define RCC_CFGR_HPRE_Msk        (0xF << RCC_CFGR_HPRE_Pos)  // Mask for HPRE bits

#define RCC_CFGR_PPRE1_Pos       (8U)  // Position of PPRE1 bits
#define RCC_CFGR_PPRE1_Msk       (0x7 << RCC_CFGR_PPRE1_Pos)  // Mask for PPRE1 bits

#define RCC_CFGR_PPRE2_Pos       (11U) // Position of PPRE2 bits
#define RCC_CFGR_PPRE2_Msk       (0x7 << RCC_CFGR_PPRE2_Pos)  // Mask for PPRE2 bits

#define RCC_CFGR_ADCPRE_Pos      (14U) // Position of ADCPRE bits
#define RCC_CFGR_ADCPRE_Msk      (0x3 << RCC_CFGR_ADCPRE_Pos)  // Mask for ADCPRE bits

#define RCC_CFGR_PLLSRC_Pos      (16U) // Position of PLLSRC bit
#define RCC_CFGR_PLLSRC_Msk      (1U << RCC_CFGR_PLLSRC_Pos)  // Mask for PLLSRC bit

#define RCC_CFGR_PLLXTPRE_Pos    (17U) // Position of PLLXTPRE bit
#define RCC_CFGR_PLLXTPRE_Msk    (1U << RCC_CFGR_PLLXTPRE_Pos)  // Mask for PLLXTPRE bit

#define RCC_CFGR_PLLMUL_Pos      (18U) // Position of PLLMUL bits
#define RCC_CFGR_PLLMUL_Msk      (0xF << RCC_CFGR_PLLMUL_Pos)  // Mask for PLLMUL bits

#define RCC_CFGR_USBPRE_Pos      (22U) // Position of USBPRE bit
#define RCC_CFGR_USBPRE_Msk      (1U << RCC_CFGR_USBPRE_Pos)  // Mask for USBPRE bit

#define RCC_CFGR_MCO_Pos         (24U) // Position of MCO bits
#define RCC_CFGR_MCO_Msk         (0x7 << RCC_CFGR_MCO_Pos)  // Mask for MCO bits

// RCC_CIR Register Fields
#define RCC_CIR_LSIRDYF_Pos      (0U)  // Position of LSIRDYF bit
#define RCC_CIR_LSIRDYF_Msk      (1U << RCC_CIR_LSIRDYF_Pos)  // Mask for LSIRDYF bit

#define RCC_CIR_LSERDYF_Pos      (1U)  // Position of LSERDYF bit
#define RCC_CIR_LSERDYF_Msk      (1U << RCC_CIR_LSERDYF_Pos)  // Mask for LSERDYF bit

#define RCC_CIR_HSIRDYF_Pos      (2U)  // Position of HSIRDYF bit
#define RCC_CIR_HSIRDYF_Msk      (1U << RCC_CIR_HSIRDYF_Pos)  // Mask for HSIRDYF bit

#define RCC_CIR_HSERDYF_Pos      (3U)  // Position of HSERDYF bit
#define RCC_CIR_HSERDYF_Msk      (1U << RCC_CIR_HSERDYF_Pos)  // Mask for HSERDYF bit

#define RCC_CIR_PLLRDYF_Pos      (4U)  // Position of PLLRDYF bit
#define RCC_CIR_PLLRDYF_Msk      (1U << RCC_CIR_PLLRDYF_Pos)  // Mask for PLLRDYF bit

#define RCC_CIR_CSSF_Pos         (7U)  // Position of CSSF bit
#define RCC_CIR_CSSF_Msk         (1U << RCC_CIR_CSSF_Pos)  // Mask for CSSF bit

#define RCC_CIR_LSIRDYIE_Pos     (8U)  // Position of LSIRDYIE bit
#define RCC_CIR_LSIRDYIE_Msk     (1U << RCC_CIR_LSIRDYIE_Pos)  // Mask for LSIRDYIE bit

#define RCC_CIR_LSERDYIE_Pos     (9U)  // Position of LSERDYIE bit
#define RCC_CIR_LSERDYIE_Msk     (1U << RCC_CIR_LSERDYIE_Pos)  // Mask for LSERDYIE bit

#define RCC_CIR_HSIRDYIE_Pos     (10U) // Position of HSIRDYIE bit
#define RCC_CIR_HSIRDYIE_Msk     (1U << RCC_CIR_HSIRDYIE_Pos)  // Mask for HSIRDYIE bit

#define RCC_CIR_HSERDYIE_Pos     (11U) // Position of HSERDYIE bit
#define RCC_CIR_HSERDYIE_Msk     (1U << RCC_CIR_HSERDYIE_Pos)  // Mask for HSERDYIE bit

#define RCC_CIR_PLLRDYIE_Pos     (12U) // Position of PLLRDYIE bit
#define RCC_CIR_PLLRDYIE_Msk     (1U << RCC_CIR_PLLRDYIE_Pos)  // Mask for PLLRDYIE bit

#define RCC_CIR_LSIRDYC_Pos      (16U) // Position of LSIRDYC bit
#define RCC_CIR_LSIRDYC_Msk      (1U << RCC_CIR_LSIRDYC_Pos)  // Mask for LSIRDYC bit

#define RCC_CIR_LSERDYC_Pos      (17U) // Position of LSERDYC bit
#define RCC_CIR_LSERDYC_Msk      (1U << RCC_CIR_LSERDYC_Pos)  // Mask for LSERDYC bit

#define RCC_CIR_HSIRDYC_Pos      (18U) // Position of HSIRDYC bit
#define RCC_CIR_HSIRDYC_Msk      (1U << RCC_CIR_HSIRDYC_Pos)  // Mask for HSIRDYC bit

#define RCC_CIR_HSERDYC_Pos      (19U) // Position of HSERDYC bit
#define RCC_CIR_HSERDYC_Msk      (1U << RCC_CIR_HSERDYC_Pos)  // Mask for HSERDYC bit

#define RCC_CIR_PLLRDYC_Pos      (20U) // Position of PLLRDYC bit
#define RCC_CIR_PLLRDYC_Msk      (1U << RCC_CIR_PLLRDYC_Pos)  // Mask for PLLRDYC bit

#define RCC_CIR_CSSC_Pos         (23U) // Position of CSSC bit
#define RCC_CIR_CSSC_Msk         (1U << RCC_CIR_CSSC_Pos)  // Mask for CSSC bit

// RCC_APB2RSTR Register Fields
#define RCC_APB2RSTR_AFIORST_Pos      (0U)   // Position of AFIORST bit
#define RCC_APB2RSTR_AFIORST_Msk      (1U << RCC_APB2RSTR_AFIORST_Pos)   // Mask for AFIORST bit

#define RCC_APB2RSTR_IOPARST_Pos      (2U)   // Position of IOPARST bit
#define RCC_APB2RSTR_IOPARST_Msk      (1U << RCC_APB2RSTR_IOPARST_Pos)   // Mask for IOPARST bit

#define RCC_APB2RSTR_IOPBRST_Pos      (3U)   // Position of IOPBRST bit
#define RCC_APB2RSTR_IOPBRST_Msk      (1U << RCC_APB2RSTR_IOPBRST_Pos)   // Mask for IOPBRST bit

#define RCC_APB2RSTR_IOPCRST_Pos      (4U)   // Position of IOPCRST bit
#define RCC_APB2RSTR_IOPCRST_Msk      (1U << RCC_APB2RSTR_IOPCRST_Pos)   // Mask for IOPCRST bit

#define RCC_APB2RSTR_IOPDRST_Pos      (5U)   // Position of IOPDRST bit
#define RCC_APB2RSTR_IOPDRST_Msk      (1U << RCC_APB2RSTR_IOPDRST_Pos)   // Mask for IOPDRST bit

#define RCC_APB2RSTR_IOPERST_Pos      (6U)   // Position of IOPERST bit
#define RCC_APB2RSTR_IOPERST_Msk      (1U << RCC_APB2RSTR_IOPERST_Pos)   // Mask for IOPERST bit

#define RCC_APB2RSTR_IOPFRST_Pos      (7U)   // Position of IOPFRST bit
#define RCC_APB2RSTR_IOPFRST_Msk      (1U << RCC_APB2RSTR_IOPFRST_Pos)   // Mask for IOPFRST bit

#define RCC_APB2RSTR_IOPGRST_Pos      (8U)   // Position of IOPGRST bit
#define RCC_APB2RSTR_IOPGRST_Msk      (1U << RCC_APB2RSTR_IOPGRST_Pos)   // Mask for IOPGRST bit

#define RCC_APB2RSTR_ADC1RST_Pos      (9U)   // Position of ADC1RST bit
#define RCC_APB2RSTR_ADC1RST_Msk      (1U << RCC_APB2RSTR_ADC1RST_Pos)   // Mask for ADC1RST bit

#define RCC_APB2RSTR_ADC2RST_Pos      (10U)  // Position of ADC2RST bit
#define RCC_APB2RSTR_ADC2RST_Msk      (1U << RCC_APB2RSTR_ADC2RST_Pos)   // Mask for ADC2RST bit

#define RCC_APB2RSTR_TIM1RST_Pos      (11U)  // Position of TIM1RST bit
#define RCC_APB2RSTR_TIM1RST_Msk      (1U << RCC_APB2RSTR_TIM1RST_Pos)   // Mask for TIM1RST bit

#define RCC_APB2RSTR_SPI1RST_Pos      (12U)  // Position of SPI1RST bit
#define RCC_APB2RSTR_SPI1RST_Msk      (1U << RCC_APB2RSTR_SPI1RST_Pos)   // Mask for SPI1RST bit

#define RCC_APB2RSTR_TIM8RST_Pos      (13U)  // Position of TIM8RST bit
#define RCC_APB2RSTR_TIM8RST_Msk      (1U << RCC_APB2RSTR_TIM8RST_Pos)   // Mask for TIM8RST bit

#define RCC_APB2RSTR_USART1RST_Pos    (14U)  // Position of USART1RST bit
#define RCC_APB2RSTR_USART1RST_Msk    (1U << RCC_APB2RSTR_USART1RST_Pos)   // Mask for USART1RST bit

#define RCC_APB2RSTR_ADC3RST_Pos      (15U)  // Position of ADC3RST bit
#define RCC_APB2RSTR_ADC3RST_Msk      (1U << RCC_APB2RSTR_ADC3RST_Pos)   // Mask for ADC3RST bit

#define RCC_APB2RSTR_TIM9RST_Pos      (19U)  // Position of TIM9RST bit
#define RCC_APB2RSTR_TIM9RST_Msk      (1U << RCC_APB2RSTR_TIM9RST_Pos)   // Mask for TIM9RST bit

#define RCC_APB2RSTR_TIM10RST_Pos     (20U)  // Position of TIM10RST bit
#define RCC_APB2RSTR_TIM10RST_Msk     (1U << RCC_APB2RSTR_TIM10RST_Pos)   // Mask for TIM10RST bit

#define RCC_APB2RSTR_TIM11RST_Pos     (21U)  // Position of TIM11RST bit
#define RCC_APB2RSTR_TIM11RST_Msk     (1U << RCC_APB2RSTR_TIM11RST_Pos)   // Mask for TIM11RST bit

// RCC_APB1RSTR Register Fields
#define RCC_APB1RSTR_TIM2RST_Pos      (0U)   // Position of TIM2RST bit
#define RCC_APB1RSTR_TIM2RST_Msk      (1U << RCC_APB1RSTR_TIM2RST_Pos)   // Mask for TIM2RST bit

#define RCC_APB1RSTR_TIM3RST_Pos      (1U)   // Position of TIM3RST bit
#define RCC_APB1RSTR_TIM3RST_Msk      (1U << RCC_APB1RSTR_TIM3RST_Pos)   // Mask for TIM3RST bit

#define RCC_APB1RSTR_TIM4RST_Pos      (2U)   // Position of TIM4RST bit
#define RCC_APB1RSTR_TIM4RST_Msk      (1U << RCC_APB1RSTR_TIM4RST_Pos)   // Mask for TIM4RST bit

#define RCC_APB1RSTR_TIM5RST_Pos      (3U)   // Position of TIM5RST bit
#define RCC_APB1RSTR_TIM5RST_Msk      (1U << RCC_APB1RSTR_TIM5RST_Pos)   // Mask for TIM5RST bit

#define RCC_APB1RSTR_TIM6RST_Pos      (4U)   // Position of TIM6RST bit
#define RCC_APB1RSTR_TIM6RST_Msk      (1U << RCC_APB1RSTR_TIM6RST_Pos)   // Mask for TIM6RST bit

#define RCC_APB1RSTR_TIM7RST_Pos      (5U)   // Position of TIM7RST bit
#define RCC_APB1RSTR_TIM7RST_Msk      (1U << RCC_APB1RSTR_TIM7RST_Pos)   // Mask for TIM7RST bit

#define RCC_APB1RSTR_TIM12RST_Pos     (6U)   // Position of TIM12RST bit
#define RCC_APB1RSTR_TIM12RST_Msk     (1U << RCC_APB1RSTR_TIM12RST_Pos)   // Mask for TIM7RST bit

#define RCC_APB1RSTR_TIM13RST_Pos     (7U)   // Position of TIM13RST bit
#define RCC_APB1RSTR_TIM13RST_Msk     (1U << RCC_APB1RSTR_TIM13RST_Pos)   // Mask for TIM7RST bit

#define RCC_APB1RSTR_TIM14RST_Pos     (8U)   // Position of TIM14RST bit
#define RCC_APB1RSTR_TIM14RST_Msk     (1U << RCC_APB1RSTR_TIM14RST_Pos)   // Mask for TIM7RST bit

#define RCC_APB1RSTR_WWDGRST_Pos     (11U)   // Position of WWDGRST bit
#define RCC_APB1RSTR_WWDGRST_Msk     (1U << RCC_APB1RSTR_WWDGRST_Pos)   // Mask for WWDGRST bit

#define RCC_APB1RSTR_SPI2RST_Pos     (14U)   // Position of SPI2RST bit
#define RCC_APB1RSTR_SPI2RST_Msk     (1U << RCC_APB1RSTR_SPI2RST_Pos)   // Mask for SPI2RST bit

#define RCC_APB1RSTR_SPI3RST_Pos     (15U)   // Position of SPI3RST bit
#define RCC_APB1RSTR_SPI3RST_Msk     (1U << RCC_APB1RSTR_SPI3RST_Pos)   // Mask for SPI3RST bit

#define RCC_APB1RSTR_USART2RST_Pos   (17U)   // Position of USART2RST bit
#define RCC_APB1RSTR_USART2RST_Msk   (1U << RCC_APB1RSTR_USART2RST_Pos)   // Mask for USART2RST bit

#define RCC_APB1RSTR_USART3RST_Pos   (18U)   // Position of USART3RST bit
#define RCC_APB1RSTR_USART3RST_Msk   (1U << RCC_APB1RSTR_USART3RST_Pos)   // Mask for USART3RST bit

#define RCC_APB1RSTR_UART4RST_Pos    (19U)   // Position of UART4RST bit
#define RCC_APB1RSTR_UART4RST_Msk    (1U << RCC_APB1RSTR_UART4RST_Pos)   // Mask for UART4RST bit

#define RCC_APB1RSTR_UART5RST_Pos    (20U)   // Position of UART5RST bit
#define RCC_APB1RSTR_UART5RST_Msk    (1U << RCC_APB1RSTR_UART5RST_Pos)   // Mask for UART5RST bit

#define RCC_APB1RSTR_I2C1RST_Pos     (21U)   // Position of I2C1RST bit
#define RCC_APB1RSTR_I2C1RST_Msk     (1U << RCC_APB1RSTR_I2C1RST_Pos)   // Mask for I2C1RST bit

#define RCC_APB1RSTR_I2C2RST_Pos     (22U)   // Position of I2C2RST bit
#define RCC_APB1RSTR_I2C2RST_Msk     (1U << RCC_APB1RSTR_I2C2RST_Pos)   // Mask for I2C2RST bit

#define RCC_APB1RSTR_USBRST_Pos      (23U)   // Position of USBRST bit
#define RCC_APB1RSTR_USBRST_Msk      (1U << RCC_APB1RSTR_USBRST_Pos)   // Mask for USBRST bit

#define RCC_APB1RSTR_CANRST_Pos      (25U)   // Position of CANRST bit
#define RCC_APB1RSTR_CANRST_Msk      (1U << RCC_APB1RSTR_CANRST_Pos)   // Mask for CANRST bit

#define RCC_APB1RSTR_BKPRST_Pos      (27U)   // Position of BKPRST bit
#define RCC_APB1RSTR_BKPRST_Msk      (1U << RCC_APB1RSTR_BKPRST_Pos)   // Mask for BKPRST bit

#define RCC_APB1RSTR_PWRRST_Pos      (28U)   // Position of PWRRST bit
#define RCC_APB1RSTR_PWRRST_Msk      (1U << RCC_APB1RSTR_PWRRST_Pos)   // Mask for PWRRST bit

#define RCC_APB1RSTR_DACRST_Pos      (29U)   // Position of DACRST bit
#define RCC_APB1RSTR_DACRST_Msk      (1U << RCC_APB1RSTR_DACRST_Pos)   // Mask for DACRST bit

// RCC_AHBENR Register Fields
#define RCC_AHBENR_DMA1EN_Pos      (0U)   // Position of DMA1EN bit
#define RCC_AHBENR_DMA1EN_Msk      (1U << RCC_AHBENR_DMA1EN_Pos)   // Mask for DMA1EN bit

#define RCC_AHBENR_DMA2EN_Pos      (1U)   // Position of DMA2EN bit
#define RCC_AHBENR_DMA2EN_Msk      (1U << RCC_AHBENR_DMA2EN_Pos)   // Mask for DMA2EN bit

#define RCC_AHBENR_SRAMEN_Pos      (2U)   // Position of SRAMEN bit
#define RCC_AHBENR_SRAMEN_Msk      (1U << RCC_AHBENR_SRAMEN_Pos)   // Mask for SRAMEN bit

#define RCC_AHBENR_FLITFEN_Pos     (4U)   // Position of FLITFEN bit
#define RCC_AHBENR_FLITFEN_Msk     (1U << RCC_AHBENR_FLITFEN_Pos)   // Mask for FLITFEN bit

#define RCC_AHBENR_CRCEN_Pos       (6U)   // Position of CRCEN bit
#define RCC_AHBENR_CRCEN_Msk       (1U << RCC_AHBENR_CRCEN_Pos)   // Mask for CRCEN bit

#define RCC_AHBENR_FSMCEN_Pos      (8U)   // Position of FSMCEN bit
#define RCC_AHBENR_FSMCEN_Msk      (1U << RCC_AHBENR_FSMCEN_Pos)   // Mask for FSMCEN bit

#define RCC_AHBENR_SDIOEN_Pos      (10U)  // Position of SDIOEN bit
#define RCC_AHBENR_SDIOEN_Msk      (1U << RCC_AHBENR_SDIOEN_Pos)   // Mask for SDIOEN bit

// RCC_APB2ENR Register Fields
#define RCC_APB2ENR_AFIOEN_Pos      (0U)   // Position of AFIOEN bit
#define RCC_APB2ENR_AFIOEN_Msk      (1U << RCC_APB2ENR_AFIOEN_Pos)   // Mask for AFIOEN bit

#define RCC_APB2ENR_IOPAEN_Pos      (2U)   // Position of IOPAEN bit
#define RCC_APB2ENR_IOPAEN_Msk      (1U << RCC_APB2ENR_IOPAEN_Pos)   // Mask for IOPAEN bit

#define RCC_APB2ENR_IOPBEN_Pos      (3U)   // Position of IOPBEN bit
#define RCC_APB2ENR_IOPBEN_Msk      (1U << RCC_APB2ENR_IOPBEN_Pos)   // Mask for IOPBEN bit

#define RCC_APB2ENR_IOPCEN_Pos      (4U)   // Position of IOPCEN bit
#define RCC_APB2ENR_IOPCEN_Msk      (1U << RCC_APB2ENR_IOPCEN_Pos)   // Mask for IOPCEN bit

#define RCC_APB2ENR_IOPDEN_Pos      (5U)   // Position of IOPDEN bit
#define RCC_APB2ENR_IOPDEN_Msk      (1U << RCC_APB2ENR_IOPDEN_Pos)   // Mask for IOPDEN bit

#define RCC_APB2ENR_IOPEEN_Pos      (6U)   // Position of IOPEEN bit
#define RCC_APB2ENR_IOPEEN_Msk      (1U << RCC_APB2ENR_IOPEEN_Pos)   // Mask for IOPEEN bit

#define RCC_APB2ENR_IOPFEN_Pos      (7U)   // Position of IOPFEN bit
#define RCC_APB2ENR_IOPFEN_Msk      (1U << RCC_APB2ENR_IOPFEN_Pos)   // Mask for IOPFEN bit

#define RCC_APB2ENR_IOPGEN_Pos      (8U)   // Position of IOPGEN bit
#define RCC_APB2ENR_IOPGEN_Msk      (1U << RCC_APB2ENR_IOPGEN_Pos)   // Mask for IOPGEN bit

#define RCC_APB2ENR_ADC1EN_Pos      (9U)   // Position of ADC1EN bit
#define RCC_APB2ENR_ADC1EN_Msk      (1U << RCC_APB2ENR_ADC1EN_Pos)   // Mask for ADC1EN bit

#define RCC_APB2ENR_ADC2EN_Pos      (10U)  // Position of ADC2EN bit
#define RCC_APB2ENR_ADC2EN_Msk      (1U << RCC_APB2ENR_ADC2EN_Pos)   // Mask for ADC2EN bit

#define RCC_APB2ENR_TIM1EN_Pos      (11U)  // Position of TIM1EN bit
#define RCC_APB2ENR_TIM1EN_Msk      (1U << RCC_APB2ENR_TIM1EN_Pos)   // Mask for TIM1EN bit

#define RCC_APB2ENR_SPI1EN_Pos      (12U)  // Position of SPI1EN bit
#define RCC_APB2ENR_SPI1EN_Msk      (1U << RCC_APB2ENR_SPI1EN_Pos)   // Mask for SPI1EN bit

#define RCC_APB2ENR_TIM8EN_Pos      (13U)  // Position of TIM8EN bit
#define RCC_APB2ENR_TIM8EN_Msk      (1U << RCC_APB2ENR_TIM8EN_Pos)   // Mask for TIM8EN bit

#define RCC_APB2ENR_USART1EN_Pos    (14U)  // Position of USART1EN bit
#define RCC_APB2ENR_USART1EN_Msk    (1U << RCC_APB2ENR_USART1EN_Pos)   // Mask for USART1EN bit

#define RCC_APB2ENR_ADC3EN_Pos      (15U)  // Position of ADC3EN bit
#define RCC_APB2ENR_ADC3EN_Msk      (1U << RCC_APB2ENR_ADC3EN_Pos)   // Mask for ADC3EN bit

#define RCC_APB2ENR_TIM9EN_Pos      (19U)  // Position of TIM9EN bit
#define RCC_APB2ENR_TIM9EN_Msk      (1U << RCC_APB2ENR_TIM9EN_Pos)   // Mask for TIM9EN bit

#define RCC_APB2ENR_TIM10EN_Pos     (20U)  // Position of TIM10EN bit
#define RCC_APB2ENR_TIM10EN_Msk     (1U << RCC_APB2ENR_TIM10EN_Pos)   // Mask for TIM10EN bit

#define RCC_APB2ENR_TIM11EN_Pos     (21U)  // Position of TIM11EN bit
#define RCC_APB2ENR_TIM11EN_Msk     (1U << RCC_APB2ENR_TIM11EN_Pos)   // Mask for TIM11EN bit

// RCC_APB1ENR Register Fields
#define RCC_APB1ENR_TIM2EN_Pos       (0U)   // Position of TIM2EN bit
#define RCC_APB1ENR_TIM2EN_Msk       (1U << RCC_APB1ENR_TIM2EN_Pos)   // Mask for TIM2EN bit

#define RCC_APB1ENR_TIM3EN_Pos       (1U)   // Position of TIM3EN bit
#define RCC_APB1ENR_TIM3EN_Msk       (1U << RCC_APB1ENR_TIM3EN_Pos)   // Mask for TIM3EN bit

#define RCC_APB1ENR_TIM4EN_Pos       (2U)   // Position of TIM4EN bit
#define RCC_APB1ENR_TIM4EN_Msk       (1U << RCC_APB1ENR_TIM4EN_Pos)   // Mask for TIM4EN bit

#define RCC_APB1ENR_TIM5EN_Pos       (3U)   // Position of TIM5EN bit
#define RCC_APB1ENR_TIM5EN_Msk       (1U << RCC_APB1ENR_TIM5EN_Pos)   // Mask for TIM5EN bit

#define RCC_APB1ENR_TIM6EN_Pos       (4U)   // Position of TIM6EN bit
#define RCC_APB1ENR_TIM6EN_Msk       (1U << RCC_APB1ENR_TIM6EN_Pos)   // Mask for TIM6EN bit

#define RCC_APB1ENR_TIM7EN_Pos       (5U)   // Position of TIM7EN bit
#define RCC_APB1ENR_TIM7EN_Msk       (1U << RCC_APB1ENR_TIM7EN_Pos)   // Mask for TIM7EN bit

#define RCC_APB1ENR_TIM12EN_Pos      (6U)   // Position of TIM12EN bit
#define RCC_APB1ENR_TIM12EN_Msk      (1U << RCC_APB1ENR_TIM12EN_Pos)  // Mask for TIM12EN bit

#define RCC_APB1ENR_TIM13EN_Pos      (7U)   // Position of TIM13EN bit
#define RCC_APB1ENR_TIM13EN_Msk      (1U << RCC_APB1ENR_TIM13EN_Pos)  // Mask for TIM13EN bit

#define RCC_APB1ENR_TIM14EN_Pos      (8U)   // Position of TIM14EN bit
#define RCC_APB1ENR_TIM14EN_Msk      (1U << RCC_APB1ENR_TIM14EN_Pos)  // Mask for TIM14EN bit

#define RCC_APB1ENR_WWDGEN_Pos       (11U)  // Position of WWDGEN bit
#define RCC_APB1ENR_WWDGEN_Msk       (1U << RCC_APB1ENR_WWDGEN_Pos)   // Mask for WWDGEN bit

#define RCC_APB1ENR_SPI2EN_Pos       (14U)  // Position of SPI2EN bit
#define RCC_APB1ENR_SPI2EN_Msk       (1U << RCC_APB1ENR_SPI2EN_Pos)   // Mask for SPI2EN bit

#define RCC_APB1ENR_SPI3EN_Pos       (15U)  // Position of SPI3EN bit
#define RCC_APB1ENR_SPI3EN_Msk       (1U << RCC_APB1ENR_SPI3EN_Pos)   // Mask for SPI3EN bit

#define RCC_APB1ENR_USART2EN_Pos     (17U)  // Position of USART2EN bit
#define RCC_APB1ENR_USART2EN_Msk     (1U << RCC_APB1ENR_USART2EN_Pos) // Mask for USART2EN bit

#define RCC_APB1ENR_USART3EN_Pos     (18U)  // Position of USART3EN bit
#define RCC_APB1ENR_USART3EN_Msk     (1U << RCC_APB1ENR_USART3EN_Pos) // Mask for USART3EN bit

#define RCC_APB1ENR_UART4EN_Pos      (19U)  // Position of UART4EN bit
#define RCC_APB1ENR_UART4EN_Msk      (1U << RCC_APB1ENR_UART4EN_Pos)  // Mask for UART4EN bit

#define RCC_APB1ENR_UART5EN_Pos      (20U)  // Position of UART5EN bit
#define RCC_APB1ENR_UART5EN_Msk      (1U << RCC_APB1ENR_UART5EN_Pos)  // Mask for UART5EN bit

#define RCC_APB1ENR_I2C1EN_Pos       (21U)  // Position of I2C1EN bit
#define RCC_APB1ENR_I2C1EN_Msk       (1U << RCC_APB1ENR_I2C1EN_Pos)   // Mask for I2C1EN bit

#define RCC_APB1ENR_I2C2EN_Pos       (22U)  // Position of I2C2EN bit
#define RCC_APB1ENR_I2C2EN_Msk       (1U << RCC_APB1ENR_I2C2EN_Pos)   // Mask for I2C2EN bit

#define RCC_APB1ENR_USBEN_Pos        (23U)  // Position of USBEN bit
#define RCC_APB1ENR_USBEN_Msk        (1U << RCC_APB1ENR_USBEN_Pos)    // Mask for USBEN bit

#define RCC_APB1ENR_CANEN_Pos        (25U)  // Position of CANEN bit
#define RCC_APB1ENR_CANEN_Msk        (1U << RCC_APB1ENR_CANEN_Pos)    // Mask for CANEN bit

#define RCC_APB1ENR_BKPEN_Pos        (27U)  // Position of BKPEN bit
#define RCC_APB1ENR_BKPEN_Msk        (1U << RCC_APB1ENR_BKPEN_Pos)    // Mask for BKPEN bit

#define RCC_APB1ENR_PWREN_Pos        (28U)  // Position of PWREN bit
#define RCC_APB1ENR_PWREN_Msk        (1U << RCC_APB1ENR_PWREN_Pos)    // Mask for PWREN bit

#define RCC_APB1ENR_DACEN_Pos        (29U)  // Position of DACEN bit
#define RCC_APB1ENR_DACEN_Msk        (1U << RCC_APB1ENR_DACEN_Pos)    // Mask for DACEN bit

// RCC_BDCR Register Fields
#define RCC_BDCR_LSEON_Pos        (0U)   // Position of LSEON bit
#define RCC_BDCR_LSEON_Msk        (1U << RCC_BDCR_LSEON_Pos)   // Mask for LSEON bit

#define RCC_BDCR_LSERDY_Pos       (1U)   // Position of LSERDY bit
#define RCC_BDCR_LSERDY_Msk       (1U << RCC_BDCR_LSERDY_Pos)  // Mask for LSERDY bit

#define RCC_BDCR_LSEBYP_Pos       (2U)   // Position of LSEBYP bit
#define RCC_BDCR_LSEBYP_Msk       (1U << RCC_BDCR_LSEBYP_Pos)  // Mask for LSEBYP bit

#define RCC_BDCR_RTCSEL_Pos       (8U)   // Position of RTCSEL bits
#define RCC_BDCR_RTCSEL_Msk       (0x3 << RCC_BDCR_RTCSEL_Pos) // Mask for RTCSEL bits

#define RCC_BDCR_RTCEN_Pos        (15U)  // Position of RTCEN bit
#define RCC_BDCR_RTCEN_Msk        (1U << RCC_BDCR_RTCEN_Pos)   // Mask for RTCEN bit

#define RCC_BDCR_BDRST_Pos        (16U)  // Position of BDRST bit
#define RCC_BDCR_BDRST_Msk        (1U << RCC_BDCR_BDRST_Pos)   // Mask for BDRST bit

// RCC_CSR Register Fields
#define RCC_CSR_LSION_Pos         (0U)   // Position of LSION bit
#define RCC_CSR_LSION_Msk         (1U << RCC_CSR_LSION_Pos)   // Mask for LSION bit

#define RCC_CSR_LSIRDY_Pos        (1U)   // Position of LSIRDY bit
#define RCC_CSR_LSIRDY_Msk        (1U << RCC_CSR_LSIRDY_Pos)  // Mask for LSIRDY bit

#define RCC_CSR_RMVF_Pos          (24U)  // Position of RMVF bit
#define RCC_CSR_RMVF_Msk          (1U << RCC_CSR_RMVF_Pos)    // Mask for RMVF bit

#define RCC_CSR_PINRSTF_Pos       (26U)  // Position of PINRSTF bit
#define RCC_CSR_PINRSTF_Msk       (1U << RCC_CSR_PINRSTF_Pos) // Mask for PINRSTF bit

#define RCC_CSR_PORRSTF_Pos       (27U)  // Position of PORRSTF bit
#define RCC_CSR_PORRSTF_Msk       (1U << RCC_CSR_PORRSTF_Pos) // Mask for PORRSTF bit

#define RCC_CSR_SFTRSTF_Pos       (28U)  // Position of SFTRSTF bit
#define RCC_CSR_SFTRSTF_Msk       (1U << RCC_CSR_SFTRSTF_Pos) // Mask for SFTRSTF bit

#define RCC_CSR_IWDGRSTF_Pos      (29U)  // Position of IWDGRSTF bit
#define RCC_CSR_IWDGRSTF_Msk      (1U << RCC_CSR_IWDGRSTF_Pos) // Mask for IWDGRSTF bit

#define RCC_CSR_WWDGRSTF_Pos      (30U)  // Position of WWDGRSTF bit
#define RCC_CSR_WWDGRSTF_Msk      (1U << RCC_CSR_WWDGRSTF_Pos) // Mask for WWDGRSTF bit

#define RCC_CSR_LPWRRSTF_Pos      (31U)  // Position of LPWRRSTF bit
#define RCC_CSR_LPWRRSTF_Msk      (1U << RCC_CSR_LPWRRSTF_Pos) // Mask for LPWRRSTF bit

/*-------------------------- AFIO BIT FIELD POSITION AND MASK DEFINITIONS -------------------------------*/

// AFIO_EVCR Register Fields
#define AFIO_EVCR_PIN_Pos                   (0U)  // Position of PIN[3:0] bit
#define AFIO_EVCR_PIN_Msk                   (0xF << AFIO_EVCR_PIN_Pos)  // Mask for PIN[3:0] bits (0b1111)

#define AFIO_EVCR_PORT_Pos                  (4U)  // Position of PORT[2:0] bit
#define AFIO_EVCR_PORT_Msk                  (0x7 << AFIO_EVCR_PORT_Pos) // Mask for PORT[2:0] bits (0b111)

#define AFIO_EVCR_EVOE_Pos                  (7U)  // Position of EVOE bit
#define AFIO_EVCR_EVOE_Msk                  (1U << AFIO_EVCR_EVOE_Pos)  // Mask for EVOE bit (0b1)


// AFIO_MAPR Register Fields
#define AFIO_MAPR_SPI1_REMAP_Pos            (0U)  // Position of SPI1_REMAP bit
#define AFIO_MAPR_SPI1_REMAP_Msk            (1U << AFIO_MAPR_SPI1_REMAP_Pos)  // Mask for SPI1_REMAP bit

#define AFIO_MAPR_I2C1_REMAP_Pos            (1U)  // Position of I2C1_REMAP bit
#define AFIO_MAPR_I2C1_REMAP_Msk            (1U << AFIO_MAPR_I2C1_REMAP_Pos)  // Mask for I2C1_REMAP bit

#define AFIO_MAPR_USART1_REMAP_Pos          (2U)  // Position of USART1_REMAP bit
#define AFIO_MAPR_USART1_REMAP_Msk          (1U << AFIO_MAPR_USART1_REMAP_Pos)  // Mask for USART1_REMAP bit

#define AFIO_MAPR_USART2_REMAP_Pos          (3U)  // Position of USART2_REMAP bit
#define AFIO_MAPR_USART2_REMAP_Msk          (1U << AFIO_MAPR_USART2_REMAP_Pos)  // Mask for USART2_REMAP bit

#define AFIO_MAPR_USART3_REMAP_Pos          (4U)  // Position of USART3_REMAP[1:0] bits
#define AFIO_MAPR_USART3_REMAP_Msk          (0x3 << AFIO_MAPR_USART3_REMAP_Pos)  // Mask for USART3_REMAP[1:0] bits (2 bits)

#define AFIO_MAPR_TIM1_REMAP_Pos            (6U)  // Position of TIM1_REMAP[1:0] bits
#define AFIO_MAPR_TIM1_REMAP_Msk            (0x3 << AFIO_MAPR_TIM1_REMAP_Pos)  // Mask for TIM1_REMAP[1:0] bits (2 bits)

#define AFIO_MAPR_TIM2_REMAP_Pos            (8U)  // Position of TIM2_REMAP[1:0] bits
#define AFIO_MAPR_TIM2_REMAP_Msk            (0x3 << AFIO_MAPR_TIM2_REMAP_Pos)  // Mask for TIM2_REMAP[1:0] bits (2 bits)

#define AFIO_MAPR_TIM3_REMAP_Pos            (10U)  // Position of TIM3_REMAP[1:0] bits
#define AFIO_MAPR_TIM3_REMAP_Msk            (0x3 << AFIO_MAPR_TIM3_REMAP_Pos)  // Mask for TIM3_REMAP[1:0] bits (2 bits)

#define AFIO_MAPR_TIM4_REMAP_Pos            (12U)  // Position of TIM4_REMAP bit
#define AFIO_MAPR_TIM4_REMAP_Msk            (1U << AFIO_MAPR_TIM4_REMAP_Pos)  // Mask for TIM4_REMAP bit

#define AFIO_MAPR_CAN_REMAP_Pos             (13U)  // Position of CAN_REMAP[1:0] bits
#define AFIO_MAPR_CAN_REMAP_Msk             (0x3 << AFIO_MAPR_CAN_REMAP_Pos)  // Mask for CAN_REMAP[1:0] bits (2 bits)

#define AFIO_MAPR_PD01_REMAP_Pos            (15U)  // Position of PD01_REMAP bit
#define AFIO_MAPR_PD01_REMAP_Msk            (1U << AFIO_MAPR_PD01_REMAP_Pos)  // Mask for PD01_REMAP bit

#define AFIO_MAPR_TIM5CH4_IREMAP_Pos        (16U)  // Position of TIM5CH4_IREMAP bit
#define AFIO_MAPR_TIM5CH4_IREMAP_Msk        (1U << AFIO_MAPR_TIM5CH4_IREMAP_Pos)  // Mask for TIM5CH4_IREMAP bit

#define AFIO_MAPR_ADC1_ETRGINJ_REMAP_Pos    (17U)  // Position of ADC1_ETRGINJ_REMAP bit
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP_Msk    (1U << AFIO_MAPR_ADC1_ETRGINJ_REMAP_Pos)  // Mask for ADC1_ETRGINJ_REMAP bit

#define AFIO_MAPR_ADC1_ETRGREG_REMAP_Pos    (18U)  // Position of ADC1_ETRGREG_REMAP bit
#define AFIO_MAPR_ADC1_ETRGREG_REMAP_Msk    (1U << AFIO_MAPR_ADC1_ETRGREG_REMAP_Pos)  // Mask for ADC1_ETRGREG_REMAP bit

#define AFIO_MAPR_ADC2_ETRGINJ_REMAP_Pos    (19U)  // Position of ADC2_ETRGINJ_REMAP bit
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP_Msk    (1U << AFIO_MAPR_ADC2_ETRGINJ_REMAP_Pos)  // Mask for ADC2_ETRGINJ_REMAP bit

#define AFIO_MAPR_ADC2_ETRGREG_REMAP_Pos    (20U)  // Position of ADC2_ETRGREG_REMAP bit
#define AFIO_MAPR_ADC2_ETRGREG_REMAP_Msk    (1U << AFIO_MAPR_ADC2_ETRGREG_REMAP_Pos)  // Mask for ADC2_ETRGREG_REMAP bit

#define AFIO_MAPR_SWJ_CFG_Pos               (24U)  // Position of SWJ_CFG[2:0] bits
#define AFIO_MAPR_SWJ_CFG_Msk               (0x7 << AFIO_MAPR_SWJ_CFG_Pos)  // Mask for SWJ_CFG[2:0] bits (3 bits)

