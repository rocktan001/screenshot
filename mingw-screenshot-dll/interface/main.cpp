#include <Windows.h>
#include<stdio.h>
#include "interface.h"
#include <tchar.h>
#include <unistd.h>
#include <time.h>
static time_t c_start, c_end;

int _tmain(int argc, _TCHAR* argv[]) {
    HMODULE hModule = LoadLibrary("Screencapture.dll");
    if (NULL == hModule) {
        printf("load Screencapture.dll error!\n");
        return FALSE;
    }

    IInterface* pscreen = NULL;
    typedef void* (*PFUNC_CreateObject)();
    PFUNC_CreateObject pfnCreateObject;

    pfnCreateObject = (PFUNC_CreateObject) GetProcAddress(hModule, "CreateObject");
    if (NULL == pfnCreateObject) {
        printf("GetProcAddress CreateObject eror!\n");
        FreeLibrary(hModule);
        return FALSE;
    }

    pscreen = (IInterface*)pfnCreateObject();
    if (pscreen == NULL) {
        printf("pfnCreateObject error!\n");
        return FALSE;
    }
    c_start       = clock();
    pscreen->Init(1920,1080);

    char* data = NULL;
    int size      = 0;
    int result;
    for(int i=0;i<1000;i++){

        pscreen->Update(&data,&size,&result);
    }
      c_end = clock();
    printf("The pause used %f ms by clock()\n", difftime(c_end, c_start));
    pscreen->Shutdown();
    return TRUE;
}