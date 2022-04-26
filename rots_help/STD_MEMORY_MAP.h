/****************************************************************************/
#ifndef STD_MEMORY_MAP_H
#define STD_MEMORY_MAP_H

#include "STD_TYPES.h"
#include "STD_BITS.h"
/********************************* GPIO REGISTERS *******************************************/
#define PORTA (*(volatile UINT8_t* const)0x3B)
#define DDRA (*(volatile UINT8_t* const)0x3A)
#define PINA (*(volatile UINT8_t* const)0x39)

#define PORTB (*(volatile UINT8_t* const)0x38)
#define DDRB (*(volatile UINT8_t* const)0x37)
#define PINB (*(volatile UINT8_t* const)0x36)

#define PORTC (*(volatile UINT8_t* const)0x35)
#define DDRC (*(volatile UINT8_t* const)0x34)
#define PINC (*(volatile UINT8_t* const)0x33)

#define PORTD (*(volatile UINT8_t* const)0x32)
#define DDRD (*(volatile UINT8_t* const)0x31)
#define PIND (*(volatile UINT8_t* const)0x30)

#define PORTA_ADD ((volatile UINT8_t* const)0x3B)
#define DDRA_ADD ((volatile UINT8_t* const)0x3A)
#define PINA_ADD ((volatile UINT8_t* const)0x39)

#define PORTB_ADD ((volatile UINT8_t* const)0x38)
#define DDRB_ADD ((volatile UINT8_t* const)0x37)
#define PINB_ADD ((volatile UINT8_t* const)0x36)

#define PORTC_ADD ((volatile UINT8_t* const)0x35)
#define DDRC_ADD ((volatile UINT8_t* const)0x34)
#define PINC_ADD ((volatile UINT8_t* const)0x33)

#define PORTD_ADD ((volatile UINT8_t* const)0x32)
#define DDRD_ADD ((volatile UINT8_t* const)0x31)
#define PIND_ADD ((volatile UINT8_t* const)0x30)

/*********************************INTERRUPT**************************************/

#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)
#define reti()  __asm__ __volatile__ ("reti" ::)

#define ISR_NOBLOCK    __attribute__((interrupt))
#define ISR_NAKED      __attribute__((naked))

#define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)
/*********************************IVT**************************************/
#define INT0_VECT			__vector_1
#define INT1_VECT			__vector_2
#define INT2_VECT			__vector_3
#define ADC_VECT			__vector_16

#define TIMER0_COMP_VECT		__vector_10
#define TIMER0_OVF_VECT			__vector_11

#define URT_TX_OVF_VECT			__vector_15
#define URT_RX_OVF_VECT			__vector_13

#define SPI_VECT       			__vector_12
/********************************* EXINT REGISTERS **************************************/
#define MCUCSR   (*(volatile unsigned char*)0x54)
#define ISC2 6

#define MCUCR   (*(volatile unsigned char*)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR     (*(volatile unsigned char*)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR    (*(volatile unsigned char*)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5
/******************************** ADC REGISTERS ********************************************/
#define ADMUX (*(volatile unsigned char*)0x27)
#define ADCSRA (*(volatile unsigned char*)0x26)
#define ADCH (*(volatile unsigned char*)0x25)
#define ADCL (*(volatile unsigned char*)0x24)

/******************************** GLOBAL INTERRUPT REGISTERS ********************************************/
#define SREG (*(volatile unsigned char*)0x5f)
#define GIE SET_BIT(SREG, 7)
#define GIC CLEAR_BIT(SREG, 7)
/******************************** TMR0 REGISTERS ********************************************/
#define TCCR0 (*(volatile unsigned char*)0x53)
#define TCNT0 (*(volatile unsigned char*)0x52)
#define OCR0 (*(volatile unsigned char*)0x5c)
#define TIMSK (*(volatile unsigned char*)0x59)
/******************************** URT REGISTERS ********************************************/
#define UDR (*(volatile unsigned char*)0x2C)
#define UCSRA (*(volatile unsigned char*)0x2B)
#define UCSRB (*(volatile unsigned char*)0x2A)
#define UBRRL (*(volatile unsigned char*)0x29)
#define UCSRC (*(volatile unsigned char*)0x40)
#define UBRRH (*(volatile unsigned char*)0x40)
#define UBRRL (*(volatile unsigned char*)0x29)
/******************************** FLASH DATA REGISTERS ********************************************/
#define EEAR  (*(volatile UINT16_t*)0x3E)
#define EEDR   (*(volatile UINT8_t*)0x3D)
#define EECR   (*(volatile UINT8_t*)0x3C)


#define EEWE  1
#define EERE  0
#define EEMWE 2
/******************************** SPI REGISTERS ********************************************/
#define SPCR (*(volatile unsigned char*)0x2D)
#define SPSR (*(volatile unsigned char*)0x2E)
#define SPDR (*(volatile unsigned char*)0x2F)

#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

#define SPIF 7
#define WCOL 6
#define SPI2X 0
/******************************** WDT REGISTERS ********************************************/
#define WDTCR (*(volatile unsigned char*)0x41)
#define MCUCSR (*(volatile unsigned char*)0x54)
/****************************************************************************/
#endif
/****************************************************************************/
