/*
 * ili9325.c
 *
 *  Created on: Jul 27, 2022
 *      Author: rus
 */

#include "ili9325.h"



void ILI9325_Init()
{
	ILI9325_WriteReg(0x01, 0x0000); /* set Driver Output Control */
	ILI9325_WriteReg(0x02, 0x0700); /* set 1 line inversion */
	ILI9325_WriteReg(0x03, (1 << 12) | (1 << 5) | (1 << 4) | (1 << 3));
	ILI9325_WriteReg(0x04, 0x0000); /* Resize register */
	ILI9325_WriteReg(0x08, 0x0207); /* set the back porch and front porch */
	ILI9325_WriteReg(0x09, 0x0000); /* set non-display area refresh cycle ISC[3:0] */
	ILI9325_WriteReg(0x0A, 0x0000); /* FMARK function */
	ILI9325_WriteReg(0x0C, 0x0000); /* RGB interface setting */
	ILI9325_WriteReg(0x0D, 0x0000); /* Frame marker Position */
	ILI9325_WriteReg(0x0F, 0x0000); /* RGB interface polarity */
	/*************Power On sequence ****************/
	ILI9325_WriteReg(0x10, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	ILI9325_WriteReg(0x11, 0x0007); /* DC1[2:0], DC0[2:0], VC[2:0] */
	ILI9325_WriteReg(0x12, 0x0000); /* VREG1OUT voltage */
	ILI9325_WriteReg(0x13, 0x0000); /* VDV[4:0] for VCOM amplitude */
	ILI9325_WriteReg(0x07, 0x0001);
	HAL_Delay(200);
	/* Dis-charge capacitor power voltage */
	ILI9325_WriteReg(0x10, 0x1090); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	ILI9325_WriteReg(0x11, 0x0227); /* Set DC1[2:0], DC0[2:0], VC[2:0] */
	HAL_Delay(50); /* Delay 50ms */
	ILI9325_WriteReg(0x12, 0x001F);
	HAL_Delay(50); /* Delay 50ms */
	ILI9325_WriteReg(0x13, 0x1500); /* VDV[4:0] for VCOM amplitude */
	ILI9325_WriteReg(0x29, 0x0027); /* 04 VCM[5:0] for VCOMH */
	ILI9325_WriteReg(0x2B, 0x000D); /* Set Frame Rate */
	HAL_Delay(50); /* Delay 50ms */
	ILI9325_WriteReg(0x20, 0x0000); /* GRAM horizontal Address */
	ILI9325_WriteReg(0x21, 0x0000); /* GRAM Vertical Address */
	/* ----------- Adjust the Gamma Curve ---------- */
	ILI9325_WriteReg(0x30, 0x0000);
	ILI9325_WriteReg(0x31, 0x0707);
	ILI9325_WriteReg(0x32, 0x0307);
	ILI9325_WriteReg(0x35, 0x0200);
	ILI9325_WriteReg(0x36, 0x0008);
	ILI9325_WriteReg(0x37, 0x0004);
	ILI9325_WriteReg(0x38, 0x0000);
	ILI9325_WriteReg(0x39, 0x0707);
	ILI9325_WriteReg(0x3C, 0x0002);
	ILI9325_WriteReg(0x3D, 0x1D04);
	/* ------------------ Set GRAM area --------------- */
	ILI9325_WriteReg(0x50, 0x0000); /* Horizontal GRAM Start Address */
	ILI9325_WriteReg(0x51, 0x00EF); /* Horizontal GRAM End Address */
	ILI9325_WriteReg(0x52, 0x0000); /* Vertical GRAM Start Address */
	ILI9325_WriteReg(0x53, 0x013F); /* Vertical GRAM Start Address */
	ILI9325_WriteReg(0x60, 0xA700); /* Gate Scan Line */
	ILI9325_WriteReg(0x61, 0x0001); /* NDL,VLE, REV */
	ILI9325_WriteReg(0x6A, 0x0000); /* set scrolling line */
	/* -------------- Partial Display Control --------- */
	ILI9325_WriteReg(0x80, 0x0000);
	ILI9325_WriteReg(0x81, 0x0000);
	ILI9325_WriteReg(0x82, 0x0000);
	ILI9325_WriteReg(0x83, 0x0000);
	ILI9325_WriteReg(0x84, 0x0000);
	ILI9325_WriteReg(0x85, 0x0000);
	/* -------------- Panel Control ------------------- */
	ILI9325_WriteReg(0x90, 0x0010);
	ILI9325_WriteReg(0x92, 0x0600);
	ILI9325_WriteReg(0x07, 0x0133); /* 262K color and display ON */
}

void ILI9325_WriteIndex(uint16_t index)
{
	LCD_REG = index;
}

void ILI9325_WriteData(uint16_t data)
{
	LCD_RAM = data;
}

uint16_t ILI9325_ReadData(void)
{
	return LCD_RAM;
}

void ILI9325_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	/* Write 16-bit Index, then Write Reg */
	ILI9325_WriteIndex(LCD_Reg);
	/* Write 16-bit Reg */
	ILI9325_WriteData(LCD_RegValue);
}

uint16_t ILI9325_ReadReg(uint16_t LCD_Reg)
{
	/* Write 16-bit Index (then Read Reg) */
	ILI9325_WriteIndex(LCD_Reg);

	/* Read 16-bit Reg */
	return ILI9325_ReadData();
}
