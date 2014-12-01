#include "mbed.h"
#define FASTGPIO_BASE (0x2009C000)
void delay(void);
#define FIO0DIR0 (FASTGPIO_BASE)
#define FIO2DIR0 (FASTGPIO_BASE + 0x40)
#define FIO0PIN0 (FASTGPIO_BASE + 0x14)
#define FIO2PIN0 (FASTGPIO_BASE + 0x54)
#define WRITE_REG(_reg_, _val_) (*((volatile unsigned char *)(_reg_)) = (_val_))
#define READ_REG(_reg_) (*((volatile unsigned char *)(_reg_)))
int main()
{
WRITE_REG (FIO0DIR0, 0x00); // set all bits of port 0 byte 0 to input
WRITE_REG (FIO2DIR0, 0xFF); // set port 2 byte 0 to output
while(1)
{
if (READ_REG(FIO0PIN0) & 0x01 ==1)
{ // bit test port 0 pin 0 (mbed pin 9)
WRITE_REG (FIO2PIN0, 0x2);
delay();
WRITE_REG (FIO2PIN0, 0x4);
delay();
WRITE_REG (FIO2PIN0, 0x8);
delay();
WRITE_REG (FIO2PIN0, 0x10);
delay();
WRITE_REG (FIO2PIN0, 0x20);
delay();
}
else
{
WRITE_REG (FIO2PIN0,0x1);
delay();
WRITE_REG (FIO2PIN0,0x0);
delay();
}
}
}
void delay(void)
{
wait (0.4);
}
