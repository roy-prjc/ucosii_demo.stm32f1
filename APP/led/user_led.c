/*
 * user_led.c
 *
 *	驱动普通IO输出
 *
 *  Created on: 2022-6-12
 *      Author: tly
 */

#include "user_led.h"


/*****************************************************************************
Function Name        :: void LED_Init(void)
Function Description :: 端口初始化
Bank Ports           :: GPIOB.5 、 GPIOE.5
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 ::
Function called	-

Last Chang Date      : 2022/06/15
*****************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);	    //使能PB,PE端口时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;			    //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);			     //初始化GPIOB.5
  GPIO_SetBits(GPIOB,GPIO_Pin_5);					//PB.5 输出高
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //LED1-->PE.5推挽输出
  GPIO_Init(GPIOE, &GPIO_InitStructure);	  	       //初始化GPIO
  GPIO_SetBits(GPIOE,GPIO_Pin_5); 			 //PE.5 输出高 	
	
}


