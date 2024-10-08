#include "spi.driver.h"

//sets the most common configuration
void spi_get_default_cfg(SPI_Cfg_t *pCfg)
{
  pCfg->mode = SPI_MODE_MASTER;
  pCfg->phase = SPI_CPHA_LEAD_EDGE;
  pCfg->polarity = SPI_CPOL_LOW;
  pCfg->datasize = SPI_DATASIZE_8BIT;
  pCfg->bit_order = SPI_BIT_ORDER_MSB;
  pCfg->baudrate = SPI_BAUDRATE_DIV8;
}

void spi_clk_enable(spi_handle_t *const hspi)
{
  SPI_t *pSPI = hspi->instance;
  
  if(!pSPI)return;
  
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
  SPI_t *pSPI = hspi->instance;
  
  if(!pSPI)return;
  
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
void spi_port_reset(spi_handle_t *const hspi)
{
  SPI_t *pSPI = hspi->instance;
  
  if(!pSPI)return;
  
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

void spi_init(spi_handle_t *const hspi);

void spi_deinit(spi_handle_t *const hspi);


//polling mode (blocking)
void spi_transmit(spi_handle_t *const hspi, uint8_t *data, uint16_t size);
void spi_receive(spi_handle_t *const hspi, uint8_t *data, uint16_t size);

//interrupt driven mode (non-blocking)
void spi_transmit_it(spi_handle_t *const hspi, uint8_t *data, uint16_t size);
void spi_receive_it(spi_handle_t *const hspi, uint8_t *data, uint16_t size);
void spi_register_cb(spi_handle_t *const hspi, spi_callback_t cb);