#include "nvic.h"
#include "spi_driver.h"
#include "utils.h"


#define SPI_ENABLE(pSPI)            SET_BIT(pSPI->CR1, SPI_CR1_SPE_Pos)
#define SPI_ENABLE_RX_IT(pSPI)      SET_BIT(pSPI->CR2, SPI_CR2_TXEIE_Pos)
#define SPI_ENABLE_TX_IT(pSPI)      SET_BIT(pSPI->CR2, SPI_CR2_RXNEIE_Pos)
#define SPI_ENABLE_ERR_IT(pSPI)     SET_BIT(pSPI->CR2, SPI_CR2_ERRIE_Pos)

#define SPI_DISABLE(pSPI)           CLEAR_BIT(pSPI->CR1, SPI_CR1_SPE_Pos)
#define SPI_DISABLE_TX_IT(pSPI)      CLEAR_BIT(pSPI->CR2, SPI_CR2_TXEIE_Pos)
#define SPI_DISABLE_RX_IT(pSPI)      CLEAR_BIT(pSPI->CR2, SPI_CR2_RXNEIE_Pos)
#define SPI_DISABLE_ERR_IT(pSPI)     CLEAR_BIT(pSPI->CR2, SPI_CR2_ERRIE_Pos)

#define SPI_GET_TXE(pSPI)   GET_BIT(pSPI->SR, SPI_SR_TXE_Pos)
#define SPI_GET_RXNE(pSPI)   GET_BIT(pSPI->SR, SPI_SR_RXNE_Pos)
#define SPI_GET_BSY(pSPI)   GET_BIT(pSPI->SR, SPI_SR_BSY_Pos)
#define SPI_GET_OVR(pSPI)   GET_BIT(pSPI->SR, SPI_SR_OVR_Pos)
#define SPI_GET_CRCERR(pSPI)   GET_BIT(pSPI->SR, SPI_SR_CRCERR_Pos)
#define SPI_GET_TXEIE(pSPI)   GET_BIT(pSPI->CR2, SPI_CR2_TXEIE_Pos)
#define SPI_GET_RXNEIE(pSPI)   GET_BIT(pSPI->CR2, SPI_CR2_RXNEIE_Pos)
#define SPI_GET_ERRIE(pSPI)   GET_BIT(pSPI->CR2, SPI_CR2_ERRIE_Pos)
#define SPI_GET_CRCEN(pSPI)   GET_BIT(pSPI->CR1, SPI_CR1_CRCEN_Pos)

//global spi config structures
SPI_Config_t spi1_cfg;
SPI_Config_t spi2_cfg;
SPI_Config_t spi3_cfg;
//global spi handlers
spi_handle_t hspi1 = { .instance = SPI1, .cfg = &spi1_cfg};
spi_handle_t hspi2 = { .instance = SPI2, .cfg = &spi2_cfg};
spi_handle_t hspi3 = { .instance = SPI3, .cfg = &spi3_cfg};

//resets the crc counters
static void spi_reset_crc(SPI_t *const pSPI)
{
  if(!pSPI)return;

  SPI_DISABLE(pSPI);
  CLEAR_BIT(pSPI->CR1, SPI_CR1_CRCEN_Pos);
  SET_BIT(pSPI->CR1, SPI_CR1_CRCEN_Pos);
  SPI_ENABLE(pSPI);
}

//sets the most common configuration
void spi_get_default_cfg(SPI_Config_t *pCfg)
{
  if(!pCfg)return;

  pCfg->mode = SPI_MODE_MASTER;
  pCfg->trans_mode = SPI_TRANS_MODE_FULLDUPLEX;
  pCfg->crc = disabled;
  pCfg->phase = SPI_CPHA_LEAD_EDGE;
  pCfg->polarity = SPI_CPOL_LOW;
  pCfg->datasize = SPI_DATASIZE_8BIT;
  pCfg->bit_order = SPI_BIT_ORDER_MSB;
  pCfg->baudrate = SPI_BAUDRATE_DIV32;
  pCfg->nss = SPI_NSS_HARD;
}

void spi_clk_enable(spi_handle_t *const hspi)
{
  if(!hspi || !hspi->instance)return;

  SPI_t *pSPI = hspi->instance;
  
  if(pSPI == SPI1)
  {
    RCC_APB2ENR_SPI1_CLK_ENABLE();
  }
  else if(pSPI == SPI2)
  {
    RCC_APB1ENR_SPI2_CLK_ENABLE();
  }
  else if(pSPI == SPI3)
  {
    RCC_APB1ENR_SPI3_CLK_ENABLE();
  }
  else
  {
    /*invalid instance*/
  }
}

void spi_clk_disable(spi_handle_t *const hspi)
{
  if(!hspi || !hspi->instance)return;

  SPI_t *pSPI = hspi->instance;
  
  if(pSPI == SPI1)
  {
    RCC_APB2ENR_SPI1_CLK_DISABLE();
  }
  else if(pSPI == SPI2)
  {
    RCC_APB1ENR_SPI2_CLK_DISABLE();
  }
  else if(pSPI == SPI3)
  {
    RCC_APB1ENR_SPI3_CLK_DISABLE();
  }
  else
  {
    /*invalid instance*/
  }
}

void spi_reset(spi_handle_t *const hspi)
{
  if(!hspi || !hspi->instance)return;

  SPI_t *pSPI = hspi->instance;
  
  if(pSPI == SPI1)
  {
    RCC_APB2RSTR_SPI1_RESET();
  }
  else if(pSPI == SPI2)
  {
    RCC_APB1RSTR_SPI2_RESET();
  }
  else if(pSPI == SPI3)
  {
    RCC_APB1RSTR_SPI3_RESET();
  }
  else
  {
    /*invalid instance*/
  }
}

void spi_init(spi_handle_t *const hspi)
{

  if(!hspi || !hspi->instance || !hspi->cfg)return;

  //enable SPI peripheral clock
  spi_clk_enable(hspi);

  //configuration of SPI instance 
  SPI_t *pSPI = hspi->instance;
  SPI_Config_t* pCfg = hspi->cfg;
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_MSTR_Pos, pCfg->mode);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_BIDIMODE_Pos, pCfg->trans_mode);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_CRCEN_Pos, pCfg->crc);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_LSBFIRST_Pos, pCfg->bit_order);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_SSM_Pos, pCfg->nss);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_DFF_Pos, pCfg->datasize);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_CPOL_Pos, pCfg->polarity);
  EN_DIS_BIT(pSPI->CR1, SPI_CR1_CPHA_Pos, pCfg->phase);

  //set baudrate
  CLEAR_BITFIELD(pSPI->CR1, SPI_CR1_BR_Msk);
  pSPI->CR1 |= ((pCfg->baudrate << SPI_CR1_BR_Pos) & SPI_CR1_BR_Msk);
}


//polling mode (blocking)
//full-duplex
void spi_transcieve(spi_handle_t *const hspi, uint8_t *const data_tx, uint8_t *const data_rx, uint16_t length)
{
  //error checking
  if(!hspi || !hspi->instance || !hspi->cfg || !data_tx || !data_rx)return;
  SPI_t *const pSPI = hspi->instance;

  //reset crc counters
  if(SPI_GET_CRCEN(pSPI))
  {
    spi_reset_crc(pSPI);
  }

  SPI_ENABLE(pSPI);

  //next byte to send
  uint16_t byte_idx_tx = 0;

  //next byte to receive
  uint16_t byte_idx_rx = 0;

  //write first byte to Tx buffer to initiate transmission
  pSPI->DR = data_tx[byte_idx_tx++];

  while(byte_idx_tx < length)
  {
    //wait until Tx buffer is empty again and load the next byte
    while(!SPI_GET_TXE(pSPI));
    pSPI->DR = data_tx[byte_idx_tx++];

    //wait until Rx buffer is not empty and read the received byte
    while(!SPI_GET_RXNE(pSPI));
    data_rx[byte_idx_rx++] = (uint8_t)pSPI->DR;
  }
  
  //after last tx byte was loaded, indicate that the next byte to send is the CRC checksum
  if(SPI_GET_CRCEN(pSPI))
  {
    SET_BIT(pSPI->CR1, SPI_CR1_CRCNEXT_Pos);
  }

  //get the last byte
  while(!SPI_GET_RXNE(pSPI));
  data_rx[byte_idx_rx++] = (uint8_t)pSPI->DR;

  while(!SPI_GET_TXE(pSPI));
  while(SPI_GET_BSY(pSPI));

  SPI_DISABLE(pSPI);
}


//interrupt mode (non-blocking)
void spi_nvic_enable_it(spi_handle_t *const hspi)
{
  if(hspi == &hspi1)
  {
    __NVIC_EnableIRQ(SPI1_IRQn);
  }
  else if(hspi == &hspi2)
  {
    __NVIC_EnableIRQ(SPI2_IRQn);
  }
  if(hspi == &hspi3)
  {
    __NVIC_EnableIRQ(SPI3_IRQn);
  }
}

void spi_nvic_disable_it(spi_handle_t *const hspi)
{
  if(hspi == &hspi1)
  {
    __NVIC_DisableIRQ(SPI1_IRQn);
  }
  else if(hspi == &hspi2)
  {
    __NVIC_DisableIRQ(SPI2_IRQn);
  }
  if(hspi == &hspi3)
  {
    __NVIC_DisableIRQ(SPI3_IRQn);
  }
}

void spi_transcieve_it(spi_handle_t *const hspi, uint8_t *const data_tx, uint8_t *const data_rx, uint16_t length)
{
  //if one of the pointers is a null pointer then return
  if(!hspi || !hspi->instance || !data_tx || !data_rx )return;
  SPI_t *const pSPI = hspi->instance;

  //if previous transmission is not finished then return
  if(hspi->rx_bytes_left || hspi->tx_buffer_length)return;

  //set handle members
  hspi->tx_buffer = data_tx;
  hspi->tx_buffer_length = length;
  hspi->rx_buffer = data_rx;
  hspi->rx_buffer_length = 0;
  hspi->rx_bytes_left = SPI_GET_CRCEN(pSPI) ? length+1 : length; 

  //reset crc
  if(SPI_GET_CRCEN(pSPI))
  {
    spi_reset_crc(pSPI);
  }

  //enable interrupts in NVIC
  spi_nvic_enable_it(hspi);

  //enable peripheral
  SPI_ENABLE(pSPI);

  //enable interrupts
  SPI_ENABLE_RX_IT(pSPI);
  SPI_ENABLE_TX_IT(pSPI);
  SPI_ENABLE_ERR_IT(pSPI);
}

void spi_register_cb(spi_handle_t *const hspi, spi_callback_t cb)
{
  if(!hspi || !cb)return;

  hspi->cb = cb;
}

static inline void spi_handle_txe_it(spi_handle_t *const hspi)
{
  SPI_t *pSPI = hspi->instance;
  if(hspi->tx_buffer_length > 0)
  {
    //write the next byte to Tx buffer
    pSPI->DR = *hspi->tx_buffer++;
    hspi->tx_buffer_length--;
    
    //if it was the last one, prepare the crc value
    if(SPI_GET_CRCEN(pSPI) && !hspi->tx_buffer_length)
    {
      SET_BIT(pSPI->CR1, SPI_CR1_CRCNEXT_Pos);
    }

    //call event handler if it's registered
    if(hspi->cb)
    {
      hspi->cb(hspi, SPI_EVENT_BYTE_SENT);
    }
  }
  else
  {
    //end of transmission
    hspi->tx_buffer = NULL;
    SPI_DISABLE_TX_IT(pSPI);
  }
}

static inline void spi_handle_rxne_it(spi_handle_t *const hspi)
{
  SPI_t *pSPI = hspi->instance;
    
  //get the arrived data
  hspi->rx_buffer[hspi->rx_buffer_length++] = (uint8_t)pSPI->DR;
  hspi->rx_bytes_left--;

  if(hspi->rx_bytes_left > 0)
  { 
    //call user callback with received data
    hspi->cb(hspi, SPI_EVENT_BYTE_RECEIVED);
  }
  else
  {
    //end reception
    SPI_DISABLE_RX_IT(pSPI);

    //call user callback with received data
    hspi->cb(hspi, SPI_EVENT_TRANS_COMPLETE);

    //reset rx buffer
    hspi->rx_buffer = NULL;
    hspi->rx_buffer_length = 0;
  }
}

static inline void SPIx_IRQHandler(spi_handle_t *const hspi)
{
  if(!hspi || !hspi->instance)return;

  SPI_t *pSPI = hspi->instance;

  if(SPI_GET_TXE(pSPI) && SPI_GET_TXEIE(pSPI))
  {
    spi_handle_txe_it(hspi);
  }

  if(SPI_GET_RXNE(pSPI) && SPI_GET_RXNEIE(pSPI))
  {
    spi_handle_rxne_it(hspi);
  }

  if(SPI_GET_OVR(pSPI) && SPI_GET_ERRIE(pSPI))
  {

    //call user callback with received data
    hspi->cb(hspi, SPI_EVENT_OVR_ERR);
    
    //clear flag
    uint8_t dummy = (uint8_t)pSPI->DR;
    dummy = (uint8_t)pSPI->SR;
    (void)dummy;
  }

  if(SPI_GET_CRCERR(pSPI) && SPI_GET_ERRIE(pSPI))
  {
    //call user callback with received data
    hspi->cb(hspi, SPI_EVENT_CRC_ERR);

    //clear flag
    CLEAR_BIT(pSPI->SR, SPI_SR_CRCERR_Pos);
  }
  
}

void SPI1_IRQHandler(void)
{
  SPIx_IRQHandler(&hspi1);
}

void SPI2_IRQHandler(void)
{
  SPIx_IRQHandler(&hspi2);
}

void SPI3_IRQHandler(void)
{
  SPIx_IRQHandler(&hspi3);
}