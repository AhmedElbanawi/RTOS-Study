/****************************************************************************/
#ifndef DIO_H
#define DIO_H

/****************************************************************************/
extern void
DIO_INIT(void);
extern void
DIO_WRITE_PIN_VALUE(const DIO_PIN_ID_t PIN_ID, const DIO_PIN_STATE_t PIN_STATE);
extern DIO_PIN_STATE_t
DIO_READ_PIN_VALUE(const DIO_PIN_ID_t PIN_ID);
extern void
DIO_WRITE_PORT(const DIO_PORT_ID_t PORT_ID, const UINT8_t VALUE);
extern UINT8_t
DIO_Read_PORT(const DIO_PORT_ID_t PORT_ID);
/****************************************************************************/
#endif
/****************************************************************************/

