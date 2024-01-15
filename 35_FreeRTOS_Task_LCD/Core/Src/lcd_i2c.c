/*
 * lcd.c
 *
 *  Created on: Oct 5, 2023
 *      Author: dg_su
 */


#include <lcd_i2c.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"


void LCD_I2C_CMD(uint8_t a,uint8_t rs){
	uint8_t dato = a<<4;
	dato |= rs << RS_BIT;
	dato |= 1<<EN_BIT;
	dato |= 1<<BL_BIT;
	HAL_I2C_Master_Transmit(&hi2c1,ADDRESS_LCD, &dato, 1, 100);
	HAL_Delay(1);
	dato &= ~(1<<EN_BIT);
	HAL_I2C_Master_Transmit(&hi2c1,ADDRESS_LCD, &dato, 1, 100);

}

void LCD_I2C_INIT(void){

	LCD_I2C_CMD(0x03,0);
	HAL_Delay(3);
	LCD_I2C_CMD(0x03,0);
	LCD_I2C_CMD(0x03,0);
	LCD_I2C_CMD(0x02,0);
	LCD_I2C_CMD(0x02,0);
	LCD_I2C_CMD(0x08,0);
	LCD_I2C_CMD(0x00,0);
	LCD_I2C_CMD(0x08,0);
	LCD_I2C_CMD(0x00,0);
	LCD_I2C_CMD(0x01,0);
	LCD_I2C_CMD(0x00,0);
	//Con curso activado es 0XD,  sin cursor : 0xC
	LCD_I2C_CMD(0x0D,0);
}


void LCD_I2C_SET_CURSOR(uint8_t x,Ubicacion y){

	uint8_t m,n;

	switch (y) {
		case fila1:
			m=0x80+x;
			n=(0x80+x)>>4;
			LCD_I2C_CMD(n,0);
			LCD_I2C_CMD(m,0);
			break;
		case fila2:
			m=0xC0+x;
			n=(0xC0+x)>>4;
			LCD_I2C_CMD(n,0);
			LCD_I2C_CMD(m,0);
			break;
		case fila3:
			m=0x94+x;
			n=(0x94+x)>>4;
			LCD_I2C_CMD(n,0);
			LCD_I2C_CMD(m,0);
			break;
		case fila4:
			m=0xD4+x;
			n=(0xD4+x)>>4;
			LCD_I2C_CMD(n,0);
			LCD_I2C_CMD(m,0);
			break;
	}


}
void LCD_I2C_PRINT_CHAR(char a){
	uint8_t m,n;
	m = a>>4;
    n = a;

    LCD_I2C_CMD(m,1);
    LCD_I2C_CMD(n,1);

}


void LCD_I2C_PRINT_STRING(char *a){


	while(*a){
		LCD_I2C_PRINT_CHAR(*a++);
	}

}

void LCD_I2C_Clear(void){

	LCD_I2C_CMD(0x00,0);
	LCD_I2C_CMD(0x01,0);
}
void LCD_I2C_Home(void){

	LCD_I2C_CMD(0x00,0);
	LCD_I2C_CMD(0x02,0);
}

void LCD_I2C_CursorOff(void){
	LCD_I2C_CMD(0x00,0);
	LCD_I2C_CMD(0x0C,0);
}
/*
void LCD_STM32_New_Char(uint8_t a,uint8_t b,uint8_t c,uint8_t d ,uint8_t e ,uint8_t f,uint8_t g,uint8_t h,uint8_t i){

	  uint8_t m,n;
		  switch(a){
			  case 1:
			  LCD_STM32_CMD(0x04);
			  LCD_STM32_CMD(0x00);
			  RS_ON;
			  m=b>>4;
			  n=b;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=d>>4;
			  n=d;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=e>>4;
			  n=e;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=f>>4;
			  n=f;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=g>>4;
			  n=g;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=h>>4;
			  n=h;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=i>>4;
			  n=i;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  RS_OFF;
			  LCD_STM32_CMD(0x00);
			  LCD_STM32_CMD(0x01);
			  HAL_Delay(100);
			  break;
			  case 2:
			  LCD_STM32_CMD(0x04);
			  LCD_STM32_CMD(0x08);
			  RS_ON;
			  m=b>>4;
			  n=b;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=d>>4;
			  n=d;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=e>>4;
			  n=e;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=f>>4;
			  n=f;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=g>>4;
			  n=g;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=h>>4;
			  n=h;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=i>>4;
			  n=i;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  RS_OFF;
			  LCD_STM32_CMD(0x00);
			  LCD_STM32_CMD(0x01);
			  HAL_Delay(100);
			  break;
			  case 3:
			  LCD_STM32_CMD(0x04);
			  LCD_STM32_CMD(0xFF);
			  RS_ON;
			  m=b>>4;
			  n=b;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=c>>4;
			  n=c;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=d>>4;
			  n=d;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=e>>4;
			  n=e;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=f>>4;
			  n=f;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=g>>4;
			  n=g;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=h>>4;
			  n=h;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  m=i>>4;
			  n=i;
			  LCD_STM32_CMD(m);
			  LCD_STM32_CMD(n);
			  RS_OFF;
			  LCD_STM32_CMD(0x00);
			  LCD_STM32_CMD(0x01);
			  HAL_Delay(100);
			  break;
		  }



}
void LCD_STM32_Print_New_Char(uint8_t a){
	RS_ON;
	LCD_STM32_CMD(0x00);
	LCD_STM32_CMD(a-1);
	RS_OFF;
}

*/
