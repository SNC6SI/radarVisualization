#include "stdio.h"
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

unsigned int gcanid = 0;
unsigned char ptr[64];


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
        printf("MapObj01P1X=%f\n", MapObj01P1X);
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
    }
     
}