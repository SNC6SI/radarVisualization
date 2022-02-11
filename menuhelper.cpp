#include <stdio.h>
#include <conio.h>
#include "vectorhelper.h"
#include "peakhelper.h"
#include "capturehelper.h"


int selected_mode;
int selected_can_vendor;
int selected_offline_mode;
int selected_offline_display_mode;


static char mode_menu[] = {
    " ========================="
    "\n Select a Mode            "
    "\n ========================="
    "\n  1. online"
    "\n  2. offline"
    "\n\n"
};

void select_mode(void) {
    int ch;
    printf("%s", mode_menu);
    selected_mode = 0;
    while (!selected_mode) {
        fflush(stdin);
        ch = getch();
        printf("  %c\n", ch);
        if (ch == KEY_ESC) {
            selected_mode = 0U;
            break;
        }
        selected_mode = ch - '0';
        if ((selected_mode != 1) && (selected_mode != 2)) {
            selected_mode = 0U;
            printf(" Invalid selection %c...Try again...\n", ch);
        }
    }
}


static char offline_mode_menu[] = {
    "\n ========================="
    "\n Select a Display Mode    "
    "\n ========================="
    "\n  1. display"
    "\n  2. silent"
    "\n\n"
};

void select_offline_mode(void) {
    int ch;
    printf("%s", offline_mode_menu);
    selected_offline_mode = 0;
    while (!selected_offline_mode) {
        fflush(stdin);
        ch = getch();
        printf("  %c\n", ch);
        if (ch == KEY_ESC) {
            selected_offline_mode = 0U;
            break;
        }
        selected_offline_mode = ch - '0';
        if ((selected_offline_mode != 1) && (selected_offline_mode != 2)) {
            selected_offline_mode = 0U;
            printf(" Invalid selection %c...Try again...\n", ch);
        }
    }
}


static char offline_display_mode_menu[] = {
    "\n ========================="
    "\n Select a Display Mode    "
    "\n ========================="
    "\n  1. display only"
    "\n  2. display and video"
    "\n\n"
};

void select_offline_display_mode(void) {
    int ch;
    printf("%s", offline_display_mode_menu);
    selected_offline_display_mode = 0;
    while (!selected_offline_display_mode) {
        fflush(stdin);
        ch = getch();
        printf("  %c\n", ch);
        if (ch == KEY_ESC) {
            selected_offline_display_mode = 0U;
            break;
        }
        selected_offline_display_mode = ch - '0';
        if ((selected_offline_display_mode != 1) && (selected_offline_display_mode != 2)) {
            selected_offline_display_mode = 0U;
            printf(" Invalid selection %c...Try again...\n", ch);
        }
    }
}


static char can_menu[] = {
    " ========================="
    "\n Available Can Devices    "
    "\n ========================="
    "\n"
};

void show_can_channel(void) {
    unsigned int i;
    int ch;
    int xlChannelMaskPre;
    system("cls");
    printf("%s", can_menu);
    printf("%s\n", "VECTOR");
    g_xlChannelMask = 0;
    for (i = 0; i < g_xlDrvConfig.channelCount; i++) {
        printf("%3d. %s\n", i + 1, g_xlDrvConfig.channel[i].name);
        if (g_xlDrvConfig.channel[i].busParams.busType == XL_BUS_TYPE_CAN) {
            g_xlChannelMask |= g_xlDrvConfig.channel[i].channelMask;
        }
    }
    printf("\n");
    printf("%s\n", "PEAK");
    for (i = 0 ; i < g_peakDrvConfig.channelCount; i++) {
        printf("%3d. %s\n", i + 1, g_peakDrvConfig.channel[i].name);
    }
    printf("\n");
#if 0
    xlChannelMaskPre = 0U;
    printf("\nPlease select one:\n\n");
    while (!xlChannelMaskPre) {
        fflush(stdin);
        ch = getch();
        printf("  %c\n", ch);
        xlChannelMaskPre = ch - '0';
        if (!((xlChannelMaskPre > 0) && (xlChannelMaskPre < g_xlDrvConfig.channelCount + 1))) {
            xlChannelMaskPre = 0U;
            printf(" Invalid selection %c...Try again...\n", ch);
        }
    }
    xlChannelMaskPre = xlChannelMaskPre - 1;
    printf("%s is selected.\n", g_xlDrvConfig.channel[xlChannelMaskPre].name);
    g_xlChannelMask = g_xlDrvConfig.channel[xlChannelMaskPre].channelMask;
#endif
}


static char can_vendor_menu[] = {
    " ========================="
    "\n Available Can Vendors    "
    "\n ========================="
    "\n"
};


void select_can_vendor(void) {
    int ch;
    printf("%s", can_vendor_menu);
    if (g_xlDrvConfig.channelCount > 0 && g_peakDrvConfig.channelCount > 0) {
        printf("%3d. %s\n", 1, "VECTOR");
        printf("%3d. %s\n", 2, "PEAK");
        selected_can_vendor = 0;
        while (!selected_can_vendor) {
            fflush(stdin);
            ch = getch();
            printf("  %c\n", ch);
            selected_can_vendor = ch - '0';
            if ((selected_can_vendor != 1) && (selected_can_vendor != 2)) {
                selected_can_vendor = 0U;
                printf(" Invalid selection %c, Try again.\n", ch);
            }
        }
    }
    
}


static char camera_menu[] = {
    "\n"
    "\n ========================="
    "\n Available Camera         "
    "\n ========================="
    "\n"
};

void select_camera(void) {
    int i;
    int ch;
    int selectednum;
    printf("%s", camera_menu);
    for (i = 0; i < cameraList.size(); i++) {
        printf("%3d. %s\n", i + 1, cameraList[i].c_str());
    }
    if (i == 0) {
        printf("No camera is available, proceeding without camera...\n");
    }
    else {
        printf("\nPlease select at most two cameras, or press 'ESC' to proceeding without camera...\n");
        selectednum = 0U;
        while (cameraSelected.size() < std::min((int)cameraList.size(), 2)) {
            if (cameraSelected.size() == 1) {
                printf("\nPlease select one more camera, or press 'ESC' to end selection...\n\n");
            }
            fflush(stdin);
            ch = getch();
            printf("  %c\n", ch);
            if (ch == KEY_ESC) {
                break;
            }
            else {
                selectednum = ch - '0';
                if (!((selectednum > 0) && (selectednum < cameraList.size() + 1))) {
                    printf(" Invalid selection %c...Try again...\n", ch);
                }
                else {
                    printf("%s is selected.\n", cameraList[selectednum - 1].c_str());
                    cameraSelected.push_back(selectednum-1);
                }
            }

        }
    }

}
