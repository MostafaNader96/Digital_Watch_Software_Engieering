/***********************************************/
/* Author: Mostafa Nader*/
/* Version: V01*/
/* Date: 14 Jan 2020*/
/***********************************************/
#include "std_types.h"
#include "bits.h"
#include "Delay_ms.h"
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"



/*Description: This API Initializes the LCD*/
void CLCD_voidInitialize(void)
{
	Delay_ms(40);

#if CLCD_u8_DATA_LENGTH==FOUR_BITS_MODE
	SetPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,0);
	SetPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);

	CLCD_voidSetHalfDataPort(0b0010);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(0b0010);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(0b1000);
	CLCD_voidSetEnablePulse();

#elif CLCD_u8_DATA_LENGTH==EIGHT_BITS_MODE
	CLCD_voidWriteCmd(0b00111000);
#else #error "WRONG DATA LENGTH CHOICE"

#endif

	CLCD_voidWriteCmd(0b00001100);
	CLCD_voidWriteCmd(0b00000001);
	Delay_ms(2);

}

/*Description: This API Shall display the data sent on the LCD*/
void CLCD_voidWriteData(u8 Copy_u8Data)
{
	/* Set RS = 1 */
	SetPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,1);
	/* Set RW = 0 */
	SetPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);
#if CLCD_u8_DATA_LENGTH==FOUR_BITS_MODE

	/*Set higher order 4bits of the command*/
	CLCD_voidSetHalfDataPort(Copy_u8Data>>4);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(Copy_u8Data);
	CLCD_voidSetEnablePulse();


#elif CLCD_u8_DATA_LENGTH==EIGHT_BITS_MODE
	/* Set Data on Data Port */
	CLCD_voidSetDataPort(Copy_u8Data);
	/* Enable Pulse */
	SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
	Delay_ms(1);
	SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
	//_delay_ms(1);
#else #error "WRONG DATA LENGTH CHOICE"

#endif
}

/*Description: This API Sends a specific command to the LCD*/
void CLCD_voidWriteCmd(u8 Copy_u8Cmd)
{
	/* Set RS = 0 */
	SetPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,0);
	/* Set RW = 0 */
	SetPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);

#if CLCD_u8_DATA_LENGTH==FOUR_BITS_MODE

	/*Set higher order 4bits of the command*/
	CLCD_voidSetHalfDataPort(Copy_u8Cmd>>4);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(Copy_u8Cmd);
	CLCD_voidSetEnablePulse();


#elif CLCD_u8_DATA_LENGTH==EIGHT_BITS_MODE
	/* Set Data on Data Port */
	CLCD_voidSetDataPort(Copy_u8Cmd);
	/* Enable Pulse */
	SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
	Delay_ms(1);
	SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
	//_delay_ms(1);
#else #error "WRONG DATA LENGTH CHOICE"

#endif


}

/*Description: This API Shall display the data string sent on the LCD*/
void CLCD_voidWriteString(const char* Copy_pchString)
{

	for(u8 i=0;Copy_pchString[i]>0;i++)
	{
		CLCD_voidWriteData(Copy_pchString[i]);
	}
}

/*Description: This API Shall Go to a certain location on the LCD*/
void CLCD_voidGoToXYPos(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8DDRamAdd;
	if(Copy_u8YPos==CLCD_u8_LINE_ONE)
	{
		Local_u8DDRamAdd=Copy_u8XPos;
	}
	else if(Copy_u8YPos==CLCD_u8_LINE_TWO)
	{
		Local_u8DDRamAdd=Copy_u8XPos+CLCD_u8_LINE_TWO_ADD_OFFSET;
	}
	else
	{
		/*Do Nothing*/
	}
	CLCD_voidWriteCmd(Local_u8DDRamAdd | CLCD_u8_SET_DDRAM_ADD_COMM);
}


static void CLCD_voidSetEnablePulse(void)
{
	SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
	Delay_ms(1);
	SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
	Delay_ms(1);

}

static void CLCD_voidSetHalfDataPort(u8 Copy_u8Data)
{
	u8 Local_u8BitVal;

	Local_u8BitVal=GET_BIT(Copy_u8Data,0);
	SetPinValue(CLCD_u8_D0_PORT,CLCD_u8_D4_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,1);
	SetPinValue(CLCD_u8_D1_PORT,CLCD_u8_D5_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,2);
	SetPinValue(CLCD_u8_D2_PORT,CLCD_u8_D6_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,3);
	SetPinValue(CLCD_u8_D3_PORT,CLCD_u8_D7_PIN,Local_u8BitVal);

}

static void CLCD_voidSetDataPort(u8 Copy_u8Data)
{
	u8 Local_u8BitVal;

	Local_u8BitVal=GET_BIT(Copy_u8Data,0);
	SetPinValue(CLCD_u8_D0_PORT,CLCD_u8_D0_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,1);
	SetPinValue(CLCD_u8_D1_PORT,CLCD_u8_D1_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,2);
	SetPinValue(CLCD_u8_D2_PORT,CLCD_u8_D2_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,3);
	SetPinValue(CLCD_u8_D3_PORT,CLCD_u8_D3_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,4);
	SetPinValue(CLCD_u8_D4_PORT,CLCD_u8_D4_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,5);
	SetPinValue(CLCD_u8_D5_PORT,CLCD_u8_D5_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,6);
	SetPinValue(CLCD_u8_D6_PORT,CLCD_u8_D6_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,7);
	SetPinValue(CLCD_u8_D7_PORT,CLCD_u8_D7_PIN,Local_u8BitVal);
}

void lcdnumberprinting(u32 num)
{
	u8 arr[100];
	u8 i=0;
while(num>=0)
{
	arr[i]=(num%10);
	num=num/10;
	i++;
	if(num==0)
		break;

}

for(u8 j=i-1; j>=0; j--)
{
CLCD_voidWriteData(arr[j]+48);
if(j==0)
	break;
}

}

