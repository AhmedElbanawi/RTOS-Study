/****************************************************************************/
#ifndef TMR0_H
#define TMR0_H
/****************************************************************************/
typedef enum{
	TMR0_NO_CLK = 0,
	TMR0_DF1,
	TMR0_DF8,
	TMR0_DF64,
	TMR0_DF256,
	TMR0_DF1024,
	TMR0_EXT_CLK_FALLING_EDGE,
	TMR0_EXT_CLK_RISING_EDGE
}TMR0_PRESCALER_t;
/****************************************************************************/
typedef enum{
	TMR0_NORMAL = 0,
	TMR0_PWM,
	TMR0_CTC,
	TMR0_FAST_PWM
}TMR0_MODE_t;
/****************************************************************************/
typedef enum{
	TMR0_OV_INT_ENABLE = 0,
	TMR0_OV_INT_DISABLE,
	TMR0_OC_INT_ENABLE,
	TMR0_OC_INT_DISABLE
}TMR0_INT_t;
/****************************************************************************/
typedef enum{
	OC0_DISABLE = 0,
	OC0_TOGGLE, /* Only in Normal Mode, else is Reserved */
	OC0_CLEAR,
	OC0_SET
}TMR0_OC0_t;
/****************************************************************************/
typedef enum{
	TMR0_TCNTR = 0,
	TMR0_OCR
}TMR0_BFF_t;
/****************************************************************************/
void TMR0_Set_Prescaler(const TMR0_PRESCALER_t PRESCALER);
void TMR0_Mode(const TMR0_MODE_t MODE);
void TMR0_Init(void);
void TMR0_INT(const TMR0_INT_t INT);
void TMR0_OC0(const TMR0_OC0_t STATE);
void TMR0_Set_Buffer(const TMR0_BFF_t BUFFER, const UINT8_t VALUE);
UINT8_t TMR0_Read_Buffer(const TMR0_BFF_t BUFFER);
/****************************************************************************/
#endif
/****************************************************************************/

