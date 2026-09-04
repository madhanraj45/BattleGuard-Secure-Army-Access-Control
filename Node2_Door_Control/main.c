#include<LPC21XX.H>
#include "delay.h"
#include "lcdheader.h"
#include "canstruct.h"
#include "canheader.h"
#define MOTOR1 (1 << 16)
#define MOTOR2 (1 << 17)

int main(){
	CAN2_MSG RX;
	IODIR0 |= MOTOR1 | MOTOR2;
	IOCLR0 = MOTOR1 | MOTOR2;
	
	LCD_INIT();
	CAN2_INIT();
	LCD_COMMAND(0X80);
	
	while(1){
		CAN2_RX(&RX);
		if((RX.ID == 0X01) && (RX.RTR == 0) && ((RX.BYTEA & 0XFF) == 0Xaa)){
			LCD_COMMAND(0X01);
			LCD_STR("MOTOR ON");
			
			IOSET0 = MOTOR1;
			IOCLR0 = MOTOR2;
		}	
	}
}

