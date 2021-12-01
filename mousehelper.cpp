#include <iostream>
#include <opencv2/opencv.hpp>
#include "rv_param.h"
#include "signalhelper.h"

using namespace std;
using namespace cv;

unsigned char LBUTTONDOWN_flg = 0;
static unsigned char MBUTTONDOWN_flg = 0;
int x_anno, y_anno;
static int x_ud, y_ud;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        LBUTTONDOWN_flg = 1;
        x_anno = x;
        y_anno = y;
    }
    else if (event == EVENT_LBUTTONUP) {
        LBUTTONDOWN_flg = 0;
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
