#include "main.h"
#include "i2c.h"

#define LCD_ADDRESS	0x04E

void LCD_Send_String (char *);
void LCD_Init();
void LCD_Clear();
void LCD_Send_Data(char);
void LCD_Send_Cmd(char);
void LCD_Put_Cur(uint8_t, uint8_t);