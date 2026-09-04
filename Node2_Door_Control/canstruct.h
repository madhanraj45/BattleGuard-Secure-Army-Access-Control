#ifndef CANSTRUCT_H
#define CANSTRUCT_H

typedef unsigned int u32;
typedef struct {
    u32 ID;
    u32 RTR;
    u32 DLC;
    u32 BYTEA;
    u32 BYTEB;
} CAN2_MSG;

#endif 
