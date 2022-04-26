/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "LCD.h"
#include "URT.h"
#include "QUEUE.h"
/****************************************************************************/
BOOL_t Queue_Is_Full(const QUEUE_t*const MyQueue)
{
    BOOL_t Ret=FALSE;
    if((1+MyQueue->Rear)%MyQueue->Size==MyQueue->Front)
    {
        Ret=TRUE;
    }
    return Ret;
}
/****************************************************************************/
BOOL_t Queue_Is_Empty(const QUEUE_t*const MyQueue)
{
    BOOL_t Ret=FALSE;
    if(-1==MyQueue->Front&&-1==MyQueue->Rear)
    {
        Ret=TRUE;
    }
    return Ret;
}
/****************************************************************************/
void Cqueue(QUEUE_t*const MyQueue, const void*const arr,const SINT8_t Size)
{
    MyQueue->Front=-1;
    MyQueue->Rear=-1;
    MyQueue->Size=Size;
    MyQueue->arr=arr;
}
/****************************************************************************/
BOOL_t Enqueue(QUEUE_t*const MyQueue,const void*const Val, const QUEUE_OBJ_t Obj_Type)
{
    BOOL_t Ret=TRUE;
    /*Check if queue is full if true return without any change*/
    if(TRUE==Queue_Is_Full(MyQueue))
    {
        Ret=FALSE;
    }
    else
    {
        /*Check if queue is empty if true make front and rear point to first object in queue*/
        if(TRUE==Queue_Is_Empty(MyQueue))
        {
            MyQueue->Front=0;
            MyQueue->Rear=0;
        }
        else
        {
            /*Check if queue is not empty and not full then increment rear circuilly*/
            MyQueue->Rear=(1+MyQueue->Rear)%MyQueue->Size;
        }
        switch(Obj_Type)
        {

        /*-****************** unsigned integer data types ********************-*/
        case QUEUE_OBJ_TYPE_UINT8:
        	*(((UINT8_t* const ) MyQueue->arr) + MyQueue->Rear)=*(const UINT8_t* const ) Val;
        	break;
        case QUEUE_OBJ_TYPE_UINT16:
        	*(((UINT16_t* const ) MyQueue->arr) + MyQueue->Rear)=*(const UINT16_t* const ) Val;
        	break;
        case QUEUE_OBJ_TYPE_UINT32:
            *(((UINT32_t*const)MyQueue->arr)+MyQueue->Rear)=*(const UINT32_t*const)Val;
            break;
        case QUEUE_OBJ_TYPE_UINT64:
            *(((UINT64_t* const ) MyQueue->arr) + MyQueue->Rear)=*(const UINT64_t* const ) Val;
            break;

            /*-****************** signed integer data types ********************-*/
		case QUEUE_OBJ_TYPE_SINT8:
			*(((CHAR_t* const ) MyQueue->arr) + MyQueue->Rear)=*(const CHAR_t* const ) Val;
			break;
		case QUEUE_OBJ_TYPE_SINT16:
			*(((SINT16_t* const ) MyQueue->arr) + MyQueue->Rear)=*(const SINT16_t* const ) Val;
			break;

        case QUEUE_OBJ_TYPE_SINT32:
            *(((SINT32_t*const)MyQueue->arr)+MyQueue->Rear)=*(const SINT32_t*const)Val;
            break;
        case QUEUE_OBJ_TYPE_SINT64:
        	*(((SINT64_t* const ) MyQueue->arr) + MyQueue->Rear)=*(const SINT64_t* const ) Val;
        	break;

        	/*-****************** lcd message data type ********************-*/
        case QUEUE_OBJ_TYPE_LCD_MESSAGE:
        	*(((LCD_MESSAGE_t*const)MyQueue->arr)+MyQueue->Rear)=*(const LCD_MESSAGE_t*const)Val;
        	break;

        	/*-****************** URT message data type ********************-*/
        case QUEUE_OBJ_TYPE_URT_MESSAGE:
        	*(((URT_MESSAGE_t*const)MyQueue->arr)+MyQueue->Rear)=*(const URT_MESSAGE_t*const)Val;
        	break;
        default:
            break;
        }
    }
    return Ret;
}
/****************************************************************************/
BOOL_t Dequeue(QUEUE_t*const MyQueue,void*const Ret_Val,const QUEUE_OBJ_t Obj_Type)
{
    BOOL_t Ret=TRUE;
    /*Check if queue is empty if true return without any change*/
    if(TRUE==Queue_Is_Empty(MyQueue))
    {
        Ret=FALSE;
    }
    else
    {
        /*Find the required data type for the required object and return its value from required queue*/
        switch(Obj_Type)
        {
        		/*-****************** unsigned integer data types ********************-*/
        case QUEUE_OBJ_TYPE_UINT8:
            *(UINT8_t*const)Ret_Val=*(((UINT8_t*const)MyQueue->arr)+MyQueue->Front);
            break;
        case QUEUE_OBJ_TYPE_UINT16:
            *(UINT16_t*const)Ret_Val=*(((UINT16_t*const)MyQueue->arr)+MyQueue->Front);
            break;
        case QUEUE_OBJ_TYPE_UINT32:
            *(UINT32_t*const)Ret_Val=*(((UINT32_t*const)MyQueue->arr)+MyQueue->Front);
            break;
        case QUEUE_OBJ_TYPE_UINT64:
            *(UINT64_t*const)Ret_Val=*(((UINT64_t*const)MyQueue->arr)+MyQueue->Front);
            break;

            /*-****************** signed integer data types ********************-*/
        case QUEUE_OBJ_TYPE_SINT8:
            *(CHAR_t*const)Ret_Val=*(((CHAR_t*const)MyQueue->arr)+MyQueue->Front);
            break;
        case QUEUE_OBJ_TYPE_SINT16:
            *(SINT16_t*const)Ret_Val=*(((SINT16_t*const)MyQueue->arr)+MyQueue->Front);
            break;
        case QUEUE_OBJ_TYPE_SINT32:
            *(SINT32_t*const)Ret_Val=*(((SINT32_t*const)MyQueue->arr)+MyQueue->Front);
            break;
        case QUEUE_OBJ_TYPE_SINT64:
            *(SINT64_t*const)Ret_Val=*(((SINT64_t*const)MyQueue->arr)+MyQueue->Front);
            break;

            /*-****************** lcd message data type ********************-*/
        case QUEUE_OBJ_TYPE_LCD_MESSAGE:
        	*(LCD_MESSAGE_t*const)Ret_Val=*(((LCD_MESSAGE_t*const)MyQueue->arr)+MyQueue->Front);
        	break;

        	/*-****************** lcd message data type ********************-*/
        case QUEUE_OBJ_TYPE_URT_MESSAGE:
        	*(URT_MESSAGE_t*const)Ret_Val=*(((URT_MESSAGE_t*const)MyQueue->arr)+MyQueue->Front);
        	break;
        default:
            break;
        }
        /*Check if queue has only one object*/
        if(MyQueue->Front==MyQueue->Rear)
        {
            MyQueue->Front=-1;
            MyQueue->Rear=-1;
        }
        else
        {
            MyQueue->Front=(1+MyQueue->Front)%MyQueue->Size;
        }
    }
    return Ret;
}
/****************************************************************************/
