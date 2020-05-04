#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_register.h"
#include "DIO_private.h"


void SetPinDirection(u8 Port,u8 Pin, u8 Direction)
{
	switch(Port)
	{
	case 'A':
	if(Direction==0)
	{
		DDRA &= ~(1<<Pin);
		
	}
	else
	{
		DDRA|= (1<<Pin);
	}
	break;
	
	case 'B':
	if(Direction==0)
	{
		DDRB &= ~(1<<Pin);
		
	}
	else
	{
		DDRB|= (1<<Pin);
		
	}
	break;
	
	case 'C':
	if(Direction==0)
	{
		DDRC &=  ~(1<<Pin);
		
		
	}
	else
	{
		DDRC|= (1<<Pin);
		
	}
	break;
	
	case 'D':
	if(Direction==0)
	{
		DDRD &= ~(1<<Pin);
		
		
	}
	else
	{
		DDRD|= (1<<Pin);
		
	}
	break;
	
		
	}
	
	
	
}


void SetPinValue(u8 Port,u8 Pin, u8 Value)
{
	switch(Port)
	{
	case 'A':
	if(Value==0)
	{
		PORTA &= ~(1<<Pin);
		
	}
	else
	{
		PORTA|= (1<<Pin);
	}
	break;
	
	case 'B':
	if(Value==0)
	{
		PORTB &= ~(1<<Pin);
		
	}
	else
	{
		PORTB|= (1<<Pin);
		
	}
	break;
	
	case 'C':
	if(Value==0)
	{
		PORTC &=  ~(1<<Pin);
		
		
	}
	else
	{
		PORTC|= (1<<Pin);
		
	}
	break;
	
	case 'D':
	if(Value==0)
	{
		PORTD &= ~(1<<Pin);
		
		
	}
	else
	{
		PORTD|= (1<<Pin);
		
	}
	break;
	
		
	}
	
	
	
}

void SetPortDirecton(u8 Port,u8 Value)
{
	switch(Port)
	{
	case 'A':
		DDRA=Value;
		break;
	case 'B':
			DDRB=Value;
			break;
	case 'C':
			DDRC=Value;
			break;
	case 'D':
			DDRD=Value;
			break;
	}
}

void SetPortValue(u8 Port,u8 Value)
{
	switch(Port)
	{
	case 'A':
		PORTA=Value;
		break;
	case 'B':
			PORTB=Value;
			break;
	case 'C':
			PORTC=Value;
			break;
	case 'D':
			PORTD=Value;
			break;
	}
}


u8 GetPinVal(u8 Port,u8 Pin)
{
	u8 x;
	switch(Port)
	{
	case 'A':
			x=GET_BIT(PINA,Pin);
		break;
	case 'B':
			x=GET_BIT(PINB,Pin);
			break;
	case 'C':
			x=GET_BIT(PINC,Pin);
			break;
	case 'D':
			x=GET_BIT(PIND,Pin);
			break;
	}
	return x;
}

