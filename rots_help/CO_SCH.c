/******************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "TMR0.h"
#include "CO_SCH.h"
/******************************************************************************/
#define ENDED 0
#define TMR_INT_CYCLE 125
/******************************************************************************/
typedef struct{
        void (*pTask)(void);
        UINT8_t Period;
        UINT8_t Delay;
        UINT8_t Id;
        UINT8_t Run;
}TASK_t;
/******************************************************************************/
static void CO_SCH_Update_Tasks(void);
/******************************************************************************/
static TASK_t CO_SCH_Task[CO_SCH_MAX_TASKS];
static volatile BOOL_t CO_SCH_Update = FALSE;
/******************************************************************************/
void
CO_SCH_Delete_Task(const UINT8_t ID){
     if(ID < CO_SCH_MAX_TASKS && CO_SCH_Task[ID].pTask != NULL_PTR){
        CO_SCH_Task[ID].pTask = NULL_PTR;
        CO_SCH_Task[ID].Run = 0;
        CO_SCH_Task[ID].Delay = 0;
        CO_SCH_Task[ID].Period = 0;
     }
     else{
        /* Error: Undefined Task */
     }
}
/******************************************************************************/
void
CO_SCH_Init(void){
	 UINT8_t Id;
	 /* ToDo: Disable Global Interrupt */
	 GIC;
     for(Id = 0; Id < CO_SCH_MAX_TASKS; Id++){
         CO_SCH_Delete_Task(Id);
     }
     /* To Do: Init Timer Here */
     TMR0_Init();
     TMR0_Mode(TMR0_CTC);
     TMR0_Set_Prescaler(TMR0_NO_CLK);
     TMR0_Set_Buffer(TMR0_OCR, TMR_INT_CYCLE); 		/* 1 ms */
     TMR0_INT(TMR0_OC_INT_ENABLE);
}
/******************************************************************************/
void
CO_SCH_Add_Task(void (*const PTASK)(void),
                     const UINT8_t DELAY,
                     const UINT8_t PERIOD){

     static UINT8_t Id = 0;
     if(Id < CO_SCH_MAX_TASKS){
        CO_SCH_Task[Id].pTask = PTASK;
        CO_SCH_Task[Id].Delay = 1 + DELAY;
        CO_SCH_Task[Id].Period = PERIOD;
        CO_SCH_Task[Id].Run = 0;
        CO_SCH_Task[Id].Id = Id;
        Id++;
     }
     else{
        /* Error: Scheduler is Full */
     }
}
/******************************************************************************/
void
CO_SCH_Dispatch_Tasks(void){
	UINT8_t Id;
     if(TRUE == CO_SCH_Update){
        CO_SCH_Update_Tasks();
        for(Id = 0; Id < CO_SCH_MAX_TASKS; Id++){
            if(CO_SCH_Task[Id].Run > 0){
               CO_SCH_Task[Id].pTask();
               CO_SCH_Task[Id].Run--;
               if(ENDED == CO_SCH_Task[Id].Period){
                  CO_SCH_Delete_Task(Id);
               }
            }
            else{
               /* Task is not Ready */
            }
        }
        CO_SCH_Update = FALSE;
     }
}
/******************************************************************************/
static void
CO_SCH_Update_Tasks(void){
	UINT8_t Id;
	for (Id = 0; Id < CO_SCH_MAX_TASKS; Id++) {
		if (CO_SCH_Task[Id].pTask != NULL_PTR) {
			CO_SCH_Task[Id].Delay--;
			if (ENDED == CO_SCH_Task[Id].Delay) {
				CO_SCH_Task[Id].Run++;
				CO_SCH_Task[Id].Delay = CO_SCH_Task[Id].Period;
			} else {
				/* Task is not Ready */
			}
		} else {
			/* Error: Undefined Task */
		}
	}
}
/******************************************************************************/
void
CO_SCH_Start(void){
     /* To Do: Enable Interrupt Here */
	TMR0_Set_Prescaler(TMR0_DF64);				/* Tick = 32 us */
	TMR0_Set_Buffer(TMR0_OCR, TMR_INT_CYCLE); 		/* 1 ms */
	GIE;
}
/******************************************************************************/
void
CO_SCH_Stop(void){
	GIC;
	TMR0_Set_Prescaler(TMR0_NO_CLK);
}
#if 0
void CO_SCH_Sleep(void){
     /* To Do: */
}
#endif
/******************************************************************************/
ISR(TIMER0_COMP_VECT){
     CO_SCH_Update = TRUE;
}
/******************************************************************************/
