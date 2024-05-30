#include "main.h"
#include "i2c.h"

#define LCD_ADDRESS	0x04E

void LCD_Send_Cmd(char cmd)
{
    char data_h,data_l;
    uint8_t frame_data[4];
    data_h = (cmd&0xf0);
    data_l = ((cmd <<4)&0xf0);
    frame_data[0] = data_h | 0x0C;    //en=1, rs=0
    frame_data[1] = data_h | 0x08;    //en=0, rs=0
    frame_data[2] = data_l | 0x0C;    //en=1, rs=0
    frame_data[3] = data_l | 0x08;    //en=0, rs=0
	
    HAL_I2C_Master_Transmit(&hi2c1,LCD_ADDRESS,(uint8_t *)frame_data,4,0x100);
    //HAL_Delay(1);
}


void LCD_Send_Data(char data)
{
    char data_h,data_l;
    uint8_t frame_data[4];
    data_h = (data&0xf0);
    data_l = ((data <<4)&0xf0);
    frame_data[0] = data_h | 0x0D;    //en=1, rs=1
    frame_data[1] = data_h | 0x09;    //en=0, rs=1
    frame_data[2] = data_l | 0x0D;    //en=1, rs=1
    frame_data[3] = data_l | 0x09;    //en=0, rs=1

    HAL_I2C_Master_Transmit(&hi2c1,LCD_ADDRESS,(uint8_t *)frame_data,4,0x100);
    //HAL_Delay(1);
}


void LCD_Clear()
{
    LCD_Send_Cmd(0x01);
    HAL_Delay(1);
}


void LCD_Init()
{
    HAL_Delay(50);
    LCD_Send_Cmd(0x30);
    HAL_Delay(5);
    LCD_Send_Cmd(0x30);
    HAL_Delay(1);
    LCD_Send_Cmd(0x30);
    HAL_Delay(10);
    LCD_Send_Cmd(0x20);
    HAL_Delay(10);


    LCD_Send_Cmd(0x28);        //function set
    HAL_Delay(1);
    LCD_Send_Cmd(0x08);        //Display on/off
    HAL_Delay(1);
    LCD_Send_Cmd(0x01);        //clear display
    HAL_Delay(1);
    LCD_Send_Cmd(0x06);        //Enter mode
    HAL_Delay(1);
    LCD_Send_Cmd(0x0C);        //Display on/off
    HAL_Delay(1);


}


void LCD_Send_String (char *str)
{
    while(*str)
    {
        LCD_Send_Data(*str++);
    }
    HAL_Delay(1);
}


void LCD_Put_Cur(uint8_t row,uint8_t col)
{
    LCD_Send_Cmd(0x80 | (col + (0x40 * row)));
}