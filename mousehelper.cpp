#include <iostream>
#include <opencv2/opencv.hpp>
#include "rv_param.h"
#include "signalhelper.h"
#include "plothelper.h"

using namespace std;
using namespace cv;

unsigned char LBUTTONDOWN_flg = 0;
static unsigned char MBUTTONDOWN_flg = 0;

int x_anno, y_anno;
static int x_ud, y_ud;
static int measureStatus;
static float xf, yf;
static vector<float> x_meas, y_meas;
vector<float> x_meas_label, y_meas_label;
vector<float> meas_dist;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void init_measure_status(void) {
    measureStatus = 0;
}

void toggle_measure_status(void) {
    measureStatus = !measureStatus;
}

int query_measure_status(void) {
    return measureStatus;
}

int query_measure_data_size(void) {
    return x_meas.size();
}

void empty_measure_data(void){
    x_meas.clear();
    y_meas.clear();
    x_meas_label.clear();
    y_meas_label.clear();
    meas_dist.clear();
}


void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata) {
    if (query_measure_status()) {
        LBUTTONDOWN_flg = 0;
        if (event == EVENT_LBUTTONDOWN) {
            x_meas.push_back((float)x);
            y_meas.push_back((float)y);
            xf = (float)x;
            yf = (float)y;
            point2pose(&xf, &yf, 1);
            x_meas_label.push_back(xf);
            y_meas_label.push_back(yf);
            int numPoints = query_measure_data_size();
            if(numPoints%2==0){
                meas_dist.push_back(sqrt((x_meas_label[numPoints-1] - x_meas_label[numPoints-2]) * (x_meas_label[numPoints-1] - x_meas_label[numPoints-2]) +
                    (y_meas_label[numPoints - 1] - y_meas_label[numPoints - 2]) * (y_meas_label[numPoints - 1] - y_meas_label[numPoints - 2])));
            }
        }
    }
    else {
        empty_measure_data();
        if (event == EVENT_LBUTTONDOWN) {
            LBUTTONDOWN_flg = 1;
            x_anno = x;
            y_anno = y;
        }
        else if (event == EVENT_LBUTTONUP) {
            LBUTTONDOWN_flg = 0;
        }
        if (LBUTTONDOWN_flg) {
            if (event == EVENT_MOUSEMOVE) {
                x_anno = x;
                y_anno = y;
            }
        }
    }


    if (event == EVENT_MBUTTONDOWN) {
        MBUTTONDOWN_flg = 1;
        x_ud = x;
        y_ud = y;
    }
    else if (event == EVENT_MBUTTONUP) {
        MBUTTONDOWN_flg = 0;
    }
    if (MBUTTONDOWN_flg) {
        if (event == EVENT_MOUSEMOVE) {
            X0 += (x - x_ud);
            Y0 += (y - y_ud);
            x_ud = x;
            y_ud = y;
        }
    }


    if (event == EVENT_MOUSEWHEEL) {
        if (sgn(flags) < 0) {      // zoom out
            gScale -= SCALESTEP;
            if (y > Y0) {
                Y0 += ORIGINSTEP;
            }
            else if (y < Y0) {
                Y0 -= ORIGINSTEP;
            }
        }
        else if (sgn(flags) > 0) { // zoom in
            gScale += SCALESTEP;
            if (y > Y0) {
                Y0 -= ORIGINSTEP;
            }
            else if (y < Y0) {
                Y0 += ORIGINSTEP;
            }
        }
        else {
            printf("interesting \n");
        }
    }
}
