/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "DIO_CFG.h"
#include "DIO.h"
#include "QUEUE.h"
#include "LCD.h"
/****************************************************************************/
#define STILL 0
#define ENDED 1
/****************************************************************************/
/* Used To Clear LCD When Send 0X00 */
static BOOL_t LCD_Send_Command(const UINT8_t CMD);
static BOOL_t LCD_Write_Char(const UINT8_t Character);
static BOOL_t LCD_Jumb_To(const LCD_ROW_ID_t ROW, const LCD_COL_ID_t COL);
/****************************************************************************/
static UINT8_t Configuration_Process = STILL;
static UINT8_t Address_Counter;

static LCD_MESSAGE_t LCD_Messages[LCD_MAX_NO_OF_MESSAGES];
static QUEUE_t LCD_Queue;
/****************************************************************************/
BOOL_t LCD_Init(void) {
	static UINT8_t Cnt=0;
	BOOL_t IsFinished=FALSE;
	switch(Cnt){
	case 0:
		/*Create queue*/
		Cqueue(&LCD_Queue, LCD_Messages, LCD_MAX_NO_OF_MESSAGES);

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH); // E should be high
		DIO_WRITE_PIN_VALUE(RW_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  R/W
		DIO_WRITE_PIN_VALUE(RS_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  RS
		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  D7

		Cnt=1;
		break;
	case 1:
		Cnt=2;
		break;
	case 2:
		Cnt=3;
		break;
	case 3:
		Cnt=4;
		break;
	case 4:
		if(TRUE==LCD_Send_Command(0X20)){
			Cnt=5;
		}
		break;
	case 5:
		if (TRUE == LCD_Send_Command(0X20)) {
			Cnt = 6;
		}
		break;
	case 6:
		if (TRUE == LCD_Send_Command(0X80)) {
			Cnt = 7;
		}
		break;
	case 7:
		if (TRUE == LCD_Send_Command(0X00)) {
			Cnt = 8;
		}
		break;
	case 8:
		if (TRUE == LCD_Send_Command(0XC0)) {
			Cnt = 9;
		}
		break;
	case 9:
		if (TRUE == LCD_Send_Command(0X00)) {
			Cnt = 10;
		}
		break;
	case 10:
		if (TRUE == LCD_Send_Command(0X10)) {
			Cnt = 11;
		}
		break;
	default:
		Configuration_Process = ENDED;
		Cnt = 0;
		IsFinished = TRUE;
		break;
	}

	return IsFinished;
}
/****************************************************************************/
BOOL_t LCD_Send_Command(const UINT8_t CMD) {

	static LCD_WR_OP_t Write_Operation_State = LCD_IDLE;
	BOOL_t IsFinished = FALSE;
	++Write_Operation_State;
	switch (Write_Operation_State) {
	case LCD_IDLE:
		break;
	case LCD_WR_4MSB:
		// Write operation
		DIO_WRITE_PIN_VALUE(RW_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  R/W
		// Command Mode
		DIO_WRITE_PIN_VALUE(RS_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  RS

		// SEND MSB
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E

		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(CMD, 4));   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(CMD, 5));   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(CMD, 6));   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(CMD, 7));   //  D7

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E
		break;
	case LCD_WR_4LSB:
		/* Latch data */
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E

		if (Configuration_Process == ENDED) {
			// SEND LSB
			DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(CMD, 0));   //  D4
			DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(CMD, 1));   //  D5
			DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(CMD, 2));   //  D6
			DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(CMD, 3));   //  D7

			DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E

			//_delay_ms(10);
		}
		break;
	case LCD_DELAY_BETWEEN_WRITINGS:
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		break;
	case LCD_WR_FINISHED:
		Write_Operation_State = LCD_IDLE;
		IsFinished = TRUE;
		break;
	default:
		break;

	}

	return IsFinished;
}
/****************************************************************************/
BOOL_t LCD_Jumb_To(const LCD_ROW_ID_t ROW, const LCD_COL_ID_t COL)
{
	BOOL_t IsFinished=FALSE;
	/*
	 First Row Start from 0X00
	 Second Row Start From 0X40
	 */
	if (ROW < LCD_MAX_ROWS && COL < LCD_MAX_COLS) {
		Address_Counter = ((0X40 * ROW) + COL) | (1 << 7); // To Write into DDRAM;
		IsFinished=LCD_Send_Command(Address_Counter);
	}
	return IsFinished;
}
/****************************************************************************/
BOOL_t LCD_Write_Char(const UINT8_t Character) {
	static LCD_WR_OP_t Write_Operation_State=LCD_IDLE;
	BOOL_t IsFinished=FALSE;
	++Write_Operation_State;
	switch (Write_Operation_State) {
	case LCD_IDLE:
		break;
	case LCD_WR_4MSB:
		// Write operation
		DIO_WRITE_PIN_VALUE(RW_PIN_NUMBER, DIO_PIN_STATE_LOW);     //  R/W
		// Data Mode
		DIO_WRITE_PIN_VALUE(RS_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //   RS

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		// SEND MSB
		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(Character, 4));   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(Character, 5));   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(Character, 6));   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(Character, 7));   //  D7
		/* Latch data */
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E
		break;
	case LCD_WR_4LSB:
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		// SEN LSB
		DIO_WRITE_PIN_VALUE(D4_PIN_NUMBER, GET_BIT(Character, 0));   //  D4
		DIO_WRITE_PIN_VALUE(D5_PIN_NUMBER, GET_BIT(Character, 1));   //  D5
		DIO_WRITE_PIN_VALUE(D6_PIN_NUMBER, GET_BIT(Character, 2));   //  D6
		DIO_WRITE_PIN_VALUE(D7_PIN_NUMBER, GET_BIT(Character, 3));   //  D7

		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_LOW);   //  E
		break;
	case LCD_DELAY_BETWEEN_WRITINGS:
		DIO_WRITE_PIN_VALUE(E_PIN_NUMBER, DIO_PIN_STATE_HIGH);   //  E
		break;
	case LCD_WR_FINISHED:
		Write_Operation_State = LCD_IDLE;
		IsFinished = TRUE;
		break;
	default:
		break;

	}

	return IsFinished;
}
/****************************************************************************/
BOOL_t LCD_Clear(void){
	BOOL_t IsFinished = FALSE;
	static UINT8_t Cnt = 0;
	switch (Cnt) {
	case 0:
		if (TRUE == LCD_Send_Command(0x00)) {
			Cnt = 1;
		}
		break;
	case 1:
		if (TRUE == LCD_Send_Command(0x01)) {
			Cnt = 2;
		}
		break;
	default:
		Cnt = 0;
		IsFinished = TRUE;
		break;
	}
	return IsFinished;
}
/****************************************************************************/
void LCD_Main(void){
	static LCD_STATE_t State=LCD_STATE_INIT;
	static UINT8_t Idx=0;
	static LCD_MESSAGE_t MyMessage;
	switch (State) {
	case LCD_STATE_INIT:
		if(TRUE==LCD_Init()){
			State=LCD_STATE_DEQUEUE_DATA;
		}
		break;
	case LCD_STATE_DEQUEUE_DATA:
		if(TRUE==Dequeue(&LCD_Queue, &MyMessage, QUEUE_OBJ_TYPE_LCD_MESSAGE))
		{
			Idx=0;
			State = LCD_STATE_JUMBTO_POSITION;
		}
		break;
	case LCD_STATE_JUMBTO_POSITION:
		if(TRUE==LCD_Jumb_To(MyMessage.Row, MyMessage.Col)){
			State=LCD_STATE_DISPLAY_CHARS;
		}
		break;
	case LCD_STATE_DISPLAY_CHARS:
		if (MyMessage.Message[Idx] != NULL_CHAR) {
			if (TRUE == LCD_Write_Char(MyMessage.Message[Idx])) {
				++Idx;
				if (MyMessage.Message[Idx] == NULL_CHAR) {
					State=LCD_STATE_DEQUEUE_DATA;
				}
			}
		}
		break;
	default:
		break;

	}
}
/****************************************************************************/
void IntToStr(char*Str,UINT8_t Num){
	if (Num / 10) {
		Str[0] = (Num / 10) + '0';
		Str[1] = (Num % 10) + '0';
		Str[2] = NULL_CHAR;
	} else {
		Str[0] = Num + '0';
		Str[1] = ' ';
		Str[2] = NULL_CHAR;
	}
}
/****************************************************************************/
void CharToStr(char*Str,UINT8_t Num){
	Str[0] = Num + '0';
	Str[1] = NULL_CHAR;
}
/****************************************************************************/
BOOL_t LCD_Set_Request(const LCD_MESSAGE_t*const Message)
{
	BOOL_t Ret=FALSE;
	Ret = Enqueue(&LCD_Queue, Message, QUEUE_OBJ_TYPE_LCD_MESSAGE);
	return Ret;
}
/****************************************************************************/
