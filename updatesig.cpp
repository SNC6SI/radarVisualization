#include "stdio.h"
#include "string.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "updatesig.h"

float MapObj01P1X=0.0F;
float MapObj01P1Y=0.0F;
float MapObj01P2X=0.0F;
float MapObj01P2Y=0.0F;
float MapObj02P1X=0.0F;
float MapObj02P1Y=0.0F;
float MapObj02P2X=0.0F;
float MapObj02P2Y=0.0F;
float MapObj03P1X=0.0F;
float MapObj03P1Y=0.0F;
float MapObj03P2X=0.0F;
float MapObj03P2Y=0.0F;
float MapObj04P1X=0.0F;
float MapObj04P1Y=0.0F;
float MapObj04P2X=0.0F;
float MapObj04P2Y=0.0F;
float MapObj05P1X=0.0F;
float MapObj05P1Y=0.0F;
float MapObj05P2X=0.0F;
float MapObj05P2Y=0.0F;
float MapObj06P1X=0.0F;
float MapObj06P1Y=0.0F;
float MapObj06P2X=0.0F;
float MapObj06P2Y=0.0F;
float MapObj07P1X=0.0F;
float MapObj07P1Y=0.0F;
float MapObj07P2X=0.0F;
float MapObj07P2Y=0.0F;
float MapObj08P1X=0.0F;
float MapObj08P1Y=0.0F;
float MapObj08P2X=0.0F;
float MapObj08P2Y=0.0F;
float MapObj09P1X=0.0F;
float MapObj09P1Y=0.0F;
float MapObj09P2X=0.0F;
float MapObj09P2Y=0.0F;
float MapObj10P1X=0.0F;
float MapObj10P1Y=0.0F;
float MapObj10P2X=0.0F;
float MapObj10P2Y=0.0F;
float MapObj11P1X=0.0F;
float MapObj11P1Y=0.0F;
float MapObj11P2X=0.0F;
float MapObj11P2Y=0.0F;
float MapObj12P1X=0.0F;
float MapObj12P1Y=0.0F;
float MapObj12P2X=0.0F;
float MapObj12P2Y=0.0F;
float MapObj13P1X=0.0F;
float MapObj13P1Y=0.0F;
float MapObj13P2X=0.0F;
float MapObj13P2Y=0.0F;
float MapObj14P1X=0.0F;
float MapObj14P1Y=0.0F;
float MapObj14P2X=0.0F;
float MapObj14P2Y=0.0F;
float MapObj15P1X=0.0F;
float MapObj15P1Y=0.0F;
float MapObj15P2X=0.0F;
float MapObj15P2Y=0.0F;
float MapObj16P1X=0.0F;
float MapObj16P1Y=0.0F;
float MapObj16P2X=0.0F;
float MapObj16P2Y=0.0F;
float MapObj17P1X=0.0F;
float MapObj17P1Y=0.0F;
float MapObj17P2X=0.0F;
float MapObj17P2Y=0.0F;
float MapObj18P1X=0.0F;
float MapObj18P1Y=0.0F;
float MapObj18P2X=0.0F;
float MapObj18P2Y=0.0F;
float MapObj19P1X=0.0F;
float MapObj19P1Y=0.0F;
float MapObj19P2X=0.0F;
float MapObj19P2Y=0.0F;
float MapObj20P1X=0.0F;
float MapObj20P1Y=0.0F;
float MapObj20P2X=0.0F;
float MapObj20P2Y=0.0F;
float ApaPscLeftSlot0Obj1X=0.0F;
float ApaPscLeftSlot0Obj1Y=0.0F;
float ApaPscLeftSlot0Obj2X=0.0F;
float ApaPscLeftSlot0Obj2Y=0.0F;
float ApaPscLeftSlot1Obj1X=0.0F;
float ApaPscLeftSlot1Obj1Y=0.0F;
float ApaPscLeftSlot1Obj2X=0.0F;
float ApaPscLeftSlot1Obj2Y=0.0F;
float ApaPscRightSlot0Obj1X=0.0F;
float ApaPscRightSlot0Obj1Y=0.0F;
float ApaPscRightSlot0Obj2X=0.0F;
float ApaPscRightSlot0Obj2Y=0.0F;
float ApaPscRightSlot1Obj1X=0.0F;
float ApaPscRightSlot1Obj1Y=0.0F;
float ApaPscRightSlot1Obj2X=0.0F;
float ApaPscRightSlot1Obj2Y=0.0F;

unsigned char ParkLeftslot0ID = 0.0F;
unsigned char ParkLeftslot1ID = 0.0F;
unsigned char ParkRightslot0ID = 0.0F;
unsigned char ParkRightslot1ID = 0.0F;

float ESP_VehicleSpeed = 0.0F;
float GW_VBU_GearLeverPos = 0.0F;

unsigned int gcanid = 0;
unsigned char ptr[64];

float objx[40];
float objy[40];
float slotx[8];
float sloty[8];
unsigned char slotid[4];


void init_sig(void) {
    memset((void*)objx, 0, 40 * sizeof(float));
    memset((void*)objy, 0, 40 * sizeof(float));
    memset((void*)slotx, 0, 8 * sizeof(float));
    memset((void*)sloty, 0, 8 * sizeof(float));
    memset((void*)slotid, 0, 4);
    GW_VBU_GearLeverPos = 0.0F;
    ESP_VehicleSpeed = 0.0F;
}


void update_sig(void) {
    if (gcanid == 0x172) {
        MapObj01P1X = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj01P1Y = ((((ptr[3]) << 2) + (((ptr[4]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj01P2X = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (4) + (-2044));
        MapObj01P2Y = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj02P1X = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj02P1Y = ((((ptr[11]) << 2) + (((ptr[12]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj02P2X = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (4) + (-2044));
        MapObj02P2Y = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj03P1X = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj03P1Y = ((((ptr[19]) << 2) + (((ptr[20]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj03P2X = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (4) + (-2044));
        MapObj03P2Y = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj04P1X = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj04P1Y = ((((ptr[27]) << 2) + (((ptr[28]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj04P2X = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (4) + (-2044));
        MapObj04P2Y = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6))* (4) + (-2044));

        objx[0] = MapObj01P1X / 10;
        objx[1] = MapObj01P2X / 10;
        objx[2] = MapObj02P1X / 10;
        objx[3] = MapObj02P2X / 10;
        objx[4] = MapObj03P1X / 10;
        objx[5] = MapObj03P2X / 10;
        objx[6] = MapObj04P1X / 10;
        objx[7] = MapObj04P2X / 10;

        objy[0] = MapObj01P1Y / 10;
        objy[1] = MapObj01P2Y / 10;
        objy[2] = MapObj02P1Y / 10;
        objy[3] = MapObj02P2Y / 10;
        objy[4] = MapObj03P1Y / 10;
        objy[5] = MapObj03P2Y / 10;
        objy[6] = MapObj04P1Y / 10;
        objy[7] = MapObj04P2Y / 10;

        //printf("MapObj01P1X=%f\n", MapObj01P1X);
        point4pose(&objx[0], &objy[0], 8);
    }


    if (gcanid == 0x173) {
        MapObj05P1X = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj05P1Y = ((((ptr[3]) << 2) + (((ptr[4]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj05P2X = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (4) + (-2044));
        MapObj05P2Y = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj06P1X = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj06P1Y = ((((ptr[11]) << 2) + (((ptr[12]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj06P2X = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (4) + (-2044));
        MapObj06P2Y = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj07P1X = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj07P1Y = ((((ptr[19]) << 2) + (((ptr[20]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj07P2X = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (4) + (-2044));
        MapObj07P2Y = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj08P1X = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj08P1Y = ((((ptr[27]) << 2) + (((ptr[28]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj08P2X = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (4) + (-2044));
        MapObj08P2Y = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6))* (4) + (-2044));

        objx[8] = MapObj05P1X;
        objx[9] = MapObj05P2X;
        objx[10] = MapObj06P1X;
        objx[11] = MapObj06P2X;
        objx[12] = MapObj07P1X;
        objx[13] = MapObj07P2X;
        objx[14] = MapObj08P1X;
        objx[15] = MapObj08P2X;

        objy[8] = MapObj05P1Y;
        objy[9] = MapObj05P2Y;
        objy[10] = MapObj06P1Y;
        objy[11] = MapObj06P2Y;
        objy[12] = MapObj07P1Y;
        objy[13] = MapObj07P2Y;
        objy[14] = MapObj08P1Y;
        objy[15] = MapObj08P2Y;

        point4pose(&objx[8], &objy[8], 8);
    }


    if (gcanid == 0x174) {
        MapObj09P1X = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj09P1Y = ((((ptr[3]) << 2) + (((ptr[4]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj09P2X = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (4) + (-2044));
        MapObj09P2Y = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj10P1X = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj10P1Y = ((((ptr[11]) << 2) + (((ptr[12]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj10P2X = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (4) + (-2044));
        MapObj10P2Y = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj11P1X = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj11P1Y = ((((ptr[19]) << 2) + (((ptr[20]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj11P2X = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (4) + (-2044));
        MapObj11P2Y = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj12P1X = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj12P1Y = ((((ptr[27]) << 2) + (((ptr[28]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj12P2X = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (4) + (-2044));
        MapObj12P2Y = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6))* (4) + (-2044));

        objx[16] = MapObj09P1X;
        objx[17] = MapObj09P2X;
        objx[18] = MapObj10P1X;
        objx[19] = MapObj10P2X;
        objx[20] = MapObj11P1X;
        objx[21] = MapObj11P2X;
        objx[22] = MapObj12P1X;
        objx[23] = MapObj12P2X;

        objy[16] = MapObj09P1Y;
        objy[17] = MapObj09P2Y;
        objy[18] = MapObj10P1Y;
        objy[19] = MapObj10P2Y;
        objy[20] = MapObj11P1Y;
        objy[21] = MapObj11P2Y;
        objy[22] = MapObj12P1Y;
        objy[23] = MapObj12P2Y;

        point4pose(&objx[16], &objy[16], 8);
    }


    if (gcanid == 0x177) {
        MapObj13P1X = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj13P1Y = ((((ptr[3]) << 2) + (((ptr[4]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj13P2X = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (4) + (-2044));
        MapObj13P2Y = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj14P1X = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj14P1Y = ((((ptr[11]) << 2) + (((ptr[12]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj14P2X = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (4) + (-2044));
        MapObj14P2Y = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj15P1X = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj15P1Y = ((((ptr[19]) << 2) + (((ptr[20]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj15P2X = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (4) + (-2044));
        MapObj15P2Y = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj16P1X = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj16P1Y = ((((ptr[27]) << 2) + (((ptr[28]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj16P2X = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (4) + (-2044));
        MapObj16P2Y = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6))* (4) + (-2044));

        objx[24] = MapObj13P1X;
        objx[25] = MapObj13P2X;
        objx[26] = MapObj14P1X;
        objx[27] = MapObj14P2X;
        objx[28] = MapObj15P1X;
        objx[29] = MapObj15P2X;
        objx[30] = MapObj16P1X;
        objx[31] = MapObj16P2X;

        objy[24] = MapObj13P1Y;
        objy[25] = MapObj13P2Y;
        objy[26] = MapObj14P1Y;
        objy[27] = MapObj14P2Y;
        objy[28] = MapObj15P1Y;
        objy[29] = MapObj15P2Y;
        objy[30] = MapObj16P1Y;
        objy[31] = MapObj16P2Y;

        point4pose(&objx[24], &objy[24], 8);
    }


    if (gcanid == 0x178) {
        MapObj17P1X = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj17P1Y = ((((ptr[3]) << 2) + (((ptr[4]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj17P2X = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (4) + (-2044));
        MapObj17P2Y = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj18P1X = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj18P1Y = ((((ptr[11]) << 2) + (((ptr[12]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj18P2X = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (4) + (-2044));
        MapObj18P2Y = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj19P1X = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj19P1Y = ((((ptr[19]) << 2) + (((ptr[20]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj19P2X = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (4) + (-2044));
        MapObj19P2Y = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj20P1X = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj20P1Y = ((((ptr[27]) << 2) + (((ptr[28]) & (3 << 6)) >> 6))* (4) + (-2044));
        MapObj20P2X = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (4) + (-2044));
        MapObj20P2Y = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6))* (4) + (-2044));

        objx[32] = MapObj17P1X;
        objx[33] = MapObj17P2X;
        objx[34] = MapObj18P1X;
        objx[35] = MapObj18P2X;
        objx[36] = MapObj19P1X;
        objx[37] = MapObj19P2X;
        objx[38] = MapObj20P1X;
        objx[39] = MapObj20P2X;

        objy[32] = MapObj17P1Y;
        objy[33] = MapObj17P2Y;
        objy[34] = MapObj18P1Y;
        objy[35] = MapObj18P2Y;
        objy[36] = MapObj19P1Y;
        objy[37] = MapObj19P2Y;
        objy[37] = MapObj20P1Y;
        objy[38] = MapObj20P2Y;

        point4pose(&objx[32], &objy[32], 8);
    }


    if (gcanid == 0x179) {
        ApaPscLeftSlot0Obj1X = ((((ptr[2]) << 3) + (((ptr[3]) & (7 << 5)) >> 5))* (2) + (-3584));
        ApaPscLeftSlot0Obj1Y = (((((ptr[3]) & 31) << 6) + (((ptr[4]) & (63 << 2)) >> 2))* (2) + (-3584));
        ApaPscLeftSlot0Obj2X = (((((ptr[4]) & 3) << 9) + ((ptr[5]) << 1) + (((ptr[6]) & (1 << 7)) >> 7))* (2) + (-3584));
        ApaPscLeftSlot0Obj2Y = (((((ptr[6]) & 127) << 4) + (((ptr[7]) & (15 << 4)) >> 4))* (2) + (-3584));
        ApaPscLeftSlot1Obj1X = ((((ptr[18]) << 3) + (((ptr[19]) & (7 << 5)) >> 5))* (2) + (-3584));
        ApaPscLeftSlot1Obj1Y = (((((ptr[19]) & 31) << 6) + (((ptr[20]) & (63 << 2)) >> 2))* (2) + (-3584));
        ApaPscLeftSlot1Obj2X = (((((ptr[20]) & 3) << 9) + ((ptr[21]) << 1) + (((ptr[22]) & (1 << 7)) >> 7))* (2) + (-3584));
        ApaPscLeftSlot1Obj2Y = (((((ptr[22]) & 127) << 4) + (((ptr[23]) & (15 << 4)) >> 4))* (2) + (-3584));
        ParkLeftslot0ID = (unsigned char)((ptr[1]) * (1) + (0));
        ParkLeftslot1ID = (unsigned char)((ptr[17]) * (1) + (0));

        slotx[0] = ApaPscLeftSlot0Obj1X;
        slotx[1] = ApaPscLeftSlot0Obj2X;
        slotx[2] = ApaPscLeftSlot1Obj1X;
        slotx[3] = ApaPscLeftSlot1Obj2X;

        sloty[0] = ApaPscLeftSlot0Obj1Y;
        sloty[1] = ApaPscLeftSlot0Obj2Y;
        sloty[2] = ApaPscLeftSlot1Obj1Y;
        sloty[3] = ApaPscLeftSlot1Obj2Y;

        point4pose(&slotx[0], &sloty[0], 4);

        slotid[0] = ParkLeftslot0ID;
        slotid[1] = ParkLeftslot1ID;
    }


    if (gcanid == 0x17A) {
        ApaPscRightSlot0Obj1X = ((((ptr[2]) << 3) + (((ptr[3]) & (7 << 5)) >> 5))* (2) + (-3584));
        ApaPscRightSlot0Obj1Y = (((((ptr[3]) & 31) << 6) + (((ptr[4]) & (63 << 2)) >> 2))* (2) + (-3584));
        ApaPscRightSlot0Obj2X = (((((ptr[4]) & 3) << 9) + ((ptr[5]) << 1) + (((ptr[6]) & (1 << 7)) >> 7))* (2) + (-3584));
        ApaPscRightSlot0Obj2Y = (((((ptr[6]) & 127) << 4) + (((ptr[7]) & (15 << 4)) >> 4))* (2) + (-3584));
        ApaPscRightSlot1Obj1X = ((((ptr[18]) << 3) + (((ptr[19]) & (7 << 5)) >> 5))* (2) + (-3584));
        ApaPscRightSlot1Obj1Y = (((((ptr[19]) & 31) << 6) + (((ptr[20]) & (63 << 2)) >> 2))* (2) + (-3584));
        ApaPscRightSlot1Obj2X = (((((ptr[20]) & 3) << 9) + ((ptr[21]) << 1) + (((ptr[22]) & (1 << 7)) >> 7))* (2) + (-3584));
        ApaPscRightSlot1Obj2Y = (((((ptr[22]) & 127) << 4) + (((ptr[23]) & (15 << 4)) >> 4))* (2) + (-3584));
        ParkRightslot0ID = (unsigned char)((ptr[1]) * (1) + (0));
        ParkRightslot1ID = (unsigned char)((ptr[17]) * (1) + (0));

        slotx[4] = ApaPscRightSlot0Obj1X;
        slotx[5] = ApaPscRightSlot0Obj2X;
        slotx[6] = ApaPscRightSlot1Obj1X;
        slotx[7] = ApaPscRightSlot1Obj2X;

        sloty[4] = ApaPscRightSlot0Obj1Y;
        sloty[5] = ApaPscRightSlot0Obj2Y;
        sloty[6] = ApaPscRightSlot1Obj1Y;
        sloty[7] = ApaPscRightSlot1Obj2Y;

        point4pose(&slotx[4], &sloty[4], 4);

        slotid[2] = ParkRightslot0ID;
        slotid[3] = ParkRightslot1ID;
    }

    if (gcanid == 0x150) {
        ESP_VehicleSpeed = (((((ptr[1]) & 15) << 8) + (ptr[2])) * (0.05625) + (0));
    }

    if (gcanid == 0x152) {
        GW_VBU_GearLeverPos = (((ptr[9]) & 7) * (1) + (0));
    }
}



float X0 = 800.0;
float Y0 = 500.0;
static float C0 = cos(M_PI/2);
static float S0 = sin(M_PI/2);


void point4pose(float* x, float* y, int iter) {
    int i;
    float xx, yy;
    for (i = 0; i < iter; i++) {
        xx = (*(x + i)) * C0 + (-*(y + i)) * S0 + X0;
        yy = (-*(y + i)) * C0 - (*(x + i)) * S0 + Y0;
        *(x + i) = xx;
        *(y + i) = yy;
    }
}