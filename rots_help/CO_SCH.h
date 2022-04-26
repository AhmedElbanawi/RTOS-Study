/******************************************************************************/
#ifndef CO_SCH_H
#define CO_SCH_H
/******************************************************************************/
#define CO_SCH_MAX_TASKS 4
/******************************************************************************/
void
CO_SCH_Init(void);
void
CO_SCH_Dispatch_Tasks(void);
void
CO_SCH_Add_Task(void (*const PTASK)(void), const UINT8_t DELAY, const UINT8_t PERIOD);
void
CO_SCH_Delete_Task(const UINT8_t ID);
void
CO_SCH_Start(void);
void
CO_SCH_Stop(void);
#if 0
void CO_SCH_Sleep(void);
#endif
/******************************************************************************/
#endif
/******************************************************************************/
