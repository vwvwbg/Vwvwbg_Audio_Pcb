#include <REG51.H>  
#include <intrins.h>
#include <absacc.h>
#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#include "uart.h"
sfr P3M0 =0xb1;
sfr P3M1 =0xb2;
//#include "ds1302.c"
#define uchar unsigned char
#define uint  unsigned int
int second,minute,hour,day,month,week,year,zwc,fwc,wdc,bal,txt,wendu;
uchar xdata buf[64];
/*******************���Ե�Ƭ��STC12LE5A60S2******************************/
/*******************���� 33MHz*******************************************/




/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڳ�ʼ��
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������
 - ����˵������
 **************************************************************************/
void UART_Init()     
{
 PCON|=0x00; //PCON�����λSMOD=1ʱ�����ʼӱ� 
 TMOD=0x20;  //ʱ��1Ϊ��ʽ2 ��ֵ�Զ�װ�� ����������
 TH1=0xf7;   //��ʱ����ʼΪ0XF7������Ϊ33MHz��������ʵ�ʲ����Ĳ�����Ϊ9600bps
 TL1=0xf7;	 //ͬ��  f7
 SCON=0x50;	 //��������Ϊ��ʽ1,REN=1,�������
 TR1=1;      //������ʱ��1
 ES=1;       //ʹ�ܴ��ڽ����жϣ�
// EA=1;     //�������ж�
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ����ֽڵĺ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����mydata:Ҫ���͵�һ���ֽ�
 - ����˵������
 - ע������һ���ֽڣ��Ǵ��ڷ��͵Ļ�������
 **************************************************************************/
void UART_Send_Byte(unsigned char mydata)	
{
 ES=0;
 TI=0;
 SBUF=mydata;
 while(!TI);
 TI=0;
 ES=1;
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ����ַ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����s:ָ���ַ�����ָ��
 - ����˵������
 **************************************************************************/
void UART_Send_Str(char *s)
{
 int i=0;
 while(s[i]!=0)
 {
 	UART_Send_Byte(s[i]);
 	i++;
 }
 
}
void UART_Send_END(void)
{
	 UART_Send_Byte(0xFF);
	 UART_Send_Byte(0xFF);
	 UART_Send_Byte(0xFF);
}
/*
void UART_Send_HEX(char *buff,char len)
{
	while(len--)
	UART_Send_Byte(*buff++);
}
*/
void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}


/*
void distime()					 //��ʾʱ��	   	
{				
			 	
				sprintf(buf,"t0.txt=\"%02d:%02d:%02d\"",hour,minute,second);
			    UART_Send_Str(buf);
				UART_Send_END();
                sprintf(buf,"t1.txt=\"20%02d��%d��%2d��\"",year,month,day);
				UART_Send_Str(buf);
				UART_Send_END();						
				if(week==1)
				{
				 	UART_Send_Str("t2.txt=\"����һ\"");
				    UART_Send_END();
				}
				if(week==2)
				{
				     UART_Send_Str("t2.txt=\"���ڶ�\"");
				     UART_Send_END();
				 }
				if(week==3)
				{
				     UART_Send_Str("t2.txt=\"������\"");
				     UART_Send_END();
				 }
				if(week==4)
				{
				     UART_Send_Str("t2.txt=\"������\"");
				     UART_Send_END();
				 }
				if(week==5)
				{
				     UART_Send_Str("t2.txt=\"������\"");
				     UART_Send_END();
				 }
				if(week==6)
				{
				     UART_Send_Str("t2.txt=\"������\"");
				     UART_Send_END();
				 }
				if(week==7)	
				{
				     UART_Send_Str("t2.txt=\"������\"");
				     UART_Send_END();
				 }
					  
}
*/
void main(void)
{
 uint s=0;
 second=50;minute=48;hour=12;day=15;month=7;week=2;year=16;bal=0;txt=0;wendu=0;
 P3M0&= ~0X02;
 P3M1|=0X02;   //TXǿ����
 UART_Init();  //��ʼ�����ڣ����ϵľ���Ϊ33MHz��ʵ�ʵĲ�����Ϊ9600bps 
 delayms(80);//�ȴ���Ļ��ʼ��,����50ms����
 UART_Send_END();//����һ�ν�����������ϵ�����Ĵ����Ӳ�����  
 UART_Send_Str("page 0");
 UART_Send_END(); 
 delayms(2000);
   while(s<=100)
  {
  	s++;
	if(bal!=100)
	{
		bal++;
		txt++;
		delayms(50);
	 	sprintf(buf,"j0.val=%d",bal);
	 	UART_Send_Str(buf);
	 	UART_Send_END();
	 	sprintf(buf,"t2.txt=\"%d%%\"",txt);
	 	UART_Send_Str(buf);
	 	UART_Send_END();
	}
	else
	 {
		UART_Send_Str("page 1");
		UART_Send_END();
		//UART_Send_Str("t2.txt=\"����\"");	
		//UART_Send_END();
		while(1)
		{
			for(second=0;second<60;second++) 
			{	
				delayms(1000);
		 		sprintf(buf,"t0.txt=\"%02d:%02d:%02d\"",hour,minute,second);
		 		UART_Send_Str(buf);
		 		UART_Send_END();
				UART_Send_Str("t2.txt=\"������\"");
				UART_Send_END();
				sprintf(buf,"t3.txt=\"%d\"",wendu);
	 			UART_Send_Str(buf);
	 			UART_Send_END();
				wendu++;
		 	}
		 		second=0;
				wendu=0;	
		 }
		
	 }
	

	}
	;
 

}


