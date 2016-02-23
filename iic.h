#ifndef __IIC_H__
#define __IIC_H__
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit scl=P2^1;
sbit sda=P2^0;
void delay();
void start();
void stop();
void ack();
void noack();
void write_byte(uchar dat);
uchar read_byte();
void write_iic(uchar add,uchar byte_add,uchar dat);
uchar  read_adc();
void channel();
void init();
#endif