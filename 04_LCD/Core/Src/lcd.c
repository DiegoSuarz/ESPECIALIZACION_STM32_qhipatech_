/*
 * lcd.c
 *
 *  Created on: Oct 5, 2023
 *      Author: dg_su
 */


#include "lcd.h"
#include "main.h"
#include "stm32f4xx_hal.h"


void LCD_STM32_CMD(uint8_t a){
	E_OFF;
	E_ON;
	LCD_STM32_BUS(a);
	HAL_Delay(2);
	E_OFF;
}
void LCD_STM32_BUS(uint8_t a){

	//0001
	if(a & 0x01){D4_ON;}
	else{D4_OFF};
	//0010
	if(a & 0x02){D5_ON;}
	else{D5_OFF};
	//0100
	if(a & 0x04){D6_ON;}
	else{D6_OFF};
	//1000
	if(a & 0x08){D7_ON;}
	else{D7_OFF};
}

void LCD_STM32_INIT(void){

	LCD_STM32_CMD(0x03);
	HAL_Delay(3);
	LCD_STM32_CMD(0x03);
	LCD_STM32_CMD(0x03);
	LCD_STM32_CMD(0x02);
	LCD_STM32_CMD(0x02);
	LCD_STM32_CMD(0x08);
	LCD_STM32_CMD(0x00);
	LCD_STM32_CMD(0x08);
	LCD_STM32_CMD(0x00);
	LCD_STM32_CMD(0x01);
	LCD_STM32_CMD(0x00);
	//Con curso activado es 0XD,  sin cursor : 0xC
	LCD_STM32_CMD(0x0D);
}


void LCD_STM32_SET_CURSOR(uint8_t x,Ubicacion y){

	uint8_t m,n;

	RS_OFF;
	switch (y) {
		case fila1:
			m=0x80+x;
			n=(0x80+x)>>4;
			LCD_STM32_CMD(n);
			LCD_STM32_CMD(m);
			break;
		case fila2:
			m=0xC0+x;
			n=(0xC0+x)>>4;
			LCD_STM32_CMD(n);
			LCD_STM32_CMD(m);
			break;
		case fila3:
			m=0x94+x;
			n=(0x94+x)>>4;
			LCD_STM32_CMD(n);
			LCD_STM32_CMD(m);
			break;
		case fila4:
			m=0xD4+x;
			n=(0xD4+x)>>4;
			LCD_STM32_CMD(n);
			LCD_STM32_CMD(m);
			break;
	}


}
void LCD_STM32_PRINT_CHAR(char a){
	uint8_t m,n;
	m = a>>4;
    n = a;
	RS_ON;
	LCD_STM32_CMD(m);
	LCD_STM32_CMD(n);

}
void LCD_STM32_PRINT_STRING(char *a){


	while(*a){
			LCD_STM32_PRINT_CHAR(*a++);
	}

}

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
void LCD_STM32_Clear(void){
	RS_OFF;
	LCD_STM32_CMD(0x00);
	LCD_STM32_CMD(0x01);
}
void LCD_STM32_Home(void){
	RS_OFF;
    LCD_STM32_CMD(0x00);
    LCD_STM32_CMD(0x02);
}
