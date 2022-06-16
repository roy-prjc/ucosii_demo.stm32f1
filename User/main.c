/*
 * main.c
 *
 *	UCosIIϵͳ��ֲ����
 *
 *  Created on: 2022-6-15
 *      Author: tly
 */


#include "sys.h" 	
#include "delay.h"	
#include "user_led.h"
#include "includes.h"


//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�����ջ	
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);	
 			   
//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO       			7 
//���������ջ��С
#define LED0_STK_SIZE  		    		64
//�����ջ	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);


//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO       			6 
//���������ջ��С
#define LED1_STK_SIZE  					64
//�����ջ
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);

 
 
 /*****************************************************************************
Function Name        :: int main(void)
Function Description :: ������
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	OSInit();   
 	OSTaskCreate(//������ʼ����
								start_task,
								(void *)0,
								(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],
								START_TASK_PRIO );
	OSStart();	  	 
}


	  
//��ʼ����
void start_task(void *pdata)
{
  OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
	
 	OSTaskCreate(//��������1
								led0_task,
								(void *)0,
								(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],
								LED0_TASK_PRIO);			
								
 	OSTaskCreate(//��������2
								led1_task,
								(void *)0,
								(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],
								LED1_TASK_PRIO);	
								
	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}

//LED0����
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

//LED1����
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


