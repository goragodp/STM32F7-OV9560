#ifndef __IRQ_PRI_H__
#define __IRQ_PRI_H__

// The UARTs have no FIFOs, so if they don't get serviced quickly then characters
// get dropped. The handling for each character only consumes about 0.5 usec
#define IRQ_PRI_UART            1
#define IRQ_SUBPRI_UART                     0

// Flash IRQ must be higher priority than interrupts of all those components
// that rely on the flash storage.
#define IRQ_PRI_FLASH           2
#define IRQ_SUBPRI_FLASH                    0

// DCMI Priority 
#define IRQ_PRI_DCMI            3
#define IRQ_SUBPRI_DCMI                     0

// DCMI DMA2_Stream1
#define IRQ_PRI_DMA21           4
#define IRQ_SUBPRI_DMA21                    0

// F7 JPEG encoder
#define IRQ_PRI_JPEG            5
#define IRQ_SUBPRI_JPEG                     0

// SDIO must be higher priority than DMA for SDIO DMA transfers to work.
#define IRQ_PRI_SDIO            5
#define IRQ_SUBPRI_SDIO                     0

// DMA should be higher priority than USB, since USB Mass Storage calls
// into the sdcard driver which waits for the DMA to complete.
#define IRQ_PRI_DMA             6
#define IRQ_SUBPRI_DMA                      0

#define IRQ_PRI_OTG_FS          7
#define IRQ_SUBPRI_OTG_FS                   0

#define IRQ_PRI_OTG_HS          7
#define IRQ_SUBPRI_OTG_HS                   0

#define IRQ_PRI_TIM3            7
#define IRQ_SUBPRI_TIM3                     0

#define IRQ_PRI_TIM4            7
#define IRQ_SUBPRI_TIM4                     0

#define IRQ_PRI_CAN             8
#define IRQ_SUBPRI_CAN                      0

// Interrupt priority for non-special timers.
#define IRQ_PRI_TIMX            14
#define IRQ_SUBPRI_TIMX                     0

#define IRQ_PRI_EXTINT          15
#define IRQ_SUBPRI_EXTINT                   0

// PENDSV should be at the lowst priority so that other interrupts complete
// before exception is raised.
#define IRQ_PRI_PENDSV          15
#define IRQ_SUBPRI_PENDSV                   0

#define IRQ_PRI_RTC_WKUP        15
#define IRQ_SUBPRI_RTC_WKUP                 0

#endif /*__IRQ_PRI_H__*/