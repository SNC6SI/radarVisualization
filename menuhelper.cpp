#include <stdio.h>
#include <conio.h>
#include "vectorhelper.h"
#include "capturehelper.h"

//#include <vector>

static char can_menu[] = {
    " ========================="
    "\n Available Vector Can     "
    "\n ========================="
    "\n"
};

void select_can_channel(void) {
    unsigned int i;
    int ch;
    int xlChannelMaskPre;
    system("cls");
    printf("%s", can_menu);
    for (i = 0; i < g_xlDrvConfig.channelCount; i++) {
        printf("%3d, %s\n", i + 1, g_xlDrvConfig.channel[i].name);
    }
    xlChannelMaskPre = 0U;
    printf("\nPlease select one:\n");
    while (!xlChannelMaskPre) {
        fflush(stdin);
        ch = getch();
        printf("%c\n", ch);
        xlChannelMaskPre = ch - '0';
        if (!((xlChannelMaskPre > 0) && (xlChannelMaskPre < g_xlDrvConfig.channelCount + 1))) {
            xlChannelMaskPre = 0U;
            printf("Invalid selection %c. Try again.\n", ch);
        }
    }
    xlChannelMaskPre = xlChannelMaskPre - 1;
    printf("%s is selected.\n", g_xlDrvConfig.channel[xlChannelMaskPre].name);
    g_xlChannelMask = g_xlDrvConfig.channel[xlChannelMaskPre].channelMask;
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
        printf("%3d, %s\n", i + 1, cameraList[i].c_str());
    }
    if (i == 0) {
        printf("No camera is available, proceeding without camera...\n");
    }
    else {
        printf("\nPlease select at most two cameras, or press 'ESC' to proceeding without camera...\n");
        selectednum = 0U;
        while (cameraSelected.size() != 2) {
            if (cameraSelected.size() == 1) {
                printf("\nPlease select one more camera, or press 'ESC' to end selection...\n");
            }
            fflush(stdin);
            ch = getch();
            printf("%c\n", ch);
            if (ch == KEY_ESC) {
                break;
            }
            else {
                selectednum = ch - '0';
                if (!((selectednum > 0) && (selectednum < cameraList.size() + 1))) {
                    printf("Invalid selection %c. Try again.\n", ch);
                }
                else {
                    printf("%s is selected.\n", cameraList[selectednum - 1].c_str());
                    cameraSelected.push_back(selectednum-1);
                }
            }

        }
    }

}
