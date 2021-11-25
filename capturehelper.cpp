#include "capturehelper.h"

using namespace cv;
VideoCapture capture[2];
int capOpened;

using namespace std;
vector<string> cameraList;
vector<int> cameraSelected;

rv_status query_camera() {
    ICreateDevEnum* pDevEnum = NULL;
    IEnumMoniker* pEnum = NULL;
    CoInitialize(NULL);
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, reinterpret_cast<void**>(&pDevEnum));
    if (SUCCEEDED(hr)) {
        hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
        if (hr == S_OK) {
            IMoniker* pMoniker = NULL;
            while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
                IPropertyBag* pPropBag;
                hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)(&pPropBag));
                if (FAILED(hr)) {
                    pMoniker->Release();
                    continue;
                }
                VARIANT varName;
                VariantInit(&varName);
                hr = pPropBag->Read(L"Description", &varName, 0);
                if (FAILED(hr)) hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                if (SUCCEEDED(hr)) {
                    hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                    int count = 0;
                    char tmp[255] = { 0 };
                    while (varName.bstrVal[count] != 0x00 && count < 255) {
                        tmp[count] = (char)varName.bstrVal[count];
                        count++;
                    }
                    cameraList.push_back(tmp);
                }
                pPropBag->Release();
                pPropBag = NULL;
                pMoniker->Release();
                pMoniker = NULL;
            }
            pDevEnum->Release();
            pDevEnum = NULL;
            pEnum->Release();
            pEnum = NULL;
        }
        return RV_SUCCESS;
    }
    else {
        return RV_FAILURE;
    }
}

void init_capture(void) {
    int i;
    capOpened = 0;
    for (i = 0; i < cameraSelected.size(); i++) {
        capture[i].open(cameraSelected[i], CAP_DSHOW);
        if (capture[i].isOpened()) {
            capOpened = 1;
        }
        
    }
}

void deinit_capture(void) {
    int i;
    for (i = 0; i < cameraSelected.size(); i++) {
        capture[i].release();
    }
}