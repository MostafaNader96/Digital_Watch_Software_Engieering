#define CLCD_u8_LINE_TWO_ADD_OFFSET 0x40
#define CLCD_u8_SET_DDRAM_ADD_COMM	0x80
#define FOUR_BITS_MODE				0
#define EIGHT_BITS_MODE				1

static void CLCD_voidSetEnablePulse(void);
static void CLCD_voidSetHalfDataPort(u8 Copy_u8Data);
static void CLCD_voidSetDataPort(u8 Copy_u8Data);
