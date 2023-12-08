#include <REGX52.H>
#include <INTRINS.h>

sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P1^2;

#define LCD_DataPort P0

unsigned int Count;

void Timer0Init(void)		//100微秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay15ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 162;
	j = 91;
	do
	{
		while (--j);
	} while (--i);
}


unsigned char LCD1602_ReadCommand(void)
{
	unsigned char a;
	RS = 0;
	RW = 1;
	EN = 0;
	Delay1ms();
	EN = 1;
	Delay1ms();
	a = LCD_DataPort;
	Delay1ms();
	EN = 0;
	Delay1ms();
	return a;
}

unsigned char LCD1602_ReadData(void)
{
	unsigned char a;
	RS = 1;
	RW = 1;
	EN = 0;
	Delay1ms();
	EN = 1;
	Delay1ms();
	a = LCD_DataPort;
	Delay1ms();
	EN = 0;
	Delay1ms();
	return a;
}

void LCD1602_WriteCommand(unsigned char a)
{
	RS = 0;
	RW = 0;
	EN = 0;
	LCD_DataPort = a;
	Delay1ms();
	EN = 1;
	Delay1ms();
	EN = 0;
	Delay1ms();
}

void LCD1602_WriteData(unsigned char a)
{
	RS = 1;
	RW = 0;
	EN = 0;
	LCD_DataPort = a;
	Delay1ms();
	EN = 1;
	Delay1ms();
	EN = 0;
	Delay1ms();
}

void LCD1602_Busy_Check()
{
	unsigned int tmp;
	tmp = LCD1602_ReadData();
	while(tmp&0x80);
}

void LCD1602_Init()
{		
	Delay15ms();
	LCD1602_WriteCommand(0x38);
	Delay5ms();
	LCD1602_WriteCommand(0x38);
	Delay5ms();
	LCD1602_WriteCommand(0x38);
	LCD1602_Busy_Check();
	LCD1602_WriteCommand(0x38);
	LCD1602_Busy_Check();
	LCD1602_WriteCommand(0x0c);
	LCD1602_Busy_Check();
	LCD1602_WriteCommand(0x06);
	LCD1602_Busy_Check();
	LCD1602_WriteCommand(0x01);
}

void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD1602_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD1602_WriteCommand(0x80|(Column-1+0x40));
	}
}

void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD1602_Busy_Check();
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD1602_WriteData(String[i]);
	}
}

void main()
{
	Timer0Init();
	LCD1602_Init();
	
	while(1)
	{
		LCD_ShowString(1, 1, "ASDFGHJKLZXCVBNM");
		LCD_ShowString(2, 6, "123");
//		LCD1602_Busy_Check();
//		LCD1602_WriteCommand(0x80);
//		LCD1602_WriteData(0x31);
		if(Count>=1000)
		{
	//		LCD1602_WriteCommand(0x18);
			LCD1602_Busy_Check();
			LCD1602_WriteCommand(0x1C);
			Count=0;
		}
	}
}

void service_timer0() interrupt 1
{
	TH0=(65535-1000)/256;
	TL0=(65535-1000)%256;
	Count++;
}