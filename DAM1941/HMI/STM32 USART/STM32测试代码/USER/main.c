/*********************************************************************************/	 
//STM32����ʾ������
//�������ϣ�www.tftmcu.taobao.com
//��Ƭ��STM32F103VCT6  �ⲿ����8MHZ  �����ʣ�9600									  
/*********************************************************************************/	

#include "delay.h"
#include "sys.h"
#include "usart.h"	 
u8 idfind(u8 *buf,u8 *val,u8 len);
void HMISends(char *buf1);
void HMISendb(u8 buf);
void beepms(u16 va);
u8 key,beep;
void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}

void HMISendstart(void)
	{
	 	delay_ms(200);
		HMISendb(0xff);
		delay_ms(200);
	}
						
int main(void)
 {	   	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	  	 //���ڳ�ʼ��Ϊ9600
	HMISendstart();          //Ϊȷ������HMI����ͨ��
	{ 
		HMISends("cls RED");  //���ʹ���ָ��
		HMISendb(0xff);		  //���ͽ����� 0XFF 0XFF 0XFF
		delay_ms(1000);
    	HMISends("cls GREEN");
		HMISendb(0xff);
    	delay_ms(1000);
    	HMISends("cls BLUE");
		HMISendb(0xff);
		delay_ms(1000);
		HMISends("cls BLACK");
		HMISendb(0xff);
		delay_ms(1000);
		HMISends("page 4");
		HMISendb(0xff);
		HMISends("t0.txt=\"���粻�����Ź�\"");
		HMISendb(0xff);
		HMISends("xstr 0,0,40,40,0,RED,BLACK,1,1,1,�й�");//������ʹ������ָ��ȥ��ʾ���֣���������λ����������Ҫ��ʾ�ĺ���
		HMISendb(0xff);	
	}
	while(1);
}
void HMISends(char *buf1)		  //�ַ������ͺ���
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			USART_SendData(USART1,buf1[i]);  //����һ���ֽ�
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
		 	i++;
		}
	 else 
	 return ;

		}
	}
void HMISendb(u8 k)		         //�ֽڷ��ͺ���
{		 
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(USART1,k);  //����һ���ֽ�
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
		}
	 else 
	 return ;

	 } 
} 



