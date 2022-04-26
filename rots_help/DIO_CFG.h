/****************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H
/****************************************************************************/
typedef enum{
	DIO_PINA0 = 0,
	DIO_PINA1,
	DIO_PINA2,
	DIO_PINA3,
	DIO_PINA4,
	DIO_PINA5,
	DIO_PINA6,
	DIO_PINA7,

	DIO_PINB0,
	DIO_PINB1,
	DIO_PINB2,
	DIO_PINB3,
	DIO_PINB4,
	DIO_PINB5,
	DIO_PINB6,
	DIO_PINB7,

	DIO_PINC0,
	DIO_PINC1,
	DIO_PINC2,
	DIO_PINC3,
	DIO_PINC4,
	DIO_PINC5,
	DIO_PINC6,
	DIO_PINC7,

	DIO_PIND0,
	DIO_PIND1,
	DIO_PIND2,
	DIO_PIND3,
	DIO_PIND4,
	DIO_PIND5,
	DIO_PIND6,
	DIO_PIND7,
	DIO_MAX_PINS
}DIO_PIN_ID_t;
/****************************************************************************/
typedef enum{
	DIO_PIN_DIRECTION_INPUT_PULL_UP = 0,
	DIO_PIN_DIRECTION_OUTPUT,
	DIO_PIN_DIRECTION_INPUT_FLOAT
}DIO_PIN_DIRECTION_t;
/****************************************************************************/
typedef enum{
	DIO_PORTA = 0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD,
	DIO_MAX_PORTS
}DIO_PORT_ID_t;
/****************************************************************************/
typedef enum{
	DIO_PIN_STATE_LOW = 0,
	DIO_PIN_STATE_HIGH
}DIO_PIN_STATE_t;
/****************************************************************************/
extern DIO_PIN_DIRECTION_t Pin_Direction[DIO_MAX_PINS];
/****************************************************************************/
#endif
/****************************************************************************/
