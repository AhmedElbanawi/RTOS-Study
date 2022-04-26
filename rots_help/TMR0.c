/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "TMR0.h"
/****************************************************************************/
void TMR0_Set_Prescaler(const TMR0_PRESCALER_t PRESCALER){
	TCCR0 &= 0XF8;
	TCCR0 |= PRESCALER;
}
/****************************************************************************/
void TMR0_Mode(const TMR0_MODE_t MODE){
	switch (MODE) {
	case TMR0_NORMAL:
		CLEAR_BIT(TCCR0, 3);
		CLEAR_BIT(TCCR0, 6);
		break;
	case TMR0_PWM:
		SET_BIT(TCCR0, 6);
		CLEAR_BIT(TCCR0, 3);
		break;
	case TMR0_CTC:
		SET_BIT(TCCR0, 3);
		CLEAR_BIT(TCCR0, 6);
		break;
	case TMR0_FAST_PWM:
		SET_BIT(TCCR0, 3);
		SET_BIT(TCCR0, 6);
		break;
	}
}
/****************************************************************************/
void TMR0_Init(void){
	TMR0_Set_Buffer(TMR0_TCNTR, 0);
	TMR0_Set_Buffer(TMR0_OCR, 0);
}
/****************************************************************************/
void TMR0_INT(const TMR0_INT_t INT){
	switch(INT){
	case TMR0_OV_INT_ENABLE:
		SET_BIT(TIMSK, 0);
		break;
	case TMR0_OV_INT_DISABLE:
		CLEAR_BIT(TIMSK, 0);
		break;
	case TMR0_OC_INT_ENABLE:
		SET_BIT(TIMSK, 1);
		break;
	case TMR0_OC_INT_DISABLE:
		CLEAR_BIT(TIMSK, 1);
		break;
	}
}
/****************************************************************************/
void TMR0_OC0(const TMR0_OC0_t STATE){
	CLEAR_BIT(TCCR0, 4);
	CLEAR_BIT(TCCR0, 5);
	TCCR0 |= (STATE << 4);
}
/****************************************************************************/
void TMR0_Set_Buffer(const TMR0_BFF_t BUFFER, const UINT8_t VALUE){
	switch (BUFFER) {
	case TMR0_TCNTR:
		TCNT0 = VALUE;
		break;
	case TMR0_OCR:
		OCR0 = VALUE;
		break;
	default:
		break;

	}
}
/****************************************************************************/
UINT8_t TMR0_Read_Buffer(const TMR0_BFF_t BUFFER){
	UINT8_t Buffer = 0;
	switch (BUFFER) {
		case TMR0_TCNTR:
			Buffer = TCNT0;
			break;
		case TMR0_OCR:
			Buffer = OCR0;
			break;
		default:
			break;
		}
	return Buffer;
}
/****************************************************************************/
