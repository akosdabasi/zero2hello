#include "usart_driver.h"

#define USART_ENABLE(pUSART)              SET_BIT(pUSART->CR1, USART_CR1_UE_Pos)
#define USART_ENABLE_RX(pUSART)           SET_BIT(pUSART->CR1, USART_CR1_TE_Pos)
#define USART_ENABLE_TX(pUSART)           SET_BIT(pUSART->CR1, USART_CR1_RE_Pos)
#define USART_ENABLE_RX_IT(pUSART)        SET_BIT(pUSART->CR1, USART_CR1_TXEIE_Pos)
#define USART_ENABLE_TX_IT(pUSART)        SET_BIT(pUSART->CR1, USART_CR1_RXNEIE_Pos)
#define USART_ENABLE_PE_IT(pUSART)        SET_BIT(pUSART->CR1, USART_CR1_PEIE_Pos)
#define USART_ENABLE_TCIE_IT(pUSART)      SET_BIT(pUSART->CR1, USART_CR1_TCIE_Pos)
#define USART_ENABLE_IDLEIE_IT(pUSART)    SET_BIT(pUSART->CR1, USART_CR1_IDLEIE_Pos)

#define USART_DISABLE(pUSART)              CLEAR_BIT(pUSART->CR1, USART_CR1_UE_Pos)
#define USART_DISABLE_RX(pUSART)           CLEAR_BIT(pUSART->CR1, USART_CR1_TE_Pos)
#define USART_DISABLE_TX(pUSART)           CLEAR_BIT(pUSART->CR1, USART_CR1_RE_Pos)
#define USART_DISABLE_RX_IT(pUSART)        CLEAR_BIT(pUSART->CR1, USART_CR1_TXEIE_Pos)
#define USART_DISABLE_TX_IT(pUSART)        CLEAR_BIT(pUSART->CR1, USART_CR1_RXNEIE_Pos)
#define USART_DISABLE_PE_IT(pUSART)        CLEAR_BIT(pUSART->CR1, USART_CR1_PEIE_Pos)
#define USART_DISABLE_TCIE_IT(pUSART)      CLEAR_BIT(pUSART->CR1, USART_CR1_TCIE_Pos)
#define USART_DISABLE_IDLEIE_IT(pUSART)    CLEAR_BIT(pUSART->CR1, USART_CR1_IDLEIE_Pos)

#define USART_GET_OVE(pUSART)       GET_BIT(pUSART->SR, USART_SR_OVE_Pos)
#define USART_GET_FE(pUSART)        GET_BIT(pUSART->SR, USART_SR_FE_Pos)
#define USART_GET_NE(pUSART)        GET_BIT(pUSART->SR, USART_SR_NE_Pos)
#define USART_GET_PE(pUSART)        GET_BIT(pUSART->SR, USART_SR_PE_Pos)
#define USART_GET_IDLE(pUSART)      GET_BIT(pUSART->SR, USART_SR_IDLE_Pos)
#define USART_GET_TXE(pUSART)       GET_BIT(pUSART->SR, USART_SR_TXE_Pos)
#define USART_GET_TC(pUSART)        GET_BIT(pUSART->SR, USART_SR_TC_Pos)
#define USART_GET_RXNE(pUSART)      GET_BIT(pUSART->SR, USART_SR_RXNE_Pos)
#define USART_GET_LBD(pUSART)       GET_BIT(pUSART->SR, USART_SR_LBD_Pos)
#define USART_GET_CTS(pUSART)       GET_BIT(pUSART->SR, USART_SR_CTS_Pos)

void usart_get_default_cfg(USART_Config_t *pCfg)
{
  if(!pCfg)return;

  pCfg->mode = USART_MODE_TX_RX;                  //enable both transmit and receive
  pCfg->data_length = USART_DATA_LENGTH_8;      
  pCfg->parity = USART_PARITY_NONE;     
  pCfg->stop_bits = USART_STOP_BITS_1;  
  pCfg->oversampl = USART_OVERSAMPLING_8;  
  pCfg->baudrate = USART_BAUDRATE_9600;            
  pCfg->hw_flow_ctrl = USART_HW_FLOWCTRL_NONE;    //no hardware flow control
  pCfg->wakeup = USART_WAKEUP_IDLE;
}

void usart_clk_enable(usart_handle_t *const husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;
  
  if(pUSART == USART1)
  {
    RCC_APB2ENR_USART1_CLK_ENABLE();
  }
  else if(pUSART == USART2)
  {
    RCC_APB1ENR_USART2_CLK_ENABLE();
  }
  else if(pUSART == USART3)
  {
    RCC_APB1ENR_USART3_CLK_ENABLE();
  }
  else
  {
    /*invalid instance*/
  }
}

void usart_clk_disable(usart_handle_t *const husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;
  
  if(pUSART == USART1)
  {
    RCC_APB2ENR_USART1_CLK_DISABLE();
  }
  else if(pUSART == USART2)
  {
    RCC_APB1ENR_USART2_CLK_DISABLE();
  }
  else if(pUSART == USART3)
  {
    RCC_APB1ENR_USART3_CLK_DISABLE();
  }
  else
  {
    /*invalid instance*/
  }
}

void usart_reset(usart_handle_t *const husart)
{
  if(!husart || !husart->instance)return;

  USART_t *pUSART = husart->instance;
  
  if(pUSART == USART1)
  {
    RCC_APB2RSTR_USART1_RESET();
  }
  else if(pUSART == USART2)
  {
    RCC_APB1RSTR_USART2_RESET();
  }
  else if(pUSART == USART3)
  {
    RCC_APB1RSTR_USART3_RESET();
  }
  else
  {
    /*invalid instance*/
  }
}

void usart_init(usart_handle_t *const husart)
{
  if(!husart || !husart->instance || !husart->cfg)return;

  USART_t *pUSART = husart->instance;
  USART_Config_t *pCfg = husart->cfg;
  usart_clk_enable(husart);

  EN_DIS_BIT(pUSART->CR1,USART_CR1_M_Pos,pCfg->data_length);
  EN_DIS_BIT(pUSART->CR1,USART_CR1_WAKE_Pos,pCfg->wakeup);
  //parity control
  state_t tmp = pCfg->parity > USART_PARITY_NONE ? enabled : disabled;
  EN_DIS_BIT(pUSART->CR1,USART_CR1_PCE_Pos,tmp);
  
  //parity
  tmp = pCfg->parity == USART_PARITY_ODD ? enabled : disabled;
  EN_DIS_BIT(pUSART->CR1,USART_CR1_PS_Pos,tmp);

  //stopbits
  CLEAR_BITFIELD(pUSART->CR2, USART_CR2_STOP_Msk);
  pUSART->CR2 |= (pCfg->stop_bits << USART_CR2_STOP_Pos);

  //todo hardware flow control 
  //todo synchronous mode
}
