#include"ds1302.h"
#include<intrins.h>
uchar write_add[];
uchar read_add[];
uchar time_data[];
void write_one(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		sclk=0;
		io=dat&0x01;
		dat=dat>>1;
		sclk=1;	
	}
}
uchar read_one(uchar add)
{
	uchar dat;
	uchar i;
	sclk=0;
	_nop_();
	rst=0;
	_nop_();
	rst=1;
	_nop_();
	write_one(add);
	for(i=0;i<8;i++)
	{
		sclk=1;
		_nop_();
		dat=dat>>1;	
		sclk=0;
		_nop_();
		if(io)
		{
			dat=dat|0x80;
		}		
		
	}
	rst=0;
	_nop_();
	io=0;
	_nop_();
	return dat;
}
void write_ds1302(uchar add,uchar dat)
{
	sclk=0;
	_nop_();
	rst=0;
	_nop_();
	rst=1;
	_nop_();
	write_one(add);
	write_one(dat);
	rst=0;
	_nop_();
	sclk=1;
	_nop_();
}
void set_time()
{
	uchar i,j;
	for(i=0;i<7;i++)
	{
		j=time_data[i]/10;
		time_data[i]=time_data[i]%10;
		time_data[i]=time_data[i]+j*16;
	}
	write_ds1302(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		write_ds1302(write_add[i],time_data[i]);
	}
	write_ds1302(0x8e,0x80);
}
void read_time()
{
	uchar i;
	for(i=0;i<8;i++)
	{
		time_data[i]=read_one(read_add[i]);
	}
}