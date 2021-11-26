#include "stdlib.h"
#include "stdio.h"
#include "rv_param.h"
#include "signalhelper.h"
#include "plothelper.h"
#include <opencv2/opencv.hpp>


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

void init_axis(void) {
	linspace_step(0, XCOL, LINSPACESTEP, grid_x, &grid_num_x);
	linspace_step(0, YROW, LINSPACESTEP, grid_y, &grid_num_y);
}

static unsigned int alive_count = 0U;

void update_img(void){
	canvas.setTo(cv::Scalar::all(255));
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
	float x1 = X0 + (HW * SCALE);
	float y1 = Y0 + (RO * SCALE);
	float x2 = X0 - (HW * SCALE);
	float y2 = Y0 - (FO * SCALE);
	rectangle(canvas, Point(x1, y1), Point(x2, y2), BLACK, 1, LINE_8, 0);
	circle(canvas, Point(X0, Y0), 2, BLACK, FILLED, 2);
}

static void plot_objs(void) {
	char label[16] = {0};
	for (int i = 0; i < 20; i++) {
		circle(canvas, Point(objx[2 * i], objy[2 * i]), 2, BLUE, FILLED, 2);
		circle(canvas, Point(objx[2 * i + 1], objy[2 * i + 1]), 2, BLUE, FILLED, 2);
		line(canvas, Point(objx[2 * i], objy[2 * i]), Point(objx[2 * i + 1], objy[2 * i + 1]), BLUE, 2);

		sprintf(label, "%d", i+1);
		putText(canvas, label, Point(objx[2 * i], objy[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, BLUE, 1, LINE_8, false);
	}
		
}

static void plot_slots(void) {
	char label[16] = { 0 };
	for (int i = 0; i < 4; i++) {
		if (slotid[i] != 0 && slotid[i] != 255) {
			circle(canvas, Point(slotx[2 * i], sloty[2 * i]), 2, RED, FILLED, 2);
			circle(canvas, Point(slotx[2 * i + 1], sloty[2 * i + 1]), 2, RED, FILLED, 2);
			line(canvas, Point(slotx[2 * i], sloty[2 * i]), Point(slotx[2 * i + 1], sloty[2 * i + 1]), RED, 2);

			sprintf(label, "%d", slotid[i]);
			putText(canvas, label, Point(slotx[2 * i], sloty[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
		}
	}
}

static void plot_misc(void) {
	char label_long[256] = { 0 };

	sprintf(label_long, "speed %3.1f", ESP_VehicleSpeed);
	putText(canvas, label_long, Point(20, 15), FONT_HERSHEY_SIMPLEX, 0.6, RED, 1, LINE_8, false);

	sprintf(label_long, "%d", alive_count);
	putText(canvas, label_long, Point(XCOL-50, YROW-50), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	
	sprintf(label_long, "can: %6lld.%3lld s", ts / 1000000000U, (ts % 1000000000U) / 1000000U);
	putText(canvas, label_long, Point(50, YROW - 50), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
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
	// obj
	for (i = 0; i < 20; i++) {
		sprintf(label, "Obj%02d: (%4.0f, %4.0f) (%4.0f, %4.0f)", i + 1, objx_rx[2 * i], objy_rx[2 * i], objx_rx[2 * i + 1], objy_rx[2 * i + 1]);
		putText(canvas, label, Point(20, 30 + i * 10), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
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