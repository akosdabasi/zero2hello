#pragma once

#include "mcu_peripherals.h"
#include "rcc_driver.h"

#define CRC_DEFAULT_POLY    0x0007u  //default crc polynomial

//events
typedef enum {
  SPI_EVENT_BYTE_RECEIVED = 0,
  SPI_EVENT_BYTE_SENT,
  SPI_EVENT_TRANS_COMPLETE,
  SPI_EVENT_OVR_ERR,
  SPI_EVENT_CRC_ERR
} spi_event_t;

//configuration enum definitions
//TODO: handling multi-master mode
typedef enum {
  SPI_MODE_SLAVE  = 0,
  SPI_MODE_MASTER = 1
} spi_mode_t;

//TODO: handling half-duplex, simplex communication modes
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

//TODO: handling 16bit datasize
typedef enum {
  SPI_DATASIZE_8BIT  = 0,
  SPI_DATASIZE_16BIT = 1
} spi_datasize_t;

typedef enum {
  SPI_NSS_HARD = 0,   // Hardware control of NSS pin
  SPI_NSS_SOFT = 1    // Software control of NSS pin
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

//spi configuration structure
typedef struct {
    spi_mode_t       mode;         // Master or slave mode
    spi_trans_mode_t trans_mode;   // Transmission mode
    state_t          crc;          // CRC enabled/disabled
    spi_cpol_t       polarity;     // Clock polarity
    spi_cpha_t       phase;        // Clock phase
    spi_bit_order_t  bit_order;    // Bit order (MSB or LSB)
    spi_datasize_t   datasize;     // Data size (8-bit or 16-bit)
    spi_baudrate_t   baudrate;     // Baud rate prescaler
    spi_nss_mode_t   nss;          // NSS management mode
} SPI_Config_t;

//forward declaration of spi_handle_t
struct spi_handle_t;

//callback function for interrupt processing
typedef void (*spi_callback_t)(struct spi_handle_t *const hspi, spi_event_t event); 

//spi handle structure definiton
typedef struct spi_handle_t {
    SPI_t *instance;      //pointer to the SPI peripheral (e.g., SPI1, SPI2)
    SPI_Config_t *cfg;    //configuration parameters
    /*interrupt handling*/
    uint8_t *tx_buffer;
    uint16_t tx_buffer_length;
    uint8_t *rx_buffer;
    uint16_t rx_buffer_length;
    uint16_t rx_bytes_left;
    spi_callback_t  cb;   //optional callback for interrupt handling
} spi_handle_t;

//global spi handlers
extern spi_handle_t hspi1;
extern spi_handle_t hspi2;
extern spi_handle_t hspi3;

//return the most common configuration
void spi_get_default_cfg(SPI_Config_t *pCfg);

//basic control functions
void spi_clk_enable(spi_handle_t *const hspi);
void spi_clk_disable(spi_handle_t *const hspi);
void spi_reset(spi_handle_t *const hspi);

//initialized SPI peripheral instance
//GPIO: gpio pins have to be configured seperately 
//AFIO: afio pins have to be configured if default pins need to be remapped
void spi_init(spi_handle_t *const hspi);

//set/reset ssi 
//master: set SSI to 1 to keep the SPI enabled 
//slave: replaces external ssn signal by setting SSI bit
static inline void spi_set_ssi(spi_handle_t *const hspi, uint8_t ssm){EN_DIS_BIT(hspi->instance->CR1, SPI_CR1_SSI_Pos, ssm);}

//enable/disable ss output (only in master mode)
//0: multimaster: ss used to notify if an other master is using the bus
//1: singlemaster: peripharel will automatically set NSS pin 
static inline void spi_set_ssoe(spi_handle_t *const hspi, uint8_t ssoe){EN_DIS_BIT(hspi->instance->CR2, SPI_CR2_SSOE_Pos, ssoe);}

//configure receive-only mode in full-duplex communication
static inline void spi_set_rxonly(spi_handle_t *const hspi, uint8_t rxonly){EN_DIS_BIT(hspi->instance->CR1, SPI_CR1_RXONLY_Pos, rxonly);}

//get busy status flag
static inline uint8_t spi_is_busy(spi_handle_t *const hspi){return (uint8_t)GET_BIT(hspi->instance->SR, SPI_SR_BSY_Pos);}

//polling mode (blocking)
//full-duplex
void spi_transcieve(spi_handle_t *const hspi, uint8_t *const data_tx, uint8_t *const data_rx, uint16_t length);

/*----------------- INTERRUPT HANDLING -----------------------*/
//interrupt driven mode (non-blocking)
void spi_nvic_enable_it(spi_handle_t *const hspi);
void spi_nvic_disable_it(spi_handle_t *const hspi);
void spi_transcieve_it(spi_handle_t *const hspi, uint8_t *const data_tx, uint8_t *const data_rx, uint16_t length);
void spi_register_cb(spi_handle_t *const hspi, spi_callback_t cb);
