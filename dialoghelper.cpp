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
#include "menuhelper.h"
#include <vector>
#include <string>

#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

extern char record_folder[512];
extern int record_folder_len;
extern char binlog_filename_read[512];
extern std::vector<std::string> binlog_filename_read_list;
extern int binlog_filename_read_len;
extern std::vector<int> binlog_filename_read_len_list;
extern DWORD num_binlog_files;


static char local_binlog_filename_read[512];
static int local_binlog_filename_read_len;


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


HRESULT BasicFolderOpenSingle() {
    IFileDialog* pfd = NULL;
    IFileDialogEvents* pfde = NULL;
    DWORD dwCookie;
    DWORD dwFlags;
    TCHAR currentDir[512];
    wchar_t wcurrentDir[MAX_PATH];
    PWSTR pszFilePath = NULL;
    IShellItem* psiResult;
    IShellItem* psiFolder;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
    hr = pfd->Advise(pfde, &dwCookie);
    hr = pfd->GetOptions(&dwFlags);
    hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM | FOS_PICKFOLDERS);
    hr = pfd->SetTitle(L"Select a folder to save record...");
    GetCurrentDirectory(MAX_PATH, currentDir);
    mbstowcs(wcurrentDir, currentDir, 512);
    hr = SHCreateItemFromParsingName(wcurrentDir, NULL, IID_PPV_ARGS(&psiFolder));
    hr = pfd->Show(NULL);
    if (SUCCEEDED(hr)) {
        hr = pfd->GetResult(&psiResult);
        hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
        setlocale(LC_CTYPE, "");
        record_folder_len = wcstombs(record_folder, pszFilePath, 512);
        CoTaskMemFree(pszFilePath);
        psiResult->Release();
        pfd->Unadvise(dwCookie);
        pfde->Release();
        pfd->Release();
    }
    return hr;
}


HRESULT BasicFileOpenSingle() {
    IFileDialog* pfd = NULL;
    IFileDialogEvents* pfde = NULL;
    DWORD dwCookie;
    DWORD dwFlags;
    IShellItem* psiResult;
    PWSTR pszFilePath = NULL;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));         
    hr = pfd->Advise(pfde, &dwCookie);        
    hr = pfd->GetOptions(&dwFlags);
    hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
    hr = pfd->SetTitle(L"Select a blf file to visiuaization");
    hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
    hr = pfd->SetFileTypeIndex(INDEX_BLF);
    hr = pfd->SetDefaultExtension(L"blf");
    hr = pfd->Show(NULL);
    if (SUCCEEDED(hr)) {
        hr = pfd->GetResult(&psiResult);
        hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
        setlocale(LC_CTYPE, "");
        binlog_filename_read_len = wcstombs(binlog_filename_read, pszFilePath, 512);
        CoTaskMemFree(pszFilePath);
        psiResult->Release();
        pfd->Unadvise(dwCookie);
        pfde->Release();
        pfd->Release();
    }
    return hr;
}


HRESULT BasicFileOpenMulti() {
    IFileOpenDialog* pfd = NULL;
    DWORD dwFlags = 0;
    IShellItemArray* pShellItem = NULL;
    PWSTR pszFilePath = NULL;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    hr = pfd->GetOptions(&dwFlags);
    hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT);
    hr = pfd->SetTitle(L"Select a blf file to visiuaization");
    hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
    hr = pfd->SetFileTypeIndex(INDEX_BLF);
    hr = pfd->SetDefaultExtension(L"blf");
    hr = pfd->Show(NULL);
    setlocale(LC_CTYPE, "");
    if (hr == S_OK)
    {
        hr = pfd->GetResults(&pShellItem);
        pShellItem->GetCount(&num_binlog_files);
        for (int i = 0; i < num_binlog_files; ++i)
        {
            IShellItem* pItem = NULL;
            hr = pShellItem->GetItemAt(i, &pItem);
            pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
            local_binlog_filename_read_len = wcstombs(local_binlog_filename_read, pszFilePath, 512);
            binlog_filename_read_list.push_back(local_binlog_filename_read);
            binlog_filename_read_len_list.push_back(local_binlog_filename_read_len);
            CoTaskMemFree(pszFilePath);
        }
        pShellItem->Release();
    }
    pfd->Release();
    return hr;
}