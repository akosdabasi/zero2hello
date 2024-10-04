#pragma once

/*
* file: this is a stripped version of the cmsis library file: core_cm3.h
* description: low level abastraction layer for Cortex M3 core and peripheral registers.
* contains: 
*     - peripheral configuration structures
*     - register bit masks and positions
*     - memory map base addresses
*     - peripheral configuration instances
*/

#include "utils.h"

/*******************************************************************************
*                 Register Abstraction
* Registers contain:
*  - Core Registers
*  - Core NVIC Registers
*  - Core SCB Registers
*  - Core SysTick Registers
 ******************************************************************************/

/*Start of Core Register Definitions*/

//Program Status Registers (xPSR).
typedef union
{
  struct
  {
    uint32_t ISR:9;                      /*!< bit:  0.. 8  Current exception number */
    uint32_t _reserved0:1;               /*!< bit:      9  Reserved */
    uint32_t ICI_IT_1:6;                 /*!< bit: 10..15  ICI/IT part 1 */
    uint32_t _reserved1:8;               /*!< bit: 16..23  Reserved */
    uint32_t T:1;                        /*!< bit:     24  Thumb bit */
    uint32_t ICI_IT_2:2;                 /*!< bit: 25..26  ICI/IT part 2 */
    uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
    uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
    uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
    uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
    uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} xPSR_t;

//xPSR register defintions
#define xPSR_N_Pos                         31U                                            
#define xPSR_N_Msk                         (1UL << xPSR_N_Pos)                            

#define xPSR_Z_Pos                         30U                                            
#define xPSR_Z_Msk                         (1UL << xPSR_Z_Pos)                            

#define xPSR_C_Pos                         29U                                            
#define xPSR_C_Msk                         (1UL << xPSR_C_Pos)                            

#define xPSR_V_Pos                         28U                                            
#define xPSR_V_Msk                         (1UL << xPSR_V_Pos)                            

#define xPSR_Q_Pos                         27U                                            
#define xPSR_Q_Msk                         (1UL << xPSR_Q_Pos)                            

#define xPSR_ICI_IT_2_Pos                  25U                                            
#define xPSR_ICI_IT_2_Msk                  (3UL << xPSR_ICI_IT_2_Pos)                     

#define xPSR_T_Pos                         24U                                            
#define xPSR_T_Msk                         (1UL << xPSR_T_Pos)                            

#define xPSR_ICI_IT_1_Pos                  10U                                            
#define xPSR_ICI_IT_1_Msk                  (0x3FUL << xPSR_ICI_IT_1_Pos)                  

#define xPSR_ISR_Pos                        0U                                            
#define xPSR_ISR_Msk                       (0x1FFUL << xPSR_ISR_Pos)                  


//Control Register (CONTROL).
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                    /*!< bit:      0  Execution privilege in Thread mode */
    uint32_t SPSEL:1;                    /*!< bit:      1  Stack to be used */
    uint32_t _reserved0:30;              /*!< bit:  2..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} CONTROL_t;

//CONTROL register defintions
#define CONTROL_SPSEL_Pos                   1U                                            
#define CONTROL_SPSEL_Msk                  (1UL << CONTROL_SPSEL_Pos)                     

#define CONTROL_nPRIV_Pos                   0U                                            
#define CONTROL_nPRIV_Msk                  (1UL << CONTROL_nPRIV_Pos)                 

#define SPSEL_MSP     0u   //use MSP as stack pointer
#define SPSEL_PSP     1u   //use PSP as stack pointer

#define NPRIV_PRIV    0u   //privileged access level
#define NPRIV_UNPRIV  1u   //unprivileged access level

/*End of Core Register Definitions */
/*Start of NVIC Register Definitions*/

typedef struct
{
  __IO uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  __IO uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RESERVED1[24U];
  __IO uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  __IO uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  __IO uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  __IO uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __O  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_t;

//Software Triggered Interrupt register definitions
#define NVIC_STIR_INTID_Pos                 0U                                         
#define NVIC_STIR_INTID_Msk                (0x1FFUL << NVIC_STIR_INTID_Pos)        

/*End of NVIC Register Definitions*/
/*Start of System Control Block register definiton*/

typedef struct
{
  __IO uint32_t ACTLR;                  /*!< Offset: 0x000 (R/W)  Auxiliary Control Register */
  __I  uint32_t CPUID;                  /*!< Offset: 0x004 (R/ )  CPUID Base Register */
  __IO uint32_t ICSR;                   /*!< Offset: 0x008 (R/W)  Interrupt Control and State Register */
  __IO uint32_t VTOR;                   /*!< Offset: 0x00C (R/W)  Vector Table Offset Register */
  __IO uint32_t AIRCR;                  /*!< Offset: 0x010 (R/W)  Application Interrupt and Reset Control Register */
  __IO uint32_t SCR;                    /*!< Offset: 0x014 (R/W)  System Control Register */
  __IO uint32_t CCR;                    /*!< Offset: 0x018 (R/W)  Configuration Control Register */
  __IO uint8_t  SHP[12U];               /*!< Offset: 0x024 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                  /*!< Offset: 0x028 (R/W)  System Handler Control and State Register */
  __IO uint32_t CFSR;                   /*!< Offset: 0x02C (R/W)  Configurable Fault Status Register */
  __IO uint32_t HFSR;                   /*!< Offset: 0x030 (R/W)  HardFault Status Register */
  __IO uint32_t DFSR;                   /*!< Offset: 0x034 (R/W)  Debug Fault Status Register */
  __IO uint32_t MMFAR;                  /*!< Offset: 0x038 (R/W)  MemManage Fault Address Register */
  __IO uint32_t BFAR;                   /*!< Offset: 0x03C (R/W)  BusFault Address Register */
  __IO uint32_t AFSR;                   /*!< Offset: 0x040 (R/W)  Auxiliary Fault Status Register */
} SCB_t;

/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_Pos          24U                                            
#define SCB_CPUID_IMPLEMENTER_Msk          (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)          

#define SCB_CPUID_VARIANT_Pos              20U                                            
#define SCB_CPUID_VARIANT_Msk              (0xFUL << SCB_CPUID_VARIANT_Pos)               

#define SCB_CPUID_ARCHITECTURE_Pos         16U                                            
#define SCB_CPUID_ARCHITECTURE_Msk         (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)          

#define SCB_CPUID_PARTNO_Pos                4U                                            
#define SCB_CPUID_PARTNO_Msk               (0xFFFUL << SCB_CPUID_PARTNO_Pos)              

#define SCB_CPUID_REVISION_Pos              0U                                            
#define SCB_CPUID_REVISION_Msk             (0xFUL << SCB_CPUID_REVISION_Pos)          

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_NMIPENDSET_Pos            31U                                            
#define SCB_ICSR_NMIPENDSET_Msk            (1UL << SCB_ICSR_NMIPENDSET_Pos)               

#define SCB_ICSR_PENDSVSET_Pos             28U                                            
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)                

#define SCB_ICSR_PENDSVCLR_Pos             27U                                            
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)                

#define SCB_ICSR_PENDSTSET_Pos             26U                                            
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                

#define SCB_ICSR_ISRPREEMPT_Pos            23U                                            
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)               

#define SCB_ICSR_ISRPENDING_Pos            22U                                            
#define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)               

#define SCB_ICSR_VECTPENDING_Pos           12U                                            
#define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)          

#define SCB_ICSR_RETTOBASE_Pos             11U                                            
#define SCB_ICSR_RETTOBASE_Msk             (1UL << SCB_ICSR_RETTOBASE_Pos)                

#define SCB_ICSR_VECTACTIVE_Pos             0U                                            
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL << SCB_ICSR_VECTACTIVE_Pos)       

/* SCB Vector Table Offset Register Definitions */
#define SCB_VTOR_TBLOFF_Pos                 7U                                            
#define SCB_VTOR_TBLOFF_Msk                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)           

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16U                                            
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            

#define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                            
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        

#define SCB_AIRCR_ENDIANESS_Pos            15U                                            
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)               

#define SCB_AIRCR_PRIGROUP_Pos              8U                                            
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                

#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                            
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)           

#define SCB_AIRCR_VECTRESET_Pos             0U                                           
#define SCB_AIRCR_VECTRESET_Msk            (1UL /<< SCB_AIRCR_VECTRESET_Pos)           

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_Pos               4U                                            
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               

/* SCB Configuration Control Register Definitions */
#define SCB_CCR_STKALIGN_Pos                9U                                            
#define SCB_CCR_STKALIGN_Msk               (1UL << SCB_CCR_STKALIGN_Pos)                  

#define SCB_CCR_BFHFNMIGN_Pos               8U                                            
#define SCB_CCR_BFHFNMIGN_Msk              (1UL << SCB_CCR_BFHFNMIGN_Pos)                 

#define SCB_CCR_DIV_0_TRP_Pos               4U                                            
#define SCB_CCR_DIV_0_TRP_Msk              (1UL << SCB_CCR_DIV_0_TRP_Pos)                 

#define SCB_CCR_UNALIGN_TRP_Pos             3U                                            
#define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)               

#define SCB_CCR_USERSETMPEND_Pos            1U                                            
#define SCB_CCR_USERSETMPEND_Msk           (1UL << SCB_CCR_USERSETMPEND_Pos)              

#define SCB_CCR_NONBASETHRDENA_Pos          0U                                            
#define SCB_CCR_NONBASETHRDENA_Msk         (1UL << SCB_CCR_NONBASETHRDENA_Pos)        

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_USGFAULTENA_Pos          18U                                            
#define SCB_SHCSR_USGFAULTENA_Msk          (1UL << SCB_SHCSR_USGFAULTENA_Pos)             

#define SCB_SHCSR_BUSFAULTENA_Pos          17U                                            
#define SCB_SHCSR_BUSFAULTENA_Msk          (1UL << SCB_SHCSR_BUSFAULTENA_Pos)             

#define SCB_SHCSR_MEMFAULTENA_Pos          16U                                            
#define SCB_SHCSR_MEMFAULTENA_Msk          (1UL << SCB_SHCSR_MEMFAULTENA_Pos)             

#define SCB_SHCSR_SVCALLPENDED_Pos         15U                                            
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)            

#define SCB_SHCSR_BUSFAULTPENDED_Pos       14U                                            
#define SCB_SHCSR_BUSFAULTPENDED_Msk       (1UL << SCB_SHCSR_BUSFAULTPENDED_Pos)          

#define SCB_SHCSR_MEMFAULTPENDED_Pos       13U                                            
#define SCB_SHCSR_MEMFAULTPENDED_Msk       (1UL << SCB_SHCSR_MEMFAULTPENDED_Pos)          

#define SCB_SHCSR_USGFAULTPENDED_Pos       12U                                            
#define SCB_SHCSR_USGFAULTPENDED_Msk       (1UL << SCB_SHCSR_USGFAULTPENDED_Pos)          

#define SCB_SHCSR_SYSTICKACT_Pos           11U                                            
#define SCB_SHCSR_SYSTICKACT_Msk           (1UL << SCB_SHCSR_SYSTICKACT_Pos)              

#define SCB_SHCSR_PENDSVACT_Pos            10U                                            
#define SCB_SHCSR_PENDSVACT_Msk            (1UL << SCB_SHCSR_PENDSVACT_Pos)               

#define SCB_SHCSR_MONITORACT_Pos            8U                                            
#define SCB_SHCSR_MONITORACT_Msk           (1UL << SCB_SHCSR_MONITORACT_Pos)              

#define SCB_SHCSR_SVCALLACT_Pos             7U                                            
#define SCB_SHCSR_SVCALLACT_Msk            (1UL << SCB_SHCSR_SVCALLACT_Pos)               

#define SCB_SHCSR_USGFAULTACT_Pos           3U                                            
#define SCB_SHCSR_USGFAULTACT_Msk          (1UL << SCB_SHCSR_USGFAULTACT_Pos)             

#define SCB_SHCSR_BUSFAULTACT_Pos           1U                                            
#define SCB_SHCSR_BUSFAULTACT_Msk          (1UL << SCB_SHCSR_BUSFAULTACT_Pos)             

#define SCB_SHCSR_MEMFAULTACT_Pos           0U                                            
#define SCB_SHCSR_MEMFAULTACT_Msk          (1UL << SCB_SHCSR_MEMFAULTACT_Pos)         

/* SCB Configurable Fault Status Register Definitions */
#define SCB_CFSR_USGFAULTSR_Pos            16U                                            
#define SCB_CFSR_USGFAULTSR_Msk            (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos)          

#define SCB_CFSR_BUSFAULTSR_Pos             8U                                            
#define SCB_CFSR_BUSFAULTSR_Msk            (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)            

#define SCB_CFSR_MEMFAULTSR_Pos             0U                                            
#define SCB_CFSR_MEMFAULTSR_Msk            (0xFFUL << SCB_CFSR_MEMFAULTSR_Pos)        

/* MemManage Fault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_MMARVALID_Pos             (SCB_CFSR_MEMFAULTSR_Pos + 7U)                 
#define SCB_CFSR_MMARVALID_Msk             (1UL << SCB_CFSR_MMARVALID_Pos)                

#define SCB_CFSR_MSTKERR_Pos               (SCB_CFSR_MEMFAULTSR_Pos + 4U)                 
#define SCB_CFSR_MSTKERR_Msk               (1UL << SCB_CFSR_MSTKERR_Pos)                  

#define SCB_CFSR_MUNSTKERR_Pos             (SCB_CFSR_MEMFAULTSR_Pos + 3U)                 
#define SCB_CFSR_MUNSTKERR_Msk             (1UL << SCB_CFSR_MUNSTKERR_Pos)                

#define SCB_CFSR_DACCVIOL_Pos              (SCB_CFSR_MEMFAULTSR_Pos + 1U)                 
#define SCB_CFSR_DACCVIOL_Msk              (1UL << SCB_CFSR_DACCVIOL_Pos)                 

#define SCB_CFSR_IACCVIOL_Pos              (SCB_CFSR_MEMFAULTSR_Pos + 0U)                 
#define SCB_CFSR_IACCVIOL_Msk              (1UL << SCB_CFSR_IACCVIOL_Pos)             

/* BusFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_BFARVALID_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 7U)                  
#define SCB_CFSR_BFARVALID_Msk            (1UL << SCB_CFSR_BFARVALID_Pos)                 

#define SCB_CFSR_STKERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 4U)                  
#define SCB_CFSR_STKERR_Msk               (1UL << SCB_CFSR_STKERR_Pos)                    

#define SCB_CFSR_UNSTKERR_Pos             (SCB_CFSR_BUSFAULTSR_Pos + 3U)                  
#define SCB_CFSR_UNSTKERR_Msk             (1UL << SCB_CFSR_UNSTKERR_Pos)                  

#define SCB_CFSR_IMPRECISERR_Pos          (SCB_CFSR_BUSFAULTSR_Pos + 2U)                  
#define SCB_CFSR_IMPRECISERR_Msk          (1UL << SCB_CFSR_IMPRECISERR_Pos)               

#define SCB_CFSR_PRECISERR_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 1U)                  
#define SCB_CFSR_PRECISERR_Msk            (1UL << SCB_CFSR_PRECISERR_Pos)                 

#define SCB_CFSR_IBUSERR_Pos              (SCB_CFSR_BUSFAULTSR_Pos + 0U)                  
#define SCB_CFSR_IBUSERR_Msk              (1UL << SCB_CFSR_IBUSERR_Pos)                   

/* UsageFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_DIVBYZERO_Pos            (SCB_CFSR_USGFAULTSR_Pos + 9U)                  
#define SCB_CFSR_DIVBYZERO_Msk            (1UL << SCB_CFSR_DIVBYZERO_Pos)                 

#define SCB_CFSR_UNALIGNED_Pos            (SCB_CFSR_USGFAULTSR_Pos + 8U)                  
#define SCB_CFSR_UNALIGNED_Msk            (1UL << SCB_CFSR_UNALIGNED_Pos)                 

#define SCB_CFSR_NOCP_Pos                 (SCB_CFSR_USGFAULTSR_Pos + 3U)                  
#define SCB_CFSR_NOCP_Msk                 (1UL << SCB_CFSR_NOCP_Pos)                      

#define SCB_CFSR_INVPC_Pos                (SCB_CFSR_USGFAULTSR_Pos + 2U)                  
#define SCB_CFSR_INVPC_Msk                (1UL << SCB_CFSR_INVPC_Pos)                     

#define SCB_CFSR_INVSTATE_Pos             (SCB_CFSR_USGFAULTSR_Pos + 1U)                  
#define SCB_CFSR_INVSTATE_Msk             (1UL << SCB_CFSR_INVSTATE_Pos)                  

#define SCB_CFSR_UNDEFINSTR_Pos           (SCB_CFSR_USGFAULTSR_Pos + 0U)                  
#define SCB_CFSR_UNDEFINSTR_Msk           (1UL << SCB_CFSR_UNDEFINSTR_Pos)                

/* SCB Hard Fault Status Register Definitions */
#define SCB_HFSR_DEBUGEVT_Pos              31U                                            
#define SCB_HFSR_DEBUGEVT_Msk              (1UL << SCB_HFSR_DEBUGEVT_Pos)                 

#define SCB_HFSR_FORCED_Pos                30U                                            
#define SCB_HFSR_FORCED_Msk                (1UL << SCB_HFSR_FORCED_Pos)                   

#define SCB_HFSR_VECTTBL_Pos                1U                                            
#define SCB_HFSR_VECTTBL_Msk               (1UL << SCB_HFSR_VECTTBL_Pos)                  

/* SCB Debug Fault Status Register Definitions */
#define SCB_DFSR_EXTERNAL_Pos               4U                                            
#define SCB_DFSR_EXTERNAL_Msk              (1UL << SCB_DFSR_EXTERNAL_Pos)                 

#define SCB_DFSR_VCATCH_Pos                 3U                                            
#define SCB_DFSR_VCATCH_Msk                (1UL << SCB_DFSR_VCATCH_Pos)                   

#define SCB_DFSR_DWTTRAP_Pos                2U                                            
#define SCB_DFSR_DWTTRAP_Msk               (1UL << SCB_DFSR_DWTTRAP_Pos)                  

#define SCB_DFSR_BKPT_Pos                   1U                                            
#define SCB_DFSR_BKPT_Msk                  (1UL << SCB_DFSR_BKPT_Pos)                     

#define SCB_DFSR_HALTED_Pos                 0U                                            
#define SCB_DFSR_HALTED_Msk                (1UL << SCB_DFSR_HALTED_Pos)               

/*End of System Control Block register definitions */
/*Start of System Timer(SysTick) register definitions*/
typedef struct
{
  __IO uint32_t CSR;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t RVR;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IO uint32_t CVR;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __I uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_t;

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            

#define SysTick_CTRL_TICKINT_Pos            1U                                            
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              

#define SysTick_CTRL_ENABLE_Pos             0U                                            
#define SysTick_CTRL_ENABLE_Msk            (1UL << SysTick_CTRL_ENABLE_Pos)           

/* SysTick Reload Value Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0U                                         
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL << SysTick_LOAD_RELOAD_Pos)    

/* SysTick Current Value Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0U                                         
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL << SysTick_VAL_CURRENT_Pos) 

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31U                                            
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               

#define SysTick_CALIB_SKEW_Pos             30U                                            
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                

#define SysTick_CALIB_TENMS_Pos             0U                                            
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL << SysTick_CALIB_TENMS_Pos)    

/*End of System Timer(SysTick) register definitions */


/*Memory mapping of core hadware*/
#define SCS_BASE            (0xE000E000u)                             /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010u)                     /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100u)                     /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0008u)                     /*!< System Control Block Base Address */


/*core peripheral instances*/
#define SCB                 ((SCB_t*)SCB_BASE)                      /*!< SCB configuration struct */
#define SysTick             ((SysTick_t*)SysTick_BASE)              /*!< SYSTCK configuration struct */
#define NVIC                ((NVIC_t*)NVIC_BASE)                    /*!< NVIC configuration struct */


/*Assembly instruction macros*/


// Macro for Instruction Synchronization Barrier (ISB)
#define __ISB() __asm volatile ("isb" : : : "memory")

// Macro for Data Synchronization Barrier (DSB)
#define __DSB() __asm volatile ("dsb" : : : "memory")

// Macro for Data Memory Barrier (DMB)
#define __DMB() __asm volatile ("dmb" : : : "memory")

// Macro for No Operation (NOP)
#define __NOP() __asm volatile ("nop")