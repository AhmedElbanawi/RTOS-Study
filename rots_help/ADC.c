/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "ADC.h"
/****************************************************************************/
void ADC(const MODE_t MODE) {
	switch (MODE) {
	case ENABLE:
		SET_BIT(ADCSRA, 7);
		break;
	case DISABLE:
		CLEAR_BIT(ADCSRA, 7);
		break;
	}
}
/****************************************************************************/
void ADC_Conversion(const CONV_MODE_t MODE, const ADC_CH_t ADC_CH) {
	ADMUX &= 0XF0;		/* Clear First 4 Bits */
	ADMUX |= ADC_CH;	/* Select Required Channel */
	switch (MODE) {
	case START:
		SET_BIT(ADCSRA, 6);
		break;
	case STOP:
		CLEAR_BIT(ADCSRA, 6);
		break;
	}
}
/****************************************************************************/
void ADC_Interrupt(const MODE_t MODE) {
	switch (MODE) {
	case ENABLE:
		SET_BIT(ADCSRA, 3);
		break;
	case DISABLE:
		CLEAR_BIT(ADCSRA, 3);
		break;
	}
}
/****************************************************************************/
void ADC_Set_Prescaler(const PRESCALER_t PRESCALER){
	ADCSRA &= 0XF8;
	ADCSRA |= PRESCALER;
}
/****************************************************************************/
BOOL_t ADC_Read_Flag(void){
	BOOL_t Flag = FALSE;
	if(GET_BIT(ADCSRA, 4)){
		Flag = TRUE;
	}
	return Flag;
}
/****************************************************************************/
void ADC_Clear_Flag(void){
	CLEAR_BIT(ADCSRA, 4);
}
/****************************************************************************/
void ADC_Init(void){
	SET_BIT(ADMUX, 6); /* External Vref +5 Volt */
}
/****************************************************************************/
UINT16_t ADC_Read(void){
	UINT16_t Reading = 0;
	Reading = ADCL;
    Reading = ((UINT16_t)(ADCH << 8)) | Reading;
    return Reading;
}
/****************************************************************************/
