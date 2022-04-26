/****************************************************************************/
#ifndef URT_H
#define URT_H
#define URT_BAUD_RATE 51
#define STOP_CHAR '.'
#define URT_TX_MAX_NO_OF_MESSAGES 3
/****************************************************************************/
typedef enum{
	URT_IE = 0,
	URT_IC
}URT_INT_t;
/****************************************************************************/
typedef enum{
	URT_ENABLE = 0,
	URT_DISABLE
}URT_MODE_t;
/****************************************************************************/
typedef struct{
	CHAR_t*Message;
}URT_MESSAGE_t;
/****************************************************************************/
extern void URT_Init(void);
extern void URT_Tx_Main(void);
extern BOOL_t URT_Tx_Set_Request(const URT_MESSAGE_t*const Data);
extern BOOL_t Str_Cmp(const UINT8_t* Str1, const UINT8_t* Str2);
/****************************************************************************/
#endif
/****************************************************************************/
