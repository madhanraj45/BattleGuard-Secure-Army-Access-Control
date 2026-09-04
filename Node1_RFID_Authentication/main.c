#include<LPC21xx.H>
#include<string.h>
#include "delay.h"
#include "lcd.h"
#include "uart.h"
#include "canstruct.h"
#include "canheader.h"


int main(){
	char store[14];	                           // Declared as standard char array
	unsigned char rx;
	char rfid[] = "9827368AHY62";              //  Expected/authorized RFID number
	CAN2_MSG M1, M2;                           // CAN message structure variables
	LCD_INIT();                                // Initialize LCD
	UART_INIT();                               // Initialize UART for RFID reader
	CAN2_INIT();                               // Initialize CAN-2
	LCD_COMMAND(0x80);                         // Move cursor to beginning of 1st line
	DELAY(1000);                               // Wait 1 second for LCD to stabilize
	LCD_STR("PLACE YOUR TAG..");               // Display message
	DELAY(10000);                               // Keep the message visible for 1 second
	LCD_COMMAND(0x01);						             // Clear the LCD display
	M1.ID = 0X01;                              // SENDING DATA FRAME
	M1.RTR = 0;                                // DATA FRAME
	M1.DLC = 1;
	M1.BYTEA = 0XAA;
	M1.BYTEB = 0;
	M2.ID = 0X02;
	M2.RTR = 0;
	M2.DLC = 1	;
	M2.BYTEA = 0XBB;
	M2.BYTEB = 0;
	
	while(1){
		short int i;
		for(i = 0;i < 12;){
			rx = UART_RX();
			if((rx >= '0' && rx <= '9') || (rx >= 'a' && rx <= 'z') || (rx >= 'A' && rx <= 'Z'))
			{
				store[i++] = rx;
				UART_TX(rx);
			}
		}
		store[12] = '\0';
		
		if (strcmp((const char *)store, (const char *)rfid) == 0) {
			LCD_COMMAND(0X01);
			LCD_STR("ACCESS GRANTED");
			CAN2_TX(M1);
		}
		else{
			LCD_COMMAND(0X01);
			LCD_STR("ACCESS DENIED");
			CAN2_TX(M2);
		}
		
	}
}

