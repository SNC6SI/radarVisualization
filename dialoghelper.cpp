#include <windows.h>
#define STRICT_TYPED_ITEMIDS
#include <shlobj.h>
#include <objbase.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <knownfolders.h>
#include <propvarutil.h>
#include <propkey.h>
#include <propidl.h>
#include <strsafe.h>
#include <shtypes.h>
#include <wchar.h>
#include <new>
#include <cstdlib>
#include <locale.h>

#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

extern char binlog_filename_read[512];
extern int binlog_filename_read_len;

const COMDLG_FILTERSPEC c_rgSaveTypes[] = {
    {L"Binary Logging Format (*.blf)",       L"*.blf"},
    {L"All Documents (*.*)",                 L"*.*"}
};

// Indices of file types
#define INDEX_BLF 1

class CDialogEventHandler : public IFileDialogEvents, public IFileDialogControlEvents {
public:
    IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv) {
        static const QITAB qit[] = {
            QITABENT(CDialogEventHandler, IFileDialogEvents),
            QITABENT(CDialogEventHandler, IFileDialogControlEvents),
            { 0 },
#pragma warning(suppress:4838)
        };
        return QISearch(this, qit, riid, ppv);
    }

    IFACEMETHODIMP_(ULONG) AddRef() {
        return InterlockedIncrement(&_cRef);
    }

    IFACEMETHODIMP_(ULONG) Release() {
        long cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
            delete this;
        return cRef;
    }
    // IFileDialogEvents methods
    IFACEMETHODIMP OnFileOk(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnFolderChange(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*) { return S_OK; };
    IFACEMETHODIMP OnHelp(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnSelectionChange(IFileDialog*) { return S_OK; };
    IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) { return S_OK; };
    IFACEMETHODIMP OnTypeChange(IFileDialog* pfd);
    IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) { return S_OK; };

    // IFileDialogControlEvents methods
    IFACEMETHODIMP OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem);
    IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize*, DWORD) { return S_OK; };
    IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize*, DWORD, BOOL) { return S_OK; };
    IFACEMETHODIMP OnControlActivating(IFileDialogCustomize*, DWORD) { return S_OK; };

    CDialogEventHandler() : _cRef(1) { };
private:
    ~CDialogEventHandler() { };
    long _cRef;
};

HRESULT CDialogEventHandler::OnTypeChange(IFileDialog* pfd) {
    IFileSaveDialog* pfsd;
    HRESULT hr = pfd->QueryInterface(&pfsd);
    return hr;
}

HRESULT CDialogEventHandler::OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem) {
    IFileDialog* pfd = NULL;
    HRESULT hr = pfdc->QueryInterface(&pfd);
    return hr;
}

HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv) {
    *ppv = NULL;
    CDialogEventHandler* pDialogEventHandler = new (std::nothrow) CDialogEventHandler();
    HRESULT hr = pDialogEventHandler ? S_OK : E_OUTOFMEMORY;
    if (SUCCEEDED(hr)) {
        hr = pDialogEventHandler->QueryInterface(riid, ppv);
        pDialogEventHandler->Release();
    }
    return hr;
}


HRESULT BasicFileOpen() {
    IFileDialog* pfd = NULL;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (SUCCEEDED(hr)) {
            IFileDialogEvents* pfde = NULL;
            hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
            if (SUCCEEDED(hr)) {
                DWORD dwCookie;
                hr = pfd->Advise(pfde, &dwCookie);
                if (SUCCEEDED(hr)) {
                    DWORD dwFlags;
                    hr = pfd->GetOptions(&dwFlags);
                    if (SUCCEEDED(hr)) {
                        hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
                        if (SUCCEEDED(hr)) {
                            hr = pfd->SetTitle(L"Select a blf file to visiuaization");
                            if (SUCCEEDED(hr)) {
                                hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
                                if (SUCCEEDED(hr)) {
                                    hr = pfd->SetFileTypeIndex(INDEX_BLF);
                                    if (SUCCEEDED(hr)) {
                                        hr = pfd->SetDefaultExtension(L"blf");
                                        if (SUCCEEDED(hr)) {
                                            hr = pfd->Show(NULL);
                                            if (SUCCEEDED(hr)) {
                                                IShellItem* psiResult;
                                                hr = pfd->GetResult(&psiResult);
                                                if (SUCCEEDED(hr)) {
                                                    PWSTR pszFilePath = NULL;
                                                    //wchar_t *pszFilePath = NULL;
                                                    hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                                                    if (SUCCEEDED(hr)) {
                                                        setlocale(LC_CTYPE, "");
                                                        binlog_filename_read_len = wcstombs(binlog_filename_read, pszFilePath, 512);
                                                        CoTaskMemFree(pszFilePath);
                                                    }
                                                    psiResult->Release();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    pfd->Unadvise(dwCookie);
                }
                pfde->Release();
            }
            pfd->Release();
        }
    }
    return hr;
}