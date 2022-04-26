/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "QUEUE.h"
#include "KEYPAD_CFG.h"
#include "KEYPAD.h"
/****************************************************************************/
static CHAR_t KEYPAD_Arr[KEYPAD_MAX_NO_OF_BUFFERS];
static QUEUE_t KEYPAD_Queue;
/****************************************************************************/
void KEYPAD_Init(void)
{
	Cqueue(&KEYPAD_Queue, KEYPAD_Arr, KEYPAD_MAX_NO_OF_BUFFERS);
}
/****************************************************************************/
void KEYPAD_Main(void)
{
	UINT8_t BTN_Idx = 0;

	for (BTN_Idx = 0; BTN_Idx < MAX_NO_OF_PBTN; ++BTN_Idx) {
		switch (PBTN_Arr[BTN_Idx].State) {
		case PBTN_STATE_RELEASED:
			if (DIO_PIN_STATE_HIGH==DIO_READ_PIN_VALUE(PBTN_Arr[BTN_Idx].Pin_Id)) {
				PBTN_Arr[BTN_Idx].State = PBTN_STATE_PRESSED;
			}
			break;
		case PBTN_STATE_PRESSED:
			if (DIO_PIN_STATE_LOW==DIO_READ_PIN_VALUE(PBTN_Arr[BTN_Idx].Pin_Id)) {
				Enqueue(&KEYPAD_Queue,&PBTN_Arr[BTN_Idx].Symbole,QUEUE_OBJ_TYPE_SINT8);
				PBTN_Arr[BTN_Idx].State = PBTN_STATE_RELEASED;
				return;
			}
			break;
		default:
			break;
		}
	}
}
/****************************************************************************/
BOOL_t KEYPAD_Set_Request(CHAR_t*const Ret_Char)
{
	BOOL_t ret=FALSE;
	if(TRUE==Dequeue(&KEYPAD_Queue,Ret_Char,QUEUE_OBJ_TYPE_SINT8))
	{
		ret=TRUE;
	}
	return ret;
}
/****************************************************************************/

