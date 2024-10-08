#pragma once

#include "mcu_peripherals.h"
#include "rcc_driver.h"

typedef enum {
    SPI_MODE_SLAVE  = 0,
    SPI_MODE_MASTER = 1
} spi_mode_t;

typedef enum {
    SPI_TRANS_MODE_FULLDUPLEX = 0,
    SPI_TRANS_MODE_HALFDUPLEX = 1
} spi_trans_mode_t;

typedef enum {
    SPI_CPOL_LOW  = 0,  // Clock polarity low when idle
    SPI_CPOL_HIGH = 1   // Clock polarity high when idle
} spi_cpol_t;

typedef enum {
    SPI_CPHA_LEAD_EDGE = 0,  // Data sampled on leading clock edge
    SPI_CPHA_TRAIL_EDGE = 1   // Data sampled on trailing clock edge
} spi_cpha_t;

typedef enum {
    SPI_DATASIZE_8BIT  = 0,
    SPI_DATASIZE_16BIT = 1
} spi_datasize_t;

typedef enum {
    SPI_NSS_SOFT = 0,  // Software control of NSS pin
    SPI_NSS_HARD = 1   // Hardware control of NSS pin
} spi_nss_mode_t;

typedef enum {
    SPI_BIT_ORDER_MSB = 0,  // Software control of NSS pin
    SPI_BIT_ORDER_LSB = 1   // Hardware control of NSS pin
} spi_bit_order_t;

typedef enum {
    SPI_BAUDRATE_DIV2   = 0,
    SPI_BAUDRATE_DIV4   = 1,
    SPI_BAUDRATE_DIV8   = 2,
    SPI_BAUDRATE_DIV16  = 3,
    SPI_BAUDRATE_DIV32  = 4,
    SPI_BAUDRATE_DIV64  = 5,
    SPI_BAUDRATE_DIV128 = 6,
    SPI_BAUDRATE_DIV256 = 7
} spi_baudrate_t;

typedef struct {
    spi_mode_t       mode;         // Master or slave mode
    spi_trans_mode_t trans_mode;   // Transmission mode
    spi_cpol_t       polarity;     // Clock polarity
    spi_cpha_t       phase;        // Clock phase
    spi_bit_order_t  bit_order;    // Bit order (MSB or LSB)
    spi_datasize_t   datasize;     // Data size (8-bit or 16-bit)
    spi_baudrate_t   baudrate;     // Baud rate prescaler
    spi_nss_mode_t   nss;          // NSS management mode
} SPI_Cfg_t;

// callback function for interrupt processing
typedef void (*spi_callback_t)(void); 

// Handle for SPI instance (e.g., SPI1, SPI2, etc.)
typedef struct {
    SPI_t    *instance;      // Pointer to the SPI peripheral (e.g., SPI1, SPI2)
    SPI_Cfg_t     *cfg;      // Configuration parameters
    spi_callback_t  cb;      // Optional callback for interrupt handling
} spi_handle_t;

void spi_get_default_cfg(SPI_Cfg_t *pCfg);

//control
void spi_clk_enable(spi_handle_t *const hspi);
void spi_clk_disable(spi_handle_t *const hspi);
void spi_port_reset(spi_handle_t *const hspi);

//initialized SPI peripheral instance
//GPIO: gpio pins have to be configured seperately 
//AFIO: afio pins have to be configured if default pins need to be remapped
void spi_init(spi_handle_t *const hspi);

void spi_deinit(spi_handle_t *const hspi);

//enable/disable internal nss line in sw 
//master: set SSI to 1 to keep the SPI enabled 
//slave: replaces external ssn signal by setting SSI bit
static inline void spi_sw_ssn(spi_handle_t *const hspi, uint8_t val){EN_DIS_BIT(hspi->instance->CR1, SPI_CR1_SSI_Pos, val);}

//configure receive-only mode in full-duplex communication
static inline void spi_set_rxonly(spi_handle_t *const hspi, uint8_t rxonly){EN_DIS_BIT(hspi->instance->CR1, SPI_CR1_RXONLY_Pos, rxonly);}

//status
static inline uint8_t spi_is_busy(spi_handle_t *const hspi){return (uint8_t)GET_BIT(hspi->instance->SR, SPI_SR_BSY_Pos);}

//polling mode (blocking)
void spi_transmit(spi_handle_t *const hspi, uint8_t *data, uint16_t size);
void spi_receive(spi_handle_t *const hspi, uint8_t *data, uint16_t size);

//interrupt driven mode (non-blocking)
void spi_transmit_it(spi_handle_t *const hspi, uint8_t *data, uint16_t size);
void spi_receive_it(spi_handle_t *const hspi, uint8_t *data, uint16_t size);
void spi_register_cb(spi_handle_t *const hspi, spi_callback_t cb);
