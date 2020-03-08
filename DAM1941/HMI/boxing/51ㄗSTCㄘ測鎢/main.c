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
uchar xdata boxing[]={120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};

uchar code zhengxianbo[] = 
{
 0x7F,0x85,0x8B,0x92,0x98,0x9E,0xA4,0xAA,0xB0,0xB6,0xBB,0xC1,0xC6,0xCB,0xD0,0xD5
,0xD9,0xDD,0xE2,0xE5,0xE9,0xEC,0xEF,0xF2,0xF5,0xF7,0xF9,0xFB,0xFC,0xFD,0xFE,0xFE
,0xFE,0xFE,0xFE,0xFD,0xFC,0xFB,0xF9,0xF7,0xF5,0xF2,0xEF,0xEC,0xE9,0xE5,0xE2,0xDD
,0xD9,0xD5,0xD0,0xCB,0xC6,0xC1,0xBB,0xB6,0xB0,0xAA,0xA4,0x9E,0x98,0x92,0x8B,0x85
,0x7F,0x79,0x73,0x6C,0x66,0x60,0x5A,0x54,0x4E,0x48,0x43,0x3D,0x38,0x33,0x2E,0x29
,0x25,0x21,0x1C,0x19,0x15,0x12,0x0F,0x0C,0x09,0x07,0x05,0x03,0x02,0x01,0x00,0x00
,0x00,0x00,0x00,0x01,0x02,0x03,0x05,0x07,0x09,0x0C,0x0F,0x12,0x15,0x19,0x1C,0x21
,0x25,0x29,0x2E,0x33,0x38,0x3D,0x43,0x48,0x4E,0x54,0x5A,0x60,0x66,0x6C,0x73,0x79
};
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

void UART_Send_start(void)
{
	 delayms(10);
	 UART_Send_END();
	 delayms(10);
}

void main(void)
{
 uint s=0; uint b;
 uint ch0,ch1;
 signed int i,j;
 second=50;minute=48;hour=12;day=15;month=7;week=2;year=16;bal=0;txt=0;wendu=0;b=0;
 P3M0&= ~0X02;
 P3M1|=0X02;   //TXǿ����
 UART_Init();  //��ʼ�����ڣ����ϵľ���Ϊ33MHz��ʵ�ʵĲ�����Ϊ9600bps
 UART_Send_start();//Ϊȷ������HMI����ͨ��  
 UART_Send_Str("page 0");
 UART_Send_END(); 
 delayms(2000);

		while(1)
		{
		/*	for(i=0;i<40;i++) 			   //������ʾ
			{
			 UART_Send_Str("s0.pco1=RED");//�ı�0ͨ������ɫ
			 UART_Send_END();
			 UART_Send_Str("ref s0");     // ˢ��
			 UART_Send_END();
			 sprintf(buf,"add 1,1,%d",b);
			 UART_Send_Str(buf);
	 		 UART_Send_END();
			 delayms(20);
			 b=boxing[i];
		
			}
				 i=0;	*/
			j= 32;
			for(i=0;i<sizeof(zhengxianbo);i++) 	//���Ҳ���ʾ
			{

			 ch0 = zhengxianbo[i]/3+40;
			 ch1 = zhengxianbo[j++]/3+40;
			 if(j>=sizeof(zhengxianbo))
			 j = 0;
			 sprintf(buf,"add 1,0,%d",ch0);
			 UART_Send_Str(buf);
	 		 UART_Send_END();
			 sprintf(buf,"add 1,1,%d",ch1);
			 UART_Send_Str(buf);
	 		 UART_Send_END();

		
			}


		/*   
		   for(i=0;i<150;i+=4) 			       //��ݲ���ʾ
		   	{
		    	
				UART_Send_Str("s0.pco0=GREEN");//�ı�0ͨ������ɫ
				UART_Send_END();
				UART_Send_Str("ref s0");     // ˢ��
				UART_Send_END();
				sprintf(buf,"add 1,0,%d",i);
			 	UART_Send_Str(buf);
			 	UART_Send_END();
			 	delayms(20);
			}
			for(i=150;i>0;i-=4)
			 {
		    	sprintf(buf,"add 1,0,%d",i);
			 	UART_Send_Str(buf);
			 	UART_Send_END();
			 	delayms(50);
			}  */
 		}
}


