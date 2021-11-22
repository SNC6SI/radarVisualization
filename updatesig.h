#ifndef _UPDATESIG_H_
#define _UPDATESIG_H_

#if 1
extern float MapObj01P1X;
extern float MapObj01P1Y;
extern float MapObj01P2X;
extern float MapObj01P2Y;
extern float MapObj02P1X;
extern float MapObj02P1Y;
extern float MapObj02P2X;
extern float MapObj02P2Y;
extern float MapObj03P1X;
extern float MapObj03P1Y;
extern float MapObj03P2X;
extern float MapObj03P2Y;
extern float MapObj04P1X;
extern float MapObj04P1Y;
extern float MapObj04P2X;
extern float MapObj04P2Y;
extern float MapObj05P1X;
extern float MapObj05P1Y;
extern float MapObj05P2X;
extern float MapObj05P2Y;
extern float MapObj06P1X;
extern float MapObj06P1Y;
extern float MapObj06P2X;
extern float MapObj06P2Y;
extern float MapObj07P1X;
extern float MapObj07P1Y;
extern float MapObj07P2X;
extern float MapObj07P2Y;
extern float MapObj08P1X;
extern float MapObj08P1Y;
extern float MapObj08P2X;
extern float MapObj08P2Y;
extern float MapObj09P1X;
extern float MapObj09P1Y;
extern float MapObj09P2X;
extern float MapObj09P2Y;
extern float MapObj10P1X;
extern float MapObj10P1Y;
extern float MapObj10P2X;
extern float MapObj10P2Y;
extern float MapObj11P1X;
extern float MapObj11P1Y;
extern float MapObj11P2X;
extern float MapObj11P2Y;
extern float MapObj12P1X;
extern float MapObj12P1Y;
extern float MapObj12P2X;
extern float MapObj12P2Y;
extern float MapObj13P1X;
extern float MapObj13P1Y;
extern float MapObj13P2X;
extern float MapObj13P2Y;
extern float MapObj14P1X;
extern float MapObj14P1Y;
extern float MapObj14P2X;
extern float MapObj14P2Y;
extern float MapObj15P1X;
extern float MapObj15P1Y;
extern float MapObj15P2X;
extern float MapObj15P2Y;
extern float MapObj16P1X;
extern float MapObj16P1Y;
extern float MapObj16P2X;
extern float MapObj16P2Y;
extern float MapObj17P1X;
extern float MapObj17P1Y;
extern float MapObj17P2X;
extern float MapObj17P2Y;
extern float MapObj18P1X;
extern float MapObj18P1Y;
extern float MapObj18P2X;
extern float MapObj18P2Y;
extern float MapObj19P1X;
extern float MapObj19P1Y;
extern float MapObj19P2X;
extern float MapObj19P2Y;
extern float MapObj20P1X;
extern float MapObj20P1Y;
extern float MapObj20P2X;
extern float MapObj20P2Y;
extern float ApaPscLeftSlot0Obj1X;
extern float ApaPscLeftSlot0Obj1Y;
extern float ApaPscLeftSlot0Obj2X;
extern float ApaPscLeftSlot0Obj2Y;
extern float ApaPscLeftSlot1Obj1X;
extern float ApaPscLeftSlot1Obj1Y;
extern float ApaPscLeftSlot1Obj2X;
extern float ApaPscLeftSlot1Obj2Y;
extern float ApaPscRightSlot0Obj1X;
extern float ApaPscRightSlot0Obj1Y;
extern float ApaPscRightSlot0Obj2X;
extern float ApaPscRightSlot0Obj2Y;
extern float ApaPscRightSlot1Obj1X;
extern float ApaPscRightSlot1Obj1Y;
extern float ApaPscRightSlot1Obj2X;
extern float ApaPscRightSlot1Obj2Y;
#endif

extern unsigned char ParkLeftslot0ID;
extern unsigned char ParkLeftslot1ID;
extern unsigned char ParkRightslot0ID;
extern unsigned char ParkRightslot1ID;

extern float ESP_VehicleSpeed;
extern float GW_VBU_GearLeverPos;

extern unsigned int gcanid;

extern unsigned char ptr[64];

extern float objx[40];
extern float objy[40];
extern float slotx[8];
extern float sloty[8];
extern unsigned char slotid[4];

extern float X0;
extern float Y0;

#define SCALE 0.5

void init_sig(void);
void update_sig(void);
void point4pose(float* x, float* y, int iter);

#endif