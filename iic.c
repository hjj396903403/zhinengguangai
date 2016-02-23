#include"iic.h"
#include<intrins.h>
void delay()
{
	_nop_(); 	_nop_();	_nop_();	_nop_();	_nop_();	_nop_();	_nop_();
}
void init()
{
	sda=1;
	scl=1;
}
void start()
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
	scl=0;
	delay();


}
void stop()
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}
void ack()
{
	uchar i;
	scl=1;
	delay();
	while((sda=1)&&(i<200))i++;
	scl=0;
	delay();
}
void noack()
{
	scl=1;
	delay();
	sda=1;
	delay();
	scl=0;
	delay();
}
void write_byte(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		scl=0;
		delay();
		sda=dat&0x80;
		dat=dat<<1;
		scl=1;
		delay();
		scl=0;
		delay();
	}
	sda=1;
	delay();
}
uchar read_byte()
{
	uchar dat,k;
	 uchar i;
	 for(i=0;i<8;i++)
	 {
	 	scl=1;
		delay();
		dat=sda;
		k=(k<<1)|dat;
		scl=0;
		delay();
	 }
	 return k;
}
void write_iic(uchar add,uchar byte_add,uchar dat)
{
	start();
	write_byte(add);
	ack();
	write_byte(byte_add);
	ack();
	write_byte(dat);
	noack();
	stop();
}
uchar  read_adc()
{
	uchar dat;
	start();
	write_byte(0x91);
	ack();
	dat=read_byte();
	noack();
	stop();
	return dat;
}
void channel()
{	
	start();
	write_byte(0x90);
	ack();
	write_byte(0x40);
	noack();
	stop();

}