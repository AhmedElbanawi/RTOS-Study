/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "DIO_CFG.h"
#include "KEYPAD_CFG.h"
/****************************************************************************/
PBTN_t PBTN_Arr[MAX_NO_OF_PBTN]={
		{ DIO_PINC0, PBTN_STATE_RELEASED, '0' },
		{ DIO_PINC1, PBTN_STATE_RELEASED, '1' },
		{ DIO_PINC2, PBTN_STATE_RELEASED, '2' },
		{ DIO_PINC3, PBTN_STATE_RELEASED, '3' },
		{ DIO_PINC4, PBTN_STATE_RELEASED, '4' },
		{ DIO_PINC5, PBTN_STATE_RELEASED, '5' },
		{ DIO_PINC6, PBTN_STATE_RELEASED, '6' },
		{ DIO_PINC7, PBTN_STATE_RELEASED, '7' },
		{ DIO_PINB0, PBTN_STATE_RELEASED, '8' },
		{ DIO_PINB1, PBTN_STATE_RELEASED, '9' }

};
/****************************************************************************/
