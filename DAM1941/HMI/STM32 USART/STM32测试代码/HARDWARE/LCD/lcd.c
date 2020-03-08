/*********************************************************************************/	 
//STM32������ʾ������
//�������ϣ�www.tftmcu.taobao.com	
/*********************************************************************************/
#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	   				 
//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 
u8 abx=0;

//4.3�Ĳ���
u16  HDP=479;
u16  HT=531;
u16  HPS=43;
u16  LPS=8;
u8   HPW=10;

u16  VDP=271;
u16  VT=288;
u16  VPS=12;
u16  FPS=4;
u8   VPW=10;

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;
	
		   
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(u16 regval)
{ 
	if(lcddev.bus16==1) //16λ�ӿ�
	{
	LCD->LCD_REG=regval;//д��Ҫд�ļĴ������
	}
	else			//��������-8λ����ģʽ 
	{
	   	LCD->LCD_REG = regval;		//д��Ҫд�ļĴ������	 
		LCD->LCD_REG = regval<<8;		//д��Ҫд�ļĴ������
	}

		 
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{
	if(lcddev.bus16==1) //16λ�ӿ�
	{
		LCD->LCD_RAM=data;
		}
	else			
	{
		LCD->LCD_RAM=data;
		LCD->LCD_RAM=data<<8;
	}
												    	   
			 
}
//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{	
									    	   
	if(lcddev.bus16==1) //16λ�ӿ�
	{
		return LCD->LCD_RAM;	
	}
	else			//��������-8λ����ģʽ
	{
		u16 h,l;
		h=LCD->LCD_RAM;
		l=LCD->LCD_RAM;
		return h+(l>>8);
	}		 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WR_REG_DATA(u8 LCD_Reg, u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}	   
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u8 LCD_Reg)
{
	u16 myid=0;
	u8 x=0;
	while(x<5 && (myid==0||myid==0xffff))	  //��5��
	{	
	//	LCD_WR_REG_DATA(0x0000,0x0001);										   
	//	delay_us(200);
		LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
		delay_us(5);		  
		myid=LCD_RD_DATA();		//���ض�����ֵ
		x++;
	}
	return myid;
}   
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);  
}	 
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);	
	if(lcddev.id==0x1943||lcddev.id==0x1907||lcddev.id==0x1905)
	{
		LCD_WR_REG(0x2E);  
	}
	else
	{
	   LCD_WR_REG(lcddev.wramcmd);
	}
	if(lcddev.id==0x9325||lcddev.id==0x9328)
	{
		opt_delay(2);
		return 	LCD_BGR2RGB( LCD_RD_DATA());

	}	
    return LCD_RD_DATA();									
}			 
//LCD������ʾ
void LCD_DisplayOn(void)
{					   

}	 
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   

}   
void Address_set1121(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	LCD_WR_REG_DATA(0x0046,(((u16)(x2))<<8)+x1);	  
    LCD_WR_REG_DATA(0x0047,y2);  
    LCD_WR_REG_DATA(0x0048,y1);
  	LCD_WR_REG_DATA(0x0020,x1);	  
    LCD_WR_REG_DATA(0x0021,y1); 
				 						 
}

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
 	if(lcddev.id==0X9341||lcddev.id==0X6804)
	{		    
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8); 
		LCD_WR_DATA(Xpos&0XFF);	 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8); 
		LCD_WR_DATA(Ypos&0XFF);
	}else if(lcddev.id==0x1907||lcddev.id==0x1905)
	{
			LCD_WR_REG(0x002A);	
			LCD_WR_DATA(Xpos>>8);	    
			LCD_WR_DATA(Xpos&0x00ff);
			LCD_WR_DATA(799>>8);	    
			LCD_WR_DATA(799&0x00ff);
		    LCD_WR_REG(0x002b);	
			LCD_WR_DATA(Ypos>>8);	    
			LCD_WR_DATA(Ypos&0x00ff);
			LCD_WR_DATA(479>>8);	    
			LCD_WR_DATA(479&0x00ff);
	}else if(lcddev.id==0x1943)
	{
			LCD_WR_REG(0x002A);	
			LCD_WR_DATA(Xpos>>8);	    
			LCD_WR_DATA(Xpos&0x00ff);
			LCD_WR_DATA(479>>8);	    
			LCD_WR_DATA(479&0x00ff);
		    LCD_WR_REG(0x002b);	
			LCD_WR_DATA(Ypos>>8);	    
			LCD_WR_DATA(Ypos&0x00ff);
			LCD_WR_DATA(271>>8);	    
			LCD_WR_DATA(271&0x00ff);
	}else if(lcddev.id==0x1121)			
	{
		Address_set1121(Xpos,Ypos,239,319);
	}else if(lcddev.id==0x0065)
	{
		LCD_WR_REG_DATA(0x06,Ypos>>8);
		LCD_WR_REG_DATA(0x07,Ypos);
	//	LCD_WR_REG_DATA(0x08,y2>>8);
	//	LCD_WR_REG_DATA(0x09,y2);
		LCD_WR_REG_DATA(0x02,Xpos>>8);
		LCD_WR_REG_DATA(0x03,Xpos);
	//	LCD_WR_REG_DATA(0x04,x2>>8);
	//	LCD_WR_REG_DATA(0x05,x2); 
	
		LCD_WR_REG_DATA(0x80, Xpos>>8);
	    LCD_WR_REG_DATA(0x81, Xpos);    
	    LCD_WR_REG_DATA(0x82, Ypos>>8);
	    LCD_WR_REG_DATA(0x83, Ypos);    
	}else if(lcddev.id==0x0052)
	{
		LCD_WR_REG_DATA(0x06,Ypos>>8);
		LCD_WR_REG_DATA(0x07,Ypos);
	//	LCD_WR_REG_DATA(0x08,y2>>8);
	//	LCD_WR_REG_DATA(0x09,y2);
		LCD_WR_REG_DATA(0x02,Xpos>>8);
		LCD_WR_REG_DATA(0x03,Xpos);
	//	LCD_WR_REG_DATA(0x04,x2>>8);
	//	LCD_WR_REG_DATA(0x05,x2); 

	}else if(lcddev.id==0x0047)
	{
		LCD_WR_REG_DATA(0x0002,Xpos>>8);	   // Column address start2
		LCD_WR_REG_DATA(0x0003,Xpos);	   // Column address start1
	//	LCD_WR_REG_DATA(0x0004,x2>>8);	   // Column address end2
	//	LCD_WR_REG_DATA(0x0005,x2);	   // Column address end1
		LCD_WR_REG_DATA(0x0006,Ypos>>8);	   // Row address start2
		LCD_WR_REG_DATA(0x0007,Ypos);	   // Row address start1
	  //  LCD_WR_REG_DATA(0x0008,y2>>8);	   // Row address end2
	//	LCD_WR_REG_DATA(0x0009,y2);	   // Row address end1
	  //  LCD_WR_REG(0x0022);	
	}else if(lcddev.id==0x9325||lcddev.id==0x9328)
	{	
		LCD_WR_REG_DATA(0x0020,Xpos);
		LCD_WR_REG_DATA(0x0021,Ypos);	 
		LCD_WR_REG_DATA(0x0050,Xpos);
		LCD_WR_REG_DATA(0x0052,Ypos);
	}else
	{
		LCD_WR_REG_DATA(lcddev.setxcmd, Xpos);
		LCD_WR_REG_DATA(lcddev.setycmd, Ypos);
	}
			
		
		 
} 
 

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA(POINT_COLOR); 
}
u8 ceshishuju()  //����������
{
	u16 cc=1;
	u16 i;
	u16 da; 	
	u16 ll=0;
 	ll=POINT_COLOR;

   if(lcddev.id!=0x1943&&lcddev.id!=0x0043&&lcddev.id!=0x1905&&lcddev.id!=0x0050&&lcddev.id!=0x1907&&lcddev.id!=0x0070)
   {
  	 return 1;
   }
	
	for(i=0;i<16;i++)
	{
		POINT_COLOR=cc<<i;
		LCD_DrawPoint(i,0);	
	}
	LCD_DrawPoint(i+1,0);
	for(i=0;i<16;i++)
	{
		da=LCD_ReadPoint(i,0);	
		da=LCD_ReadPoint(i,0);	
		if(da!=(cc<<i))//�����쳣
		{
			LCD_Clear(BLACK);
			POINT_COLOR=RED;
			LCD_ShowString(0,0,200,16,16,"DATA ERROR AT");
			LCD_ShowNum(100,0,cc<<i,6,16);
			LCD_ShowNum(100,40,da,6,16);
		   	POINT_COLOR=ll;
			return 0;
		}
	} 		 

	POINT_COLOR=ll;
	return 1;
}

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void LCD_Init(void)
{ 	
 	u16 x1=0;
	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;

   	// Enable FSMC, GPIOD, GPIOE clocks
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);

	// Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.07(NE1), PD.08(D13),
  	// PD.09(D14), PD.10(D15), PD.13(A18), PD.14(D0), PD.15(D1) as alternate 
  	// function push pull 
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| 
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	// Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
  	// PE.14(D11), PE.15(D12) as alternate function push pull */
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                   GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                   GPIO_Pin_15;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

  	//PB14 --> LCD_RST
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	readWriteTiming.FSMC_AddressSetupTime = 2;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 1;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
    readWriteTiming.FSMC_DataSetupTime = 10;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
    readWriteTiming.FSMC_BusTurnAroundDuration = 1;
    readWriteTiming.FSMC_CLKDivision = 1;
    readWriteTiming.FSMC_DataLatency = 1;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

	writeTiming.FSMC_AddressSetupTime = 2;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
    writeTiming.FSMC_AddressHoldTime = 1;	 //��ַ����ʱ�䣨A		
    writeTiming.FSMC_DataSetupTime = 10;		 ////���ݱ���ʱ��Ϊ4��HCLK	
    writeTiming.FSMC_BusTurnAroundDuration =1;
    writeTiming.FSMC_CLKDivision =1;
    writeTiming.FSMC_DataLatency =1;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 

 
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����		

   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // ʹ��BANK1 
	
	LCD_REST=0;		 
 	delay_ms(50); // delay 20 ms 
   	LCD_REST=1;		 
 	delay_ms(50); // delay 20 ms 
 //	LCD_WR_REG_DATA(0x0000,0x0001);
//	delay_ms(10); // delay 50 ms 
	if(lcddev.busauto==1) //�Զ�ʶ�����߽ӿ�
	{
		lcddev.bus16=1;	 			 		
		x1=LCD_ReadReg(0x0000)&0x00ff;
	    if(x1==0x0000||x1==0x00ff)
		{
			lcddev.bus16=0;
		}


	}

	if(lcddev.id==0x1234) //�Զ���ID
	{
  		lcddev.id = LCD_ReadReg(0x0000);  
		lcddev.idid=lcddev.id; 
	}



//	lcddev.id=0x1943;//ǿ��ָ��ID
//	lcddev.id=0x9320;  

	lcddev.width=240;
	lcddev.height=320;

	if(lcddev.bus16==1)
	{
		printf("if=%x",0x16);
	}else  printf("if=%x",0x8);
 	printf("id=%x\r\n",lcddev.id); //��ӡLCD ID 
	
		

		if(lcddev.id==0X9341||lcddev.id==0X6804)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
			if(lcddev.id==0X6804)
			{
				lcddev.width=320;
				lcddev.height=480;
			}
		}else if(lcddev.id==0X8989)
		{
			lcddev.wramcmd=0x22;
	 		lcddev.setxcmd=0X4E;
			lcddev.setycmd=0X4F;  
		}else if(lcddev.id==0x0070||lcddev.id==0x0050)
		{
			lcddev.width=800;
			lcddev.height=480;
			lcddev.setxcmd=0x03;
			lcddev.setycmd=0x02;
			lcddev.wramcmd=0x0f;
		}else if(lcddev.id==0x0043)
		{
			lcddev.width=480;
			lcddev.height=272;
			lcddev.setxcmd=0x03;
			lcddev.setycmd=0x02;
			lcddev.wramcmd=0x0f;
		}
		else if(lcddev.id==0x1907||lcddev.id==0x1905)
		{
			lcddev.width=800;
			lcddev.height=480;
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	
		}else if(lcddev.id==0x1943)
		{
			lcddev.width=480;
			lcddev.height=272;
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	
		}else if(lcddev.id==0x0065||lcddev.id==0x0052)
		{
			lcddev.width=240;
			lcddev.height=400;
			lcddev.wramcmd=0x22;

		}else
		{
			lcddev.wramcmd=0x22; //дGRAMָ��
	 		lcddev.setxcmd=0x20; //дXָ��
			lcddev.setycmd=0x21; //дYָ�� 
		}
		  
	if(lcddev.id==0x0065)
	{
		if(abx!=110)
		{
			LCD_WR_REG_DATA(0x00E5,0x0010);
			LCD_WR_REG_DATA(0x00E7,0x0010);
			LCD_WR_REG_DATA(0x00E8,0x0048);
			LCD_WR_REG_DATA(0x00EC,0x0009);
			LCD_WR_REG_DATA(0x00ED,0x006C);
			// Power on Setting
			LCD_WR_REG_DATA(0x0017,0x0005);
			LCD_WR_REG_DATA(0x0023,0x006F);
			LCD_WR_REG_DATA(0x0024,0x004e);//68
			LCD_WR_REG_DATA(0x0025,0x0071);
			LCD_WR_REG_DATA(0x002f,0x0001);
			LCD_WR_REG_DATA(0x00E2,0x0018);
			LCD_WR_REG_DATA(0x001B,0x0015);
			LCD_WR_REG_DATA(0x0001,0x0000);
			LCD_WR_REG_DATA(0x001C,0x0003);
			// Power on sequence
			LCD_WR_REG_DATA(0x0018,0x00dd);
			LCD_WR_REG_DATA(0x0019,0x0001);
			delay_ms(5);
			LCD_WR_REG_DATA(0x001F,0x008C);
			LCD_WR_REG_DATA(0x001F,0x0084);
			delay_ms(10);
			LCD_WR_REG_DATA(0x001F,0x0094);
			delay_ms(10);
			LCD_WR_REG_DATA(0x001F,0x00D4);
			delay_ms(5);
			// Gamma Setting
			LCD_WR_REG_DATA(0x0040,0x0000);
			LCD_WR_REG_DATA(0x0041,0x002B);
			LCD_WR_REG_DATA(0x0042,0x0029);
			LCD_WR_REG_DATA(0x0043,0x003E);
			LCD_WR_REG_DATA(0x0044,0x003D);
			LCD_WR_REG_DATA(0x0045,0x003F);
			LCD_WR_REG_DATA(0x0046,0x0024);
			LCD_WR_REG_DATA(0x0047,0x0074);
			LCD_WR_REG_DATA(0x0048,0x0008);
			LCD_WR_REG_DATA(0x0049,0x0006);
			LCD_WR_REG_DATA(0x004A,0x0007);
			LCD_WR_REG_DATA(0x004B,0x000D);
			LCD_WR_REG_DATA(0x004C,0x0017);
			LCD_WR_REG_DATA(0x0050,0x0000);
			LCD_WR_REG_DATA(0x0051,0x0002);
			LCD_WR_REG_DATA(0x0052,0x0001);
			LCD_WR_REG_DATA(0x0053,0x0016);
			LCD_WR_REG_DATA(0x0054,0x0014);
			LCD_WR_REG_DATA(0x0055,0x003F);
			LCD_WR_REG_DATA(0x0056,0x000B);
			LCD_WR_REG_DATA(0x0057,0x005B);
			LCD_WR_REG_DATA(0x0058,0x0008);
			LCD_WR_REG_DATA(0x0059,0x0012);
			LCD_WR_REG_DATA(0x005A,0x0018);
			LCD_WR_REG_DATA(0x005B,0x0019);
			LCD_WR_REG_DATA(0x005C,0x0017);
			LCD_WR_REG_DATA(0x005D,0x00FF); 
			// Display ON Setting
			LCD_WR_REG_DATA(0x0016,0x0B);
			LCD_WR_REG_DATA(0x0028,0x0020);
			delay_ms(40);
			LCD_WR_REG_DATA(0x0028,0x0038);
			delay_ms(40); // Waiting 2 frames al least
			LCD_WR_REG_DATA(0x0028,0x003C);
		}else
		{
			LCD_WR_REG_DATA(0xE2,0x15); //VREFsetting
			LCD_WR_REG_DATA(0xE5,0x28);
			LCD_WR_REG_DATA(0xE7,0x28);
			LCD_WR_REG_DATA(0xE8,0x48);
			LCD_WR_REG_DATA(0xEC,0x09);
			LCD_WR_REG_DATA(0xED,0x06);
			// Power on Setting
			LCD_WR_REG_DATA(0x0017,0x0005);
			LCD_WR_REG_DATA(0x23,0x76);
			LCD_WR_REG_DATA(0x24,0x57);
			LCD_WR_REG_DATA(0x25,0x71);
			LCD_WR_REG_DATA(0x1B,0x1E); //VREG1 = 4.5V
			LCD_WR_REG_DATA(0x01,0x00);
			LCD_WR_REG_DATA(0x1C,0x04);
			// Power on sequence
			LCD_WR_REG_DATA(0x0018,0x0088);
			LCD_WR_REG_DATA(0x19,0x01);
			delay_ms(5);
			LCD_WR_REG_DATA(0x1F,0x8C);
			LCD_WR_REG_DATA(0x1F,0x84);
			delay_ms(10);
			LCD_WR_REG_DATA(0x1F,0x94);
			delay_ms(10);
			LCD_WR_REG_DATA(0x1F,0xD4);
			delay_ms(5);
			// Gamma Setting
			LCD_WR_REG_DATA(0x40,0x08);
			LCD_WR_REG_DATA(0x41,0x31);
			LCD_WR_REG_DATA(0x42,0x2F);
			LCD_WR_REG_DATA(0x43,0x3E);
			LCD_WR_REG_DATA(0x44,0x3D);
			LCD_WR_REG_DATA(0x45,0x3F);
			LCD_WR_REG_DATA(0x46,0x2F);
			LCD_WR_REG_DATA(0x47,0x79);
			LCD_WR_REG_DATA(0x48,0x08);
			LCD_WR_REG_DATA(0x49,0x06);
			LCD_WR_REG_DATA(0x4A,0x08);
			LCD_WR_REG_DATA(0x4B,0x0E);
			LCD_WR_REG_DATA(0x4C,0x17);
			LCD_WR_REG_DATA(0x50,0x00);
			LCD_WR_REG_DATA(0x51,0x02);
			LCD_WR_REG_DATA(0x52,0x01);
			LCD_WR_REG_DATA(0x53,0x10);
			LCD_WR_REG_DATA(0x54,0x0E);
			LCD_WR_REG_DATA(0x55,0x37);
			LCD_WR_REG_DATA(0x56,0x06);
			LCD_WR_REG_DATA(0x57,0x50);
			LCD_WR_REG_DATA(0x58,0x08);
			LCD_WR_REG_DATA(0x59,0x11);
			LCD_WR_REG_DATA(0x5A,0x17);
			LCD_WR_REG_DATA(0x5B,0x19);
			LCD_WR_REG_DATA(0x5C,0x17);
			LCD_WR_REG_DATA(0x5D,0xFF);
			// Display ON Setting
			LCD_WR_REG_DATA(0x16,0x0b);
			LCD_WR_REG_DATA(0x28,0x20);
			delay_ms(40);
			LCD_WR_REG_DATA(0x28,0x38);
			delay_ms(40); // Waiting 2 frames al least
			LCD_WR_REG_DATA(0x28,0x3C);
		}
	}else if(lcddev.id==0x0052)
	{
		LCD_WR_REG(0x0083);           
		LCD_WR_DATA(0x0002);  //TESTM=1 
		             
		LCD_WR_REG(0x0085);  
		LCD_WR_DATA(0x0003);  //VDC_SEL=011
		LCD_WR_REG(0x008B);  
		LCD_WR_DATA(0x0001);
		LCD_WR_REG(0x008C);  
		LCD_WR_DATA(0x0093); //STBA[7]=1,STBA[5:4]=01,STBA[1:0]=11
		        
		LCD_WR_REG(0x0091);  
		LCD_WR_DATA(0x0001); //DCDC_SYNC=1
		        
		LCD_WR_REG(0x0083);  
		LCD_WR_DATA(0x0000); //TESTM=0
		         //Gamma Setting
		
		LCD_WR_REG(0x003E);  
		LCD_WR_DATA(0x00B0);
		LCD_WR_REG(0x003F);  
		LCD_WR_DATA(0x0003);
		LCD_WR_REG(0x0040);  
		LCD_WR_DATA(0x0010);
		LCD_WR_REG(0x0041);  
		LCD_WR_DATA(0x0056);
		LCD_WR_REG(0x0042);  
		LCD_WR_DATA(0x0013);
		LCD_WR_REG(0x0043);  
		LCD_WR_DATA(0x0046);
		LCD_WR_REG(0x0044);  
		LCD_WR_DATA(0x0023);
		LCD_WR_REG(0x0045);  
		LCD_WR_DATA(0x0076);
		LCD_WR_REG(0x0046);  
		LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0047);  
		LCD_WR_DATA(0x005E);
		LCD_WR_REG(0x0048);  
		LCD_WR_DATA(0x004F);
		LCD_WR_REG(0x0049);  
		LCD_WR_DATA(0x0040);	
		//**********Power On sequence************
		        
		LCD_WR_REG(0x0017);  
		LCD_WR_DATA(0x0091);
		       
		LCD_WR_REG(0x002B);  
		LCD_WR_DATA(0x00F9);
		         delay_ms(10);
		        
		LCD_WR_REG(0x001B);  
		LCD_WR_DATA(0x0014);
		        
		LCD_WR_REG(0x001A);  
		LCD_WR_DATA(0x0011);
		              
		LCD_WR_REG(0x001C);  
		LCD_WR_DATA(0x0006);	  //0d
		        
		LCD_WR_REG(0x001F);  
		LCD_WR_DATA(0x0042);
		        delay_ms(20);
		        
		LCD_WR_REG(0x0019);  
		LCD_WR_DATA(0x000A);
		     
		LCD_WR_REG(0x0019);  
		LCD_WR_DATA(0x001A);
		         delay_ms(40);
		        
		        
		LCD_WR_REG(0x0019);  
		LCD_WR_DATA(0x0012);
		        delay_ms(40);
		        
		LCD_WR_REG(0x001E);  
		LCD_WR_DATA(0x0027);
		        delay_ms(100);	   
		        
		        
		 //**********DISPLAY ON SETTING***********
		        
		LCD_WR_REG(0x0024);  
		LCD_WR_DATA(0x0060);
		        
		LCD_WR_REG(0x003D);  
		LCD_WR_DATA(0x0040);
		        
		LCD_WR_REG(0x0034);  
		LCD_WR_DATA(0x0038);
		        
		LCD_WR_REG(0x0035);  
		LCD_WR_DATA(0x0038);
		        
		LCD_WR_REG(0x0024);  
		LCD_WR_DATA(0x0038);
		delay_ms(40);
		        
		LCD_WR_REG(0x0024);  
		LCD_WR_DATA(0x003C);
		        
		LCD_WR_REG(0x0016);  
		LCD_WR_DATA(0x001C);
		        
		LCD_WR_REG(0x0001);  
		LCD_WR_DATA(0x0006);
		        
		LCD_WR_REG(0x0055);  
		LCD_WR_DATA(0x0000); 
		
		LCD_WR_REG(0x0002);           
		LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0003);           
		LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0004);           
		LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0005);           
		LCD_WR_DATA(0x00ef);
		
		LCD_WR_REG(0x0006);           
		LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0007);           
		LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0008);           
		LCD_WR_DATA(0x0001);
		LCD_WR_REG(0x0009);           
		LCD_WR_DATA(0x008f);
	}else if(lcddev.id==0X0047)	
	{
	//  VENDOR   
	LCD_WR_REG_DATA(0x0046,0x00A4);
	LCD_WR_REG_DATA(0x0047,0x0053);
	LCD_WR_REG_DATA(0x0048,0x0000);
	LCD_WR_REG_DATA(0x0049,0x0044);
	LCD_WR_REG_DATA(0x004a,0x0004);
	LCD_WR_REG_DATA(0x004b,0x0067);
	LCD_WR_REG_DATA(0x004c,0x0033);
	LCD_WR_REG_DATA(0x004d,0x0077);
	LCD_WR_REG_DATA(0x004e,0x0012);
	LCD_WR_REG_DATA(0x004f,0x004C);
	LCD_WR_REG_DATA(0x0050,0x0046);
	LCD_WR_REG_DATA(0x0051,0x0044);
	  
	  //240x320 window setting
    LCD_WR_REG_DATA(0x0002,0x0000); // Column address start2
 	LCD_WR_REG_DATA(0x0003,0x0000); // Column address start1
 	LCD_WR_REG_DATA(0x0004,0x0000); // Column address end2
 	LCD_WR_REG_DATA(0x0005,0x00ef); // Column address end1
    LCD_WR_REG_DATA(0x0006,0x0000); // Row address start2
	LCD_WR_REG_DATA(0x0007,0x0000); // Row address start1
	LCD_WR_REG_DATA(0x0008,0x0001); // Row address end2
	LCD_WR_REG_DATA(0x0009,0x003f); // Row address end1
  
  // Display Setting
	LCD_WR_REG_DATA(0x0001,0x0006); // IDMON=0, INVON=1, NORON=1, PTLON=0
	LCD_WR_REG_DATA(0x0016,0x00C8); // MY=0, MX=0, MV=0, ML=1, BGR=0, TEON=0   0048
	LCD_WR_REG_DATA(0x0023,0x0095); // N_DC=1001 0101
	LCD_WR_REG_DATA(0x0024,0x0095); // PI_DC=1001 0101
	LCD_WR_REG_DATA(0x0025,0x00FF); // I_DC=1111 1111
	
	LCD_WR_REG_DATA(0x0027,0x0002); // N_BP=0000 0010
	LCD_WR_REG_DATA(0x0028,0x0002); // N_FP=0000 0010
	LCD_WR_REG_DATA(0x0029,0x0002); // PI_BP=0000 0010
	LCD_WR_REG_DATA(0x002a,0x0002); // PI_FP=0000 0010
	LCD_WR_REG_DATA(0x002C,0x0002); // I_BP=0000 0010
	LCD_WR_REG_DATA(0x002d,0x0002); // I_FP=0000 0010
	
	LCD_WR_REG_DATA(0x003a,0x0001); // N_RTN=0000, N_NW=001    0001
	LCD_WR_REG_DATA(0x003b,0x0000); // P_RTN=0000, P_NW=001
	LCD_WR_REG_DATA(0x003c,0x00f0); // I_RTN=1111, I_NW=000
	LCD_WR_REG_DATA(0x003d,0x0000); // DIV=00
	delay_ms(1);
	LCD_WR_REG_DATA(0x0035,0x0038); // EQS=38h
	LCD_WR_REG_DATA(0x0036,0x0078); // EQP=78h
	LCD_WR_REG_DATA(0x003E,0x0038); // SON=38h
	LCD_WR_REG_DATA(0x0040,0x000F); // GDON=0Fh
	LCD_WR_REG_DATA(0x0041,0x00F0); // GDOFF
	
	// Power Supply Setting
	LCD_WR_REG_DATA(0x0019,0x0049); // CADJ=0100, CUADJ=100, OSD_EN=1 ,60Hz
	LCD_WR_REG_DATA(0x0093,0x000F); // RADJ=1111, 100%
	delay_ms(1);
	LCD_WR_REG_DATA(0x0020,0x0040); // BT=0100
	LCD_WR_REG_DATA(0x001D,0x0007); // VC1=111   0007
	LCD_WR_REG_DATA(0x001E,0x0000); // VC3=000
	LCD_WR_REG_DATA(0x001F,0x0004); // VRH=0011
	
	//VCOM SETTING
	LCD_WR_REG_DATA(0x0044,0x004D); // VCM=101 0000  4D
	LCD_WR_REG_DATA(0x0045,0x000E); // VDV=1 0001   0011
	delay_ms(1);
	LCD_WR_REG_DATA(0x001C,0x0004); // AP=100
	delay_ms(2);
	
	LCD_WR_REG_DATA(0x001B,0x0018); // GASENB=0, PON=0, DK=1, XDK=0, VLCD_TRI=0, STB=0
	delay_ms(1);
	LCD_WR_REG_DATA(0x001B,0x0010); // GASENB=0, PON=1, DK=0, XDK=0, VLCD_TRI=0, STB=0
	delay_ms(1);
	LCD_WR_REG_DATA(0x0043,0x0080); //set VCOMG=1
	delay_ms(2);
	
	// Display ON Setting
	LCD_WR_REG_DATA(0x0090,0x007F); // SAP=0111 1111
	LCD_WR_REG_DATA(0x0026,0x0004); //GON=0, DTE=0, D=01
	delay_ms(1);
	LCD_WR_REG_DATA(0x0026,0x0024); //GON=1, DTE=0, D=01
	LCD_WR_REG_DATA(0x0026,0x002C); //GON=1, DTE=0, D=11
	delay_ms(1);
	LCD_WR_REG_DATA(0x0026,0x003C); //GON=1, DTE=1, D=11
	
	// INTERNAL REGISTER SETTING
	LCD_WR_REG_DATA(0x0057,0x0002); // TEST_Mode=1: into TEST mode
	LCD_WR_REG_DATA(0x0095,0x0001); // SET DISPLAY CLOCK AND PUMPING CLOCK TO SYNCHRONIZE
	LCD_WR_REG_DATA(0x0057,0x0000); // TEST_Mode=0: exit TEST mode
	//LCD_WR_REG_DATA(0x0021,0x0000);
	LCD_WR_REG(0x0022);  
	}else if(lcddev.id==0X9341)	//9341��ʼ��
	{	 
		LCD_WR_REG(0xCF);  
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0xC1); 
		LCD_WR_DATA(0X30); 
		LCD_WR_REG(0xED);  
		LCD_WR_DATA(0x64); 
		LCD_WR_DATA(0x03); 
		LCD_WR_DATA(0X12); 
		LCD_WR_DATA(0X81); 
		LCD_WR_REG(0xE8);  
		LCD_WR_DATA(0x85); 
		LCD_WR_DATA(0x10); 
		LCD_WR_DATA(0x7A); 
		LCD_WR_REG(0xCB);  
		LCD_WR_DATA(0x39); 
		LCD_WR_DATA(0x2C); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x34); 
		LCD_WR_DATA(0x02); 
		LCD_WR_REG(0xF7);  
		LCD_WR_DATA(0x20); 
		LCD_WR_REG(0xEA);  
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_REG(0xC0);    //Power control 
		LCD_WR_DATA(0x1B);   //VRH[5:0] 
		LCD_WR_REG(0xC1);    //Power control 
		LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0] 
		LCD_WR_REG(0xC5);    //VCM control 
		LCD_WR_DATA(0x30); 	 //3F
		LCD_WR_DATA(0x30); 	 //3C
		LCD_WR_REG(0xC7);    //VCM control2 
		LCD_WR_DATA(0XB7); 
		LCD_WR_REG(0x36);    // Memory Access Control 
		LCD_WR_DATA(0x48); 
		LCD_WR_REG(0x3A);   
		LCD_WR_DATA(0x55); 
		LCD_WR_REG(0xB1);   
		LCD_WR_DATA(0x00);   
		LCD_WR_DATA(0x1A); 
		LCD_WR_REG(0xB6);    // Display Function Control 
		LCD_WR_DATA(0x0A); 
		LCD_WR_DATA(0xA2); 
		LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
		LCD_WR_DATA(0x00); 
		LCD_WR_REG(0x26);    //Gamma curve selected 
		LCD_WR_DATA(0x01); 
		LCD_WR_REG(0xE0);    //Set Gamma 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x2A); 
		LCD_WR_DATA(0x28); 
		LCD_WR_DATA(0x08); 
		LCD_WR_DATA(0x0E); 
		LCD_WR_DATA(0x08); 
		LCD_WR_DATA(0x54); 
		LCD_WR_DATA(0XA9); 
		LCD_WR_DATA(0x43); 
		LCD_WR_DATA(0x0A); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 		 
		LCD_WR_REG(0XE1);    //Set Gamma 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x15); 
		LCD_WR_DATA(0x17); 
		LCD_WR_DATA(0x07); 
		LCD_WR_DATA(0x11); 
		LCD_WR_DATA(0x06); 
		LCD_WR_DATA(0x2B); 
		LCD_WR_DATA(0x56); 
		LCD_WR_DATA(0x3C); 
		LCD_WR_DATA(0x05); 
		LCD_WR_DATA(0x10); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x3F); 
		LCD_WR_DATA(0x3F); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x3f);
		LCD_WR_REG(0x2A); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xef);	 
		LCD_WR_REG(0x11); //Exit Sleep
		delay_ms(120);
		LCD_WR_REG(0x29); //display on	
	}else if(lcddev.id==0x6804) //6804��ʼ��
	{
		LCD_WR_REG(0X11);
		delay_ms(20);
		LCD_WR_REG(0XD0);//VCI1  VCL  VGH  VGL DDVDH VREG1OUT power amplitude setting
		LCD_WR_DATA(0X07); 
		LCD_WR_DATA(0X42); 
		LCD_WR_DATA(0X1D); 
		LCD_WR_REG(0XD1);//VCOMH VCOM_AC amplitude setting
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X1a);
		LCD_WR_DATA(0X09); 
		LCD_WR_REG(0XD2);//Operational Amplifier Circuit Constant Current Adjust , charge pump frequency setting
		LCD_WR_DATA(0X01);
		LCD_WR_DATA(0X22);
		LCD_WR_REG(0XC0);//REV SM GS 
		LCD_WR_DATA(0X10);
		LCD_WR_DATA(0X3B);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X02);
		LCD_WR_DATA(0X11);
		
		LCD_WR_REG(0XC5);// Frame rate setting = 72HZ  when setting 0x03
		LCD_WR_DATA(0X03);
		
		LCD_WR_REG(0XC8);//Gamma setting
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X25);
		LCD_WR_DATA(0X21);
		LCD_WR_DATA(0X05);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X0a);
		LCD_WR_DATA(0X65);
		LCD_WR_DATA(0X25);
		LCD_WR_DATA(0X77);
		LCD_WR_DATA(0X50);
		LCD_WR_DATA(0X0f);
		LCD_WR_DATA(0X00);	  
						  
   		LCD_WR_REG(0XF8);
		LCD_WR_DATA(0X01);	  

 		LCD_WR_REG(0XFE);
 		LCD_WR_DATA(0X00);
 		LCD_WR_DATA(0X02);
		
		LCD_WR_REG(0X20);//Exit invert mode

		LCD_WR_REG(0X36);
		LCD_WR_DATA(0X08);//ԭ����a
		
		LCD_WR_REG(0X3A);
		LCD_WR_DATA(0X55);//16λģʽ	  
		LCD_WR_REG(0X2B);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X01);
		LCD_WR_DATA(0X3F);
		
		LCD_WR_REG(0X2A);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X00);
		LCD_WR_DATA(0X01);
		LCD_WR_DATA(0XDF);
		delay_ms(120);
		LCD_WR_REG(0X29); 	 
 	}else if(lcddev.id==0x9325||lcddev.id==0x9328)//9325 9328
	{
	     LCD_WR_REG_DATA(0x0001,0x0100); 
		 LCD_WR_REG_DATA(0x0002,0x0700); 
		 LCD_WR_REG_DATA(0x0003,0x1030); 
		 LCD_WR_REG_DATA(0x0004,0x0000); 
		 LCD_WR_REG_DATA(0x0008,0x0207);  
		 LCD_WR_REG_DATA(0x0009,0x0000);
		 LCD_WR_REG_DATA(0x000A,0x0000); 
		 LCD_WR_REG_DATA(0x000C,0x0000); 
		 LCD_WR_REG_DATA(0x000D,0x0000);
		 LCD_WR_REG_DATA(0x000F,0x0000);
		//power on sequence VGHVGL
		 LCD_WR_REG_DATA(0x0010,0x0000);   
		 LCD_WR_REG_DATA(0x0011,0x0007);  
		 LCD_WR_REG_DATA(0x0012,0x0000);  
		 LCD_WR_REG_DATA(0x0013,0x0000); 
		//vgh 
		 LCD_WR_REG_DATA(0x0010,0x1290);   
		 LCD_WR_REG_DATA(0x0011,0x0227);
		 //delay_ms(100);
		 //vregiout 
		 LCD_WR_REG_DATA(0x0012,0x001d); //0x001b
		 //delay_ms(100); 
		 //vom amplitude
		 LCD_WR_REG_DATA(0x0013,0x1500);
		 //delay_ms(100); 
		 //vom H
		 LCD_WR_REG_DATA(0x0029,0x0018); 
		 LCD_WR_REG_DATA(0x002B,0x000D); 
		
		//gamma
		 LCD_WR_REG_DATA(0x0030,0x0004);
		 LCD_WR_REG_DATA(0x0031,0x0307);
		 LCD_WR_REG_DATA(0x0032,0x0002);// 0006
		 LCD_WR_REG_DATA(0x0035,0x0206);
		 LCD_WR_REG_DATA(0x0036,0x0408);
		 LCD_WR_REG_DATA(0x0037,0x0507); 
		 LCD_WR_REG_DATA(0x0038,0x0204);//0200
		 LCD_WR_REG_DATA(0x0039,0x0707); 
		 LCD_WR_REG_DATA(0x003C,0x0405);// 0504
		 LCD_WR_REG_DATA(0x003D,0x0F02); 
		 //ram
		 LCD_WR_REG_DATA(0x0050,0x0000); 
		 LCD_WR_REG_DATA(0x0051,0x00EF);
		 LCD_WR_REG_DATA(0x0052,0x0000); 
		 LCD_WR_REG_DATA(0x0053,0x013F);  
		 LCD_WR_REG_DATA(0x0060,0xA700); 
		 LCD_WR_REG_DATA(0x0061,0x0001); 
		 LCD_WR_REG_DATA(0x006A,0x0000); 
		 //
		 LCD_WR_REG_DATA(0x0080,0x0000); 
		 LCD_WR_REG_DATA(0x0081,0x0000); 
		 LCD_WR_REG_DATA(0x0082,0x0000); 
		 LCD_WR_REG_DATA(0x0083,0x0000); 
		 LCD_WR_REG_DATA(0x0084,0x0000); 
		 LCD_WR_REG_DATA(0x0085,0x0000); 
		 //
		 LCD_WR_REG_DATA(0x0090,0x0010); 
		 LCD_WR_REG_DATA(0x0092,0x0600); 
		 LCD_WR_REG_DATA(0x0093,0x0003); 
		 LCD_WR_REG_DATA(0x0095,0x0110); 
		 LCD_WR_REG_DATA(0x0097,0x0000); 
		 LCD_WR_REG_DATA(0x0098,0x0000);
		 LCD_WR_REG_DATA(0x0007,0x0133);
	}else if(lcddev.id==0x9320)//����OK.
	{

	    LCD_WR_REG_DATA(0x0007,0x0000);
        delay_ms(50); 
        LCD_WR_REG_DATA(0x0012,0x011C);//0x011A   why need to set several times?
        LCD_WR_REG_DATA(0x00A4,0x0001);//NVM	 
        LCD_WR_REG_DATA(0x0008,0x000F);
        LCD_WR_REG_DATA(0x000A,0x0008);
        LCD_WR_REG_DATA(0x000D,0x0008);	    
  		//٤��У��
        LCD_WR_REG_DATA(0x0030,0x0707);
        LCD_WR_REG_DATA(0x0031,0x0007); //0x0707
        LCD_WR_REG_DATA(0x0032,0x0603); 
        LCD_WR_REG_DATA(0x0033,0x0700); 
        LCD_WR_REG_DATA(0x0034,0x0202); 
        LCD_WR_REG_DATA(0x0035,0x0002); //?0x0606
        LCD_WR_REG_DATA(0x0036,0x1F0F);
        LCD_WR_REG_DATA(0x0037,0x0707); //0x0f0f  0x0105
        LCD_WR_REG_DATA(0x0038,0x0000); 
        LCD_WR_REG_DATA(0x0039,0x0000); 
        LCD_WR_REG_DATA(0x003A,0x0707); 
        LCD_WR_REG_DATA(0x003B,0x0000); //0x0303
        LCD_WR_REG_DATA(0x003C,0x0007); //?0x0707
        LCD_WR_REG_DATA(0x003D,0x0000); //0x1313//0x1f08
        delay_ms(50); 
        LCD_WR_REG_DATA(0x0007,0x0001);
        LCD_WR_REG_DATA(0x0017,0x0001);//������Դ
        delay_ms(50); 
  		//��Դ����
        LCD_WR_REG_DATA(0x0010,0x17A0); 
        LCD_WR_REG_DATA(0x0011,0x0217);//reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        LCD_WR_REG_DATA(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        LCD_WR_REG_DATA(0x0013,0x0F00);//VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        LCD_WR_REG_DATA(0x002A,0x0000);  
        LCD_WR_REG_DATA(0x0029,0x000A);//0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        LCD_WR_REG_DATA(0x0012,0x013E);// 0x013C  power supply on
        //Coordinates Control//
        LCD_WR_REG_DATA(0x0050,0x0000);//0x0e00
        LCD_WR_REG_DATA(0x0051,0x00EF); 
        LCD_WR_REG_DATA(0x0052,0x0000); 
        LCD_WR_REG_DATA(0x0053,0x013F); 
    	//Pannel Image Control//
        LCD_WR_REG_DATA(0x0060,0x2700); 
        LCD_WR_REG_DATA(0x0061,0x0001); 
        LCD_WR_REG_DATA(0x006A,0x0000); 
        LCD_WR_REG_DATA(0x0080,0x0000); 
    	//Partial Image Control//
        LCD_WR_REG_DATA(0x0081,0x0000); 
        LCD_WR_REG_DATA(0x0082,0x0000); 
        LCD_WR_REG_DATA(0x0083,0x0000); 
        LCD_WR_REG_DATA(0x0084,0x0000); 
        LCD_WR_REG_DATA(0x0085,0x0000); 
  		//Panel Interface Control//
        LCD_WR_REG_DATA(0x0090,0x0013);//0x0010 frenqucy
        LCD_WR_REG_DATA(0x0092,0x0300); 
        LCD_WR_REG_DATA(0x0093,0x0005); 
        LCD_WR_REG_DATA(0x0095,0x0000); 
        LCD_WR_REG_DATA(0x0097,0x0000); 
        LCD_WR_REG_DATA(0x0098,0x0000); 
  
        LCD_WR_REG_DATA(0x0001,0x0100); 
        LCD_WR_REG_DATA(0x0002,0x0700); 
        LCD_WR_REG_DATA(0x0003,0x1030); 
        LCD_WR_REG_DATA(0x0004,0x0000); 
        LCD_WR_REG_DATA(0x000C,0x0000); 
        LCD_WR_REG_DATA(0x000F,0x0000); 
        LCD_WR_REG_DATA(0x0020,0x0000); 
        LCD_WR_REG_DATA(0x0021,0x0000); 
        LCD_WR_REG_DATA(0x0007,0x0021); 
        delay_ms(20);
        LCD_WR_REG_DATA(0x0007,0x0061); 
        delay_ms(20);
        LCD_WR_REG_DATA(0x0007,0x0173); 
        delay_ms(20);
	LCD_WR_REG(0x0022);


	/*
		LCD_WR_REG_DATA(0x00,0x0000);
		LCD_WR_REG_DATA(0x01,0x0100);	//Driver Output Contral.
		LCD_WR_REG_DATA(0x02,0x0700);	//LCD Driver Waveform Contral.
		LCD_WR_REG_DATA(0x03,0x1030);//Entry Mode Set.
		//LCD_WR_REG_DATA(0x03,0x1018);	//Entry Mode Set.
	
		LCD_WR_REG_DATA(0x04,0x0000);	//Scalling Contral.
		LCD_WR_REG_DATA(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WR_REG_DATA(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WR_REG_DATA(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WR_REG_DATA(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WR_REG_DATA(0x0d,0x0000);	//Frame Maker Position.
		LCD_WR_REG_DATA(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		delay_ms(50); 
		LCD_WR_REG_DATA(0x07,0x0101);	//Display Contral.
		delay_ms(50); 								  
		LCD_WR_REG_DATA(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WR_REG_DATA(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WR_REG_DATA(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		LCD_WR_REG_DATA(0x13,0x0b00);								//Power Control 4.
		LCD_WR_REG_DATA(0x29,0x0000);								//Power Control 7.
	
		LCD_WR_REG_DATA(0x2b,(1<<14)|(1<<4));	    
		LCD_WR_REG_DATA(0x50,0);	//Set X Star
		//ˮƽGRAM��ֹλ��Set X End.
		LCD_WR_REG_DATA(0x51,239);	//Set Y Star
		LCD_WR_REG_DATA(0x52,0);	//Set Y End.t.
		LCD_WR_REG_DATA(0x53,319);	//
	
		LCD_WR_REG_DATA(0x60,0x2700);	//Driver Output Control.
		LCD_WR_REG_DATA(0x61,0x0001);	//Driver Output Control.
		LCD_WR_REG_DATA(0x6a,0x0000);	//Vertical Srcoll Control.
	
		LCD_WR_REG_DATA(0x80,0x0000);	//Display Position? Partial Display 1.
		LCD_WR_REG_DATA(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		LCD_WR_REG_DATA(0x82,0x0000);	//RAM Address End-Partial Display 1.
		LCD_WR_REG_DATA(0x83,0x0000);	//Displsy Position? Partial Display 2.
		LCD_WR_REG_DATA(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		LCD_WR_REG_DATA(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		LCD_WR_REG_DATA(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		LCD_WR_REG_DATA(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		LCD_WR_REG_DATA(0x93,0x0001);	//Panel Interface Contral 3.
		LCD_WR_REG_DATA(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		LCD_WR_REG_DATA(0x97,(0<<8));	//
		LCD_WR_REG_DATA(0x98,0x0000);	//Frame Cycle Contral.	   
		LCD_WR_REG_DATA(0x07,0x0173);	//(0x0173)
		*/

	}else if(lcddev.id==0X9331)//OK |/|/|			 
	{
		LCD_WR_REG_DATA(0x00E7, 0x1014);
		LCD_WR_REG_DATA(0x0001, 0x0100); // set SS and SM bit
		LCD_WR_REG_DATA(0x0002, 0x0200); // set 1 line inversion
        LCD_WR_REG_DATA(0x0003,(1<<12)|(3<<4)|(1<<3));//65K    
		//LCD_WR_REG_DATA(0x0003, 0x1030); // set GRAM write direction and BGR=1.
		LCD_WR_REG_DATA(0x0008, 0x0202); // set the back porch and front porch
		LCD_WR_REG_DATA(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		LCD_WR_REG_DATA(0x000A, 0x0000); // FMARK function
		LCD_WR_REG_DATA(0x000C, 0x0000); // RGB interface setting
		LCD_WR_REG_DATA(0x000D, 0x0000); // Frame marker Position
		LCD_WR_REG_DATA(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		LCD_WR_REG_DATA(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WR_REG_DATA(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		LCD_WR_REG_DATA(0x0012, 0x0000); // VREG1OUT voltage
		LCD_WR_REG_DATA(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		delay_ms(200); // Dis-charge capacitor power voltage
		LCD_WR_REG_DATA(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		LCD_WR_REG_DATA(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		delay_ms(50); // Delay 50ms
		LCD_WR_REG_DATA(0x0012, 0x000C); // Internal reference voltage= Vci;
		delay_ms(50); // Delay 50ms
		LCD_WR_REG_DATA(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		LCD_WR_REG_DATA(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		LCD_WR_REG_DATA(0x002B, 0x000B); // Set Frame Rate
		delay_ms(50); // Delay 50ms
		LCD_WR_REG_DATA(0x0020, 0x0000); // GRAM horizontal Address
		LCD_WR_REG_DATA(0x0021, 0x013f); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		LCD_WR_REG_DATA(0x0030, 0x0000);
		LCD_WR_REG_DATA(0x0031, 0x0106);
		LCD_WR_REG_DATA(0x0032, 0x0000);
		LCD_WR_REG_DATA(0x0035, 0x0204);
		LCD_WR_REG_DATA(0x0036, 0x160A);
		LCD_WR_REG_DATA(0x0037, 0x0707);
		LCD_WR_REG_DATA(0x0038, 0x0106);
		LCD_WR_REG_DATA(0x0039, 0x0707);
		LCD_WR_REG_DATA(0x003C, 0x0402);
		LCD_WR_REG_DATA(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		LCD_WR_REG_DATA(0x0050, 0x0000); // Horizontal GRAM Start Address
		LCD_WR_REG_DATA(0x0051, 0x00EF); // Horizontal GRAM End Address
		LCD_WR_REG_DATA(0x0052, 0x0000); // Vertical GRAM Start Address
		LCD_WR_REG_DATA(0x0053, 0x013F); // Vertical GRAM Start Address
		LCD_WR_REG_DATA(0x0060, 0x2700); // Gate Scan Line
		LCD_WR_REG_DATA(0x0061, 0x0001); // NDL,VLE, REV 
		LCD_WR_REG_DATA(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		LCD_WR_REG_DATA(0x0080, 0x0000);
		LCD_WR_REG_DATA(0x0081, 0x0000);
		LCD_WR_REG_DATA(0x0082, 0x0000);
		LCD_WR_REG_DATA(0x0083, 0x0000);
		LCD_WR_REG_DATA(0x0084, 0x0000);
		LCD_WR_REG_DATA(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		LCD_WR_REG_DATA(0x0090, 0x0010);
		LCD_WR_REG_DATA(0x0092, 0x0600);
		LCD_WR_REG_DATA(0x0007, 0x0133); // 262K color and display ON
	}else if(lcddev.id==0x5408)
	{
		LCD_WR_REG_DATA(0x01,0x0100);								  
		LCD_WR_REG_DATA(0x02,0x0700);//LCD Driving Waveform Contral 
		LCD_WR_REG_DATA(0x03,0x1030);//Entry Mode���� 	   
		//ָ������������϶��µ��Զ���ģʽ
		//Normal Mode(Window Mode disable)
		//RGB��ʽ
		//16λ����2�δ����8��������
		LCD_WR_REG_DATA(0x04,0x0000); //Scalling Control register     
		LCD_WR_REG_DATA(0x08,0x0207); //Display Control 2 
		LCD_WR_REG_DATA(0x09,0x0000); //Display Control 3	 
		LCD_WR_REG_DATA(0x0A,0x0000); //Frame Cycle Control	 
		LCD_WR_REG_DATA(0x0C,0x0000); //External Display Interface Control 1 
		LCD_WR_REG_DATA(0x0D,0x0000); //Frame Maker Position		 
		LCD_WR_REG_DATA(0x0F,0x0000); //External Display Interface Control 2 
 		delay_ms(20);
		//TFT Һ����ɫͼ����ʾ����14
		LCD_WR_REG_DATA(0x10,0x16B0); //0x14B0 //Power Control 1
		LCD_WR_REG_DATA(0x11,0x0001); //0x0007 //Power Control 2
		LCD_WR_REG_DATA(0x17,0x0001); //0x0000 //Power Control 3
		LCD_WR_REG_DATA(0x12,0x0138); //0x013B //Power Control 4
		LCD_WR_REG_DATA(0x13,0x0800); //0x0800 //Power Control 5
		LCD_WR_REG_DATA(0x29,0x0009); //NVM read data 2
		LCD_WR_REG_DATA(0x2a,0x0009); //NVM read data 3
		LCD_WR_REG_DATA(0xa4,0x0000);	 
		LCD_WR_REG_DATA(0x50,0x0000); //���ò������ڵ�X�Ὺʼ��
		LCD_WR_REG_DATA(0x51,0x00EF); //���ò������ڵ�X�������
		LCD_WR_REG_DATA(0x52,0x0000); //���ò������ڵ�Y�Ὺʼ��
		LCD_WR_REG_DATA(0x53,0x013F); //���ò������ڵ�Y�������
		LCD_WR_REG_DATA(0x60,0x2700); //Driver Output Control
		//������Ļ�ĵ����Լ�ɨ�����ʼ��
		LCD_WR_REG_DATA(0x61,0x0001); //Driver Output Control
		LCD_WR_REG_DATA(0x6A,0x0000); //Vertical Scroll Control
		LCD_WR_REG_DATA(0x80,0x0000); //Display Position �C Partial Display 1
		LCD_WR_REG_DATA(0x81,0x0000); //RAM Address Start �C Partial Display 1
		LCD_WR_REG_DATA(0x82,0x0000); //RAM address End - Partial Display 1
		LCD_WR_REG_DATA(0x83,0x0000); //Display Position �C Partial Display 2
		LCD_WR_REG_DATA(0x84,0x0000); //RAM Address Start �C Partial Display 2
		LCD_WR_REG_DATA(0x85,0x0000); //RAM address End �C Partail Display2
		LCD_WR_REG_DATA(0x90,0x0013); //Frame Cycle Control
		LCD_WR_REG_DATA(0x92,0x0000);  //Panel Interface Control 2
		LCD_WR_REG_DATA(0x93,0x0003); //Panel Interface control 3
		LCD_WR_REG_DATA(0x95,0x0110);  //Frame Cycle Control
		LCD_WR_REG_DATA(0x07,0x0173);		 
		delay_ms(50);
	}	
	else if(lcddev.id==0x1505)//OK
	{
		// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        LCD_WR_REG_DATA(0x0007,0x0000);
        delay_ms(50); 
        LCD_WR_REG_DATA(0x0012,0x011C);//0x011A   why need to set several times?
        LCD_WR_REG_DATA(0x00A4,0x0001);//NVM	 
        LCD_WR_REG_DATA(0x0008,0x000F);
        LCD_WR_REG_DATA(0x000A,0x0008);
        LCD_WR_REG_DATA(0x000D,0x0008);	    
  		//٤��У��
        LCD_WR_REG_DATA(0x0030,0x0707);
        LCD_WR_REG_DATA(0x0031,0x0007); //0x0707
        LCD_WR_REG_DATA(0x0032,0x0603); 
        LCD_WR_REG_DATA(0x0033,0x0700); 
        LCD_WR_REG_DATA(0x0034,0x0202); 
        LCD_WR_REG_DATA(0x0035,0x0002); //?0x0606
        LCD_WR_REG_DATA(0x0036,0x1F0F);
        LCD_WR_REG_DATA(0x0037,0x0707); //0x0f0f  0x0105
        LCD_WR_REG_DATA(0x0038,0x0000); 
        LCD_WR_REG_DATA(0x0039,0x0000); 
        LCD_WR_REG_DATA(0x003A,0x0707); 
        LCD_WR_REG_DATA(0x003B,0x0000); //0x0303
        LCD_WR_REG_DATA(0x003C,0x0007); //?0x0707
        LCD_WR_REG_DATA(0x003D,0x0000); //0x1313//0x1f08
        delay_ms(50); 
        LCD_WR_REG_DATA(0x0007,0x0001);
        LCD_WR_REG_DATA(0x0017,0x0001);//������Դ
        delay_ms(50); 
  		//��Դ����
        LCD_WR_REG_DATA(0x0010,0x17A0); 
        LCD_WR_REG_DATA(0x0011,0x0217);//reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        LCD_WR_REG_DATA(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        LCD_WR_REG_DATA(0x0013,0x0F00);//VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        LCD_WR_REG_DATA(0x002A,0x0000);  
        LCD_WR_REG_DATA(0x0029,0x000A);//0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        LCD_WR_REG_DATA(0x0012,0x013E);// 0x013C  power supply on
        //Coordinates Control//
        LCD_WR_REG_DATA(0x0050,0x0000);//0x0e00
        LCD_WR_REG_DATA(0x0051,0x00EF); 
        LCD_WR_REG_DATA(0x0052,0x0000); 
        LCD_WR_REG_DATA(0x0053,0x013F); 
    	//Pannel Image Control//
        LCD_WR_REG_DATA(0x0060,0x2700); 
        LCD_WR_REG_DATA(0x0061,0x0001); 
        LCD_WR_REG_DATA(0x006A,0x0000); 
        LCD_WR_REG_DATA(0x0080,0x0000); 
    	//Partial Image Control//
        LCD_WR_REG_DATA(0x0081,0x0000); 
        LCD_WR_REG_DATA(0x0082,0x0000); 
        LCD_WR_REG_DATA(0x0083,0x0000); 
        LCD_WR_REG_DATA(0x0084,0x0000); 
        LCD_WR_REG_DATA(0x0085,0x0000); 
  		//Panel Interface Control//
        LCD_WR_REG_DATA(0x0090,0x0013);//0x0010 frenqucy
        LCD_WR_REG_DATA(0x0092,0x0300); 
        LCD_WR_REG_DATA(0x0093,0x0005); 
        LCD_WR_REG_DATA(0x0095,0x0000); 
        LCD_WR_REG_DATA(0x0097,0x0000); 
        LCD_WR_REG_DATA(0x0098,0x0000); 
  
        LCD_WR_REG_DATA(0x0001,0x0100); 
        LCD_WR_REG_DATA(0x0002,0x0700); 
        LCD_WR_REG_DATA(0x0003,0x1038);//ɨ�跽�� ��->��  ��->�� 
        LCD_WR_REG_DATA(0x0004,0x0000); 
        LCD_WR_REG_DATA(0x000C,0x0000); 
        LCD_WR_REG_DATA(0x000F,0x0000); 
        LCD_WR_REG_DATA(0x0020,0x0000); 
        LCD_WR_REG_DATA(0x0021,0x0000); 
        LCD_WR_REG_DATA(0x0007,0x0021); 
        delay_ms(20);
        LCD_WR_REG_DATA(0x0007,0x0061); 
        delay_ms(20);
        LCD_WR_REG_DATA(0x0007,0x0173); 
        delay_ms(20);
	}else if(lcddev.id==0xB505)
	{
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
		
		LCD_WR_REG_DATA(0x00a4,0x0001);
		delay_ms(20);		  
		LCD_WR_REG_DATA(0x0060,0x2700);
		LCD_WR_REG_DATA(0x0008,0x0202);
		
		LCD_WR_REG_DATA(0x0030,0x0214);
		LCD_WR_REG_DATA(0x0031,0x3715);
		LCD_WR_REG_DATA(0x0032,0x0604);
		LCD_WR_REG_DATA(0x0033,0x0e16);
		LCD_WR_REG_DATA(0x0034,0x2211);
		LCD_WR_REG_DATA(0x0035,0x1500);
		LCD_WR_REG_DATA(0x0036,0x8507);
		LCD_WR_REG_DATA(0x0037,0x1407);
		LCD_WR_REG_DATA(0x0038,0x1403);
		LCD_WR_REG_DATA(0x0039,0x0020);
		
		LCD_WR_REG_DATA(0x0090,0x001a);
		LCD_WR_REG_DATA(0x0010,0x0000);
		LCD_WR_REG_DATA(0x0011,0x0007);
		LCD_WR_REG_DATA(0x0012,0x0000);
		LCD_WR_REG_DATA(0x0013,0x0000);
		delay_ms(20);
		
		LCD_WR_REG_DATA(0x0010,0x0730);
		LCD_WR_REG_DATA(0x0011,0x0137);
		delay_ms(20);
		
		LCD_WR_REG_DATA(0x0012,0x01b8);
		delay_ms(20);
		
		LCD_WR_REG_DATA(0x0013,0x0f00);
		LCD_WR_REG_DATA(0x002a,0x0080);
		LCD_WR_REG_DATA(0x0029,0x0048);
		delay_ms(20);
		
		LCD_WR_REG_DATA(0x0001,0x0100);
		LCD_WR_REG_DATA(0x0002,0x0700);
        LCD_WR_REG_DATA(0x0003,0x1038);//ɨ�跽�� ��->��  ��->�� 
		LCD_WR_REG_DATA(0x0008,0x0202);
		LCD_WR_REG_DATA(0x000a,0x0000);
		LCD_WR_REG_DATA(0x000c,0x0000);
		LCD_WR_REG_DATA(0x000d,0x0000);
		LCD_WR_REG_DATA(0x000e,0x0030);
		LCD_WR_REG_DATA(0x0050,0x0000);
		LCD_WR_REG_DATA(0x0051,0x00ef);
		LCD_WR_REG_DATA(0x0052,0x0000);
		LCD_WR_REG_DATA(0x0053,0x013f);
		LCD_WR_REG_DATA(0x0060,0x2700);
		LCD_WR_REG_DATA(0x0061,0x0001);
		LCD_WR_REG_DATA(0x006a,0x0000);
		//LCD_WR_REG_DATA(0x0080,0x0000);
		//LCD_WR_REG_DATA(0x0081,0x0000);
		LCD_WR_REG_DATA(0x0090,0X0011);
		LCD_WR_REG_DATA(0x0092,0x0600);
		LCD_WR_REG_DATA(0x0093,0x0402);
		LCD_WR_REG_DATA(0x0094,0x0002);
		delay_ms(20);
		
		LCD_WR_REG_DATA(0x0007,0x0001);
		delay_ms(20);
		LCD_WR_REG_DATA(0x0007,0x0061);
		LCD_WR_REG_DATA(0x0007,0x0173);
		
		LCD_WR_REG_DATA(0x0020,0x0000);
		LCD_WR_REG_DATA(0x0021,0x0000);	  
		LCD_WR_REG_DATA(0x00,0x22);  
	}else if(lcddev.id==0xC505)
	{
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
		delay_ms(20);		  
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
		LCD_WR_REG_DATA(0x0000,0x0000);
 		LCD_WR_REG_DATA(0x00a4,0x0001);
		delay_ms(20);		  
		LCD_WR_REG_DATA(0x0060,0x2700);
		LCD_WR_REG_DATA(0x0008,0x0806);
		
		LCD_WR_REG_DATA(0x0030,0x0703);//gamma setting
		LCD_WR_REG_DATA(0x0031,0x0001);
		LCD_WR_REG_DATA(0x0032,0x0004);
		LCD_WR_REG_DATA(0x0033,0x0102);
		LCD_WR_REG_DATA(0x0034,0x0300);
		LCD_WR_REG_DATA(0x0035,0x0103);
		LCD_WR_REG_DATA(0x0036,0x001F);
		LCD_WR_REG_DATA(0x0037,0x0703);
		LCD_WR_REG_DATA(0x0038,0x0001);
		LCD_WR_REG_DATA(0x0039,0x0004);
		
		
		
		LCD_WR_REG_DATA(0x0090, 0x0015);	//80Hz
		LCD_WR_REG_DATA(0x0010, 0X0410);	//BT,AP
		LCD_WR_REG_DATA(0x0011,0x0247);	//DC1,DC0,VC
		LCD_WR_REG_DATA(0x0012, 0x01BC);
		LCD_WR_REG_DATA(0x0013, 0x0e00);
		delay_ms(120);
		LCD_WR_REG_DATA(0x0001, 0x0100);
		LCD_WR_REG_DATA(0x0002, 0x0200);
		LCD_WR_REG_DATA(0x0003, 0x1030);
		
		LCD_WR_REG_DATA(0x000A, 0x0008);
		LCD_WR_REG_DATA(0x000C, 0x0000);
		
		LCD_WR_REG_DATA(0x000E, 0x0020);
		LCD_WR_REG_DATA(0x000F, 0x0000);
		LCD_WR_REG_DATA(0x0020, 0x0000);	//H Start
		LCD_WR_REG_DATA(0x0021, 0x0000);	//V Start
		LCD_WR_REG_DATA(0x002A,0x003D);	//vcom2
		delay_ms(20);
		LCD_WR_REG_DATA(0x0029, 0x002d);
		LCD_WR_REG_DATA(0x0050, 0x0000);
		LCD_WR_REG_DATA(0x0051, 0xD0EF);
		LCD_WR_REG_DATA(0x0052, 0x0000);
		LCD_WR_REG_DATA(0x0053, 0x013F);
		LCD_WR_REG_DATA(0x0061, 0x0000);
		LCD_WR_REG_DATA(0x006A, 0x0000);
		LCD_WR_REG_DATA(0x0092,0x0300); 
 
 		LCD_WR_REG_DATA(0x0093, 0x0005);
		LCD_WR_REG_DATA(0x0007, 0x0100);
	}else if(lcddev.id==0x8989)//OK |/|/|
	{	   
		LCD_WR_REG_DATA(0x0000,0x0001);    delay_ms(1);  //�򿪾���
	    LCD_WR_REG_DATA(0x0003,0xA8A4);    delay_ms(1);   //0xA8A4
	    LCD_WR_REG_DATA(0x000C,0x0000);    delay_ms(1);   
	    LCD_WR_REG_DATA(0x000D,0x080C);    delay_ms(1);   
	    LCD_WR_REG_DATA(0x000E,0x2B00);    delay_ms(1);   
	    LCD_WR_REG_DATA(0x001E,0x00B7);    delay_ms(1);   
	    LCD_WR_REG_DATA(0x0001,0x2B3F);    delay_ms(1);   //�����������320*240  0x6B3F
	    LCD_WR_REG_DATA(0x0002,0x0600);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0010,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0011,0x6070);    delay_ms(1);        //0x4030           //�������ݸ�ʽ  16λɫ 
	    LCD_WR_REG_DATA(0x0005,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0006,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0016,0xEF1C);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0017,0x0003);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0007,0x0233);    delay_ms(1);        //0x0233       
	    LCD_WR_REG_DATA(0x000B,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x000F,0x0000);    delay_ms(1);        //ɨ�迪ʼ��ַ
	    LCD_WR_REG_DATA(0x0041,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0042,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0048,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0049,0x013F);    delay_ms(1);
	    LCD_WR_REG_DATA(0x004A,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x004B,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0044,0xEF00);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0045,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0046,0x013F);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0030,0x0707);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0031,0x0204);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0032,0x0204);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0033,0x0502);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0034,0x0507);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0035,0x0204);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0036,0x0204);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0037,0x0502);    delay_ms(1);
	    LCD_WR_REG_DATA(0x003A,0x0302);    delay_ms(1);
	    LCD_WR_REG_DATA(0x003B,0x0302);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0023,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0024,0x0000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x0025,0x8000);    delay_ms(1);
	    LCD_WR_REG_DATA(0x004f,0);        //����ַ0
	    LCD_WR_REG_DATA(0x004e,0);        //����ַ0
	}else if(lcddev.id==0x4531)//OK |/|/|
	{
		LCD_WR_REG_DATA(0X00,0X0001);   
		delay_ms(10);   
		LCD_WR_REG_DATA(0X10,0X1628);   
		LCD_WR_REG_DATA(0X12,0X000e);//0x0006    
		LCD_WR_REG_DATA(0X13,0X0A39);   
		delay_ms(10);   
		LCD_WR_REG_DATA(0X11,0X0040);   
		LCD_WR_REG_DATA(0X15,0X0050);   
		delay_ms(10);   
		LCD_WR_REG_DATA(0X12,0X001e);//16    
		delay_ms(10);   
		LCD_WR_REG_DATA(0X10,0X1620);   
		LCD_WR_REG_DATA(0X13,0X2A39);   
		delay_ms(10);   
		LCD_WR_REG_DATA(0X01,0X0100);   
		LCD_WR_REG_DATA(0X02,0X0300);   
		LCD_WR_REG_DATA(0X03,0X1038);//�ı䷽���   
		LCD_WR_REG_DATA(0X08,0X0202);   
		LCD_WR_REG_DATA(0X0A,0X0008);   
		LCD_WR_REG_DATA(0X30,0X0000);   
		LCD_WR_REG_DATA(0X31,0X0402);   
		LCD_WR_REG_DATA(0X32,0X0106);   
		LCD_WR_REG_DATA(0X33,0X0503);   
		LCD_WR_REG_DATA(0X34,0X0104);   
		LCD_WR_REG_DATA(0X35,0X0301);   
		LCD_WR_REG_DATA(0X36,0X0707);   
		LCD_WR_REG_DATA(0X37,0X0305);   
		LCD_WR_REG_DATA(0X38,0X0208);   
		LCD_WR_REG_DATA(0X39,0X0F0B);   
		LCD_WR_REG_DATA(0X41,0X0002);   
		LCD_WR_REG_DATA(0X60,0X2700);   
		LCD_WR_REG_DATA(0X61,0X0001);   
		LCD_WR_REG_DATA(0X90,0X0210);   
		LCD_WR_REG_DATA(0X92,0X010A);   
		LCD_WR_REG_DATA(0X93,0X0004);   
		LCD_WR_REG_DATA(0XA0,0X0100);   
		LCD_WR_REG_DATA(0X07,0X0001);   
		LCD_WR_REG_DATA(0X07,0X0021);   
		LCD_WR_REG_DATA(0X07,0X0023);   
		LCD_WR_REG_DATA(0X07,0X0033);   
		LCD_WR_REG_DATA(0X07,0X0133);   
		LCD_WR_REG_DATA(0XA0,0X0000); 
	}else if(lcddev.id==0x4535)
	{			      
		LCD_WR_REG_DATA(0X15,0X0030);   
		LCD_WR_REG_DATA(0X9A,0X0010);   
 		LCD_WR_REG_DATA(0X11,0X0020);   
 		LCD_WR_REG_DATA(0X10,0X3428);   
		LCD_WR_REG_DATA(0X12,0X0002);//16    
 		LCD_WR_REG_DATA(0X13,0X1038);   
		delay_ms(40);   
		LCD_WR_REG_DATA(0X12,0X0012);//16    
		delay_ms(40);   
  		LCD_WR_REG_DATA(0X10,0X3420);   
 		LCD_WR_REG_DATA(0X13,0X3038);   
		delay_ms(70);   
		LCD_WR_REG_DATA(0X30,0X0000);   
		LCD_WR_REG_DATA(0X31,0X0402);   
		LCD_WR_REG_DATA(0X32,0X0307);   
		LCD_WR_REG_DATA(0X33,0X0304);   
		LCD_WR_REG_DATA(0X34,0X0004);   
		LCD_WR_REG_DATA(0X35,0X0401);   
		LCD_WR_REG_DATA(0X36,0X0707);   
		LCD_WR_REG_DATA(0X37,0X0305);   
		LCD_WR_REG_DATA(0X38,0X0610);   
		LCD_WR_REG_DATA(0X39,0X0610); 
		  
		LCD_WR_REG_DATA(0X01,0X0100);   
		LCD_WR_REG_DATA(0X02,0X0300);   
		LCD_WR_REG_DATA(0X03,0X1030);//�ı䷽���   
		LCD_WR_REG_DATA(0X08,0X0808);   
		LCD_WR_REG_DATA(0X0A,0X0008);   
 		LCD_WR_REG_DATA(0X60,0X2700);   
		LCD_WR_REG_DATA(0X61,0X0001);   
		LCD_WR_REG_DATA(0X90,0X013E);   
		LCD_WR_REG_DATA(0X92,0X0100);   
		LCD_WR_REG_DATA(0X93,0X0100);   
 		LCD_WR_REG_DATA(0XA0,0X3000);   
 		LCD_WR_REG_DATA(0XA3,0X0010);   
		LCD_WR_REG_DATA(0X07,0X0001);   
		LCD_WR_REG_DATA(0X07,0X0021);   
		LCD_WR_REG_DATA(0X07,0X0023);   
		LCD_WR_REG_DATA(0X07,0X0033);   
		LCD_WR_REG_DATA(0X07,0X0133);   
	}else if(lcddev.id==0x0070||lcddev.id==0x0043||lcddev.id==0x0050)	 //MD070SD OR MD050SD
	{
		//��ҵ��������ģ�����ʼ����
	    LCD_WR_REG_DATA(0X01,16);  //�򿪱���	
	}else if(lcddev.id==0x1907)	 
	{

	HDP=799;
    HT=928;
    HPS=46;
    LPS=15;
    HPW=48;

    VDP=479;
    VT=525;
    VPS=16;
    FPS=8;
    VPW=16;


	LCD_WR_REG(0x00E2);	//PLL multiplier, set PLL clock to 120M
	LCD_WR_DATA(0x0023);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_DATA(0x0002);
	LCD_WR_DATA(0x0004);
	LCD_WR_REG(0x00E0);  // PLL enable
	LCD_WR_DATA(0x0001);
	delay_ms(1);
	LCD_WR_REG(0x00E0);
	LCD_WR_DATA(0x0003);
	delay_ms(5);
	LCD_WR_REG(0x0001);  // software reset
	delay_ms(5);
	LCD_WR_REG(0x00E6);	//PLL setting for PCLK, depends on resolution
	LCD_WR_DATA(0x0003);
	LCD_WR_DATA(0x00ff);
	LCD_WR_DATA(0x00ff);

	LCD_WR_REG(0x00B0);	//LCD SPECIFICATION
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_DATA(HDP&0X00FF);
    LCD_WR_DATA((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_DATA(VDP&0X00FF);
    LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_DATA((HT>>8)&0X00FF);  //Set HT
	LCD_WR_DATA(HT&0X00FF);
	LCD_WR_DATA((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(HPS&0X00FF);
	LCD_WR_DATA(HPW);			   //Set HPW
	LCD_WR_DATA((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(LPS&0X00FF);
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_DATA((VT>>8)&0X00FF);   //Set VT
	LCD_WR_DATA(VT&0X00FF);
	LCD_WR_DATA((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_DATA(VPS&0X00FF);
	LCD_WR_DATA(VPW);			   //Set VPW
	LCD_WR_DATA((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_DATA(FPS&0X00FF);

	LCD_WR_REG(0x00BA);
	LCD_WR_DATA(0x0005);    //GPIO[3:0] out 1

	LCD_WR_REG(0x00B8);
	LCD_WR_DATA(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_DATA(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x0036); //rotation
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00F0); //pixel data interface
	LCD_WR_DATA(0x0003);


	delay_ms(5);

	LCD_WR_REG(0x0029); //display on



	LCD_WR_REG(0x00d0); 
	LCD_WR_DATA(0x000d);
	
	}else if(lcddev.id==0x1905)	 
	{

	HDP=799;
    HT=928;
    HPS=46;
    LPS=15;
    HPW=48;

    VDP=479;
    VT=525;
    VPS=16;
    FPS=8;
    VPW=16;

	LCD_WR_REG(0x00E2);	//PLL multiplier, set PLL clock to 120M
	LCD_WR_DATA(0x0023);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_DATA(0x0002);
	LCD_WR_DATA(0x0004);
	LCD_WR_REG(0x00E0);  // PLL enable
	LCD_WR_DATA(0x0001);
	delay_ms(1);
	LCD_WR_REG(0x00E0);
	LCD_WR_DATA(0x0003);
	delay_ms(5);
	LCD_WR_REG(0x0001);  // software reset
	delay_ms(5);
	LCD_WR_REG(0x00E6);	//PLL setting for PCLK, depends on resolution
	LCD_WR_DATA(0x0003);
	LCD_WR_DATA(0x00ff);
	LCD_WR_DATA(0x00ff);

	LCD_WR_REG(0x00B0);	//LCD SPECIFICATION
	LCD_WR_DATA(0x0027);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_DATA(HDP&0X00FF);
    LCD_WR_DATA((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_DATA(VDP&0X00FF);
    LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_DATA((HT>>8)&0X00FF);  //Set HT
	LCD_WR_DATA(HT&0X00FF);
	LCD_WR_DATA((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(HPS&0X00FF);
	LCD_WR_DATA(HPW);			   //Set HPW
	LCD_WR_DATA((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(LPS&0X00FF);
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_DATA((VT>>8)&0X00FF);   //Set VT
	LCD_WR_DATA(VT&0X00FF);
	LCD_WR_DATA((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_DATA(VPS&0X00FF);
	LCD_WR_DATA(VPW);			   //Set VPW
	LCD_WR_DATA((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_DATA(FPS&0X00FF);

	LCD_WR_REG(0x00BA);
	LCD_WR_DATA(0x000F);    //GPIO[3:0] out 1

	LCD_WR_REG(0x00B8);
	LCD_WR_DATA(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_DATA(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x0036); //rotation
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00F0); //pixel data interface
	LCD_WR_DATA(0x0003);


	delay_ms(5);

	LCD_WR_REG(0x0029); //display on



	LCD_WR_REG(0x00d0); 
	LCD_WR_DATA(0x000d);
	}else if(lcddev.id==0x1943)	 
	{

	HDP=479;
	HT=531;
	HPS=43;
	LPS=8;
	HPW=10;
	
	VDP=271;
	VT=288;
	VPS=12;
  	FPS=4;
	VPW=10;
	LCD_WR_REG(0x00E2);	//PLL multiplier, set PLL clock to 120M
	LCD_WR_DATA(0x002d);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_DATA(0x0002);
	LCD_WR_DATA(0x0004);
	LCD_WR_REG(0x00E0);  // PLL enable
	LCD_WR_DATA(0x0001);
	delay_ms(1);
	LCD_WR_REG(0x00E0);
	LCD_WR_DATA(0x0003);
	delay_ms(5);
	LCD_WR_REG(0x0001);  // software reset
	delay_ms(5);
	LCD_WR_REG(0x00E6);	//PLL setting for PCLK, depends on resolution
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x00ff);
	LCD_WR_DATA(0x00be);

	LCD_WR_REG(0x00B0);	//LCD SPECIFICATION
	LCD_WR_DATA(0x0020);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_DATA(HDP&0X00FF);
    LCD_WR_DATA((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_DATA(VDP&0X00FF);
    LCD_WR_DATA(0x0000);
	delay_ms(5);
	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_DATA((HT>>8)&0X00FF);  //Set HT
	LCD_WR_DATA(HT&0X00FF);
	LCD_WR_DATA((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_DATA(HPS&0X00FF);
	LCD_WR_DATA(HPW);			   //Set HPW
	LCD_WR_DATA((LPS>>8)&0X00FF);  //SetLPS
	LCD_WR_DATA(LPS&0X00FF);
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_DATA((VT>>8)&0X00FF);   //Set VT
	LCD_WR_DATA(VT&0X00FF);
	LCD_WR_DATA((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_DATA(VPS&0X00FF);
	LCD_WR_DATA(VPW);			   //Set VPW
	LCD_WR_DATA((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_DATA(FPS&0X00FF);


	LCD_WR_REG(0x0036); //rotation
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00F0); //pixel data interface
	LCD_WR_DATA(0x0003);


	delay_ms(5);


	LCD_WR_REG(0x0029); //display on

	LCD_WR_REG(0x00BE); //set PWM for B/L
	LCD_WR_DATA(0x0006);
	LCD_WR_DATA(0x00f0);
	LCD_WR_DATA(0x0001);
	LCD_WR_DATA(0x00f0);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x0000);

	LCD_WR_REG(0x00d0); 
	LCD_WR_DATA(0x000d);

    //----------LCD RESET---GPIO0-------------------//
	LCD_WR_REG(0x00B8);
	LCD_WR_DATA(0x0000);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_DATA(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x00BA);
	LCD_WR_DATA(0x0000);  
	}else if(lcddev.id==0x1121)	 
	{
	  	LCD_WR_REG_DATA(0x11,0x2004);		
	    LCD_WR_REG_DATA(0x13,0xCC00);		
	    LCD_WR_REG_DATA(0x15,0x2600);	
		LCD_WR_REG_DATA(0x14,0x252A);	
	//	LCD_WR_REG_DATA(0x14,0x002A);		
		LCD_WR_REG_DATA(0x12,0x0033);		
		LCD_WR_REG_DATA(0x13,0xCC04);		
		delay_ms(1); 
		LCD_WR_REG_DATA(0x13,0xCC06);		
		delay_ms(1); 
		LCD_WR_REG_DATA(0x13,0xCC4F);		
		delay_ms(1); 
		LCD_WR_REG_DATA(0x13,0x674F);
		LCD_WR_REG_DATA(0x11,0x2003);
		delay_ms(1); 	
		LCD_WR_REG_DATA(0x30,0x2609);		
		LCD_WR_REG_DATA(0x31,0x242C);		
		LCD_WR_REG_DATA(0x32,0x1F23);		
		LCD_WR_REG_DATA(0x33,0x2425);		
		LCD_WR_REG_DATA(0x34,0x2226);		
		LCD_WR_REG_DATA(0x35,0x2523);		
		LCD_WR_REG_DATA(0x36,0x1C1A);		
		LCD_WR_REG_DATA(0x37,0x131D);		
		LCD_WR_REG_DATA(0x38,0x0B11);		
		LCD_WR_REG_DATA(0x39,0x1210);		
		LCD_WR_REG_DATA(0x3A,0x1315);		
		LCD_WR_REG_DATA(0x3B,0x3619);		
		LCD_WR_REG_DATA(0x3C,0x0D00);		
		LCD_WR_REG_DATA(0x3D,0x000D);		
		LCD_WR_REG_DATA(0x16,0x0007);		
		LCD_WR_REG_DATA(0x02,0x0013);		
		LCD_WR_REG_DATA(0x03,0x0003);		
		LCD_WR_REG_DATA(0x01,0x0127);		
		delay_ms(1); 
		LCD_WR_REG_DATA(0x08,0x0303);		
		LCD_WR_REG_DATA(0x0A,0x000B);		
		LCD_WR_REG_DATA(0x0B,0x0003);   
		LCD_WR_REG_DATA(0x0C,0x0000);   
		LCD_WR_REG_DATA(0x41,0x0000);    
		LCD_WR_REG_DATA(0x50,0x0000);   
		LCD_WR_REG_DATA(0x60,0x0005);    
	    LCD_WR_REG_DATA(0x70,0x000B);    
		LCD_WR_REG_DATA(0x71,0x0000);    
		LCD_WR_REG_DATA(0x78,0x0000);    
		LCD_WR_REG_DATA(0x7A,0x0000);   
		LCD_WR_REG_DATA(0x79,0x0007);		
		LCD_WR_REG_DATA(0x07,0x0051);   
		delay_ms(1); 	
		LCD_WR_REG_DATA(0x07,0x0053);		
		LCD_WR_REG_DATA(0x79,0x0000);
		delay_ms(1);
	}

    delay_ms(50);
	LCD_Clear(WHITE); 
	
}  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA(color);
	}

}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{									   
	 	LCD_SetCursor(sx,i);      				//���ù��λ�� 
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
		for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
	}
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//д������ 
	}	  
}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }  
}

void showimage(u16 x,u16 y) //��ʾ40*40ͼƬ
{  
	u16 i,j,k;
	u16 da;
	k=0;
	for(i=0;i<40;i++)
	{	
		LCD_SetCursor(x,y+i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2];
			LCD_WR_DATA(da);		
			k++;
		}
	}
}
 void copyimage() //����һ����
{
	u16 i;
	u16 da;
	u16 ll;

    ll=POINT_COLOR;
	POINT_COLOR=RED;
	 for(i=100;i<150;i++)
	 {
		LCD_DrawPoint(i,100);
	 }
	LCD_ShowNum(0,0,POINT_COLOR,5,16);//��ʾ��ɫֵ��ʮ����

	 for(i=100;i<150;i++)
	 {
		da=LCD_ReadPoint(i,100);
		da=LCD_ReadPoint(i,100);
		POINT_COLOR=da;
		LCD_DrawPoint(i,120);
	 	if(i==100)
		{
			LCD_ShowNum(0,20,da,5,16); //��ʾ�����ĵ�һ�������ɫֵ��ʮ����
		}
		if(i==101)
		{
			LCD_ShowNum(0,40,da,5,16);
		}
		if(i==102)
		{
			LCD_ShowNum(0,60,da,5,16);
		}
	
	 }

	 POINT_COLOR=ll;
	 while(1)
	 {
	 }
}




























