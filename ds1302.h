#ifndef __DS1302_H__
#define __DS1302_H__
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
 sbit sclk=P3^6;
 sbit io=P3^4;
 sbit rst=P3^5;
 void write_one(uchar dat);
 uchar read_one(uchar add);
 void write_ds1302(uchar add,uchar dat);
 void set_time();
 void read_time();

#endif