#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "QUEUE.h"
#include "CO_SCH.h"
#include "KEYPAD_CFG.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "URT.h"
void DISP_Update(void)
{
	static LCD_COL_ID_t Curr_Col=COL1;
	static UINT8_t urt_mess_no=0;
	CHAR_t Curr_Char;
	LCD_MESSAGE_t Curr_Message;
	URT_MESSAGE_t URT_mess={ "ahmed" };
	if(TRUE==KEYPAD_Set_Request(&Curr_Char))
	{
		switch (Curr_Char) {
		case '0':
			Curr_Message.Message = "0";
			break;
		case '1':
			Curr_Message.Message = "1";
			break;
		case '2':
			Curr_Message.Message = "2";
			break;
		case '3':
			Curr_Message.Message = "3";
			break;
		case '4':
			Curr_Message.Message = "4";
			break;
		case '5':
			Curr_Message.Message = "5";
			break;
		case '6':
			Curr_Message.Message = "6";
			break;
		case '7':
			Curr_Message.Message = "7";
			break;
		case '8':
			Curr_Message.Message = "8";
			break;
		case '9':
			Curr_Message.Message = "9";
			break;
		default:
			break;
		}
		Curr_Message.Row=ROW1;
		Curr_Message.Col=Curr_Col;
		LCD_Set_Request(&Curr_Message);
		++Curr_Col;
		if(LCD_MAX_COLS==Curr_Col)
		{
			Curr_Col=COL1;
		}
	}


		switch (urt_mess_no) {
	case 0:
		URT_mess.Message = "ahmed ";
		if (TRUE == URT_Tx_Set_Request(&URT_mess)) {
			urt_mess_no = 1;
		}

		break;
	case 1:
		URT_mess.Message = "sayed ";
		if (TRUE == URT_Tx_Set_Request(&URT_mess)) {
			urt_mess_no = 2;
		}
		break;
	case 2:
		URT_mess.Message = "aelbanawi ";
		if (TRUE == URT_Tx_Set_Request(&URT_mess)) {
			urt_mess_no = 0;
		}
		break;
	default:
			break;
		}


}
int main(void)
{
	DIO_INIT();
	KEYPAD_Init();
	URT_Init();
	CO_SCH_Init();
	CO_SCH_Add_Task(KEYPAD_Main, 0, 100);
	CO_SCH_Add_Task(LCD_Main, 0, 20);
	CO_SCH_Add_Task(DISP_Update, 0, 10);
	CO_SCH_Add_Task(URT_Tx_Main, 0, 5);
	CO_SCH_Start();

	while(1)
	{
		CO_SCH_Dispatch_Tasks();
	}
}
