/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "ADC.h"
#include "TMP_SENSOR.h"
/****************************************************************************/
volatile static BOOL_t ADC_Finished = FALSE;
static UINT32_t TMP_Reading;
/****************************************************************************/
void TMP_Sensor_Init(void){
	ADC_Init();
	ADC_Set_Prescaler(DF128);
	ADC_Interrupt(ENABLE);
	ADC(ENABLE);
	ADC_Conversion(START, TMP_SENSOR_CHANNEL);
}
/****************************************************************************/
UINT32_t TMP_Sensor_Read(void){
	return TMP_Reading;
}
/****************************************************************************/
void TMP_Sensor_Main(void){
	if(TRUE == ADC_Finished){
		TMP_Reading = ADC_Read();
		TMP_Reading = (((TMP_Reading * 5000) / 1024)) / 10;
		ADC_Conversion(START, TMP_SENSOR_CHANNEL);
		ADC_Finished = FALSE;
	}
}
/****************************************************************************/
ISR(ADC_VECT){
	ADC_Finished = TRUE;
}
/****************************************************************************/
