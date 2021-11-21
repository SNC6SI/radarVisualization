#include "stdlib.h"
#include "stdio.h"
#include "updateimg.h"
#include "updatesig.h"
#include<opencv2/opencv.hpp>


using namespace cv;
extern Mat canvas;

static void plot_axis(void);
static void plot_vehicle(void);
static void plot_objs(void);
static void plot_slots(void);
static void plot_misc(void);

static void linspace_step(float x1, float x2, int step, float* xo, int* num);

static float grid_x[LINSPACEMAXNUM];
static float grid_y[LINSPACEMAXNUM];
static int grid_num_x = 0;
static int grid_num_y = 0;

void init_axis(void) {
	linspace_step(0, XCOL, 100, grid_x, &grid_num_x);
	linspace_step(0, YROW, 100, grid_y, &grid_num_y);
}

static unsigned int alive_count = 0U;

void update_img(void){
	alive_count++;
	plot_axis();
	plot_vehicle();
	plot_objs();
	plot_slots();
	plot_misc();
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
	float x1 = X0 + 100;
	float y1 = Y0 + 100;
	float x2 = X0 - 100;
	float y2 = Y0 - 350;
	rectangle(canvas, Point(x1, y1), Point(x2, y2), BLACK, 1, LINE_8, 0);
	circle(canvas, Point(X0, Y0), 2, BLACK, FILLED, 2);
}

static void plot_objs(void) {
	char label[16] = {0};
	for (int i = 0; i < 20; i++) {
		circle(canvas, Point(objx[2 * i], objy[2 * i]), 2, BLUE, FILLED, 2);
		circle(canvas, Point(objx[2 * i + 1], objy[2 * i + 1]), 2, BLUE, FILLED, 2);
		line(canvas, Point(objx[2 * i], objy[2 * i]), Point(objx[2 * i + 1], objy[2 * i + 1]), BLUE, 2);

		sprintf(label, "%d", i);
		putText(canvas, label, Point(objx[2 * i], objy[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, BLUE, 1, LINE_8, false);
	}
}

static void plot_slots(void) {
	char label[16] = { 0 };
	for (int i = 0; i < 4; i++) {
		circle(canvas, Point(slotx[2 * i], sloty[2 * i]), 2, RED, FILLED, 2);
		circle(canvas, Point(slotx[2 * i + 1], sloty[2 * i + 1]), 2, RED, FILLED, 2);
		line(canvas, Point(slotx[2 * i], sloty[2 * i]), Point(slotx[2 * i + 1], sloty[2 * i + 1]), RED, 2);

		sprintf(label, "%d", i);
		putText(canvas, label, Point(slotx[2 * i], sloty[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	}
}

static void plot_misc(void) {
	char label[16] = { 0 };
	char label_alive_count[16] = { 0 };
	sprintf(label, "speed %3.1f", ESP_VehicleSpeed);
	sprintf(label_alive_count, "%d", alive_count);

	putText(canvas, label, Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	putText(canvas, label_alive_count, Point(1550, 950), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
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