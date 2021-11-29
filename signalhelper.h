#ifndef _UPDATESIG_H_
#define _UPDATESIG_H_

extern float ESP_VehicleSpeed;
extern unsigned char  GW_VBU_GearLeverPos;

extern unsigned int gcanid;
extern unsigned __int64 ts;

extern unsigned char ptr[64];

extern float objx_rx[40];
extern float objy_rx[40];
extern float slotx_rx[8];
extern float sloty_rx[8];

extern float objx[40];
extern float objy[40];
extern float slotx[8];
extern float sloty[8];
extern float slotxrec[16];
extern float slotyrec[16];

extern unsigned char objH[20];
extern unsigned char slotid[4];

extern float slot_Depth[4];
extern float slot_Length[4];
extern float slot_theta[4];

extern float X0;
extern float Y0;

extern const float C0;
extern const float S0;

void init_sig(void);
void update_sig(void);

#endif