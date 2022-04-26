/****************************************************************************/
#ifndef LCD_H
#define LCD_H
#define LCD_MAX_NO_OF_MESSAGES 2

#define D4_PIN_NUMBER DIO_PINA0
#define D5_PIN_NUMBER DIO_PINA1
#define D6_PIN_NUMBER DIO_PINA2
#define D7_PIN_NUMBER DIO_PINA3
#define E_PIN_NUMBER  DIO_PINA4
#define RW_PIN_NUMBER DIO_PINA5
#define RS_PIN_NUMBER DIO_PINA6
/****************************************************************************/
typedef enum{
	ROW1 = 0,
	ROW2,
	LCD_MAX_ROWS
}LCD_ROW_ID_t;
/****************************************************************************/
typedef enum{
	COL1 = 0,
	COL2,
	COL3,
	COL4,
	COL5,
	COL6,
	COL7,
	COL8,
	COL9,
	COL10,
	COL11,
	COL12,
	COL13,
	COL14,
	COL15,
	COL16,
	LCD_MAX_COLS
}LCD_COL_ID_t;
/****************************************************************************/
typedef struct{
	CHAR_t* Message;
	LCD_ROW_ID_t Row;
	LCD_COL_ID_t Col;
}LCD_MESSAGE_t;
/****************************************************************************/
typedef enum{
	LCD_STATE_INIT=0,
	LCD_STATE_DEQUEUE_DATA,
	LCD_STATE_JUMBTO_POSITION,
	LCD_STATE_DISPLAY_CHARS
}LCD_STATE_t;
/****************************************************************************/
typedef enum {
	LCD_IDLE = 0,
	LCD_WR_4MSB = 1,
	LCD_WR_4LSB = 3,
	LCD_DELAY_BETWEEN_WRITINGS = 5,
	LCD_WR_FINISHED = 8
} LCD_WR_OP_t;
/****************************************************************************/
extern BOOL_t LCD_Init(void);
extern BOOL_t LCD_Clear(void);
extern void LCD_Main(void);
extern BOOL_t LCD_Set_Request(const LCD_MESSAGE_t*const Message);
extern void IntToStr(char*Str, UINT8_t Num);
void CharToStr(char*Str,UINT8_t Num);
/****************************************************************************/
#endif
/****************************************************************************/
