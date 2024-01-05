/*
 * lcd.h
 *
 *  Created on: Oct 5, 2023
 *      Author: dg_su
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_


#include "stdint.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define ADDRESS_ (0x3F << 1)
#define ADDRESS_LCD (0x27 << 1)


#define RS_BIT 	0
#define RW_BIT  1
#define EN_BIT	2
#define D4_BIT 	4
#define D5_BIT 	5
#define D6_BIT 	6
#define D7_BIT 	7

#define BL_BIT	3	//backlight lcd

typedef enum{
	fila1=0,
	fila2,
	fila3,
	fila4
}Ubicacion;


void LCD_I2C_CMD(uint8_t a,uint8_t rs);
void LCD_I2C_INIT(void);
void LCD_I2C_SET_CURSOR(uint8_t x,Ubicacion y);
void LCD_I2C_PRINT_CHAR(char a);
void LCD_I2C_PRINT_STRING(char *a);
void LCD_I2C_New_Char(uint8_t a,uint8_t b,uint8_t c,uint8_t d ,uint8_t e ,uint8_t f,uint8_t g,uint8_t h,uint8_t i);
void LCD_I2C_Print_New_Char(uint8_t a);
void LCD_I2C_Clear(void);
void LCD_I2C_Home(void);
void LCD_I2C_CursorOff(void);


#endif /* INC_LCD_I2C_H_ */
