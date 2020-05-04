/*
 * main.c
 *
 *  Created on: Mar 14, 2020
 *      Author: MOSTAFA
 */

#include "std_types.h"
#include "bits.h"
#include "Delay_ms.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "INTGLB_interface.h"
#include "TIMER_interface.h"
#include "TIMER_register.h"
#include "CLCD_interface.h"

void TimeInc(void);
void TimeDisplay(void);
void Time_AdjustCursor(void);
void Time_incerement(void);
void AlarmDisplay(void);
void Alarm_AdjustCursor(void);
void Alarm_incerement(void);
void SWDisplay(void);
void SW_Start_Stop(void);
void SW_Reset(void);

u8 flag=100;
u8 Mode=0;

u8 HrVar=0,MinVar=0,SecVar=0,CL=0;
u8 AlHrVar=0,AlMinVar=0,AlCL=1;
u8 SWHrVar=0,SWMinVar=0,SWSecVar=0;

u8 TimeCell=1,AlCell=1,SWstatus=0,SWIncerementFlag;

void main(void)
{
	PortInitialize();
	CLCD_voidInitialize();
	Timer0_voidSetCallBack(&TimeInc);
	Timer0_voidInit();
	INT_voidEnableGlobal();

	while(1)
	{

		if(!(GetPinVal('A',0)))
		{
			if(GetPinVal('A',3))
			{
				AlMinVar++;
				SetPinValue('A',3,0);
				Delay_ms(500);
			}
			else
			{
			Mode++;						//ReadMode
			if(Mode==3)	Mode=0;
			flag=0;
			Delay_ms(500);
			}
		}


		if(Mode==0)			TimeDisplay();
		else if(Mode==1)	AlarmDisplay();		//Display
		else if(Mode==2)	SWDisplay();

		if(!(GetPinVal('A',1)))
		{
			if(Mode==0)				Time_AdjustCursor();
			else if(Mode==1)		Alarm_AdjustCursor();		//ReadPos
			else if(Mode==2)		SW_Start_Stop();
			Delay_ms(500);
		}

		if(!(GetPinVal('A',2)))
		{
			if(Mode==0)				Time_incerement();
			else if(Mode==1)		Alarm_incerement();			//ReadInc
			else if(Mode==2)		SW_Reset();
			Delay_ms(500);
		}

		if(HrVar==AlHrVar && MinVar==AlMinVar && CL==AlCL)
		{
			SetPinValue('A',3,1);
		}
	}
}


void TimeInc(void)
{
	static u16 count=0;
	TCNT0=131;
	if(count==1000)
	{
		SecVar++;
		if(SecVar>59)
		{
			SecVar=0; MinVar++;
		}
		if(MinVar>59)
		{
			MinVar=0; HrVar++;
		}
		if(HrVar>11)
		{
			HrVar=0; CL^=0x01;
		}

		if(SWIncerementFlag)
		{
			SWSecVar++;
			if(SWSecVar>59)
			{
				SWSecVar=0; SWMinVar++;
			}
			if(SWMinVar>59)
			{
				SWMinVar=0; SWHrVar++;
			}
			if(SWHrVar>11)
			{
				SWHrVar=0;
			}
		}

		count=0;

	}
	count++;

}


void TimeDisplay(void)
{
	if (flag==0)
		CLCD_voidWriteCmd(1);
	flag=100;

	CLCD_voidGoToXYPos(0,0);	//Initial place
	CLCD_voidWriteString("TIME MODE: ");
	CLCD_voidGoToXYPos(0,1);	//Initial place

	if(HrVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(HrVar);
	}
	else
		lcdnumberprinting(HrVar);
	CLCD_voidWriteString(":");

	if(MinVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(MinVar);
	}
	else
		lcdnumberprinting(MinVar);
	CLCD_voidWriteString(":");

	if(SecVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(SecVar);
	}
	else
		lcdnumberprinting(SecVar);
	CLCD_voidWriteString(" ");

	if(CL==0)
		CLCD_voidWriteString("Am");
	else
		CLCD_voidWriteString("Pm");
}


void Time_AdjustCursor(void)
{
	if(TimeCell==10)
		TimeCell=1;
	else
		TimeCell=TimeCell+3;
}

void Time_incerement(void)
{
	if(TimeCell==1)
	{
		HrVar++;
		if(HrVar>11)
			HrVar=0;
	}
	else if(TimeCell==4)
	{
		MinVar++;
		if(MinVar>59)
			MinVar=0;
	}
	else if(TimeCell==7)
	{
		SecVar++;
		if(SecVar>59)
			HrVar=0;
	}
	else if(TimeCell==10)
	{
		CL=CL^0x01;
	}

}


void AlarmDisplay(void)
{
	if (flag==0)
		CLCD_voidWriteCmd(1);
	flag=100;

	CLCD_voidGoToXYPos(0,0);	//Initial place
	CLCD_voidWriteString("ALARM MODE: ");
	CLCD_voidGoToXYPos(0,1);	//Initial place

	if(AlHrVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(AlHrVar);
	}
	else
		lcdnumberprinting(AlHrVar);
	CLCD_voidWriteString(":");

	if(AlMinVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(AlMinVar);
	}
	else
		lcdnumberprinting(AlMinVar);
	CLCD_voidWriteString(" ");

	if(AlCL==0)
		CLCD_voidWriteString("Am");
	else
		CLCD_voidWriteString("Pm");

}


void Alarm_AdjustCursor(void)
{
	if(AlCell==7)
		AlCell=1;
	else
		AlCell=AlCell+3;
}

void Alarm_incerement(void)
{
	if(AlCell==1)
	{
		AlHrVar++;
		if(AlHrVar>11)
			AlHrVar=0;
	}
	else if(AlCell==4)
	{
		AlMinVar++;
		if(AlMinVar>59)
			AlMinVar=0;
	}
	else if(AlCell==7)
	{
		AlCL=AlCL^0x01;
	}

}

void SWDisplay(void)
{
	if (flag==0)
		CLCD_voidWriteCmd(1);
	flag=100;

	CLCD_voidGoToXYPos(0,0);	//Initial place
	CLCD_voidWriteString("STOPWATCH MODE: ");
	CLCD_voidGoToXYPos(0,1);	//Initial place

	if(SWHrVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(SWHrVar);
	}
	else
		lcdnumberprinting(SWHrVar);
	CLCD_voidWriteString(":");

	if(SWMinVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(SWMinVar);
	}
	else
		lcdnumberprinting(SWMinVar);
	CLCD_voidWriteString(":");

	if(SWSecVar<10)
	{
		CLCD_voidWriteData('0');
		lcdnumberprinting(SWSecVar);
	}
	else
		lcdnumberprinting(SWSecVar);
}

void SW_Start_Stop(void)
{
	if(SWstatus==1)
		SWstatus=0;
	else
		SWstatus++;

	if(SWstatus==0)
	{
		SWIncerementFlag=0;
	}
	else if(SWstatus==1)
	{
		SWIncerementFlag=1;
	}
}

void SW_Reset(void)
{
	CLCD_voidWriteCmd(1);
	SWIncerementFlag=0;
	SWstatus=0;
	SWHrVar=0; SWMinVar=0; SWSecVar=0;
}
