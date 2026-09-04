#include<LPC21XX.H>
#include "canstruct.h"

void CAN2_INIT(){
	PINSEL1 |= 0X14000;         // P0.23(RD2) P0.24(TD2)
	VPBDIV = 1;                 // Pclk = 60MHz
	C2MOD = 0X1;                // CAN2 INTO RESET MODE
	AFMR = 0X2;                 //CONFIGUR ACCEPTANCE FILTER
	C2BTR = 0X001C001D;         // SPEED
	C2MOD = 0X0;                // RESET MOTO TO NORMAL MODE;
}

void CAN2_TX(CAN2_MSG M1){
	C2TID1 = M1.ID;              // TRANSMIT ID 1 REGSTER
	C2TFI1 = (M1.DLC << 16);     // CAN2 Transmit Frame Information Register. the DLC field is stored starting at bit 16.
	if(M1.RTR == 0){            // IF DATA FRAME 
		C2TFI1 &= ~(1 << 30);   // RTR = 0
		C2TDA1 = M1.BYTEA;
		C2TDB1 = M1.BYTEB;	
	}else{
		C2TFI1 |= (1 << 30);    // RTR = 1
	}
	C2CMR = (1 << 0) | (1 << 5);
	while((C2GSR & (1 << 3)) == 0);
}

void CAN2_RX(CAN2_MSG *M1){
	while((C2GSR & 0X1) == 0);
		M1->ID = C2RID;
		M1->DLC = (C2RFS >> 16)&0XF;
		M1->RTR = (C2RFS >> 30) & 0X1;
		if(M1 -> RTR == 0){
			M1->BYTEA = C2RDA;
			M1->BYTEB = C2RDB;
		}
	C2CMR = (1 << 2);
}
