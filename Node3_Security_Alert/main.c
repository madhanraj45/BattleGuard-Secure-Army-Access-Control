#include<LPC21XX.H>
#include "delay.h"
#include "lcdheader.h"
#include "canstruct.h"
#include "canheader.h"

#define LIGHT (1 << 16)

int main(){
	CAN2_MSG RX;
	IODIR0 |= LIGHT;
	
	LCD_INIT();
	CAN2_INIT();
	LCD_COMMAND(0X80);
	
	while(1){
		CAN2_RX(&RX);
		if((RX.ID == 0X02) && (RX.RTR == 0) && ((RX.BYTEA & 0XFF) == 0XBB)){
			LCD_COMMAND(0X01);
			LCD_STR("WARNING...!");
			
			IOSET0 = LIGHT;
			
		}
	}
}

