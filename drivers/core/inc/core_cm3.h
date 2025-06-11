#pragma once

/*
* file: this is a stripped down version of the cmsis library file: core_cm3.h
* description: low level abastraction layer for Cortex M3 core and peripheral registers.
* contains: 
*     - core register definitions
*     - peripheral configuration structures
*     - register bit masks and positions
*     - memory map base addresses
*     - peripheral configuration instances
*/

#include "utils.h"

// constants
#define VECTKEY   0xFA05u

/*******************************************************************************
*                 Register Abstraction
* Registers contain:
*  - Core Registers: R0-R12, SP, LR, PC, PSR, PRIMASK, FAULTMASK, BASEPRIO, CONTROL
*  - Core NVIC Registers
*  - Core SCB Registers
*  - Core SysTick Registers
 ******************************************************************************/

/*Start of Core Register Definitions*/
/*
R0-R12: general purpose registers
SP: Stack Pointer (MSP or PSP)
LR: Link Register
  - function calls: stores the return address 
    1. BL --> branches to given address and stores next instruction in LR
    2. BX LR --> returns from function to the address in LR
  - exception handling: the CPU stores |R0-R3, R12, LR, PC, PSR| on stack and puts a special code in LR:
    0xFFFFFFF9: Return to thread mode using MSP
    0xFFFFFFFD: Return to thread mode using PSP
    0xFFFFFFF1: Return to handler mode
    1. Exception entry
    2. BX LR --> returns from ISR and the CPU will recognice the special code in LR and restore the execution context from the stack
PC: Program Counter
PRIMASK:    disable configurable priority exceptions
FAULTMASK:  disable all exceptions (excpet for NMI and HardFault)
BASEPRIO:   mask exceptions based on priority level
CONTROL: see below
PSR: see below
*/

//Program Status Registers (xPSR)
/*
It's 3 mutually exclusive registers in one: APSR(Application), IPSR(Interrupt), EPSR(Execution)
They can be accessed individually or together: PSR, IEPSR, APSR...
*/
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
//APSR: Application Program Status Register
//Negative: Just looks at the sign bit(31st bit), meaningless when working with unsigned numbers
#define xPSR_N_Pos                         31U                                            
#define xPSR_N_Msk                         (1UL << xPSR_N_Pos)                            

//Zero
#define xPSR_Z_Pos                         30U                                            
#define xPSR_Z_Msk                         (1UL << xPSR_Z_Pos)                            

//Carry: unsigned addition: result doesnt fit in 32bits
#define xPSR_C_Pos                         29U                                            
#define xPSR_C_Msk                         (1UL << xPSR_C_Pos)                            

//Overflow: signed addition: ++ = - or -- = +
#define xPSR_V_Pos                         28U                                            
#define xPSR_V_Msk                         (1UL << xPSR_V_Pos)                            

//Saturation: result of special instructions: SSAT, USAT
#define xPSR_Q_Pos                         27U                                            
#define xPSR_Q_Msk                         (1UL << xPSR_Q_Pos)                            

//EPSR: Execution Program Status Register
//Used by some special instructions
#define xPSR_ICI_IT_2_Pos                  25U                                            
#define xPSR_ICI_IT_2_Msk                  (3UL << xPSR_ICI_IT_2_Pos)                     

//Thumb bit: has to be 1. It is set when the PC register is loaded with a branch instruction: BX, BLX, BX LR, POP{PC}
//Thumb bit will be bit0 of the address we branch to, but bit 0 will be cleared before loading it to PC.
#define xPSR_T_Pos                         24U                                            
#define xPSR_T_Msk                         (1UL << xPSR_T_Pos)                            

#define xPSR_ICI_IT_1_Pos                  10U                                            
#define xPSR_ICI_IT_1_Msk                  (0x3FUL << xPSR_ICI_IT_1_Pos)                  

//Contains the current exception number. In thread mode it is set to 0.
#define xPSR_ISR_Pos                        0U                                            
#define xPSR_ISR_Msk                       (0x1FFUL << xPSR_ISR_Pos)                  


//Control Register (CONTROL)
/*
The processor can:
          - run in Thread mode or Handler mode.
          - use the Main Stack(MSP) or the Process Stack(PSP).
          - execute code in privileged or unprivileged mode. 

Handler mode: privileged with MSP
Thread mode: depends on nPRIV and SPSEL

Some registers and instructions are only accessible in privileged mode. 
*/
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
/*TODO: Some register definitions are missing*/

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

/* SCB CPUID Register Definitions - gives processor version information*/
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
/*
Can be used to pend: NMI, PendSV and SysTick 
Can be used to get information about active, pending and preempted exceptions
*/
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
/*
Can be used to set the priority grouping. (the rest is implementation defined)
Write is only valid with the correct VECTKEY and bit[0-1] set to 0. 
*/
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
/*
Can be used to control low-power modes. 
SEVONPEND: If set to 1, even disabled interrupts can wake up the processor from WFE
SLEEPDEEP: Controls if the processor uses sleep or deep sleep as its low power mode
SLEEPONEXIT: For interrupt-driven applications
*/
#define SCB_SCR_SEVONPEND_Pos               4U                                            
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               

/* SCB Configuration Control Register Definitions */
/*
Controls how the processor handles: divide by 0, unaligned access
Can enable unprivileged SW to access STIR 
TODO: understanding the rest 
*/
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
/*
Can be used to:
  - enable/disable system handlers (BusFault, UsageFault, MemManage)
  - check if system handlers are pending (BusFault, UsageFault, MemManage, SVCall)
  - check if system handlers are active (SysTick, PendSV, UsageFault, BusFault, MemManage)
  - check if debug monitor is active: debug monitor is an ISR that runs at debug events
*/
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
/*
Indicates the cause of MemManage, Usage and Bus-Faults
*/
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
#define SysTick_CSR_COUNTFLAG_Pos         16U                                            
#define SysTick_CSR_COUNTFLAG_Msk         (1UL << SysTick_CSR_COUNTFLAG_Pos)            

#define SysTick_CSR_CLKSOURCE_Pos          2U                                            
#define SysTick_CSR_CLKSOURCE_Msk         (1UL << SysTick_CSR_CLKSOURCE_Pos)            

#define SysTick_CSR_TICKINT_Pos            1U                                            
#define SysTick_CSR_TICKINT_Msk           (1UL << SysTick_CSR_TICKINT_Pos)              

#define SysTick_CSR_ENABLE_Pos             0U                                            
#define SysTick_CSR_ENABLE_Msk            (1UL << SysTick_CSR_ENABLE_Pos)           

/* SysTick Reload Value Register Definitions */
#define SysTick_RVR_RELOAD_Pos             0U                                         
#define SysTick_RVR_RELOAD_Msk            (0xFFFFFFUL << SysTick_RVR_RELOAD_Pos)    

/* SysTick Current Value Register Definitions */
#define SysTick_CVR_CURRENT_Pos             0U                                         
#define SysTick_CVR_CURRENT_Msk            (0xFFFFFFUL << SysTick_CVR_CURRENT_Pos) 

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
//isb: all subsequent instructions have to wait until previous instructions are executed
//dsb: ensures that memory writes are fully completed and visible before continuing with subsequent instructions
//dmb: ensures that previous memory accesses are observed before proceeding (not neccesarily completed)
//memory clobber: tells the compiler that the assembly instructions may affect memory

// No Operation (NOP): Does nothing, often used for timing or synchronization(consumes 1 instruction cycle).
#define __NOP() __asm volatile ("nop")

// Wait For Interrupt (WFI): Puts the processor in low-power mode until an interrupt occurs.
#define __WFI() __asm volatile ("wfi")

// Wait For Event (WFE): Waits for an event or interrupt to resume execution.
#define __WFE() __asm volatile ("wfe")

// Send Event (SEV): Sends an event signal, typically used to wake up cores waiting on WFE.
#define __SEV() __asm volatile ("sev")

// Instruction Synchronization Barrier (ISB): Flushes the pipeline, ensuring previous instructions are completed.
#define __ISB() __asm volatile ("isb" : : : "memory")

// Data Synchronization Barrier (DSB): Ensures memory operations are complete before continuing.
#define __DSB() __asm volatile ("dsb" : : : "memory")

// Data Memory Barrier (DMB): Ensures the correct ordering of memory accesses across the barrier.
#define __DMB() __asm volatile ("dmb" : : : "memory")

// Supervisor Call (SVC): Triggers a software interrupt (system call) with a specified value.
#define __SVC(value) __asm volatile ("svc %0" : : "I"(value))

// Break Point (BKPT): Inserts a breakpoint, useful for debugging.
#define __BKPT(value) __asm volatile ("bkpt %0" : : "I"(value))

// Branch to Link Register (BX LR): Explicitly returns from a subroutine by branching to the link register.
#define __BX_LR() __asm volatile ("bx lr")

// Yield (YIELD): Hints the processor to switch to another task or core.
#define __YIELD() __asm volatile ("yield")

// Enable Interrupts (CPSIE I): Enables all maskable interrupts. (clears the PRIMASK register)
#define __ENABLE_INTERRUPTS() __asm volatile ("cpsie i")

// Disable Interrupts (CPSID I): Disables all maskable interrupts. (sets the PRIMASK regsiter)
#define __DISABLE_INTERRUPTS() __asm volatile ("cpsid i")

// Enable Fault Handling (CPSIE F): Enables all exceptions except NMI and HardFault (clears the FAULTMASK register)
#define __ENABLE_FAULTS() __asm volatile ("cpsie f")

// Disable Fault Handling (CPSID F): Disables all exceptions except NMI and HardFault (sets the FAULTMASK register)
#define __DISABLE_FAULTS() __asm volatile ("cpsid f")

// Reverses byte order to switch between little-endien and big-endien
static inline uint32_t __reverse_byte_order(uint32_t value) 
{
    uint32_t result;
    __asm volatile ("rev %0, %1" : "=r"(result) : "r"(value));
    return result;
}

// Reverses byte order per word
static inline uint32_t __reverse_byte_order_w(uint32_t value) 
{
    uint32_t result;
    __asm volatile ("rev16 %0, %1" : "=r"(result) : "r"(value));
    return result;
}

static inline int32_t __reverse_byte_order_sh(int32_t value) 
{
    int32_t result;
    __asm volatile ("revsh %0, %1" : "=r"(result) : "r"(value));
    return result;
}

static inline uint32_t __reverse_bit_order(uint32_t value)
{
    uint32_t result;
    __asm volatile ("rbit %0, %1" : "=r"(result) : "r"(value));
    return result;
}

// Set Priority Mask (MSR PRIMASK): Disables all configurable exceptions.
static inline void __set_specreg_primask(uint32_t value) 
{
    __asm volatile ("msr primask, %0" : : "r"(value) : "memory");
}
// Get Priority Mask (MRS PRIMASK): Gets the current PRIMASK value to check if interrupts are masked.
static inline uint32_t __get_specreg_primask(void) 
{
    uint32_t result;
    __asm volatile ("mrs %0, primask" : "=r"(result));
    return result;
}

// Set Base Priority (MSR BASEPRI): Sets the base priority register to control exception priority.
static inline void __set_specreg_basepri(uint32_t value)
{
    __asm volatile ("msr basepri, %0" : : "r"(value) : "memory");
}
// Get Base Priority (MRS BASEPRI): Reads the current base priority value.
static inline uint32_t __get_specreg_basepri(void) 
{
    uint32_t result;
    __asm volatile ("mrs %0, basepri" : "=r"(result));
    return result;
}


// Set Fault Mask (MSR FAULTMASK): Disables all exceptions except NMI and HardFault.
static inline void __set_specreg_faultmask(uint32_t value) 
{
    __asm volatile ("msr faultmask, %0" : : "r"(value) : "memory");
}
// Get Fault Mask (MRS FAULTMASK): Reads the current fault mask value.
static inline uint32_t __get_specreg_faultmask(void) 
{
    uint32_t result;
    __asm volatile ("mrs %0, faultmask" : "=r"(result));
    return result;
}


// Set Control Register (MSR CONTROL): Sets the CONTROL register, which controls privilege level and stack mode.
static inline void __set_specreg_control(uint32_t value) {
  __asm volatile ("msr control, %0" : : "r"(value) : "memory");
}
// Get Control Register (MRS CONTROL): Reads the current CONTROL register value.
static inline uint32_t __get_specreg_control(void) 
{
    uint32_t result;
    __asm volatile ("mrs %0, control" : "=r"(result));
    return result;
}


// Set Process Stack Pointer (MSR PSP)
static inline __attribute__((always_inline)) void __set_specreg_psp(uint32_t value) 
{
    __asm volatile ("msr psp, %0" : : "r"(value) : "memory");
}
// Get Process Stack Pointer (MRS PSP)
static inline __attribute__((always_inline)) uint32_t __get_specreg_psp(void)
{
    uint32_t result;
    __asm volatile ("mrs %0, psp" : "=r"(result));
    return result;
}

// Set Main Stack Pointer (MSR MSP)
static inline __attribute__((always_inline)) void __set_specreg_msp(uint32_t value) 
{
    __asm volatile ("msr msp, %0" : : "r"(value) : "memory");
}
// Get Main Stack Pointer (MRS MSP)
static inline __attribute__((always_inline)) uint32_t __get_specreg_msp(void)
{
    uint32_t result;
    __asm volatile ("mrs %0, msp" : "=r"(result));
    return result;
}

// Functions to change the active Stack Pointer
static inline __attribute__((always_inline)) void __switch_to_psp(void) 
{
    __asm volatile (
        "mrs r0, control      \n" // Read CONTROL
        "orr r0, r0, #2       \n" // Set bit 1 (SPSEL = 1 → use PSP)
        "msr control, r0      \n" // Write back
        "isb                  \n" // Instruction sync barrier
        :
        :
        : "r0", "memory"
    );
}
static inline __attribute__((always_inline)) void __switch_to_msp(void) 
{
    __asm volatile (
        "mrs r0, control      \n"
        "bic r0, r0, #2       \n" // Clear bit 1 (SPSEL = 0 → use MSP)
        "msr control, r0      \n"
        "isb                  \n"
        :
        :
        : "r0", "memory"
    );
}