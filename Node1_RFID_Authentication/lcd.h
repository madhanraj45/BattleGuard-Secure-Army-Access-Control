#include<LPC21XX.H>


#define LCD  (0xFF << 10)
#define RS   (1 << 18)
#define E    (1 << 19)



void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_STR(unsigned char*);
void LCD_DATA(unsigned char);

/*
void LCD_INIT(){
	IODIR0 |= (0xFF << 10) | (1 << 18) | (1 << 19);
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X38);
}

void LCD_COMMAND(unsigned char d){
	IOCLR0 = LCD;
	IOSET0 = d << 10;
	IOCLR0 = RS;
	IOSET0 = E;
	DELAY(2);
	IOCLR0 = E;
}

void LCD_DATA(unsigned char d){
	IOCLR0 = LCD;
	IOSET0 = d <<10;
	IOSET0 = RS;
	IOSET0 = E;
	DELAY(2);
	IOCLR0 = E;
}
*/

void LCD_INIT()
{
    IODIR0 |= (0xFF << 10) | (1 << 18) | (1 << 19);

    LCD_COMMAND(0x38);
    LCD_COMMAND(0x0C);
    LCD_COMMAND(0x01);
    DELAY(2);
    LCD_COMMAND(0x06);
}

void LCD_COMMAND(unsigned char d)
{
    IOCLR0 = LCD;
    IOSET0 = d << 10;

    IOCLR0 = RS;

    IOSET0 = E;
    DELAY(2);
    IOCLR0 = E;
    DELAY(2);
}

void LCD_DATA(unsigned char d)
{
    IOCLR0 = LCD;
    IOSET0 = d << 10;

    IOSET0 = RS;

    IOSET0 = E;
    DELAY(2);
    IOCLR0 = E;
    DELAY(2);
}

void LCD_STR(unsigned char *p){
	while(*p){
		LCD_DATA(*p++);
	}
}
