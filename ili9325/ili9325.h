/*
 * ili9325.h
 *
 *  Created on: Jul 27, 2022
 *      Author: rus
 */

#ifndef ILI9325_H_
#define ILI9325_H_

#include "main.h"

#define LCD_REG              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */

void ILI9325_Init(void);
void ILI9325_WriteIndex(uint16_t index);
void ILI9325_WriteData(uint16_t data);
uint16_t ILI9325_ReadData(void);
void ILI9325_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t ILI9325_ReadReg(uint16_t LCD_Reg);

#endif /* ILI9325_H_ */
