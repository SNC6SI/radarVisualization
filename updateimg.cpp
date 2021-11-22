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
static void plot_info(void);

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
		if (slotid[i] != 0 && slotid[i] != 255) {
			circle(canvas, Point(slotx[2 * i], sloty[2 * i]), 2, RED, FILLED, 2);
			circle(canvas, Point(slotx[2 * i + 1], sloty[2 * i + 1]), 2, RED, FILLED, 2);
			line(canvas, Point(slotx[2 * i], sloty[2 * i]), Point(slotx[2 * i + 1], sloty[2 * i + 1]), RED, 2);

			sprintf(label, "%d", i);
			putText(canvas, label, Point(slotx[2 * i], sloty[2 * i]), FONT_HERSHEY_SIMPLEX, 0.4, RED, 1, LINE_8, false);
		}
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

static void plot_info(void) {
	char label[256] = { 0 };
	
	// obj1
	sprintf(label, "Obj01: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj01P1X, MapObj01P1Y, MapObj01P2X, MapObj01P2Y);
	putText(canvas, label, Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	// obj2
	sprintf(label, "Obj02: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj02P1X, MapObj02P1Y, MapObj02P2X, MapObj02P2Y);
	putText(canvas, label, Point(20, 40), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj3
	sprintf(label, "Obj03: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj03P1X, MapObj03P1Y, MapObj03P2X, MapObj03P2Y);
	putText(canvas, label, Point(20, 50), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj4
	sprintf(label, "Obj04: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj04P1X, MapObj04P1Y, MapObj04P2X, MapObj04P2Y);
	putText(canvas, label, Point(20, 60), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj5
	sprintf(label, "Obj05: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj05P1X, MapObj05P1Y, MapObj05P2X, MapObj05P2Y);
	putText(canvas, label, Point(20, 70), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj6
	sprintf(label, "Obj06: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj06P1X, MapObj06P1Y, MapObj06P2X, MapObj06P2Y);
	putText(canvas, label, Point(20, 80), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj7
	sprintf(label, "Obj07: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj07P1X, MapObj07P1Y, MapObj07P2X, MapObj07P2Y);
	putText(canvas, label, Point(20, 90), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj8
	sprintf(label, "Obj08: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj08P1X, MapObj08P1Y, MapObj08P2X, MapObj08P2Y);
	putText(canvas, label, Point(20, 100), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj9
	sprintf(label, "Obj09: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj09P1X, MapObj09P1Y, MapObj09P2X, MapObj09P2Y);
	putText(canvas, label, Point(20, 110), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj10
	sprintf(label, "Obj10: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj10P1X, MapObj10P1Y, MapObj10P2X, MapObj10P2Y);
	putText(canvas, label, Point(20, 120), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj11
	sprintf(label, "Obj11: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj11P1X, MapObj11P1Y, MapObj11P2X, MapObj11P2Y);
	putText(canvas, label, Point(20, 130), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj12
	sprintf(label, "Obj12: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj12P1X, MapObj12P1Y, MapObj12P2X, MapObj12P2Y);
	putText(canvas, label, Point(20, 140), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj13
	sprintf(label, "Obj13: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj13P1X, MapObj13P1Y, MapObj13P2X, MapObj13P2Y);
	putText(canvas, label, Point(20, 150), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj14
	sprintf(label, "Obj14: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj14P1X, MapObj14P1Y, MapObj14P2X, MapObj14P2Y);
	putText(canvas, label, Point(20, 160), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj15
	sprintf(label, "Obj15: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj15P1X, MapObj15P1Y, MapObj15P2X, MapObj15P2Y);
	putText(canvas, label, Point(20, 170), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj16
	sprintf(label, "Obj16: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj16P1X, MapObj16P1Y, MapObj16P2X, MapObj16P2Y);
	putText(canvas, label, Point(20, 180), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj17
	sprintf(label, "Obj17: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj17P1X, MapObj17P1Y, MapObj17P2X, MapObj17P2Y);
	putText(canvas, label, Point(20, 190), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj18
	sprintf(label, "Obj18: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj18P1X, MapObj18P1Y, MapObj18P2X, MapObj18P2Y);
	putText(canvas, label, Point(20, 200), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj19
	sprintf(label, "Obj19: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj19P1X, MapObj19P1Y, MapObj19P2X, MapObj19P2Y);
	putText(canvas, label, Point(20, 210), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// obj20
	sprintf(label, "Obj20: (%4.0f, %4.0f) (%4.0f, %4.0f)", MapObj20P1X, MapObj20P1Y, MapObj20P2X, MapObj20P2Y);
	putText(canvas, label, Point(20, 220), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);




	// slot id
	sprintf(label, "slotid: %d %d %d %d", slotid[0], slotid[1], slotid[2], slotid[3]);
	putText(canvas, label, Point(20, 500), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// slot left 1
	sprintf(label, "slot left 1: (%4.0f, %4.0f) (%4.0f, %4.0f)", ApaPscLeftSlot0Obj1X, ApaPscLeftSlot0Obj1Y, ApaPscLeftSlot0Obj2X, ApaPscLeftSlot0Obj2Y);
	putText(canvas, label, Point(20, 510), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	// slot left 2
	sprintf(label, "slot left 2: (%4.0f, %4.0f) (%4.0f, %4.0f)", ApaPscLeftSlot1Obj1X, ApaPscLeftSlot1Obj1Y, ApaPscLeftSlot1Obj2X, ApaPscLeftSlot1Obj2Y);
	putText(canvas, label, Point(20, 520), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);

	// slot right 1
	sprintf(label, "slot right 1: (%4.0f, %4.0f) (%4.0f, %4.0f)", ApaPscRightSlot0Obj1X, ApaPscRightSlot0Obj1Y, ApaPscRightSlot0Obj2X, ApaPscRightSlot0Obj2Y);
	putText(canvas, label, Point(20, 530), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);
	// slot right 2
	sprintf(label, "slot right 1: (%4.0f, %4.0f) (%4.0f, %4.0f)", ApaPscRightSlot1Obj1X, ApaPscRightSlot1Obj1Y, ApaPscRightSlot1Obj2X, ApaPscRightSlot1Obj2Y);
	putText(canvas, label, Point(20, 540), FONT_HERSHEY_SIMPLEX, 0.35, RED, 1, LINE_8, false);


}