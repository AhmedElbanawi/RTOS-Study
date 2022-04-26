/****************************************************************************/
#ifndef ADC_H
#define ADC_H
/****************************************************************************/
typedef enum{
	ADC_CH0 = 0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7
}ADC_CH_t;
/****************************************************************************/
typedef enum{
	ENABLE = 0,
	DISABLE
}MODE_t;
/****************************************************************************/
typedef enum{
	START = 0,
	STOP
}CONV_MODE_t;
/****************************************************************************/
typedef enum{
	DF2 = 1,
	DF4 = 2,
	DF8 = 3,
	DF16 = 4,
	DF32 = 5,
	DF64 = 6,
	DF128 = 7,
}PRESCALER_t;
/****************************************************************************/
void ADC_Init(void);
void ADC(const MODE_t MODE);
void ADC_Interrupt(const MODE_t MODE);
void ADC_Conversion(const CONV_MODE_t MODE, const ADC_CH_t ADC_CH);
UINT16_t ADC_Read(void);
void ADC_Set_Prescaler(const PRESCALER_t PRESCALER);
BOOL_t ADC_Read_Flag(void);
void ADC_Clear_Flag(void);
/****************************************************************************/
#endif
/****************************************************************************/
