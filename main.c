#include<reg52.h>
#include"iic.h"
#include"ds1302.h"
uchar code tabel1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40,0x00};
uchar code tabel2[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
bit state,save,beep;
 sbit didi=P3^0;
sbit jidianqi=P3^1;
sbit la=P3^2;
sbit lb=P3^3;
sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;
sbit key4=P1^3;

extern uchar time_data[]={13,12,11,30,8,30,30};
extern uchar write_add[]={0x8c,0x8a,0x88,0x86,0x84,0x82,0x80};
extern uchar read_add[]={0x8d,0x8b,0x89,0x87,0x85,0x83,0x81};
uchar d[8];
uchar shidu,eep;
void delay_50us(uint a)
{
	uchar j;
	for(;a>0;a--)
	for(j=19;j>0;j--);
}
void display()
{
	 uchar i;
	if(save==1)
	{
	d[0]=time_data[4]/16;
	d[1]=time_data[4]%16;
	d[2]=10;
	d[3]=time_data[5]/16;
	d[4]=time_data[5]%16;
	d[5]=11;
	d[6]=shidu/10;
	d[7]=shidu%10;
	}
	if(save==0)
	{
	d[0]=10;
	d[1]=10;
	d[2]=eep/10;
	d[3]=eep%10;
	d[4]=11;
	d[5]=11;
	d[6]=11;
	d[7]=11;	
	}
	for(i=0;i<8;i++)
	{
		P0=tabel1[d[i]];
		P2=tabel2[i];
		delay_50us(20);
		P0=0;
	}
}

void key()
{
	if(key1==0)
	{
		delay_50us(200);
		if(key1==0)
		{
			state=~state;
			while(!key1)display();
		}
	}
	if(state==1)
	{
		la=0;
		lb=1;
		if(key2==0)
		{
			delay_50us(200);
			if(key2==0)
			{
				save=~save;
				while(!key2)display();
			}
		}
		if(save==0)
		{
			if(key3==0)
			{
				delay_50us(200);
				if(key3==0)
				{
					eep++;
					while(!key3)display();
				}
			}
			if(key4==0)
			{
				delay_50us(200);
				if(key4==0)
				{
					eep--;
					while(!key4)display();
				}
			}
		}
		if(eep>99||eep<0)eep=0;
		if(save==1)
		{
			write_iic(0xa0,1,eep);
			if(shidu<eep)
			{
				jidianqi=0;
			}
			else jidianqi=1;
		}
	}
	if(state==0)
	{
		la=1;
		lb=0;
		if(key2==0)
		{
			delay_50us(200);
			if(key2==0)
			{
				beep=~beep;
				while(!key2)display();
			}
		}
		if(key3==0)
		{
			delay_50us(200);
			if(key3==0)
			{
				jidianqi=0;
				while(!key3)display();
			}
		}
		if(key4==0)
		{
			delay_50us(200);
			if(key4==0)
			{
				jidianqi=1;
				while(!key4)display();
			}
		}
		if((beep==1)&&(shidu<eep))
		{
			didi=0;
			delay_50us(5);
			didi=1;
			delay_50us(5);
		}
	}
}
void main()
{
	init();
	set_time();
	write_iic(0xa0,1,50);
	channel();
	eep=50;
	beep=1;
	jidianqi=1;
	save=1;
	state=1;
	while(1)
	{
		read_time();
		shidu=read_adc();
		shidu=shidu*0.3883;
		key();
		display();
	}
}