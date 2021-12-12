#ifndef _UPDATESIG_H_
#define _UPDATESIG_H_

extern float ESP_VehicleSpeed;
extern unsigned char  GW_VBU_GearLeverPos;

extern unsigned int gcanid;
extern unsigned __int64 ts;

extern unsigned char ptr[64];

extern unsigned char MapObjType[20];
extern float MapObjProb[20];
extern float MapObjHeightProb[20];

extern float objx_rx[40];
extern float objy_rx[40];
extern float slotx_rx[8];
extern float sloty_rx[8];

extern float objx[40];
extern float objy[40];
extern float slotx[8];
extern float sloty[8];
//extern float slotxrec[16];
//extern float slotyrec[16];

extern float slotxrec_alpha[24];
extern float slotyrec_alpha[24];
extern float slot_alpha_deg_rx[8];

extern float de_1[12];
extern float de_2[12];
extern float de_3[12];

extern float de_cc_x[12];
extern float de_cc_y[12];

extern float ps_x[28];
extern float ps_y[28];
extern float ps_r;
extern float ps_dis[16];
extern unsigned char ps_color_idx[16];
extern float ps_angle_anchor[4];
extern float ps_angle_start[4];
extern float ps_angle_end[4];

extern const float de_angle_anchor[12];
extern const float de_angle_start[12];
extern const float de_angle_end[12];

extern unsigned char objH[20];
extern unsigned char slotid[4];

//extern float slot_Depth[4];
//extern float slot_Length[4];
//extern float slot_theta[4];

extern unsigned char ParkslotI_Selected;
extern unsigned char APS_Workingsts;

extern unsigned char PAS_Mode;
extern unsigned char PASWarningType;
extern unsigned char PASFailureReason;
extern unsigned char UPC_SDW_WorkMode;
extern unsigned char APA_PSLSts;

extern float X0;
extern float Y0;

extern const float C0;
extern const float S0;

extern unsigned int timeout_0x121; // ADASCAN
extern unsigned int timeout_0x171; // PACAN APS MCU 3_0
extern unsigned int timeout_0x150; // PACAN APS MCU 1_0
extern unsigned int timeout_0x172; // PACAN PA

void init_sig(void);
void update_sig(void);

void check_timeout(void);

void point4pose(float* x, float* y, float* xo, float* yo, int iter);

#endif