#include "stdlib.h"
#include "stdio.h"
#include "rv_param.h"
#include "signalhelper.h"
#include "plothelper.h"
#include "systimehelper.h"
#include "menuhelper.h"
#include "binloghelper.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
Mat canvas(YROW, XCOL, CV_8UC3, Scalar(255, 255, 255));

static void plot_axis(void);
static void plot_vehicle(void);
static void plot_objs(void);
static void plot_slots(void);
static void plot_misc(void);
static void plot_info(void);

static void linspace_step(float x1, float x2, int step, float* xo, int* num);

static float grid_x[LINSPACEMAXNUM];
static float grid_y[LINSPACEMAXNUM];
static int grid_num_x = 0;
static int grid_num_y = 0;

static unsigned int alive_count = 0U;

static const char cGEAR[5] = { 'P','R', 'N', 'D', 'E' };
static const Scalar mHeight_blue[4] = { BLUEL, BLUEH , BLUET , BLUEU };
static const vector<string> mlegend_blue = { "Low", "High" , "Traversable" , "Unknown" };


void init_axis(void) {
	linspace_step(0, XCOL, LINSPACESTEP, grid_x, &grid_num_x);
	linspace_step(0, YROW, LINSPACESTEP, grid_y, &grid_num_y);
}


void restore_axis(void) {
	gScale = DEFAULTSCALE;
	X0 = XCOL / 2;
	Y0 = YROW / 2;
}


void update_img(void) {
	canvas.setTo(Scalar::all(255));
	alive_count++;
	plot_axis();
	plot_vehicle();
	plot_objs();
	plot_slots();
	plot_misc();
	plot_info();
}


static void plot_axis(void) {
	int i;
	for (i = 0; i < grid_num_x; i++) {
		line(canvas, Point(grid_x[i], 0), Point(grid_x[i], YROW), GRAY, 1);
	}
	for (i = 0; i < grid_num_y; i++) {
		line(canvas, Point(0, grid_y[i]), Point(XCOL, grid_y[i]), GRAY, 1);
	}
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

				sprintf(label, "%d", slotid[i]);
				putText(canvas, label, Point(slotx[2 * i], sloty[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
			}
		}
	}
}


static void plot_misc(void) {
	char label[256] = { 0 };
	int i;

	sprintf(label, "%d", alive_count);
	putText(canvas, label, Point(XCOL-50, YROW-50), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	
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
		putText(canvas, mlegend_blue[i], Point(XCOL - 90, 50 + 20 * i), FONT_HERSHEY_SIMPLEX, 0.4, BLACK, 1, LINE_8, false);
	}
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
		sprintf(label, "Obj%02d: (%4.0f, %4.0f) (%4.0f, %4.0f)", i + 1, objx_rx[2 * i], objy_rx[2 * i], objx_rx[2 * i + 1], objy_rx[2 * i + 1]);
		putText(canvas, label, Point(20, 50 + i * 10), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	}

	// slot id
	sprintf(label, "slotid: %d %d %d %d", slotid[0], slotid[1], slotid[2], slotid[3]);
	putText(canvas, label, Point(20, 300), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// slot
	for (i = 0; i < 4; i++) {
		sprintf(label, "slot : (%4.0f, %4.0f) (%4.0f, %4.0f)", slotx_rx[2 * i], sloty_rx[2 * i], slotx_rx[2 * i + 1], sloty_rx[2 * i + 1]);
		putText(canvas, label, Point(20, 310 + i * 10), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	}
}