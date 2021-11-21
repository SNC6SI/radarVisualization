#include "stdlib.h"
#include "stdio.h"
#include "updateimg.h"
#include "updatesig.h"
#include<opencv2/opencv.hpp>


using namespace cv;
extern Mat canvas;

static void plot_objs(void);
static void plot_slots(void);
static void plot_vehicle(void);
static void plot_misc(void);

static unsigned int alive_count = 0U;

void update_img(void){
	alive_count++;
	plot_objs();
	plot_slots();
	plot_vehicle();
	plot_misc();
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

static void plot_vehicle(void) {
	float x1 = X0 + 100;
	float y1 = Y0 + 100;
	float x2 = X0 - 100;
	float y2 = Y0 - 350;
	rectangle(canvas, Point(x1,y1), Point(x2,y2), BLACK, 1, LINE_8, 0);
	circle(canvas, Point(X0,Y0), 2, BLACK, FILLED, 2);
}

static void plot_misc(void) {
	char label[16] = { 0 };
	char label_alive_count[16] = { 0 };
	sprintf(label, "speed %3.1f", ESP_VehicleSpeed);
	sprintf(label_alive_count, "%d", alive_count);

	putText(canvas, label, Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
	putText(canvas, label_alive_count, Point(1550, 950), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
}