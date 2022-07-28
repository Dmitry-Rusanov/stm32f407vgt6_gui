/*********************************************************************************************************
*
* File                : touch_panel.h
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#ifndef _TOUCH_PANEL_H_
#define _TOUCH_PANEL_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
/**
 * @brief Definition for TouchPanel
 */

/*ScreenSamples*/
#define SS_X0 517
#define SS_Y0 3169
#define SS_X1 2567
#define SS_Y1 3200
#define SS_X2 1952
#define SS_Y2 597


/* Private typedef -----------------------------------------------------------*/
typedef  struct POINT 
{
   uint16_t x;
   uint16_t y;
}Coordinate;


typedef struct Matrix 
{            
long double An,  
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
} Matrix ;

/* Private variables ---------------------------------------------------------*/
extern Coordinate ScreenSample[3];
extern Coordinate DisplaySample[3];
extern Matrix matrix ;
extern Coordinate  display ;

/* Private define ------------------------------------------------------------*/

#define  CHX   0x90
#define  CHY   0xd0

/* Private function prototypes -----------------------------------------------*/        
void TP_Init(void);  
Coordinate *Read_Ads7846(void);
void TouchPanel_Calibrate(void);
void TouchPanel_Calibrate_default(void);
void DrawCross(uint16_t Xpos, uint16_t Ypos);
void TP_DrawPoint(uint16_t Xpos, uint16_t Ypos);
FunctionalState setCalibrationMatrix( Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr);
FunctionalState getDisplayPoint(Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr );

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


