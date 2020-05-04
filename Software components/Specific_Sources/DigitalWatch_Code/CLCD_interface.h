/***********************************************/
/* Author: Mostafa Nader*/
/* Version: V01*/
/* Date: 14 Jan 2020*/
/***********************************************/

/*Description: This API Initializes the LCD*/
void CLCD_voidInitialize(void);

/*Description: This API Shall display the data sent on the LCD*/
void CLCD_voidWriteData(u8 Copy_u8Data);

/*Description: This API Sends a specific command to the LCD*/
void CLCD_voidWriteCmd(u8 Copy_u8Cmd);

/*Description: This API Shall display the data string sent on the LCD*/
void CLCD_voidWriteString(const char* Copy_pchString);

/*Description: This API Shall Go to a certain location on the LCD*/
void CLCD_voidGoToXYPos(u8 Copy_u8XPos,u8 Copy_u8YPos);

void lcdnumberprinting(u32 num);

#define CLCD_u8_LINE_ONE	0
#define CLCD_u8_LINE_TWO	1

