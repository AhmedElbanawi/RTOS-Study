/****************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
/****************************************************************************/
typedef struct{
	SINT8_t Front;
	SINT8_t Rear;
	SINT8_t Size;
    void* arr;
}QUEUE_t;
/****************************************************************************/
typedef enum{
    QUEUE_OBJ_TYPE_UINT8=0,
    QUEUE_OBJ_TYPE_UINT16,
    QUEUE_OBJ_TYPE_UINT32,
    QUEUE_OBJ_TYPE_UINT64,
    QUEUE_OBJ_TYPE_SINT8,
    QUEUE_OBJ_TYPE_SINT16,
    QUEUE_OBJ_TYPE_SINT32,
    QUEUE_OBJ_TYPE_SINT64,
    QUEUE_OBJ_TYPE_LCD_MESSAGE,
    QUEUE_OBJ_TYPE_URT_MESSAGE
}QUEUE_OBJ_t;
/****************************************************************************/
extern BOOL_t Queue_Is_Full(const QUEUE_t*const MyQueue);
extern BOOL_t Queue_Is_Empty(const QUEUE_t*const MyQueue);
extern void Cqueue(QUEUE_t*const MyQueue, const void*const arr,const SINT8_t Size);
extern BOOL_t Enqueue(QUEUE_t*const MyQueue,const void*const Val, const QUEUE_OBJ_t Obj_Type);
extern BOOL_t Dequeue(QUEUE_t*const MyQueue,void*const Ret_Val,const QUEUE_OBJ_t Obj_Type);
/****************************************************************************/
#endif
/****************************************************************************/

