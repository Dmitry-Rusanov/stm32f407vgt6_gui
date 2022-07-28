/*********************************************************************************************************
*
* File                : touch_panel.c
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

/* Includes ------------------------------------------------------------------*/
#include "touch_panel.h"
#include "../lvgl/lvgl.h"
#include "strings.h"

#define TP_CS(x)  x ? HAL_GPIO_WritePin(LCDTP_CS_GPIO_Port, LCDTP_CS_Pin, GPIO_PIN_SET): HAL_GPIO_WritePin(LCDTP_CS_GPIO_Port, LCDTP_CS_Pin, GPIO_PIN_RESET)

/* Private variables ---------------------------------------------------------*/
Matrix matrix ;
Coordinate  display ;


Coordinate ScreenSample[3];

Coordinate DisplaySample[3] = {
                                {30, 45},
                                {220, 45},
                                {160,210}
                              };

/* Private define ------------------------------------------------------------*/
#define THRESHOLD 2
extern SPI_HandleTypeDef hspi2;
#define TP_hspi hspi2
/*******************************************************************************
* Function Name  : TP_Init
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void TP_Init(void) 
{ 

} 
/*******************************************************************************
* Function Name  : DelayUS
* Description    : 
* Input          : - cnt:
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void DelayUS(uint32_t cnt)
{
  uint32_t i;
  i = cnt * 4;
  while(i--);
}
/*******************************************************************************
* Function Name  : WR_CMD
* Description    : 
* Input          : - cmd: 
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
static void WR_CMD (uint8_t cmd)  
{ 
  HAL_SPI_Transmit(&TP_hspi,&cmd,1,1000);
} 
/*******************************************************************************
* Function Name  : RD_AD
* Description    : 
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
static int RD_AD(void)  
{ 
  uint8_t buf[2];
  int value;
  HAL_SPI_Receive(&TP_hspi,buf,2,1000);
  value = (uint16_t)((buf[0] << 8) + buf[1]) >> 3;
  return value;
} 
/*******************************************************************************
* Function Name  : Read_X
* Description    : Read ADS7843 ADC X 
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
int Read_X(void)  
{  
  int i; 
  TP_CS(0); 
  DelayUS(1); 
  WR_CMD(CHX); 
  DelayUS(1); 
  i=RD_AD(); 
  TP_CS(1); 
  return i;    
} 
/*******************************************************************************
* Function Name  : Read_Y
* Description    : Read ADS7843 ADC Y
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
int Read_Y(void)  
{  
  int i; 
  TP_CS(0); 
  DelayUS(1); 
  WR_CMD(CHY); 
  DelayUS(1); 
  i=RD_AD(); 
  TP_CS(1); 
  return i;     
} 
/*******************************************************************************
* Function Name  : TP_GetAdXY
* Description    : Read ADS7843
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
void TP_GetAdXY(int *x,int *y)  
{ 
  int adx,ady; 
  adx=Read_X(); 
  DelayUS(1); 
  ady=Read_Y(); 
  *x=adx; 
  *y=ady; 
} 

/*******************************************************************************
* Function Name  : DrawCross
* Description    : 
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void DrawCross(uint16_t Xpos,uint16_t Ypos)
{
	lv_obj_clean(lv_scr_act());
    static lv_point_t line1_points[2];
    line1_points[0].x = Xpos + 10;
    line1_points[0].y = Ypos;
    line1_points[1].x = Xpos - 10;
    line1_points[1].y = Ypos;
    static lv_point_t line2_points[2];
    line2_points[0].x = Xpos;
    line2_points[0].y = Ypos + 10;
    line2_points[1].x = Xpos;
    line2_points[1].y = Ypos -10;
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 1);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line1_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_align(line1, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t * line2;
    line2 = lv_line_create(lv_scr_act());
    lv_line_set_points(line2, line2_points, 2);     /*Set the points*/
    lv_obj_add_style(line2, &style_line, 0);
    lv_obj_align(line2, LV_ALIGN_TOP_LEFT, 0, 0);

}  
  
/*******************************************************************************
* Function Name  : Read_Ads7846
* Description    : Get TouchPanel X Y
* Input          : None
* Output         : None
* Return         : Coordinate *
* Attention      : None
*******************************************************************************/
Coordinate *Read_Ads7846(void)
{

  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}};

  do
  {
    TP_GetAdXY(TP_X,TP_Y);
    buffer[0][count]=TP_X[0];
    buffer[1][count]=TP_Y[0];
    count++;
  }
  while(!(HAL_GPIO_ReadPin(LCDTP_IRQ_GPIO_Port, LCDTP_IRQ_Pin))&& count<9);  /* TP_INT_IN  */
  if(count==9)   /* Average X Y  */
  {
    /* Average X  */
    temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
    temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
    temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;

    m0=temp[0]-temp[1];
    m1=temp[1]-temp[2];
    m2=temp[2]-temp[0];

    m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
    m2=m2>0?m2:(-m2);

    if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;

    if(m0<m1)
    {
      if(m2<m0)
        screen.x=(temp[0]+temp[2])/2;
      else
        screen.x=(temp[0]+temp[1])/2;
    }
    else if(m2<m1)
      screen.x=(temp[0]+temp[2])/2;
    else
      screen.x=(temp[1]+temp[2])/2;

    /* Average Y  */
    temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
    temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
    temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
    m0=temp[0]-temp[1];
    m1=temp[1]-temp[2];
    m2=temp[2]-temp[0];
    m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
    m2=m2>0?m2:(-m2);
    if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

    if(m0<m1)
    {
      if(m2<m0)
        screen.y=(temp[0]+temp[2])/2;
      else
        screen.y=(temp[0]+temp[1])/2;
      }
    else if(m2<m1)
       screen.y=(temp[0]+temp[2])/2;
    else
       screen.y=(temp[1]+temp[2])/2;

    return &screen;
  }
  return 0; 
}
   

/*******************************************************************************
* Function Name  : setCalibrationMatrix
* Description    : Calculate K A B C D E F
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
FunctionalState setCalibrationMatrix( Coordinate * displayPtr,
                          Coordinate * screenPtr,
                          Matrix * matrixPtr)
{

  FunctionalState retTHRESHOLD = ENABLE ;
  /* K=(X0-X2) (Y1-Y2)-(X1-X2) (Y0-Y2) */
  matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  if( matrixPtr->Divider == 0 )
  {
    retTHRESHOLD = DISABLE;
  }
  else
  {
    /* A=((XD0-XD2) (Y1-Y2)-(XD1-XD2) (Y0-Y2))/K  */
    matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  /* B=((X0-X2) (XD1-XD2)-(XD0-XD2) (X1-X2))/K  */
    matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                    ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
    /* C=(Y0(X2XD1-X1XD2)+Y1(X0XD2-X2XD0)+Y2(X1XD0-X0XD1))/K */
    matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
    /* D=((YD0-YD2) (Y1-Y2)-(YD1-YD2) (Y0-Y2))/K  */
    matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    /* E=((X0-X2) (YD1-YD2)-(YD0-YD2) (X1-X2))/K  */
    matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                    ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
    /* F=(Y0(X2YD1-X1YD2)+Y1(X0YD2-X2YD0)+Y2(X1YD0-X0YD1))/K */
    matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
  }
  return( retTHRESHOLD ) ;
}

/*******************************************************************************
* Function Name  : getDisplayPoint
* Description    : Touch panel X Y to display X Y
* Input          : None
* Output         : None
* Return         : 
* Attention      : None
*******************************************************************************/
FunctionalState getDisplayPoint(Coordinate * displayPtr,
                     Coordinate * screenPtr,
                     Matrix * matrixPtr )
{
  FunctionalState retTHRESHOLD =ENABLE ;
  /*
  An=168
  */
  if( matrixPtr->Divider != 0 )
  {
    /* XD = AX+BY+C */        
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;
    /* YD = DX+EY+F */        
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;
  }
  else
  {
    retTHRESHOLD = DISABLE;
  }
  return(retTHRESHOLD);
} 


/*******************************************************************************
* Function Name  : TouchPanel_Calibrate
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void TouchPanel_Calibrate(void)
{
  uint8_t i;
  Coordinate * Ptr;

  for(i=0;i<3;i++)
  {
	HAL_Delay(1000);
    DrawCross(DisplaySample[i].x,DisplaySample[i].y);
    do
    {
    	lv_task_handler();
    	Ptr=Read_Ads7846();
    }
    while( Ptr == (void*)0 );
    ScreenSample[i].x= Ptr->x; ScreenSample[i].y= Ptr->y;
  }
  setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix );

  char str[320]={0};
  lv_obj_clean(lv_scr_act());
  /*ScreenSample[0].x*/
  lv_obj_t * label1 = lv_label_create(lv_scr_act());
  lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 20, 20);
  lv_obj_set_width(label1, 300);
  sprintf(str,"ScreenSample[0].x = %d",ScreenSample[0].x);
  lv_label_set_text(label1, str);
  /*ScreenSample[0].y*/
  lv_obj_t * label2 = lv_label_create(lv_scr_act());
  lv_obj_align(label2, LV_ALIGN_TOP_LEFT, 20, 40);
  lv_obj_set_width(label2, 300);
  sprintf(str,"ScreenSample[0].y = %d",ScreenSample[0].y);
  lv_label_set_text(label2, str);
  /*ScreenSample[1].x*/
  lv_obj_t * label3 = lv_label_create(lv_scr_act());
  lv_obj_align(label3, LV_ALIGN_TOP_LEFT, 20, 60);
  lv_obj_set_width(label3, 300);
  sprintf(str,"ScreenSample[1].x = %d",ScreenSample[1].x);
  lv_label_set_text(label3, str);
  /*ScreenSample[1].y*/
  lv_obj_t * label4 = lv_label_create(lv_scr_act());
  lv_obj_align(label4, LV_ALIGN_TOP_LEFT, 20, 80);
  lv_obj_set_width(label4, 300);
  sprintf(str,"ScreenSample[1].y = %d",ScreenSample[1].y);
  lv_label_set_text(label4, str);
  /*ScreenSample[2].x*/
  lv_obj_t * label5 = lv_label_create(lv_scr_act());
  lv_obj_align(label5, LV_ALIGN_TOP_LEFT, 20, 100);
  lv_obj_set_width(label5, 300);
  sprintf(str,"ScreenSample[1].x = %d",ScreenSample[2].x);
  lv_label_set_text(label5, str);
  /*ScreenSample[2].y*/
  lv_obj_t * label6 = lv_label_create(lv_scr_act());
  lv_obj_align(label6, LV_ALIGN_TOP_LEFT, 20, 120);
  lv_obj_set_width(label6, 300);
  sprintf(str,"ScreenSample[1].y = %d",ScreenSample[2].y);
  lv_label_set_text(label6, str);

  lv_obj_t * label7 = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label7, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
  lv_label_set_recolor(label7, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_text(label7, "Please, if you do not use EEPROM,"
		  	  	  	  	  	" then write the result to the file #ff0000 touch_panel.h#");
  lv_obj_set_width(label7, 300);  /*Set smaller width to make the lines wrap*/
  lv_obj_align(label7, LV_ALIGN_TOP_LEFT, 20, 160);
  lv_obj_set_width(label7, 300);

} 

void TouchPanel_Calibrate_default(void)
{
	ScreenSample[0].x = SS_X0;
	ScreenSample[0].y = SS_Y0;
	ScreenSample[1].x = SS_X1;
	ScreenSample[1].y = SS_Y1;
	ScreenSample[2].x = SS_X2;
	ScreenSample[2].y = SS_Y2;
	setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix );
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
