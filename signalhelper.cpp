#include "stdio.h"
#include "string.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "rv_param.h"
#include "signalhelper.h"
#include "menuhelper.h"
#include "systimehelper.h"

extern unsigned int msgEdlFlag;

static float calcPointDis(float x0, float y0, float x1, float y1);
static void lengthScaling(float* l, float* lo, int iter);

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

unsigned char MapObj01Height = 0U;
unsigned char MapObj02Height = 0U;
unsigned char MapObj03Height = 0U;
unsigned char MapObj04Height = 0U;
unsigned char MapObj05Height = 0U;
unsigned char MapObj06Height = 0U;
unsigned char MapObj07Height = 0U;
unsigned char MapObj08Height = 0U;
unsigned char MapObj09Height = 0U;
unsigned char MapObj10Height = 0U;
unsigned char MapObj11Height = 0U;
unsigned char MapObj12Height = 0U;
unsigned char MapObj13Height = 0U;
unsigned char MapObj14Height = 0U;
unsigned char MapObj15Height = 0U;
unsigned char MapObj16Height = 0U;
unsigned char MapObj17Height = 0U;
unsigned char MapObj18Height = 0U;
unsigned char MapObj19Height = 0U;
unsigned char MapObj20Height = 0U;

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

float ApaPsc_LeftPSL0_Depth = 0.0F;
float ApaPsc_LeftPSL0_Length = 0.0F;
float ApaPsc_LeftPSL1_Depth = 0.0F;
float ApaPsc_LeftPSL1_Length = 0.0F;
float ApaPsc_RightPSL0_Depth = 0.0F;
float ApaPsc_RightPSL0_Length = 0.0F;
float ApaPsc_RightPSL1_Depth = 0.0F;
float ApaPsc_RightPSL1_Length = 0.0F;

float ApaPscLeftSlot0Obj1Alpha = 0.0F;
float ApaPscLeftSlot0Obj2Alpha = 0.0F;
float ApaPscLeftSlot1Obj1Alpha = 0.0F;
float ApaPscLeftSlot1Obj2Alpha = 0.0F;
float ApaPscRightSlot0Obj1Alpha = 0.0F;
float ApaPscRightSlot0Obj2Alpha = 0.0F;
float ApaPscRightSlot1Obj1Alpha = 0.0F;
float ApaPscRightSlot1Obj2Alpha = 0.0F;

unsigned char ParkLeftslot0ID = 0.0F;
unsigned char ParkLeftslot1ID = 0.0F;
unsigned char ParkRightslot0ID = 0.0F;
unsigned char ParkRightslot1ID = 0.0F;

float PAS_FL_Distance = 0.0F;
float PAS_FLM_Distance = 0.0F;
float PAS_FRM_Distance = 0.0F;
float PAS_FR_Distance = 0.0F;
float PAS_RL_Distance = 0.0F;
float PAS_RLM_Distance = 0.0F;
float PAS_RRM_Distance = 0.0F;
float PAS_RR_Distance = 0.0F;
float SDW_FL_1SideDistance = 0.0F;
float SDW_FL_2SideDistance = 0.0F;
float SDW_RL_2SideDistance = 0.0F;
float SDW_RL_1SideDistance = 0.0F;
float SDW_FR_1SideDistance = 0.0F;
float SDW_FR_2SideDistance = 0.0F;
float SDW_RR_2SideDistance = 0.0F;
float SDW_RR_1SideDistance = 0.0F;

float USS_DE1_1=0.0F;
float USS_DE1_2 = 0.0F;
float USS_DE1_3 = 0.0F;
float USS_DE1_4 = 0.0F;
float USS_DE1_5 = 0.0F;
float USS_DE1_6 = 0.0F;
float USS_DE1_7 = 0.0F;
float USS_DE1_8 = 0.0F;
float USS_DE1_9 = 0.0F;
float USS_DE1_10 = 0.0F;
float USS_DE1_11 = 0.0F;
float USS_DE1_12 = 0.0F;
float USS_DE2_1 = 0.0F;
float USS_DE2_2 = 0.0F;
float USS_DE2_3 = 0.0F;
float USS_DE2_4 = 0.0F;
float USS_DE2_5 = 0.0F;
float USS_DE2_6 = 0.0F;
float USS_DE2_7 = 0.0F;
float USS_DE2_8 = 0.0F;
float USS_DE2_9 = 0.0F;
float USS_DE2_10 = 0.0F;
float USS_DE2_11 = 0.0F;
float USS_DE2_12 = 0.0F;
float USS_DE3_1 = 0.0F;
float USS_DE3_2 = 0.0F;
float USS_DE3_3 = 0.0F;
float USS_DE3_4 = 0.0F;
float USS_DE3_5 = 0.0F;
float USS_DE3_6 = 0.0F;
float USS_DE3_7 = 0.0F;
float USS_DE3_8 = 0.0F;
float USS_DE3_9 = 0.0F;
float USS_DE3_10 = 0.0F;
float USS_DE3_11 = 0.0F;
float USS_DE3_12 = 0.0F; 

float USS_CE1_1_right = 0.0F;
float USS_CE1_2_right = 0.0F;
float USS_CE1_3_right = 0.0F;
float USS_CE1_4_right = 0.0F;
float USS_CE1_5_right = 0.0F;
float USS_CE1_7_right = 0.0F;
float USS_CE1_8_right = 0.0F;
float USS_CE1_9_right = 0.0F;
float USS_CE1_10_right = 0.0F;
float USS_CE1_11_right = 0.0F;
float USS_CE1_2_left = 0.0F;
float USS_CE1_3_left = 0.0F;
float USS_CE1_4_left = 0.0F;
float USS_CE1_5_left = 0.0F;
float USS_CE1_6_left = 0.0F;
float USS_CE1_8_left = 0.0F;
float USS_CE1_9_left = 0.0F;
float USS_CE1_10_left = 0.0F;
float USS_CE1_11_left = 0.0F;
float USS_CE1_12_left = 0.0F;

float USS_CE2_1_right = 0.0F;
float USS_CE2_2_right = 0.0F;
float USS_CE2_3_right = 0.0F;
float USS_CE2_4_right = 0.0F;
float USS_CE2_5_right = 0.0F;
float USS_CE2_7_right = 0.0F;
float USS_CE2_8_right = 0.0F;
float USS_CE2_9_right = 0.0F;
float USS_CE2_10_right = 0.0F;
float USS_CE2_11_right = 0.0F;
float USS_CE2_2_left = 0.0F;
float USS_CE2_3_left = 0.0F;
float USS_CE2_4_left = 0.0F;
float USS_CE2_5_left = 0.0F;
float USS_CE2_6_left = 0.0F;
float USS_CE2_8_left = 0.0F;
float USS_CE2_9_left = 0.0F;
float USS_CE2_10_left = 0.0F;
float USS_CE2_11_left = 0.0F;
float USS_CE2_12_left = 0.0F;

float USS_CE3_1_right = 0.0F;
float USS_CE3_2_right = 0.0F;
float USS_CE3_3_right = 0.0F;
float USS_CE3_4_right = 0.0F;
float USS_CE3_5_right = 0.0F;
float USS_CE3_7_right = 0.0F;
float USS_CE3_8_right = 0.0F;
float USS_CE3_9_right = 0.0F;
float USS_CE3_10_right = 0.0F;
float USS_CE3_11_right = 0.0F;
float USS_CE3_2_left = 0.0F;
float USS_CE3_3_left = 0.0F;
float USS_CE3_4_left = 0.0F;
float USS_CE3_5_left = 0.0F;
float USS_CE3_6_left = 0.0F;
float USS_CE3_8_left = 0.0F;
float USS_CE3_9_left = 0.0F;
float USS_CE3_10_left = 0.0F;
float USS_CE3_11_left = 0.0F;
float USS_CE3_12_left = 0.0F;


float ESP_VehicleSpeed = 0.0F;
unsigned char GW_VBU_GearLeverPos = 0.0F;

unsigned int gcanid = 0;
unsigned char ptr[64];
unsigned __int64 ts;

float objx_rx[40];
float objy_rx[40];
float slotx_rx[8];
float sloty_rx[8];
float slotxrec_rx[16];
float slotyrec_rx[16];
float de_1_rx[12];
float de_2_rx[12];
float de_3_rx[12];
float ce_1_right_rx[10];
float ce_1_left_rx[10];
float ce_2_right_rx[10];
float ce_2_left_rx[10];
float ce_3_right_rx[10];
float ce_3_left_rx[10];

float objx[40];
float objy[40];
float slotx[8];
float sloty[8];
float slotxrec[16];
float slotyrec[16];
float de_1[12];
float de_2[12];
float de_3[12];

unsigned char objH[20];
unsigned char slotid[4];
float slot_Depth[4];
float slot_Length[4];
float slot_theta[4];

float gScale;

float de_cc_x_raw[12];
float de_cc_y_raw[12];
float de_cc_x[12];
float de_cc_y[12];

float ps_x_raw[28];
float ps_y_raw[28];
float ps_x[28];
float ps_y[28];
float ps_r_raw;
float ps_r;
float ps_dis[16];
unsigned char ps_color_idx[16];
float ps_angle_anchor[4];
float ps_angle_start[4];
float ps_angle_end[4];

static const float halt_fov_short = 25;
static const float halt_fov_long = 20;

const float de_angle_anchor[12] = { 180, -90, -90, -90, -90, 0,
                                      0,  90,  90,  90,  90, 180};
const float de_angle_start[12]  = { -halt_fov_long, -halt_fov_short, -halt_fov_short, -halt_fov_short, -halt_fov_short, -halt_fov_long,
                                    -halt_fov_long, -halt_fov_short, -halt_fov_short, -halt_fov_short, -halt_fov_short, -halt_fov_long };
const float de_angle_end[12]    = {  halt_fov_long,  halt_fov_short,  halt_fov_short,  halt_fov_short,  halt_fov_short,  halt_fov_long,
                                     halt_fov_long,  halt_fov_short,  halt_fov_short,  halt_fov_short,  halt_fov_short,  halt_fov_long };

static unsigned __int64 ts_anchor_0x121;
static unsigned __int64 ts_anchor_0x171;
static unsigned __int64 ts_anchor_0x150;
static unsigned __int64 ts_anchor_0x172;
static unsigned __int64 ts_check;

unsigned int timeout_0x121;
unsigned int timeout_0x171;
unsigned int timeout_0x150;
unsigned int timeout_0x172;


void init_sig(void) {
    gScale = DEFAULTSCALE;
    memset((void*)objx_rx, 0, sizeof(objx_rx));
    memset((void*)objy_rx, 0, sizeof(objy_rx));
    memset((void*)slotx_rx, 0, sizeof(slotx_rx));
    memset((void*)sloty_rx, 0, sizeof(sloty_rx));
    memset((void*)objx, 0, sizeof(objx));
    memset((void*)objy, 0, sizeof(objy));
    memset((void*)slotx, 0, sizeof(slotx));
    memset((void*)sloty, 0, sizeof(sloty));
    memset((void*)slotid, 0, 4);
    memset((void*)slot_Depth, 0, sizeof(slot_Depth));
    memset((void*)slot_Length, 0, sizeof(slot_Length));
    memset((void*)slot_theta, 0, sizeof(slot_theta));
    memset((void*)de_1_rx, 0, sizeof(de_1_rx));
    memset((void*)de_2_rx, 0, sizeof(de_2_rx));
    memset((void*)de_3_rx, 0, sizeof(de_3_rx));
    memset((void*)de_1, 0, sizeof(de_1));
    memset((void*)de_2, 0, sizeof(de_2));
    memset((void*)de_3, 0, sizeof(de_3));
    memset((void*)de_cc_x, 0, sizeof(de_cc_x));
    memset((void*)de_cc_y, 0, sizeof(de_cc_y));
    GW_VBU_GearLeverPos = 0U;
    ESP_VehicleSpeed = 0.0F;
    ts_anchor_0x121 = 0;
    ts_anchor_0x171 = 0;
    ts_anchor_0x150 = 0;
    ts_anchor_0x172 = 0;
    ts_check = 0;
    timeout_0x121 = timeout_0x171 = timeout_0x150 = timeout_0x172 = 0;
}


static void update_sig_internal(void) {
    point4pose(&objx_rx[0], &objy_rx[0], &objx[0], &objy[0], sizeof(objy_rx)/ sizeof(objy_rx[0]));
    point4pose(&slotx_rx[0], &sloty_rx[0], &slotx[0], &sloty[0], sizeof(slotx_rx) / sizeof(slotx_rx[0]));
    point4pose(&slotxrec_rx[0], &slotyrec_rx[0], &slotxrec[0], &slotyrec[0], sizeof(slotxrec_rx) / sizeof(slotxrec_rx[0]));
}


static void update_de_internal(void) {
    de_cc_x_raw[0] = FO_ - 1.0 / 4.0 * RO_;
    de_cc_x_raw[1] = FO_;
    de_cc_x_raw[2] = FO_;
    de_cc_x_raw[3] = FO_;
    de_cc_x_raw[4] = FO_;
    de_cc_x_raw[5] = FO_ - 1.0 / 4.0 * RO_;
    de_cc_x_raw[6] = -3.0 / 4.0 * RO_;
    de_cc_x_raw[7] = -RO_;
    de_cc_x_raw[8] = -RO_;
    de_cc_x_raw[9] = -RO_;
    de_cc_x_raw[10] = -RO_;
    de_cc_x_raw[11] = -3.0 / 4.0 * RO_;

    de_cc_y_raw[0] =  HW_;
    de_cc_y_raw[1] =  3.0 / 4.0 * HW_;
    de_cc_y_raw[2] =  1.0 / 4.0 * HW_;
    de_cc_y_raw[3] = -1.0 / 4.0 * HW_;
    de_cc_y_raw[4] = -3.0 / 4.0 * HW_;
    de_cc_y_raw[5] = -HW_;
    de_cc_y_raw[6] = -HW_;
    de_cc_y_raw[7] = -3.0 / 4.0 * HW_;
    de_cc_y_raw[8] = -1.0 / 4.0 * HW_;
    de_cc_y_raw[9] =  1.0 / 4.0 * HW_;
    de_cc_y_raw[10] = 3.0 / 4.0 * HW_;
    de_cc_y_raw[11] = HW_;

    point4pose(&de_cc_x_raw[0], &de_cc_y_raw[0], &de_cc_x[0], &de_cc_y[0], 12);

    lengthScaling(&de_1_rx[0], &de_1[0], sizeof(de_1_rx) / sizeof(de_1_rx[0]));
    lengthScaling(&de_2_rx[0], &de_2[0], sizeof(de_2_rx) / sizeof(de_2_rx[0]));
    lengthScaling(&de_3_rx[0], &de_3[0], sizeof(de_3_rx) / sizeof(de_3_rx[0]));
}


static void update_pas_sdw_internal(void) {
    ps_x_raw[0] = FO_ - GAP_ / 2;
    ps_x_raw[1] = FO_ - (FO_ + RO_) / 4.0 + GAP_ / 2;
    ps_x_raw[2] = FO_ - (FO_ + RO_) / 4.0 - GAP_ / 2;
    ps_x_raw[3] = FO_ - (FO_ + RO_) / 2.0 + GAP_ / 2;
    ps_x_raw[4] = FO_ - (FO_ + RO_) / 2.0 - GAP_ / 2;
    ps_x_raw[5] = FO_ - (FO_ + RO_) / 4.0 * 3.0 + GAP_ / 2;
    ps_x_raw[6] = FO_ - (FO_ + RO_) / 4.0 * 3.0 - GAP_ / 2;
    ps_x_raw[7] = FO_ - (FO_ + RO_) + GAP_ / 2;

    ps_x_raw[8] = FO_ - GAP_ / 2;
    ps_x_raw[9] = FO_ - (FO_ + RO_) / 4.0 + GAP_ / 2;
    ps_x_raw[10] = FO_ - (FO_ + RO_) / 4.0 - GAP_ / 2;
    ps_x_raw[11] = FO_ - (FO_ + RO_) / 2.0 + GAP_ / 2;
    ps_x_raw[12] = FO_ - (FO_ + RO_) / 2.0 - GAP_ / 2;
    ps_x_raw[13] = FO_ - (FO_ + RO_) / 4.0 * 3.0 + GAP_ / 2;
    ps_x_raw[14] = FO_ - (FO_ + RO_) / 4.0 * 3.0 - GAP_ / 2;
    ps_x_raw[15] = FO_ - (FO_ + RO_) + GAP_ / 2;

    ps_x_raw[16] = (FO_ + SP_);
    ps_x_raw[17] = (FO_ + SP_);
    ps_x_raw[18] = (FO_ + SP_);
    ps_x_raw[19] = (FO_ + SP_);

    ps_x_raw[20] = -(RO_ + SP_);
    ps_x_raw[21] = -(RO_ + SP_);
    ps_x_raw[22] = -(RO_ + SP_);
    ps_x_raw[23] = -(RO_ + SP_);

    ps_x_raw[24] = (FO_ - HW_);
    ps_x_raw[25] = (FO_ - HW_);
    ps_x_raw[26] = (-RO_ + HW_);
    ps_x_raw[27] = (-RO_ + HW_);

    ps_y_raw[0] = (HW_ + SP_);
    ps_y_raw[1] = (HW_ + SP_);
    ps_y_raw[2] = (HW_ + SP_);
    ps_y_raw[3] = (HW_ + SP_);
    ps_y_raw[4] = (HW_ + SP_);
    ps_y_raw[5] = (HW_ + SP_);
    ps_y_raw[6] = (HW_ + SP_);
    ps_y_raw[7] = (HW_ + SP_);

    ps_y_raw[8] = -(HW_ + SP_);
    ps_y_raw[9] = -(HW_ + SP_);
    ps_y_raw[10] = -(HW_ + SP_);
    ps_y_raw[11] = -(HW_ + SP_);
    ps_y_raw[12] = -(HW_ + SP_);
    ps_y_raw[13] = -(HW_ + SP_);
    ps_y_raw[14] = -(HW_ + SP_);
    ps_y_raw[15] = -(HW_ + SP_);

    ps_y_raw[16] = (HW_ - GAP_ / 2);
    ps_y_raw[17] = (GAP_ / 2);
    ps_y_raw[18] = -(GAP_ / 2);
    ps_y_raw[19] = -(HW_ - GAP_ / 2);

    ps_y_raw[20] = (HW_ - GAP_ / 2);
    ps_y_raw[21] = (GAP_ / 2);
    ps_y_raw[22] = -(GAP_ / 2);
    ps_y_raw[23] = -(HW_ - GAP_ / 2);

    ps_y_raw[24] = 0.0;
    ps_y_raw[25] = 0.0;
    ps_y_raw[26] = 0.0;
    ps_y_raw[27] = 0.0;

    ps_angle_anchor[0] = 180;
    ps_angle_anchor[1] = -90;
    ps_angle_anchor[2] = 90;
    ps_angle_anchor[3] = 0;

    ps_angle_start[0] = AG_;
    ps_angle_start[1] = AG_;
    ps_angle_start[2] = AG_;
    ps_angle_start[3] = AG_;

    ps_angle_end[0] = 90 - AG_;
    ps_angle_end[1] = 90 - AG_;
    ps_angle_end[2] = 90 - AG_;
    ps_angle_end[3] = 90 - AG_;

    point4pose(&ps_x_raw[0], &ps_y_raw[0], &ps_x[0], &ps_y[0], 28);
    ps_r_raw = (HW_ + GAP_);
    lengthScaling(&ps_r_raw, &ps_r, 1);
}


void check_timeout(void) {
    if (selected_mode == 1) {
        GetLocalTime(&local_time);
        SystemTimeToFileTime(&local_time, &local_time_TM.ft);
        ts_check = local_time_TM.li.QuadPart / 10000;
    }
    else if (selected_mode == 2) {
        ts_check = ts / 1000000;
    }

    if (ts_check - ts_anchor_0x121 > TM_0x121)
        timeout_0x121 = 1;
    if (ts_check - ts_anchor_0x171 > TM_0x171)
        timeout_0x171 = 1;
    if (ts_check - ts_anchor_0x150 > TM_0x150)
        timeout_0x150 = 1;
    if (ts_check - ts_anchor_0x172 > TM_0x172)
        timeout_0x172 = 1;
}


void update_sig(void) {
    if (gcanid == 0x172 && msgEdlFlag == 1) {
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
        MapObj01Height = ((((ptr[7]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj02Height = ((((ptr[15]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj03Height = ((((ptr[23]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj04Height = ((((ptr[31]) & (3 << 4)) >> 4) * (1) + (0));

        objx_rx[0] = MapObj01P1X;
        objx_rx[1] = MapObj01P2X;
        objx_rx[2] = MapObj02P1X;
        objx_rx[3] = MapObj02P2X;
        objx_rx[4] = MapObj03P1X;
        objx_rx[5] = MapObj03P2X;
        objx_rx[6] = MapObj04P1X;
        objx_rx[7] = MapObj04P2X;

        objy_rx[0] = MapObj01P1Y;
        objy_rx[1] = MapObj01P2Y;
        objy_rx[2] = MapObj02P1Y;
        objy_rx[3] = MapObj02P2Y;
        objy_rx[4] = MapObj03P1Y;
        objy_rx[5] = MapObj03P2Y;
        objy_rx[6] = MapObj04P1Y;
        objy_rx[7] = MapObj04P2Y;

        objH[0] = MapObj01Height;
        objH[1] = MapObj02Height;
        objH[2] = MapObj03Height;
        objH[3] = MapObj04Height;

        if (selected_mode == 1) {
            GetLocalTime(&local_time);
            SystemTimeToFileTime(&local_time, &local_time_TM.ft);
            ts_anchor_0x172 = local_time_TM.li.QuadPart / 10000;
            timeout_0x172 = 0;
        }
        else if (selected_mode == 2) {
            ts_anchor_0x172 = ts / 1000000;
            timeout_0x172 = 0;
        }
    }


    if (gcanid == 0x173 && msgEdlFlag == 1) {
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
        MapObj05Height = ((((ptr[7]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj06Height = ((((ptr[15]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj07Height = ((((ptr[23]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj08Height = ((((ptr[31]) & (3 << 4)) >> 4) * (1) + (0));

        objx_rx[8] = MapObj05P1X;
        objx_rx[9] = MapObj05P2X;
        objx_rx[10] = MapObj06P1X;
        objx_rx[11] = MapObj06P2X;
        objx_rx[12] = MapObj07P1X;
        objx_rx[13] = MapObj07P2X;
        objx_rx[14] = MapObj08P1X;
        objx_rx[15] = MapObj08P2X;

        objy_rx[8] = MapObj05P1Y;
        objy_rx[9] = MapObj05P2Y;
        objy_rx[10] = MapObj06P1Y;
        objy_rx[11] = MapObj06P2Y;
        objy_rx[12] = MapObj07P1Y;
        objy_rx[13] = MapObj07P2Y;
        objy_rx[14] = MapObj08P1Y;
        objy_rx[15] = MapObj08P2Y;

        objH[4] = MapObj05Height;
        objH[5] = MapObj06Height;
        objH[6] = MapObj07Height;
        objH[7] = MapObj08Height;
    }


    if (gcanid == 0x174 && msgEdlFlag == 1) {
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
        MapObj09Height = ((((ptr[7]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj10Height = ((((ptr[15]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj11Height = ((((ptr[23]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj12Height = ((((ptr[31]) & (3 << 4)) >> 4) * (1) + (0));

        objx_rx[16] = MapObj09P1X;
        objx_rx[17] = MapObj09P2X;
        objx_rx[18] = MapObj10P1X;
        objx_rx[19] = MapObj10P2X;
        objx_rx[20] = MapObj11P1X;
        objx_rx[21] = MapObj11P2X;
        objx_rx[22] = MapObj12P1X;
        objx_rx[23] = MapObj12P2X;

        objy_rx[16] = MapObj09P1Y;
        objy_rx[17] = MapObj09P2Y;
        objy_rx[18] = MapObj10P1Y;
        objy_rx[19] = MapObj10P2Y;
        objy_rx[20] = MapObj11P1Y;
        objy_rx[21] = MapObj11P2Y;
        objy_rx[22] = MapObj12P1Y;
        objy_rx[23] = MapObj12P2Y;

        objH[8]  = MapObj09Height;
        objH[9]  = MapObj10Height;
        objH[10] = MapObj11Height;
        objH[11] = MapObj12Height;
    }


    if (gcanid == 0x177 && msgEdlFlag == 1) {
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
        MapObj13Height = ((((ptr[7]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj14Height = ((((ptr[15]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj15Height = ((((ptr[23]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj16Height = ((((ptr[31]) & (3 << 4)) >> 4) * (1) + (0));

        objx_rx[24] = MapObj13P1X;
        objx_rx[25] = MapObj13P2X;
        objx_rx[26] = MapObj14P1X;
        objx_rx[27] = MapObj14P2X;
        objx_rx[28] = MapObj15P1X;
        objx_rx[29] = MapObj15P2X;
        objx_rx[30] = MapObj16P1X;
        objx_rx[31] = MapObj16P2X;

        objy_rx[24] = MapObj13P1Y;
        objy_rx[25] = MapObj13P2Y;
        objy_rx[26] = MapObj14P1Y;
        objy_rx[27] = MapObj14P2Y;
        objy_rx[28] = MapObj15P1Y;
        objy_rx[29] = MapObj15P2Y;
        objy_rx[30] = MapObj16P1Y;
        objy_rx[31] = MapObj16P2Y;

        objH[12] = MapObj13Height;
        objH[13] = MapObj14Height;
        objH[14] = MapObj15Height;
        objH[15] = MapObj16Height;
    }


    if (gcanid == 0x178 && msgEdlFlag == 1) {
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
        MapObj17Height = ((((ptr[7]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj18Height = ((((ptr[15]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj19Height = ((((ptr[23]) & (3 << 4)) >> 4) * (1) + (0));
        MapObj20Height = ((((ptr[31]) & (3 << 4)) >> 4) * (1) + (0));

        objx_rx[32] = MapObj17P1X;
        objx_rx[33] = MapObj17P2X;
        objx_rx[34] = MapObj18P1X;
        objx_rx[35] = MapObj18P2X;
        objx_rx[36] = MapObj19P1X;
        objx_rx[37] = MapObj19P2X;
        objx_rx[38] = MapObj20P1X;
        objx_rx[39] = MapObj20P2X;

        objy_rx[32] = MapObj17P1Y;
        objy_rx[33] = MapObj17P2Y;
        objy_rx[34] = MapObj18P1Y;
        objy_rx[35] = MapObj18P2Y;
        objy_rx[36] = MapObj19P1Y;
        objy_rx[37] = MapObj19P2Y;
        objy_rx[38] = MapObj20P1Y;
        objy_rx[39] = MapObj20P2Y;

        objH[16] = MapObj17Height;
        objH[17] = MapObj18Height;
        objH[18] = MapObj19Height;
        objH[19] = MapObj20Height;
    }


    if (gcanid == 0x179 && msgEdlFlag == 1) {
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
        ApaPscLeftSlot0Obj1Alpha = ((((ptr[9]) & (127 << 1)) >> 1) * (2) + (-128));
        ApaPscLeftSlot0Obj2Alpha = ((((ptr[10]) & (127 << 1)) >> 1) * (2) + (-128));
        ApaPscLeftSlot1Obj1Alpha = ((((ptr[25]) & (127 << 1)) >> 1) * (2) + (-128));
        ApaPscLeftSlot1Obj2Alpha = ((((ptr[26]) & (127 << 1)) >> 1) * (2) + (-128));

        ApaPsc_LeftPSL0_Depth = ((ptr[11]) * (4) + (0));
        ApaPsc_LeftPSL0_Length = ((((ptr[12]) << 1) + (((ptr[13]) & (1 << 7)) >> 7)) * (4) + (0));
        ApaPsc_LeftPSL1_Depth = ((ptr[27]) * (4) + (0));
        ApaPsc_LeftPSL1_Length = ((((ptr[28]) << 1) + (((ptr[29]) & (1 << 7)) >> 7)) * (4) + (0));

        slotx_rx[0] = ApaPscLeftSlot0Obj1X;
        slotx_rx[1] = ApaPscLeftSlot0Obj2X;
        slotx_rx[2] = ApaPscLeftSlot1Obj1X;
        slotx_rx[3] = ApaPscLeftSlot1Obj2X;

        sloty_rx[0] = ApaPscLeftSlot0Obj1Y;
        sloty_rx[1] = ApaPscLeftSlot0Obj2Y;
        sloty_rx[2] = ApaPscLeftSlot1Obj1Y;
        sloty_rx[3] = ApaPscLeftSlot1Obj2Y;

        slot_Depth[0] = ApaPsc_LeftPSL0_Depth;
        slot_Length[0] = ApaPsc_LeftPSL0_Length;
        slot_Depth[1] = ApaPsc_LeftPSL1_Length;
        slot_Length[1] = ApaPsc_LeftPSL1_Length;

        slotid[0] = ParkLeftslot0ID;
        slotid[1] = ParkLeftslot1ID;

        if (slotx_rx[0] > slotx_rx[1]) {
            slotxrec_rx[0] = slotx_rx[0];
            slotyrec_rx[0] = sloty_rx[0];
            slotxrec_rx[1] = slotx_rx[1];
            slotyrec_rx[1] = sloty_rx[1];
        }
        else {
            slotxrec_rx[0] = slotx_rx[1];
            slotyrec_rx[0] = sloty_rx[1];
            slotxrec_rx[1] = slotx_rx[0];
            slotyrec_rx[1] = sloty_rx[0];
        }
        slot_theta[0] = -asinf((slotyrec_rx[0] - slotyrec_rx[1]) / calcPointDis(slotxrec_rx[0], slotyrec_rx[0], slotxrec_rx[1], slotyrec_rx[1]));
        slotxrec_rx[2] = slotxrec_rx[1] + slot_Depth[0] * sinf(slot_theta[0]);
        slotyrec_rx[2] = slotyrec_rx[1] + slot_Depth[0] * cosf(slot_theta[0]);
        slotxrec_rx[3] = slotxrec_rx[0] + slot_Depth[0] * sinf(slot_theta[0]);
        slotyrec_rx[3] = slotyrec_rx[0] + slot_Depth[0] * cosf(slot_theta[0]);


        if (slotx_rx[2] > slotx_rx[3]) {
            slotxrec_rx[4] = slotx_rx[2];
            slotyrec_rx[4] = sloty_rx[2];
            slotxrec_rx[5] = slotx_rx[3];
            slotyrec_rx[5] = sloty_rx[3];
        }
        else {
            slotxrec_rx[4] = slotx_rx[3];
            slotyrec_rx[4] = sloty_rx[3];
            slotxrec_rx[5] = slotx_rx[2];
            slotyrec_rx[5] = sloty_rx[2];
        }
        slot_theta[1] = -asinf((slotyrec_rx[4] - slotyrec_rx[5]) / calcPointDis(slotxrec_rx[4], slotyrec_rx[4], slotxrec_rx[5], slotyrec_rx[5]));
        slotxrec_rx[6] = slotxrec_rx[5] + slot_Depth[1] * sinf(slot_theta[1]);
        slotyrec_rx[6] = slotyrec_rx[5] + slot_Depth[1] * cosf(slot_theta[1]);
        slotxrec_rx[7] = slotxrec_rx[4] + slot_Depth[1] * sinf(slot_theta[1]);
        slotyrec_rx[7] = slotyrec_rx[4] + slot_Depth[1] * cosf(slot_theta[1]);
    }


    if (gcanid == 0x17A && msgEdlFlag == 1) {
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
        ApaPscRightSlot0Obj1Alpha = ((((ptr[9]) & (127 << 1)) >> 1) * (2) + (-128));
        ApaPscRightSlot0Obj2Alpha = ((((ptr[10]) & (127 << 1)) >> 1) * (2) + (-128));
        ApaPscRightSlot1Obj1Alpha = ((((ptr[25]) & (127 << 1)) >> 1) * (2) + (-128));
        ApaPscRightSlot1Obj2Alpha = ((((ptr[26]) & (127 << 1)) >> 1) * (2) + (-128));

        ApaPsc_RightPSL0_Depth = ((ptr[11]) * (4) + (0));
        ApaPsc_RightPSL0_Length = ((((ptr[12]) << 1) + (((ptr[13]) & (1 << 7)) >> 7)) * (4) + (0));
        ApaPsc_RightPSL1_Depth = ((ptr[27]) * (4) + (0));
        ApaPsc_RightPSL1_Length = ((((ptr[28]) << 1) + (((ptr[29]) & (1 << 7)) >> 7)) * (4) + (0));

        slotx_rx[4] = ApaPscRightSlot0Obj1X;
        slotx_rx[5] = ApaPscRightSlot0Obj2X;
        slotx_rx[6] = ApaPscRightSlot1Obj1X;
        slotx_rx[7] = ApaPscRightSlot1Obj2X;

        sloty_rx[4] = ApaPscRightSlot0Obj1Y;
        sloty_rx[5] = ApaPscRightSlot0Obj2Y;
        sloty_rx[6] = ApaPscRightSlot1Obj1Y;
        sloty_rx[7] = ApaPscRightSlot1Obj2Y;

        slot_Depth[2] = ApaPsc_RightPSL0_Depth;
        slot_Length[2] = ApaPsc_RightPSL0_Length;
        slot_Depth[3] = ApaPsc_RightPSL1_Depth;
        slot_Length[3] = ApaPsc_RightPSL1_Length;

        slotid[2] = ParkRightslot0ID;
        slotid[3] = ParkRightslot1ID;

        if (slotx_rx[4] > slotx_rx[5]) {
            slotxrec_rx[8] = slotx_rx[4];
            slotyrec_rx[8] = sloty_rx[4];
            slotxrec_rx[9] = slotx_rx[5];
            slotyrec_rx[9] = sloty_rx[5];
        }
        else {
            slotxrec_rx[8] = slotx_rx[5];
            slotyrec_rx[8] = sloty_rx[5];
            slotxrec_rx[9] = slotx_rx[4];
            slotyrec_rx[9] = sloty_rx[4];
        }
        slot_theta[2] = asinf((slotyrec_rx[8] - slotyrec_rx[9]) / calcPointDis(slotxrec_rx[8], slotyrec_rx[8], slotxrec_rx[9], slotyrec_rx[9]));
        slotxrec_rx[10] = slotxrec_rx[9] + slot_Depth[2] * sinf(slot_theta[2]);
        slotyrec_rx[10] = slotyrec_rx[9] - slot_Depth[2] * cosf(slot_theta[2]);
        slotxrec_rx[11] = slotxrec_rx[8] + slot_Depth[2] * sinf(slot_theta[2]);
        slotyrec_rx[11] = slotyrec_rx[8] - slot_Depth[2] * cosf(slot_theta[2]);

        if (slotx_rx[6] > slotx_rx[7]) {
            slotxrec_rx[12] = slotx_rx[6];
            slotyrec_rx[12] = sloty_rx[6];
            slotxrec_rx[13] = slotx_rx[7];
            slotyrec_rx[13] = sloty_rx[7];
        }
        else {
            slotxrec_rx[12] = slotx_rx[7];
            slotyrec_rx[12] = sloty_rx[7];
            slotxrec_rx[13] = slotx_rx[6];
            slotyrec_rx[13] = sloty_rx[6];
        }
        slot_theta[3] = asinf((slotyrec_rx[12] - slotyrec_rx[13]) / calcPointDis(slotxrec_rx[12], slotyrec_rx[12], slotxrec_rx[13], slotyrec_rx[13]));
        slotxrec_rx[14] = slotxrec_rx[13] + slot_Depth[3] * sinf(slot_theta[3]);
        slotyrec_rx[14] = slotyrec_rx[13] - slot_Depth[3] * cosf(slot_theta[3]);
        slotxrec_rx[15] = slotxrec_rx[12] + slot_Depth[3] * sinf(slot_theta[3]);
        slotyrec_rx[15] = slotyrec_rx[12] - slot_Depth[3] * cosf(slot_theta[3]);
    }

    if (gcanid == 0x17B && msgEdlFlag == 1) {
        USS_DE1_1 = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE1_2 = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE1_3 = (((((ptr[2]) & 3) << 8) + (ptr[3])) * (1) + (0));
        USS_DE1_4 = ((((ptr[4]) << 2) + (((ptr[5]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE1_5 = (((((ptr[5]) & 3) << 8) + (ptr[6])) * (1) + (0));
        USS_DE1_6 = (((((ptr[18]) & 3) << 8) + (ptr[19])) * (1) + (0));
        USS_DE1_7 = ((((ptr[20]) << 2) + (((ptr[21]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE1_8 = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE1_9 = (((((ptr[10]) & 3) << 8) + (ptr[11])) * (1) + (0));
        USS_DE1_10 = ((((ptr[12]) << 2) + (((ptr[13]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE1_11 = (((((ptr[13]) & 3) << 8) + (ptr[14])) * (1) + (0));
        USS_DE1_12 = (((((ptr[21]) & 3) << 8) + (ptr[22])) * (1) + (0));
        de_1_rx[0]  = USS_DE1_1;
        de_1_rx[1]  = USS_DE1_2;
        de_1_rx[2]  = USS_DE1_3;
        de_1_rx[3]  = USS_DE1_4;
        de_1_rx[4]  = USS_DE1_5;
        de_1_rx[5]  = USS_DE1_6;
        de_1_rx[6]  = USS_DE1_7;
        de_1_rx[7]  = USS_DE1_8;
        de_1_rx[8]  = USS_DE1_9;
        de_1_rx[9]  = USS_DE1_10;
        de_1_rx[10] = USS_DE1_11;
        de_1_rx[11] = USS_DE1_12;
    }

    if (gcanid == 0x17D && msgEdlFlag == 1) {
        USS_DE2_1 = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE2_2 = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE2_3 = (((((ptr[2]) & 3) << 8) + (ptr[3])) * (1) + (0));
        USS_DE2_4 = ((((ptr[4]) << 2) + (((ptr[5]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE2_5 = (((((ptr[5]) & 3) << 8) + (ptr[6])) * (1) + (0));
        USS_DE2_6 = (((((ptr[18]) & 3) << 8) + (ptr[19])) * (1) + (0));
        USS_DE2_7 = ((((ptr[20]) << 2) + (((ptr[21]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE2_8 = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE2_9 = (((((ptr[10]) & 3) << 8) + (ptr[11])) * (1) + (0));
        USS_DE2_10 = ((((ptr[12]) << 2) + (((ptr[13]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE2_11 = (((((ptr[13]) & 3) << 8) + (ptr[14])) * (1) + (0));
        USS_DE2_12 = (((((ptr[21]) & 3) << 8) + (ptr[22])) * (1) + (0));
        de_2_rx[0]  = USS_DE2_1;
        de_2_rx[1]  = USS_DE2_2;
        de_2_rx[2]  = USS_DE2_3;
        de_2_rx[3]  = USS_DE2_4;
        de_2_rx[4]  = USS_DE2_5;
        de_2_rx[5]  = USS_DE2_6;
        de_2_rx[6]  = USS_DE2_7;
        de_2_rx[7]  = USS_DE2_8;
        de_2_rx[8]  = USS_DE2_9;
        de_2_rx[9]  = USS_DE2_10;
        de_2_rx[10] = USS_DE2_11;
        de_2_rx[11] = USS_DE2_12;
    }

    if (gcanid == 0x181 && msgEdlFlag == 1) {
        USS_DE3_1 = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE3_2 = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE3_3 = (((((ptr[2]) & 3) << 8) + (ptr[3])) * (1) + (0));
        USS_DE3_4 = ((((ptr[4]) << 2) + (((ptr[5]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE3_5 = (((((ptr[5]) & 3) << 8) + (ptr[6])) * (1) + (0));
        USS_DE3_6 = (((((ptr[18]) & 3) << 8) + (ptr[19])) * (1) + (0));
        USS_DE3_7 = ((((ptr[20]) << 2) + (((ptr[21]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE3_8 = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE3_9 = (((((ptr[10]) & 3) << 8) + (ptr[11])) * (1) + (0));
        USS_DE3_10 = ((((ptr[12]) << 2) + (((ptr[13]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_DE3_11 = (((((ptr[13]) & 3) << 8) + (ptr[14])) * (1) + (0));
        USS_DE3_12 = (((((ptr[21]) & 3) << 8) + (ptr[22])) * (1) + (0));
        de_3_rx[0]  = USS_DE3_1;
        de_3_rx[1]  = USS_DE3_2;
        de_3_rx[2]  = USS_DE3_3;
        de_3_rx[3]  = USS_DE3_4;
        de_3_rx[4]  = USS_DE3_5;
        de_3_rx[5]  = USS_DE3_6;
        de_3_rx[6]  = USS_DE3_7;
        de_3_rx[7]  = USS_DE3_8;
        de_3_rx[8]  = USS_DE3_9;
        de_3_rx[9]  = USS_DE3_10;
        de_3_rx[10] = USS_DE3_11;
        de_3_rx[11] = USS_DE3_12;
    }

    if (gcanid == 0x17C && msgEdlFlag == 1) {
        USS_CE1_1_right = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_2_right = (((((ptr[2]) & 63) << 4) + (((ptr[3]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE1_3_right = (((((ptr[3]) & 15) << 6) + (((ptr[4]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE1_4_right = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (1) + (0));
        USS_CE1_5_right = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_7_right = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_8_right = (((((ptr[10]) & 63) << 4) + (((ptr[11]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE1_9_right = (((((ptr[11]) & 15) << 6) + (((ptr[12]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE1_10_right = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (1) + (0));
        USS_CE1_11_right = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_2_left = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_3_left = (((((ptr[18]) & 63) << 4) + (((ptr[19]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE1_4_left = (((((ptr[19]) & 15) << 6) + (((ptr[20]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE1_5_left = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (1) + (0));
        USS_CE1_6_left = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_8_left = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE1_9_left = (((((ptr[26]) & 63) << 4) + (((ptr[27]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE1_10_left = (((((ptr[27]) & 15) << 6) + (((ptr[28]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE1_11_left = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (1) + (0));
        USS_CE1_12_left = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6)) * (1) + (0));

        ce_1_right_rx[0] = USS_CE1_1_right;
        ce_1_right_rx[1] = USS_CE1_2_right;
        ce_1_right_rx[2] = USS_CE1_3_right;
        ce_1_right_rx[3] = USS_CE1_4_right;
        ce_1_right_rx[4] = USS_CE1_5_right;
        ce_1_right_rx[5] = USS_CE1_7_right;
        ce_1_right_rx[6] = USS_CE1_8_right;
        ce_1_right_rx[7] = USS_CE1_9_right;
        ce_1_right_rx[8] = USS_CE1_10_right;
        ce_1_right_rx[9] = USS_CE1_11_right;

        ce_1_left_rx[0] = USS_CE1_2_left;
        ce_1_left_rx[1] = USS_CE1_3_left;
        ce_1_left_rx[2] = USS_CE1_4_left;
        ce_1_left_rx[3] = USS_CE1_5_left;
        ce_1_left_rx[4] = USS_CE1_6_left;
        ce_1_left_rx[5] = USS_CE1_8_left;
        ce_1_left_rx[6] = USS_CE1_9_left;
        ce_1_left_rx[7] = USS_CE1_10_left;
        ce_1_left_rx[8] = USS_CE1_11_left;
        ce_1_left_rx[9] = USS_CE1_12_left;
    }

    if (gcanid == 0x17E && msgEdlFlag == 1) {
        USS_CE2_1_right = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_2_right = (((((ptr[2]) & 63) << 4) + (((ptr[3]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE2_3_right = (((((ptr[3]) & 15) << 6) + (((ptr[4]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE2_4_right = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (1) + (0));
        USS_CE2_5_right = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_7_right = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_8_right = (((((ptr[10]) & 63) << 4) + (((ptr[11]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE2_9_right = (((((ptr[11]) & 15) << 6) + (((ptr[12]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE2_10_right = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (1) + (0));
        USS_CE2_11_right = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_2_left = (((((ptr[18]) & 63) << 4) + (((ptr[19]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE2_3_left = (((((ptr[19]) & 15) << 6) + (((ptr[20]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE2_4_left = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (1) + (0));
        USS_CE2_5_left = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_6_left = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_8_left = (((((ptr[26]) & 63) << 4) + (((ptr[27]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE2_9_left = (((((ptr[27]) & 15) << 6) + (((ptr[28]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE2_10_left = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (1) + (0));
        USS_CE2_11_left = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE2_12_left = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6)) * (1) + (0));

        ce_2_right_rx[0] = USS_CE2_1_right;
        ce_2_right_rx[1] = USS_CE2_2_right;
        ce_2_right_rx[2] = USS_CE2_3_right;
        ce_2_right_rx[3] = USS_CE2_4_right;
        ce_2_right_rx[4] = USS_CE2_5_right;
        ce_2_right_rx[5] = USS_CE2_7_right;
        ce_2_right_rx[6] = USS_CE2_8_right;
        ce_2_right_rx[7] = USS_CE2_9_right;
        ce_2_right_rx[8] = USS_CE2_10_right;
        ce_2_right_rx[9] = USS_CE2_11_right;

        ce_2_left_rx[0] = USS_CE2_2_left;
        ce_2_left_rx[1] = USS_CE2_3_left;
        ce_2_left_rx[2] = USS_CE2_4_left;
        ce_2_left_rx[3] = USS_CE2_5_left;
        ce_2_left_rx[4] = USS_CE2_6_left;
        ce_2_left_rx[5] = USS_CE2_8_left;
        ce_2_left_rx[6] = USS_CE2_9_left;
        ce_2_left_rx[7] = USS_CE2_10_left;
        ce_2_left_rx[8] = USS_CE2_11_left;
        ce_2_left_rx[9] = USS_CE2_12_left;
    }

    if (gcanid == 0x182 && msgEdlFlag == 1) {
        USS_CE3_1_right = ((((ptr[1]) << 2) + (((ptr[2]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_2_right = (((((ptr[2]) & 63) << 4) + (((ptr[3]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE3_3_right = (((((ptr[3]) & 15) << 6) + (((ptr[4]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE3_4_right = (((((ptr[4]) & 3) << 8) + (ptr[5])) * (1) + (0));
        USS_CE3_5_right = ((((ptr[6]) << 2) + (((ptr[7]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_7_right = ((((ptr[9]) << 2) + (((ptr[10]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_8_right = (((((ptr[10]) & 63) << 4) + (((ptr[11]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE3_9_right = (((((ptr[11]) & 15) << 6) + (((ptr[12]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE3_10_right = (((((ptr[12]) & 3) << 8) + (ptr[13])) * (1) + (0));
        USS_CE3_11_right = ((((ptr[14]) << 2) + (((ptr[15]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_2_left = (((((ptr[18]) & 63) << 4) + (((ptr[19]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE3_3_left = (((((ptr[19]) & 15) << 6) + (((ptr[20]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE3_4_left = (((((ptr[20]) & 3) << 8) + (ptr[21])) * (1) + (0));
        USS_CE3_5_left = ((((ptr[22]) << 2) + (((ptr[23]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_6_left = ((((ptr[17]) << 2) + (((ptr[18]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_8_left = (((((ptr[26]) & 63) << 4) + (((ptr[27]) & (15 << 4)) >> 4)) * (1) + (0));
        USS_CE3_9_left = (((((ptr[27]) & 15) << 6) + (((ptr[28]) & (63 << 2)) >> 2)) * (1) + (0));
        USS_CE3_10_left = (((((ptr[28]) & 3) << 8) + (ptr[29])) * (1) + (0));
        USS_CE3_11_left = ((((ptr[30]) << 2) + (((ptr[31]) & (3 << 6)) >> 6)) * (1) + (0));
        USS_CE3_12_left = ((((ptr[25]) << 2) + (((ptr[26]) & (3 << 6)) >> 6)) * (1) + (0));

        ce_3_right_rx[0] = USS_CE3_1_right;
        ce_3_right_rx[1] = USS_CE3_2_right;
        ce_3_right_rx[2] = USS_CE3_3_right;
        ce_3_right_rx[3] = USS_CE3_4_right;
        ce_3_right_rx[4] = USS_CE3_5_right;
        ce_3_right_rx[5] = USS_CE3_7_right;
        ce_3_right_rx[6] = USS_CE3_8_right;
        ce_3_right_rx[7] = USS_CE3_9_right;
        ce_3_right_rx[8] = USS_CE3_10_right;
        ce_3_right_rx[9] = USS_CE3_11_right;

        ce_3_left_rx[0] = USS_CE3_2_left;
        ce_3_left_rx[1] = USS_CE3_3_left;
        ce_3_left_rx[2] = USS_CE3_4_left;
        ce_3_left_rx[3] = USS_CE3_5_left;
        ce_3_left_rx[4] = USS_CE3_6_left;
        ce_3_left_rx[5] = USS_CE3_8_left;
        ce_3_left_rx[6] = USS_CE3_9_left;
        ce_3_left_rx[7] = USS_CE3_10_left;
        ce_3_left_rx[8] = USS_CE3_11_left;
        ce_3_left_rx[9] = USS_CE3_12_left;
    }

    if (gcanid == 0x183 && msgEdlFlag == 1) {
        PAS_FL_Distance = ((ptr[1]) * (1) + (0));
        PAS_FLM_Distance = ((ptr[2]) * (1) + (0));
        PAS_FRM_Distance = ((ptr[4]) * (1) + (0));
        PAS_FR_Distance = ((ptr[3]) * (1) + (0));
        PAS_RL_Distance = ((ptr[17]) * (1) + (0));
        PAS_RLM_Distance = ((ptr[18]) * (1) + (0));
        PAS_RRM_Distance = ((ptr[20]) * (1) + (0));
        PAS_RR_Distance = ((ptr[19]) * (1) + (0));
        SDW_FL_1SideDistance = ((ptr[21]) * (1) + (0));
        SDW_FL_2SideDistance = ((ptr[27]) * (1) + (0));
        SDW_RL_2SideDistance = ((ptr[29]) * (1) + (0));
        SDW_RL_1SideDistance = ((ptr[25]) * (1) + (0));
        SDW_FR_1SideDistance = ((ptr[22]) * (1) + (0));
        SDW_FR_2SideDistance = ((ptr[28]) * (1) + (0));
        SDW_RR_2SideDistance = ((ptr[30]) * (1) + (0));
        SDW_RR_1SideDistance = ((ptr[26]) * (1) + (0));

        ps_dis[0] = SDW_FL_1SideDistance;
        ps_dis[1] = SDW_FL_2SideDistance;
        ps_dis[2] = SDW_RL_2SideDistance;
        ps_dis[3] = SDW_RL_1SideDistance;

        ps_dis[4] = SDW_FR_1SideDistance;
        ps_dis[5] = SDW_FR_2SideDistance;
        ps_dis[6] = SDW_RR_2SideDistance;
        ps_dis[7] = SDW_RR_1SideDistance;

        ps_dis[8] = PAS_FLM_Distance;
        ps_dis[9] = PAS_FRM_Distance;
        ps_dis[10] = PAS_RLM_Distance;
        ps_dis[11] = PAS_RRM_Distance;

        ps_dis[12] = PAS_FL_Distance;
        ps_dis[13] = PAS_FR_Distance;
        ps_dis[14] = PAS_RL_Distance;
        ps_dis[15] = PAS_RR_Distance;
        
        int i;
        for (i = 0; i < 12; i++) {
            if (ps_dis[i] >= 0 && ps_dis[i] <= 30)
                ps_color_idx[i] = 0;
            else if (ps_dis[i] > 30 && ps_dis[i] <= 50)
                ps_color_idx[i] = 1;
            else if (ps_dis[i] > 50 && ps_dis[i] <= 70)
                ps_color_idx[i] = 2;
            else
                ps_color_idx[i] = 4;
        }
        for (i = 12; i < 14; i++) {
            if (ps_dis[i] >= 0 && ps_dis[i] <= 30)
                ps_color_idx[i] = 0;
            else if (ps_dis[i] > 30 && ps_dis[i] <= 50)
                ps_color_idx[i] = 1;
            else if (ps_dis[i] > 50 && ps_dis[i] <= 70)
                ps_color_idx[i] = 2;
            else if (ps_dis[i] > 70 && ps_dis[i] <= 100)
                ps_color_idx[i] = 3;
            else
                ps_color_idx[i] = 4;
        }
        for (i = 14; i < 16; i++) {
            if (ps_dis[i] >= 0 && ps_dis[i] <= 30)
                ps_color_idx[i] = 0;
            else if (ps_dis[i] > 30 && ps_dis[i] <= 50)
                ps_color_idx[i] = 1;
            else if (ps_dis[i] > 50 && ps_dis[i] <= 70)
                ps_color_idx[i] = 2;
            else if (ps_dis[i] > 70 && ps_dis[i] <= 150)
                ps_color_idx[i] = 3;
            else
                ps_color_idx[i] = 4;
        }
    }

    if (gcanid == 0x150 && msgEdlFlag == 1) {
        ESP_VehicleSpeed = (((((ptr[1]) & 15) << 8) + (ptr[2])) * (0.05625) + (0));
        if (selected_mode == 1) {
            GetLocalTime(&local_time);
            SystemTimeToFileTime(&local_time, &local_time_TM.ft);
            ts_anchor_0x150 = local_time_TM.li.QuadPart / 10000;
            timeout_0x150 = 0;
        }
        else if (selected_mode == 2) {
            ts_anchor_0x150 = ts / 1000000;
            timeout_0x150 = 0;
        }
    }

    if (gcanid == 0x152 && msgEdlFlag == 1) {
        GW_VBU_GearLeverPos = (((ptr[9]) & 7) * (1) + (0));
        if (GW_VBU_GearLeverPos > 3) {
            GW_VBU_GearLeverPos = 4;
        }
    }

    if (gcanid == 0x171 && msgEdlFlag == 1) {
        if (selected_mode == 1) {
            GetLocalTime(&local_time);
            SystemTimeToFileTime(&local_time, &local_time_TM.ft);
            ts_anchor_0x171 = local_time_TM.li.QuadPart / 10000;
            timeout_0x171 = 0;
        }
        else if (selected_mode == 2) {
            ts_anchor_0x171 = ts / 1000000;
            timeout_0x171 = 0;
        }
    }

    if (gcanid == 0x121) {
        if (selected_mode == 1) {
            GetLocalTime(&local_time);
            SystemTimeToFileTime(&local_time, &local_time_TM.ft);
            ts_anchor_0x121 = local_time_TM.li.QuadPart / 10000;
            timeout_0x121 = 0;
        }
        else if (selected_mode == 2) {
            ts_anchor_0x121 = ts / 1000000;
            timeout_0x121 = 0;
        }
    }

    update_sig_internal();
    update_de_internal();
    update_pas_sdw_internal();
}


float X0 = XCOL/2;
float Y0 = YROW/2;
const float C0 = cos(M_PI/2);
const float S0 = sin(M_PI/2);


void point4pose(float* x, float* y, float* xo, float *yo, int iter) {
    for (int i = 0; i < iter; i++) {
        *(xo + i) = ((*(x + i)) * C0 + (-*(y + i)) * S0) * gScale + X0;
        *(yo + i) = ((-*(y + i)) * C0 - (*(x + i)) * S0) * gScale + Y0;
    }
}


static void lengthScaling(float* l, float* lo, int iter) {
    for (int i = 0; i < iter; i++) {
        *(lo + i) = (*(l + i)) * gScale;
    }
}


static float calcPointDis(float x0, float y0, float x1, float y1) {
    return sqrtf((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
}