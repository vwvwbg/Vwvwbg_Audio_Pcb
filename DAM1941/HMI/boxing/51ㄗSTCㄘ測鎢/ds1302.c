#include <intrins.h>        /* use _nop_() function */
//DS1302�ܽŶ���
sbit T_CLK  = P3^6;    //p3.6
sbit T_IO   = P3^7;    //p3.7
sbit T_RST  = P3^3;    //P3.3

sbit ACC0   = ACC^0;
sbit ACC1   = ACC^1;
sbit ACC2   = ACC^2;
sbit ACC3   = ACC^3;
sbit ACC4   = ACC^4;
sbit ACC5   = ACC^5;
sbit ACC6   = ACC^6;
sbit ACC7   = ACC^7;
//------------------------------------------------------------------------------------------
//ʱ������(7�ֽ�BCD��)��ʽΪ�� ��   ��   ʱ   ��    ������   ��-----------------------------
unsigned char idata Time[7];//={0x30,0x42,0x23,0x18,0x06,0x04,0x09};
unsigned char idata Wc[3];
unsigned char idata alarm[2]={0x30,0x06};
//------------------------------------------------------------------------------------------
bit flag; //flag-������

unsigned char alarm_ss,alarm_hh;
int second,minute,hour,day,month,week,year,zwc,fwc,wdc,bal,txt,wendu;
unsigned char BCD2HEX(unsigned char BCDChar);
unsigned char HEX2BCD(unsigned char HEXChar);
void WriteByteDS1302(unsigned char Data);
unsigned char ReadByteDS1302(void); 
void WriteDS1302(unsigned char Addr,unsigned char Data);
unsigned char ReadDS1302(unsigned char Addr);
void Set(unsigned char sel,unsigned char selby);
void SetTime(unsigned char  *pClock);
void ReadTime();
void WriteTime();
void StopTime();
void StartTime();
void bucang(void);
/******************************************************************************************* 
*  �������� BCD2HEX    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/ 
unsigned char BCD2HEX(unsigned char BCDChar)     
{ 
    unsigned char temp; 
    temp=(BCDChar/16*10+BCDChar%16); 
    return temp; 
} 
/******************************************************************************************* 
*  �������� WriteByteDS1302    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/  
void WriteByteDS1302(unsigned char Data) 
{ 
    unsigned char i;
    ACC = Data;
    for(i=8; i>0; i--)
    {
        T_IO = ACC0; _nop_();_nop_();_nop_();        
        T_CLK = 1;	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        T_CLK = 0;	_nop_();_nop_();_nop_();
        ACC = ACC >> 1; 
    } 
}
/******************************************************************************************* 
*  �������� ReadByteDS1302    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/  
unsigned char ReadByteDS1302(void) 
{ 
    unsigned char i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;       
        ACC7 = T_IO; _nop_();_nop_();
        T_CLK = 1;	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
        T_CLK = 0;
    } 
    return(ACC); 
}
/******************************************************************************************* 
*  �������� WriteDS1302    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/  
void WriteDS1302(unsigned char Addr,unsigned char Data)
{
    T_RST = 0;	 _nop_();_nop_();_nop_();_nop_();
    T_CLK = 0;	 _nop_();_nop_();_nop_();_nop_();
    T_RST = 1;	 _nop_();_nop_();_nop_();_nop_();
    WriteByteDS1302(Addr); _nop_();_nop_();_nop_();_nop_();   
    WriteByteDS1302(Data); _nop_();_nop_();_nop_();_nop_(); 
    T_CLK = 1;	 _nop_();_nop_();_nop_();_nop_();
    T_RST = 0;	_nop_();_nop_();_nop_();_nop_();
	

}
/******************************************************************************************* 
*  �������� ReadDS1302    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/  
unsigned char ReadDS1302(unsigned char Addr)
{
    unsigned char Data;
    T_RST = 0;	_nop_();_nop_();_nop_();_nop_();
    T_CLK = 0;	_nop_();_nop_();
    T_RST = 1;	_nop_();_nop_();_nop_();_nop_();
    WriteByteDS1302(Addr);    _nop_();_nop_();_nop_();_nop_();      
    Data = ReadByteDS1302();  _nop_();_nop_();_nop_();_nop_();   
    T_CLK = 1;	  _nop_();_nop_();_nop_();_nop_();
    T_RST = 0;
    return(Data);
}
/******************************************************************************************* 
*  �������� Set    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/ 
void Set(unsigned char sel,unsigned char selby) 
{
    unsigned char address;
	char item;
    unsigned char max,min;

    if(sel==0)  {address=0x80; max=59;min=0;}    //��
    if(sel==1)  {address=0x82; max=59;min=0;}    //����
    if(sel==2)  {address=0x84; max=23;min=0;}    //Сʱ
	if(month==2)
		if(flag==1)
		{
			if(sel==3)  {address=0x86; max=28;min=1;} 
		}
		else
		{
			if(sel==3)  {address=0x86; max=27;min=1;}
		}
	else
	{
	   	if(month==1|month==3|month==5|month==7|month==8|month==10|month==12)
		{    
			if(sel==3)  {address=0x86; max=31;min=1;}
		}
		if(month==4|month==6|month==9|month==11)
		{    
			if(sel==3)  {address=0x86; max=30;min=1;}
		}
	}
    if(sel==4)  {address=0x88; max=12;min=1;}    //��
    if(sel==5)  {address=0x8a; max=7; min=1;}    //����
    if(sel==6)  {address=0x8c; max=99;min=0;}    //��
    if(sel==7)  {address=0xc2; max=1;min=0;}     //N������
    if(sel==8)  {address=0xc4; max=28;min=0;}    //����N������
    item=ReadDS1302(address+1)/16*10+ReadDS1302(address+1)%16;
    if (selby==0) item++;  else item--;
    if(item>max) item=min;   
    if(item<min) item=max;
           
    WriteDS1302(0x8e,0x00);
    WriteDS1302(address,item/10*16+item%10);
    WriteDS1302(0x90,0xa5); 
    WriteDS1302(0x8e,0x80);  
}

/******************************************************************************************* 
*  �������� ReadTime    
*  ����������  
*  ��ڲ�����  �� 
*  ���ڲ�����  �� 
*******************************************************************************************/  
void ReadTime()
{
    second = BCD2HEX(Time[0]=ReadDS1302(0x81));   _nop_();_nop_();
	minute = BCD2HEX(Time[1]=ReadDS1302(0x83));	 _nop_();_nop_();
	hour   = BCD2HEX(Time[2]=ReadDS1302(0x85));	_nop_();_nop_();
	day    = BCD2HEX(Time[3]=ReadDS1302(0x87));	_nop_();_nop_();
	month  = BCD2HEX(Time[4]=ReadDS1302(0x89));	_nop_();_nop_();
	week   = BCD2HEX(Time[6]=ReadDS1302(0x8b));	_nop_();_nop_();
	year   = BCD2HEX(Time[5]=ReadDS1302(0x8d));	_nop_();_nop_();
	zwc   = BCD2HEX(Wc[0]=ReadDS1302(0xc3)); _nop_();_nop_(); //N������
	fwc   = BCD2HEX(Wc[1]=ReadDS1302(0xc5)); //����N������

}

/*****************************************************************************/
//����1302�ĳ�ʼʱ�䣨�Զ���ʼ����
void Init_1302(void){//-����1302�ĳ�ʼʱ�䣨2007��1��1��00ʱ00��00������һ��

	if(ReadDS1302(0xc1) != 0xaa){
		WriteDS1302(0x8e,0x00);//����д����
		WriteDS1302(0x8c,0x14);//��
		WriteDS1302(0x8a,0x02);//����
		WriteDS1302(0x88,0x06);//��
		WriteDS1302(0x86,0x24);//��
		WriteDS1302(0x84,0x12);//Сʱ
		WriteDS1302(0x82,0x00);//����
		WriteDS1302(0x80,0x00);//��
		WriteDS1302(0x90,0xa5);//���	
		WriteDS1302(0xc0,0xaa);//д���ʼ����־RAM����00��RAMλ�ã�

		WriteDS1302(0x8e,0x80);//��ֹд����
	}
}

