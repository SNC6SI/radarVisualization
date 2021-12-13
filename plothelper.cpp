#include "stdlib.h"
#include "stdio.h"
#include "rv_param.h"
#include "signalhelper.h"
#include "plothelper.h"
#include "systimehelper.h"
#include "menuhelper.h"
#include "binloghelper.h"
#include "mousehelper.h"
#include "replayhelper.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

extern char version[];

Mat canvas(YROW, XCOL, CV_8UC3, Scalar(255, 255, 255));

static void plot_axis(void);
static void plot_vehicle(void);
static void plot_objs(void);
static void plot_slots(void);
static void plot_misc(void);
static void plot_info(void);
static void plot_anno(void);
static void plot_measure(void);
static void plot_echo(void);
static void plot_pas_sdw(void);
static void plot_help(void);
static void plot_version(void);

static void linspace_step(float x1, float x2, int step, float* xo, int* num);
static void DrawDashedLine(Mat& img, Point pt1, Point pt2, Scalar color, int thickness, string style, int gap);

static float grid_x[LINSPACEMAXNUM];
static float grid_y[LINSPACEMAXNUM];
static int grid_num_x = 0;
static int grid_num_y = 0;

static int plotDeStatus;
static int plotPsStatus;
static int plotInfoStatus;
static int plotGridStatus;
static int plotHelpStatus;
static unsigned int alive_count = 0U;

static const char cGEAR[5] = { 'P','R', 'N', 'D', 'E' };
static const Scalar mHeight_blue[4] = { BLUEL, BLUEH , BLUET , BLUEU };
static const vector<string> mlobjheight = { "Low", "High" , "Traversable" , "Unknown" };
static const Scalar mPs[5] = { RED, ORANGE, YELLOW, GREEN, WHITE };
static const Scalar mTimeout[2] = { GREEN, RED };
static const vector<string> mAPS2PA_working_sts = { "0x0 Off", "0x1 Standby", "0x2 Searching", "0x3 Tracking", "0x4 APS Failure", "0x5 PA Failure", "0x6 Reserved", "0x7 Reserved"};
static const vector<string> mPAS_Mode = {"0x0 Off", "0x1 Standby", "0x2 StandbyAndFrontFailure", "0x3 StandbyAndRearFailure",
                                         "0x4 FrontAcitve", "0x5 FrontActiveAndRearFailure", "0x6 RearActive", "0x7 RearActiveAndFrontFailure",
                                         "0x8 FrontRearActive", "0x9 SystemFailure", "0xA FrontFailureAndRearInactive", "0xB RearFailureAndFrontInactive",
                                         "0xC Reserved", "0xD Reserved" , "0xE Reserved" , "0xF Reserved" };
static const vector<string> mPASWarningType = { "0x0 no object", "0x1 Buzzer On", "0x2 Buzzer ON at 8Hz", "0x3 Buzzer ON at 4Hz", "0x4 Buzzer ON at 1Hz",
												"0x5 Reserved", "0x6 Reserved", "0x7 Reserved" };
static const vector<string> mPASFailureReason = { "0x0 No failure", "0x1 Sensor blindness", "0x2 Other reason", "0x3 reserved"};
static const vector<string> mUPC_SDW_WorkMode = { "0x0 Off", "0x1 Standby", "0x2 Active", "0x3 Failure"};
static const vector<string> mAPA_PSLSts = { "0x0 Off", "0x1 Standby", "0x2 Searching", "0x3 Tracking", "0x4 APS Failure", "0x5 PA Failure",
                                            "0x6 Reserved", "0x7 Reserved"};
static const vector<string> mMapObjType = { "None", "Point", "Straight0Corner", "Straight1Corner", "Straight2Corner", "Reserved", "Reserved", "Invalid"};
static const vector<string> mSlot = { "left0", "left1", "right0" , "right1" };
static const vector<string> mApaPscSlotTpye = { "None", "LeftParallel", "RightParallel", "LeftCross", "RightCross", "LeftDiagnal", "RightDiagnal", "Invalid"};
static const vector<string> mApaPscPSLObjectType = { "None", "Curb", "Wall", "Virtual", "Low", "High", "Unknow", "Reserved"};


void init_axis(void) {
	linspace_step(0, XCOL, LINSPACESTEP, grid_x, &grid_num_x);
	linspace_step(0, YROW, LINSPACESTEP, grid_y, &grid_num_y);
	plotDeStatus = 1;
	plotPsStatus = 1;
	plotInfoStatus = 1;
	plotGridStatus = 1;
	plotHelpStatus = 0;
}


void restore_axis(void) {
	gScale = DEFAULTSCALE;
	X0 = XCOL / 2;
	Y0 = YROW / 2;
}

void toggle_info_status(void) {
	plotInfoStatus = !plotInfoStatus;
}

void toggle_grid_status(void) {
	plotGridStatus = !plotGridStatus;
}

void toggle_de_status(void) {
	plotDeStatus = !plotDeStatus;
}

void toggle_ps_status(void) {
	plotPsStatus = !plotPsStatus;
}

void toggle_help_status(void) {
	plotHelpStatus = !plotHelpStatus;
}


void update_img(void) {
	canvas.setTo(Scalar::all(255));
	alive_count++;
	if (plotGridStatus) {
		plot_axis();
	}
	plot_version();
	plot_vehicle();
	if (plotPsStatus) {
		plot_pas_sdw();
	}
	if (plotDeStatus) {
		plot_echo();
	}
	if (plotInfoStatus) {
		plot_objs();
		plot_slots();
		plot_misc();
		plot_info();
	}
	plot_anno();
	plot_measure();
	if (plotHelpStatus) {
		plot_help();
	}
}
static void plot_version(void) {
	char label[256] = { 0 };
	sprintf(label, "version: %s by SNC6SI", version);
	putText(canvas, label, Point(XCOL - 180, YROW - 20), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
}

static void plot_help(void) {
	char label[256] = { 0 };
	sprintf(label, "%s", "H: help menu");
	putText(canvas, label, Point(XCOL / 2 - 300, YROW - 200), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	sprintf(label, "%s", "D: direct echo");
	putText(canvas, label, Point(XCOL / 2 - 300, YROW - 180), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	sprintf(label, "%s", "W: radar wall");
	putText(canvas, label, Point(XCOL / 2 - 300, YROW - 160), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	sprintf(label, "%s", "M: messure distance");
	putText(canvas, label, Point(XCOL / 2 - 300, YROW - 140), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	sprintf(label, "%s", "Enter: restore axis");
	putText(canvas, label, Point(XCOL / 2 - 300, YROW - 120), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);

	sprintf(label, "%s", "G: grid");
	putText(canvas, label, Point(XCOL / 2, YROW - 200), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	sprintf(label, "%s", "I: infos");
	putText(canvas, label, Point(XCOL / 2, YROW - 180), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);

	sprintf(label, "%s", "Mouse Left: measure");
	putText(canvas, label, Point(XCOL / 2, YROW - 140), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	sprintf(label, "%s", "Mouse Wheel: zoom");
	putText(canvas, label, Point(XCOL / 2, YROW - 120), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);

	if (selected_mode == 2) {
		sprintf(label, "%s", "F: fast forward");
		putText(canvas, label, Point(XCOL / 2 - 300, YROW - 100), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
		sprintf(label, "%s", "Space: pause");
		putText(canvas, label, Point(XCOL / 2 - 300, YROW - 80), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	}
}

static void plot_axis(void) {
	int i;
	for (i = 0; i < grid_num_x; i++) {
		line(canvas, Point(grid_x[i], 0), Point(grid_x[i], YROW), GRAY, 1);
	}
	for (i = 0; i < grid_num_y; i++) {
		line(canvas, Point(0, grid_y[i]), Point(XCOL, grid_y[i]), GRAY, 1);
	}
	//arrowedLine(canvas, Point(X0, Y0), Point(X0, 0), GRAY, 4, LINE_8, 0, 0.8);
	//arrowedLine(canvas, Point(X0, Y0), Point(0, Y0), GRAY, 4, LINE_8, 0, 0.8);
}


static void plot_vehicle(void) {
	float x1 = X0 + HW;
	float y1 = Y0 + RO;
	float x2 = X0 - HW;
	float y2 = Y0 - FO;
	rectangle(canvas, Point(x1, y1), Point(x2, y2), BLACK, 1, LINE_8, 0);
#if 0
	if (GW_VBU_GearLeverPos == 1) {
		// R
		arrowedLine(canvas, Point(X0, Y0), Point(X0, Y0 + RO), BLACK, 1, LINE_8, 0);
	}
	else if (GW_VBU_GearLeverPos == 3) {
		// D
		arrowedLine(canvas, Point(X0, Y0), Point(X0, Y0 - RO), BLACK, 1, LINE_8, 0);
	}
#endif
}

static void plot_echo(void) {
	char label[16] = { 0 };
	for (int i = 0; i < 12; i++) {
		Point center(de_cc_x[i], de_cc_y[i]);
		Size sz1(de_1[i], de_1[i]);
		Size sz2(de_2[i], de_2[i]);
		Size sz3(de_3[i], de_3[i]);
		ellipse(canvas, center, sz1, de_angle_anchor[i], de_angle_start[i], de_angle_end[i], SlateGray1, -1);
		ellipse(canvas, center, sz2, de_angle_anchor[i], de_angle_start[i], de_angle_end[i], LightBlue1, 2);
		ellipse(canvas, center, sz3, de_angle_anchor[i], de_angle_start[i], de_angle_end[i], LightYellow2, 2);
		circle(canvas, Point(de_cc_x[i], de_cc_y[i]), 2, GREENDARK, FILLED, 10);
		sprintf(label, "%d", i + 1);
		putText(canvas, label, Point(de_cc_x[i], de_cc_y[i]), FONT_HERSHEY_SIMPLEX, 0.4, GREENDARK, 1, LINE_8, false);
	}
}

static void plot_pas_sdw(void) {
	int i;
	for (i = 0; i < 12; i++) {
		line(canvas, Point(ps_x[2 * i], ps_y[2 * i]), Point(ps_x[2 * i + 1], ps_y[2 * i + 1]), mPs[ps_color_idx[i]], 8);
		// line(canvas, Point(ps_x[2 * i], ps_y[2 * i]), Point(ps_x[2 * i + 1], ps_y[2 * i + 1]), BLACK, 8);
	}
	for (i = 12; i < 16; i++) {
		ellipse(canvas, Point(ps_x[i + 12], ps_y[i + 12]), Size(ps_r, ps_r), ps_angle_anchor[i - 12], ps_angle_start[i - 12], ps_angle_end[i - 12], mPs[ps_color_idx[i]], 8);
	}
}


static void plot_objs(void) {
	char label[16] = { 0 };
	for (int i = 0; i < 20; i++) {
		if (((int)objx[2 * i] != (int)X0) && ((int)objy[2 * i] != (int)Y0) && ((int)objx[2 * i + 1] != (int)X0) && ((int)objy[2 * i + 1] != (int)Y0)){
			circle(canvas, Point(objx[2 * i], objy[2 * i]), 2, mHeight_blue[objH[i]], FILLED, 2);
			circle(canvas, Point(objx[2 * i + 1], objy[2 * i + 1]), 2, mHeight_blue[objH[i]], FILLED, 2);
			line(canvas, Point(objx[2 * i], objy[2 * i]), Point(objx[2 * i + 1], objy[2 * i + 1]), mHeight_blue[objH[i]], 2);

			sprintf(label, "%d", i + 1);
			putText(canvas, label, Point(objx[2 * i], objy[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, BLUE, 1, LINE_8, false);
		}
	}
		
}


static void plot_slots(void) {
	char label[16] = { 0 };
	for (int i = 0; i < 4; i++) {
		if (slotid[i] != 0 && slotid[i] != 255) {
			if ((slotx[2 * i] != 0) && (sloty[2 * i] != 0) && (slotx[2 * i + 1] != 0) && (sloty[2 * i + 1] != 0)) {
#if 0
				circle(canvas, Point(slotx[2 * i], sloty[2 * i]), 2, RED, FILLED, 2);
				circle(canvas, Point(slotx[2 * i + 1], sloty[2 * i + 1]), 2, RED, FILLED, 2);
				line(canvas, Point(slotx[2 * i], sloty[2 * i]), Point(slotx[2 * i + 1], sloty[2 * i + 1]), RED, 2);

				for (int j = 0; j < 4; j++) {
					if (j != 3) {
						line(canvas, Point(slotxrec[4 * i + j], slotyrec[4 * i + j]), Point(slotxrec[4 * i + j + 1], slotyrec[4 * i + j + 1]), BLACK, 1, LINE_4);
					}
					else {
						line(canvas, Point(slotxrec[4 * i + j], slotyrec[4 * i + j]), Point(slotxrec[4 * i], slotyrec[4 * i]), BLACK, 1, LINE_4);
					}
				}
#endif
				
				line(canvas, Point(slotxrec_alpha[6 * i], slotyrec_alpha[6 * i]), Point(slotxrec_alpha[6 * i + 1], slotyrec_alpha[6 * i + 1]), Chocolate, 2, LINE_4);
				line(canvas, Point(slotxrec_alpha[6 * i], slotyrec_alpha[6 * i]), Point(slotxrec_alpha[6 * i + 2], slotyrec_alpha[6 * i + 2]), Chocolate, 2, LINE_4);

				line(canvas, Point(slotxrec_alpha[6 * i + 3], slotyrec_alpha[6 * i + 3]), Point(slotxrec_alpha[6 * i + 4], slotyrec_alpha[6 * i + 4]), Chocolate, 2, LINE_4);
				line(canvas, Point(slotxrec_alpha[6 * i + 3], slotyrec_alpha[6 * i + 3]), Point(slotxrec_alpha[6 * i + 5], slotyrec_alpha[6 * i + 5]), Chocolate, 2, LINE_4);
#if 0
				circle(canvas, Point(slotxrec_alpha[6 * i], slotyrec_alpha[6 * i]), 3, Chocolate, FILLED, 2);
				sprintf(label, "%d", 6 * i);
				putText(canvas, label, Point(slotxrec_alpha[6 * i], slotyrec_alpha[6 * i]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);

				circle(canvas, Point(slotxrec_alpha[6 * i + 1], slotyrec_alpha[6 * i + 1]), 3, Chocolate, FILLED, 2);
				sprintf(label, "%d", 6 * i + 1);
				putText(canvas, label, Point(slotxrec_alpha[6 * i + 1], slotyrec_alpha[6 * i + 1]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);

				circle(canvas, Point(slotxrec_alpha[6 * i + 2], slotyrec_alpha[6 * i + 2]), 3, Chocolate, FILLED, 2);
				sprintf(label, "%d", 6 * i + 2);
				putText(canvas, label, Point(slotxrec_alpha[6 * i + 2], slotyrec_alpha[6 * i + 2]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);

				circle(canvas, Point(slotxrec_alpha[6 * i + 3], slotyrec_alpha[6 * i + 3]), 3, Chocolate, FILLED, 2);
				sprintf(label, "%d", 6 * i + 3);
				putText(canvas, label, Point(slotxrec_alpha[6 * i + 3], slotyrec_alpha[6 * i + 3]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);

				circle(canvas, Point(slotxrec_alpha[6 * i + 4], slotyrec_alpha[6 * i + 4]), 3, Chocolate, FILLED, 2);
				sprintf(label, "%d", 6 * i + 4);
				putText(canvas, label, Point(slotxrec_alpha[6 * i + 4], slotyrec_alpha[6 * i + 4]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);

				circle(canvas, Point(slotxrec_alpha[6 * i + 5], slotyrec_alpha[6 * i + 5]), 3, Chocolate, FILLED, 2);
				sprintf(label, "%d", 6 * i + 5);
				putText(canvas, label, Point(slotxrec_alpha[6 * i + 5], slotyrec_alpha[6 * i + 5]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);

				sprintf(label, "%4.1f", slot_alpha_deg_rx[2 * i]);
				putText(canvas, label, Point(slotx[2 * i] + 10, sloty[2 * i] + 10), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);
				sprintf(label, "%4.1f", slot_alpha_deg_rx[2 * i + 1]);
				putText(canvas, label, Point(slotx[2 * i + 1] + 10, sloty[2 * i + 1] + 10), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);
#endif

				sprintf(label, "%d", slotid[i]);
				putText(canvas, label, Point(slotx[2 * i], sloty[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, Chocolate, 1, LINE_8, false);
			}
		}
	}
}


static void plot_misc(void) {
	char label[256] = { 0 };
	int i;

	if (selected_mode == 2) {
		sprintf(label, "%s", greadcnt_fraction);
		putText(canvas, label, Point(XCOL - 200, YROW - 50), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	}
	else {
		sprintf(label, "%d", alive_count);
		putText(canvas, label, Point(XCOL - 50, YROW - 50), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	}
	
	sprintf(label, "can: %6lld.%3lld s", ts / 1000000000U, (ts % 1000000000U) / 1000000U);
	putText(canvas, label, Point(20, YROW - 50), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	if (selected_mode == 1) {
		GetLocalTime(&localTime);
	}
	if (selected_mode == 2) {
		TM.ft = timeInSec;
		TM.li.QuadPart += ts / 100U;
		FileTimeToSystemTime(&TM.ft, &localTime);
	}
	sprintf(label, "%d/%02d/%02d %02d:%02d:%02d.%03d", localTime.wYear, localTime.wMonth, localTime.wDay, localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
	putText(canvas, label, Point(20, YROW - 30), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// legend
	for (i = 0; i < 4; i++) {
		line(canvas, Point(XCOL - 150, 50 + 20 * i), Point(XCOL - 100, 50 + 20 * i), mHeight_blue[i], 2);
		putText(canvas, mlobjheight[i], Point(XCOL - 90, 50 + 20 * i), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	}

	// timeout
	sprintf(label, "%s", "ADASCAN");
	putText(canvas, label, Point(20, YROW - 80), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	circle(canvas, Point(100, YROW - 80), 8, mTimeout[timeout_0x121], FILLED, 2);

	sprintf(label, "%s", "MCU3_0");
	putText(canvas, label, Point(20, YROW - 100), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	circle(canvas, Point(100, YROW - 100), 8, mTimeout[timeout_0x171], FILLED, 2);

	sprintf(label, "%s", "MCU1_0");
	putText(canvas, label, Point(20, YROW - 120), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	circle(canvas, Point(100, YROW - 120), 8, mTimeout[timeout_0x150], FILLED, 2);

	sprintf(label, "%s", "PA");
	putText(canvas, label, Point(20, YROW - 140), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	circle(canvas, Point(100, YROW - 140), 8, mTimeout[timeout_0x172], FILLED, 2);
}


static void linspace_step(float x1, float x2, int step, float* xo, int* num) {
	int i;
	if ((x2 - x1) * step <= 0) {
		*num = 0;
		*xo = x1;
	}
	else {
		i = 1;
		*xo = x1;
		while ((x1 + step * i) < x2) {
			*(xo + i) = (x1 + step * i);
			i++;
		}
		*num = i;
	}
}


static void plot_info(void) {
	char label[256] = { 0 };
	int i;

	sprintf(label, "%c", cGEAR[GW_VBU_GearLeverPos]);
	putText(canvas, label, Point(20, 15), FONT_HERSHEY_TRIPLEX, 0.5, RED, 1, LINE_8, false);

	sprintf(label, "%3.2f", ESP_VehicleSpeed);
	putText(canvas, label, Point(60, 15), FONT_HERSHEY_TRIPLEX, 0.5, RED, 1, LINE_8, false);

	// obj
	for (i = 0; i < 20; i++) {
		sprintf(label, "Obj%02d: (%4.0f, %-4.0f) (%4.0f, %-4.0f) {%-3.1f%% %s} |%3.1f%% %-s| ", i + 1, objx_rx[2 * i], objy_rx[2 * i], objx_rx[2 * i + 1], objy_rx[2 * i + 1],
			    MapObjHeightProb[i], mlobjheight[objH[i]].c_str(), MapObjProb[i], mMapObjType[MapObjType[i]].c_str());
		putText(canvas, label, Point(20, 50 + i * 10), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	}

	// slot
	for (i = 0; i < 4; i++) {
		sprintf(label, "slot: %3d %s %s %s", slotid[i], mSlot[i].c_str(), mApaPscSlotTpye[ApaPscSlotTpye[i]].c_str(), mApaPscPSLObjectType[ApaPscPSLObjectType[i]].c_str());
		putText(canvas, label, Point(20, 280 + 2 * i * 15), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
		sprintf(label, "     (%6.0f, %-6.0f) (%6.0f, %-6.0f) <%.0fdeg %.0fdeg>", slotx_rx[2 * i], sloty_rx[2 * i], slotx_rx[2 * i + 1], sloty_rx[2 * i + 1], slot_alpha_deg_rx[2 * i], slot_alpha_deg_rx[2 * i + 1]);
		putText(canvas, label, Point(20, 280 + 2 * i * 15 + 10), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	}

	// 0x171
	sprintf(label, "APS_Workingsts: %s", mAPS2PA_working_sts[APS_Workingsts].c_str());
	putText(canvas, label, Point(20, 420), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	sprintf(label, "ParkslotI_Selected: %d", ParkslotI_Selected);
	putText(canvas, label, Point(20, 435), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// 0x2B0
	sprintf(label, "PAS_Mode: %s", mPAS_Mode[PAS_Mode].c_str());
	putText(canvas, label, Point(20, 470), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	sprintf(label, "PASWarningType: %s", mPASWarningType[PASWarningType].c_str());
	putText(canvas, label, Point(20, 485), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	sprintf(label, "PASFailureReason: %s", mPASFailureReason[PASFailureReason].c_str());
	putText(canvas, label, Point(20, 500), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	sprintf(label, "UPC_SDW_WorkMode: %s", mUPC_SDW_WorkMode[UPC_SDW_WorkMode].c_str());
	putText(canvas, label, Point(20, 515), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	sprintf(label, "APA_PSLSts: %s", mAPA_PSLSts[APA_PSLSts].c_str());
	putText(canvas, label, Point(20, 530), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
}


static void plot_anno(void) {
	char label[256] = { 0 };
	float x_anno_local, y_anno_local;
	if (LBUTTONDOWN_flg == 1) {
		DrawDashedLine(canvas, Point(X0, Y0), Point(X0, y_anno), DIMGREY, 1, "dotted", 4);
		DrawDashedLine(canvas, Point(X0, Y0), Point(x_anno, Y0), DIMGREY, 1, "dotted", 4);
		DrawDashedLine(canvas, Point(X0, y_anno), Point(x_anno, y_anno), DIMGREY, 1, "dotted", 4);
		DrawDashedLine(canvas, Point(x_anno, Y0), Point(x_anno, y_anno), DIMGREY, 1, "dotted", 4);
		x_anno_local = (float)x_anno;
		y_anno_local = (float)y_anno;
		point2pose(&x_anno_local, &y_anno_local, 1);
		sprintf(label, "(%4d, %4d)", (int)x_anno_local, (int)y_anno_local);
		if (x_anno >= X0 && y_anno <= Y0) { // 1
			putText(canvas, label, Point(x_anno + 20, y_anno), FONT_HERSHEY_SIMPLEX, 0.35, DIMGREY, 1, LINE_8, false);
		}
		else if (x_anno < X0 && y_anno < Y0) { // 2
			putText(canvas, label, Point(x_anno - 80, y_anno), FONT_HERSHEY_SIMPLEX, 0.35, DIMGREY, 1, LINE_8, false);
		}
		else if (x_anno <= X0 && y_anno >= Y0) { // 3
			putText(canvas, label, Point(x_anno - 80, y_anno + 20), FONT_HERSHEY_SIMPLEX, 0.35, DIMGREY, 1, LINE_8, false);
		}
		else { // 4
			putText(canvas, label, Point(x_anno, y_anno + 20), FONT_HERSHEY_SIMPLEX, 0.35, DIMGREY, 1, LINE_8, false);
		}
	}
}


static void plot_measure(void) {
	char label[256] = { 0 };
	static vector<float> x_meas_follow, y_meas_follow;
	static float x_dist, y_dist;
	if (!query_measure_status()) {
		empty_measure_data();
	}
	int numPoints = query_measure_data_size();
	if (numPoints > 0) {
		x_meas_follow = x_meas_label;
		y_meas_follow = y_meas_label;
		point4pose(&x_meas_label[0], &y_meas_label[0], &x_meas_follow[0], &y_meas_follow[0], numPoints);
	}
	for (int i = 0; i < numPoints / 2; i++) {
		DrawDashedLine(canvas, Point(x_meas_follow[2 * i], y_meas_follow[2 * i]), Point(x_meas_follow[2 * i + 1], y_meas_follow[2 * i + 1]), OrangeRed1, 1, "dotted", 4);
		sprintf(label, "(%4d, %4d)", (int)x_meas_label[2 * i], (int)y_meas_label[2 * i]);
		putText(canvas, label, Point(x_meas_follow[2 * i], y_meas_follow[2 * i]), FONT_HERSHEY_SIMPLEX, 0.35, OrangeRed1, 1, LINE_8, false);
		sprintf(label, "(%4d, %4d)", (int)x_meas_label[2 * i + 1], (int)y_meas_label[2 * i + 1]);
		putText(canvas, label, Point(x_meas_follow[2 * i + 1], y_meas_follow[2 * i + 1]), FONT_HERSHEY_SIMPLEX, 0.35, OrangeRed1, 1, LINE_8, false);

		x_dist = (x_meas_follow[2 * i + 1] - x_meas_follow[2 * i]) / 2 + x_meas_follow[2 * i];
		y_dist = (y_meas_follow[2 * i + 1] - y_meas_follow[2 * i]) / 2 + y_meas_follow[2 * i];
		sprintf(label, "%4d", (int)meas_dist[i]);
		putText(canvas, label, Point(x_dist, y_dist), FONT_HERSHEY_SIMPLEX, 0.35, OrangeRed1, 1, LINE_8, false);
	}
}


static void DrawDashedLine(Mat& img, Point pt1, Point pt2, Scalar color, int thickness, string style,int gap) {
	float dx = pt1.x - pt2.x;
	float dy = pt1.y - pt2.y;
	float dist = hypot(dx, dy);

	vector<Point> pts;
	for (int i = 0; i < dist; i += gap) {
		float r = static_cast<float>(i / dist);
		int x = static_cast<int>((pt1.x * (1.0 - r) + pt2.x * r) + .5);
		int y = static_cast<int>((pt1.y * (1.0 - r) + pt2.y * r) + .5);
		pts.emplace_back(x, y);
	}

	int pts_size = pts.size();

	if (style == "dotted") {
		for (int i = 0; i < pts_size; ++i) {
			circle(img, pts[i], thickness, color, -1);
		}
	}
	else {
		Point s = pts[0];
		Point e = pts[0];

		for (int i = 0; i < pts_size; ++i) {
			s = e;
			e = pts[i];
			if (i % 2 == 1) {
				line(img, s, e, color, thickness);
			}
		}
	}
}


void point2pose(float* x, float* y, int iter) {
	int i;
	float xx, yy;
	for (i = 0; i < iter; i++) {
		xx = (*(x + i) - X0) / gScale;
		yy = - (*(y + i) - Y0) / gScale;
		*(x + i) = xx * C0 + yy * S0;
		*(y + i) = yy * C0 - xx * S0;
	}
}