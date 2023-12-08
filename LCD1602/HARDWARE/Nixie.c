#include <REGX52.H>
#include <INTRINS.H>

unsigned char NixieTable[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88};

sbit P27 = P2^7;
sbit P26 = P2^6;
sbit P25 = P2^5;

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void Nixie(unsigned char Location,Number)
{
	switch(Location)
	{
		case 1: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 0; break; 
		case 2: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 1; break; 
		case 3: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 2; break;
		case 4: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 3; break; 
		case 5: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 4; break; 
		case 6: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 5; break; 
		case 7: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 6; break; 
		case 8: P27 = 1; P26 = 1; P25 = 0; P0 = 0x01 << 7; break;
	}
	P27 = 1;
	P26 = 1;
	P25 = 1;
	P0 = NixieTable[Number];
	Delay500us();
}
