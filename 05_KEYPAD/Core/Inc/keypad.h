/*
 * keypad.h
 *
 *  Created on: Oct 5, 2023
 *      Author: dg_su
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#define ROW1_Pin GPIO_PIN_8
#define ROW1_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_10
#define ROW2_GPIO_Port GPIOB
#define ROW3_Pin GPIO_PIN_4
#define ROW3_GPIO_Port GPIOB
#define ROW4_Pin GPIO_PIN_5
#define ROW4_GPIO_Port GPIOB

#define COL1_Pin GPIO_PIN_0
#define COL1_GPIO_Port GPIOA
#define COL2_Pin GPIO_PIN_1
#define COL2_GPIO_Port GPIOA
#define COL3_Pin GPIO_PIN_4
#define COL3_GPIO_Port GPIOA
#define COL4_Pin GPIO_PIN_0
#define COL4_GPIO_Port GPIOB

void Keypad_Init(void);
char  Keypad_Read(void);

#endif /* INC_KEYPAD_H_ */
