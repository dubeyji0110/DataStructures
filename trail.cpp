#include <windows.h>
#include <sphelper.h>
#include <string>
#include "resource.h"
#define WM_RECOEVENT    WM_USER+1

BOOL CALLBACK DlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void LaunchRecognition(HWND hWnd);
void HandleEvent(HWND hWnd);
WCHAR *ExtractInput(CSpEvent event);
void CleanupSAPI();

CComPtr<ISpRecognizer> g_cpEngine;
CComPtr<ISpRecoContext> g_cpRecoCtx;
CComPtr<ISpRecoGrammar> g_cpRecoGrammar;
WCHAR *lpszBuffer;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // allocating memory for buffer this buffer is used to store
    // the text during the speech recognition process
    lpszBuffer = new WCHAR[MAX_PATH];
    lpszBuffer[0] = 0;

    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
    // freeing the memory that was allocated for the buffer
    delete [] lpszBuffer;
    return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
    case WM_RECOEVENT:
        HandleEvent(hWnd);
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case ID_START_RECOG:
            LaunchRecognition(hWnd);
            break;
        }
        break;
    case WM_CLOSE:
        CleanupSAPI();
        EndDialog(hWnd, 0);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

void LaunchRecognition(HWND hWnd)
{
    if(FAILED(::CoInitialize(NULL)))
    {
        throw std::string("Unable to initialise COM objects");
    }

    ULONGLONG ullGramId = 1;
    HRESULT hr = g_cpEngine.CoCreateInstance(CLSID_SpSharedRecognizer);
    if(FAILED(hr))
    {
        throw std::string("Unable to create recognition engine");
    }
    
    hr = g_cpEngine->CreateRecoContext(&g_cpRecoCtx);
    if(FAILED(hr))
    {
        throw std::string("Failed command recognition");
    }

    hr = g_cpRecoCtx->SetNotifyWindowMessage( hWnd, WM_RECOEVENT, 0, 0 );
    if(FAILED(hr))
    {
        throw std::string("Unable to select notification window");
    }

    const ULONGLONG ullInterest = SPFEI(SPEI_SOUND_START) | SPFEI(SPEI_SOUND_END) |
                                      SPFEI(SPEI_PHRASE_START) | SPFEI(SPEI_RECOGNITION) |
                                      SPFEI(SPEI_FALSE_RECOGNITION) | SPFEI(SPEI_HYPOTHESIS) |
                                      SPFEI(SPEI_INTERFERENCE) | SPFEI(SPEI_RECO_OTHER_CONTEXT) |
                                      SPFEI(SPEI_REQUEST_UI) | SPFEI(SPEI_RECO_STATE_CHANGE) |
                                      SPFEI(SPEI_PROPERTY_NUM_CHANGE) | SPFEI(SPEI_PROPERTY_STRING_CHANGE);
    hr = g_cpRecoCtx->SetInterest(ullInterest, ullInterest);
    if(FAILED(hr))
    {
        throw std::string("Failed to create interest");
    }

    hr = g_cpRecoCtx->CreateGrammar(ullGramId, &g_cpRecoGrammar);
    if(FAILED(hr))
    {
        throw std::string("Unable to create grammar");
    }

    hr = g_cpRecoGrammar->LoadDictation(0, SPLO_STATIC);
    if(FAILED(hr)) 
    {
        throw std::string("Failed to load dictation");
    }
    
    hr = g_cpRecoGrammar->SetDictationState(SPRS_ACTIVE);
    if(FAILED(hr)) 
    {
        throw std::string("Failed setting dictation state");
    }
}

void HandleEvent(HWND hWnd)
{
    CSpEvent event; 
    WCHAR  *pwszText;
    
    // Loop processing events while there are any in the queue
    while (event.GetFrom(g_cpRecoCtx)== S_OK)
    {
        switch (event.eEventId)
        {
        case SPEI_HYPOTHESIS:
            {
                pwszText = ExtractInput(event);
                //MessageBoxW(NULL, pwszText, L"text", MB_ICONERROR);
                wcscat(lpszBuffer, pwszText);
                wcsncat(lpszBuffer, L"\r\n", 2);
                SetDlgItemTextW(hWnd, IDC_EDIT1, lpszBuffer);
            }
            break;
        }
    }
}

WCHAR *ExtractInput(CSpEvent event)
{
    HRESULT                   hr = S_OK;
    CComPtr<ISpRecoResult>    cpRecoResult;
    SPPHRASE                  *pPhrase;
    WCHAR                     *pwszText;

    cpRecoResult = event.RecoResult();

    hr = cpRecoResult->GetPhrase(&pPhrase);

    if (SUCCEEDED (hr))
    {
        if (event.eEventId == SPEI_FALSE_RECOGNITION)
        {
            pwszText = L"False recognition";
            //MessageBoxW(NULL, pwszText, L"text", MB_ICONERROR);
        }
        else
        {
            // Get the phrase's entire text string, including replacements.
            hr = cpRecoResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &pwszText, NULL);
        }
    }
    CoTaskMemFree(pPhrase);
    return pwszText;
}

void CleanupSAPI()
{
    if(g_cpRecoGrammar)
    {
        g_cpRecoGrammar.Release();
    }
    if(g_cpRecoCtx)
    {
        g_cpRecoCtx->SetNotifySink(NULL);
        g_cpRecoCtx.Release();
    }
    if(g_cpEngine)
    {
        g_cpEngine.Release();
    }
    CoUninitialize();
}