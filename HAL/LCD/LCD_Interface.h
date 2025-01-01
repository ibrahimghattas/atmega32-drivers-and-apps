

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init(void);
void LCD_Clear(void);



/**line 0:1 cell 0:15 **/
void LCD_GoTo(u8 line,u8 cell);



void LCD_WriteString(char*str);
void LCD_WriteNumber(s32 num);
void LCD_WriteNumber5(u8 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);

void LCD_Write_4D(u16 num);

void LCD_WriteStringLength(u8*str,u16 len);

void LCD_WriteChar(u8 ch);
void LCD_WriteCharPos(u8 ch,u8 line,u8 cell);
void LCD_CustomChar(u8 address,u8*patten);

void LCD_MoveString(u8*str);

void LCD_ShiftCursorLeft(void);


typedef enum{
	MAN =0,
	ARROW ,
	ARROW_MAN,
	DEAD_R ,
	DEAD_L
}patterns_t;

/*********************patterns**************/
extern u8 ManPattern[8];
extern u8 DeadManL[8];
extern u8 DeadManR[8];
extern u8 ArrowManPat[8];
extern u8 ArrowPattern[8];

#endif /* LCD_INTERFACE_H_ */