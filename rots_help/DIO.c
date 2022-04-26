/****************************************************************************/
#include "STD_TYPES.h"
#include "STD_MEMORY_MAP.h"
#include "STD_BITS.h"
#include "DIO_CFG.h"
#include "DIO.h"
/****************************************************************************/

void DIO_INIT(void)
{
	DIO_PIN_ID_t Pin_Id;
	DIO_PORT_ID_t Port_Id;
	volatile UINT8_t* const Reg[DIO_MAX_PORTS] = { DDRA_ADD, DDRB_ADD, DDRC_ADD, DDRD_ADD };
	for (Pin_Id = DIO_PINA0; Pin_Id < DIO_MAX_PINS; Pin_Id++) {
		Port_Id = Pin_Id / 8;
		switch (Pin_Direction[Pin_Id]) {
		case DIO_PIN_DIRECTION_OUTPUT:
			SET_BIT(*Reg[Port_Id], Pin_Id % 8);
			break;
		case DIO_PIN_DIRECTION_INPUT_PULL_UP:
			CLEAR_BIT(*Reg[Port_Id], Pin_Id % 8);
			DIO_WRITE_PIN_VALUE(Pin_Id, DIO_PIN_STATE_HIGH);
			break;
		case DIO_PIN_DIRECTION_INPUT_FLOAT:
			CLEAR_BIT(*Reg[Port_Id], Pin_Id % 8);
			DIO_WRITE_PIN_VALUE(Pin_Id, DIO_PIN_STATE_LOW);
		break;
		default:
			break;
		}
	}
}
/****************************************************************************/
void DIO_WRITE_PIN_VALUE(const DIO_PIN_ID_t PIN_ID, const DIO_PIN_STATE_t PIN_STATE){
	volatile UINT8_t* const Reg[DIO_MAX_PORTS] = { PORTA_ADD, PORTB_ADD, PORTC_ADD, PORTD_ADD };
	DIO_PORT_ID_t Port_Id = PIN_ID / 8;
	switch (PIN_STATE) {
	case DIO_PIN_STATE_HIGH:
		SET_BIT(*Reg[Port_Id], PIN_ID % 8);
		break;
	case DIO_PIN_STATE_LOW:
		CLEAR_BIT(*Reg[Port_Id], PIN_ID % 8);
		break;
	default:
		break;
	}
}
/****************************************************************************/
DIO_PIN_STATE_t DIO_READ_PIN_VALUE(const DIO_PIN_ID_t PIN_ID){
	volatile UINT8_t* const Reg[DIO_MAX_PORTS] = { PINA_ADD, PINB_ADD, PINC_ADD, PIND_ADD };
	DIO_PORT_ID_t Port_Id = PIN_ID / 8;
	DIO_PIN_STATE_t State = DIO_PIN_STATE_LOW;
	if(DIO_PIN_STATE_HIGH == GET_BIT(*Reg[Port_Id], PIN_ID % 8)){
		State = DIO_PIN_STATE_HIGH;
	}
	return State;
}
/****************************************************************************/
void DIO_WRITE_PORT(const DIO_PORT_ID_t PORT_ID, const UINT8_t VALUE){
	volatile UINT8_t* const Reg[DIO_MAX_PORTS] = { PORTA_ADD, PORTB_ADD, PORTC_ADD, PORTD_ADD };
	*Reg[PORT_ID] = VALUE;
}
/****************************************************************************/
UINT8_t DIO_Read_PORT(const DIO_PORT_ID_t PORT_ID){
	volatile UINT8_t* const Reg[DIO_MAX_PORTS] = { PINA_ADD, PINB_ADD, PINC_ADD, PIND_ADD };
	return *Reg[PORT_ID];
}
/****************************************************************************/
