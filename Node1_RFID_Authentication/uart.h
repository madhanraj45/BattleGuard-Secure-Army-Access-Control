#include<LPC21XX.H>

void UART_INIT(void);
void UART_TX(unsigned char);
unsigned char UART_RX(void);
void UART_STR(unsigned char*);


void UART_INIT(){
	PINSEL0 = 0X5;
	U0LCR   = 0X83;
	U0DLL   = 97;
	U0DLM = 0;
	U0LCR = 0X03;
}
void UART_TX(unsigned char TXBYTE){
	while(((U0LSR >> 5) & 1)==0);
	U0THR = TXBYTE;
}
unsigned char UART_RX(void){
	while((U0LSR&1) == 0);
	return U0RBR;
}
void UART_STR(unsigned char* S){
	while(*S){
		UART_TX(*S++);
	}
}
