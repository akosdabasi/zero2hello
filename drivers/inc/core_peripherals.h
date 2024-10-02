#pragma once

#include "utils.h"


/*core peripheral structure definitions*/
typedef struct
{
  __vo uint32_t CSR;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __vo uint32_t RVR;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __vo uint32_t CVR;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __vo uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_t;

typedef struct
{
  __vo uint32_t ISER[16U];              /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[16U];
  __vo uint32_t ICER[16U];              /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[16U];
  __vo uint32_t ISPR[16U];              /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[16U];
  __vo uint32_t ICPR[16U];              /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[16U];
  __vo uint32_t IABR[16U];              /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[16U];
  __vo uint32_t ITNS[16U];              /*!< Offset: 0x280 (R/W)  Interrupt Non-Secure State Register */
        uint32_t RESERVED5[16U];
  __vo uint32_t IPR[124U];              /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
}  NVIC_t;


/*core peripheral bit definitions*/


/*core peripheral base addresses*/

#define SCS_BASE            (0xE000E000u)                             /*!< System Control Space Base Address */
#define DWT_BASE            (0xE0001000u)                             /*!< DWT Base Address */
#define TPI_BASE            (0xE0040000u)                             /*!< TPI Base Address */
#define CoreDebug_BASE      (0xE000EDF0u)                             /*!< Core Debug Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010u)                     /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100u)                     /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00u)                     /*!< System Control Block Base Address */



/*core peripheral instances*/

#define SYSTICK             ((SysTick_t*)SysTick_BASE)              /*!< SYSTCK configuration struct */
#define NVIC                ((NVIC_t*)NVIC_BASE)                    /*!< NVIC configuration struct */

