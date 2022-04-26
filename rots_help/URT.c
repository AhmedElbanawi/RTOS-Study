/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_BITS.h"
#include "STD_MEMORY_MAP.h"
#include "QUEUE.h"
#include "URT.h"
/****************************************************************************/
static void URT_Rx_INT(const URT_INT_t INT);
static void URT_Rx(const URT_MODE_t MODE);
static void URT_Tx_INT(const URT_INT_t INT);
static void URT_Tx(const URT_MODE_t MODE);
/****************************************************************************/

static URT_MESSAGE_t URT_Tx_Arr[URT_TX_MAX_NO_OF_MESSAGES];
QUEUE_t URT_Tx_Queue;

static volatile UINT8_t URT_Tx_Curr_Char_Idx=0;
static volatile URT_MESSAGE_t URT_Tx_Curr_Message;
static volatile BOOL_t URT_Tx_Message_Finished=TRUE;

/****************************************************************************/
static void URT_Rx_INT(const URT_INT_t INT){
	switch (INT) {
	case URT_IE:
		SET_BIT(UCSRB, 7);
		break;
	case URT_IC:
		CLEAR_BIT(UCSRB, 7);
		break;
	}
}
/****************************************************************************/
static void URT_Tx_INT(const URT_INT_t INT){
	switch (INT) {
	case URT_IE:
		SET_BIT(UCSRB, 6);
		break;
	case URT_IC:
		CLEAR_BIT(UCSRB, 6);
		break;
	}
}
/****************************************************************************/
static void URT_Rx(const URT_MODE_t MODE){
	switch (MODE) {
	case URT_ENABLE:
		SET_BIT(UCSRB, 4);
		break;
	case URT_DISABLE:
		CLEAR_BIT(UCSRB, 4);
		break;
	}
}
/****************************************************************************/
static void URT_Tx(const URT_MODE_t MODE){
	switch (MODE) {
	case URT_ENABLE:
		SET_BIT(UCSRB, 3);
		break;
	case URT_DISABLE:
		CLEAR_BIT(UCSRB, 3);
		break;
	}
}
/****************************************************************************/
void URT_Init(void){
	SET_BIT(UCSRC, 1);
	SET_BIT(UCSRC, 2);
	UBRRH = URT_BAUD_RATE >> 8;
	UBRRL = URT_BAUD_RATE;


	/*- init URT transmiter -*/
	URT_Tx_INT(URT_IE);
	URT_Tx(URT_ENABLE);
	/*- Create URT_Tx_Queue -*/
	Cqueue(&URT_Tx_Queue, URT_Tx_Arr, URT_TX_MAX_NO_OF_MESSAGES);
}
/****************************************************************************/
BOOL_t Str_Cmp(const UINT8_t* Str1, const UINT8_t* Str2){
	BOOL_t IsSame = FALSE;
	while(*Str1 == *Str2){
		if(*Str1 == '\0'){
			IsSame = TRUE;
			break;
		}
		++Str1;
		++Str2;
	}
	return IsSame;
}
/****************************************************************************/
ISR(URT_RX_OVF_VECT){

}
/****************************************************************************/
ISR(URT_TX_OVF_VECT){
	/*- increment the current index to the next character of the current message  -*/
	++URT_Tx_Curr_Char_Idx;
	/*- check if this is the null character  -*/
	if(URT_Tx_Curr_Message.Message[URT_Tx_Curr_Char_Idx]==NULL_CHAR)
	{
		/*- URT finished sending the message -*/
		URT_Tx_Message_Finished=TRUE;
	}else {
		/*- send the current character of the current message  -*/
		UDR=URT_Tx_Curr_Message.Message[URT_Tx_Curr_Char_Idx];
	}
}
/****************************************************************************/
void URT_Tx_Main(void)
{
	/*- check if URT transmitted the current message -*/
	if(TRUE==URT_Tx_Message_Finished)
	{
		/*- dequeue a new message if queue is not empty -*/
		if(TRUE==Dequeue(&URT_Tx_Queue, &URT_Tx_Curr_Message, QUEUE_OBJ_TYPE_URT_MESSAGE))
		{
			/*- init the current index to the first character of the current message  -*/
			URT_Tx_Curr_Char_Idx=0;
			URT_Tx_Message_Finished=FALSE;
			/*- send the first character -*/
			UDR=URT_Tx_Curr_Message.Message[URT_Tx_Curr_Char_Idx];
		}
	}
}
/****************************************************************************/
BOOL_t URT_Tx_Set_Request(const URT_MESSAGE_t*const Data)
{
	BOOL_t Ret=FALSE;
	/*- request to enqueue the new message -*/
	if(TRUE==Enqueue(&URT_Tx_Queue, Data, QUEUE_OBJ_TYPE_URT_MESSAGE))
	{
		Ret=TRUE;
	}
	return Ret;
}
/****************************************************************************/
