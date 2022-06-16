/*
 * main.c
 *
 *	UCosII系统移植程序
 *
 *  Created on: 2022-6-15
 *      Author: tly
 */


#include "sys.h" 	
#include "delay.h"	
#include "user_led.h"
#include "includes.h"


//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	
 			   
//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);


//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED1_STK_SIZE  					64
//任务堆栈
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *pdata);

 
 
 /*****************************************************************************
Function Name        :: int main(void)
Function Description :: 主函数
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	OSInit();   
 	OSTaskCreate(//创建起始任务
								start_task,
								(void *)0,
								(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],
								START_TASK_PRIO );
	OSStart();	  	 
}


	  
//开始任务
void start_task(void *pdata)
{
  OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
	
 	OSTaskCreate(//创建任务1
								led0_task,
								(void *)0,
								(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],
								LED0_TASK_PRIO);			
								
 	OSTaskCreate(//创建任务2
								led1_task,
								(void *)0,
								(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],
								LED1_TASK_PRIO);	
								
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//LED0任务
void led0_task(void *pdata)
{	 	
	while(1)
	{
		LED0_ON;
		delay_ms(80);
		LED0_OFF;
		delay_ms(920);
	};
}

//LED1任务
void led1_task(void *pdata)
{	  
	while(1)
	{
		LED1_ON;
		delay_ms(3000);
		LED1_OFF;
		delay_ms(300);
	};
}


