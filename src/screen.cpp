#include <Windows.h>
#include<stdio.h>
#include "interface.h"
extern "C" {
    #include "screen.h"
}

IInterface* pscreen = NULL;


int Init(int width, int height) {
    HMODULE hModule = LoadLibrary("Screencapture.dll");
    if (NULL == hModule) {
        printf("load Screencapture.dll error!\n");
        return FALSE;
    }

    typedef void* (*PFUNC_CreateObject)();
    PFUNC_CreateObject pfnCreateObject;

    pfnCreateObject = (PFUNC_CreateObject) GetProcAddress(hModule, "CreateObject");
    if (NULL == pfnCreateObject) {
        printf("GetProcAddress CreateObject eror!\n");
        FreeLibrary(hModule);
        return FALSE;
    }

    pscreen = (IInterface*) pfnCreateObject();
    if (pscreen == NULL) {
        printf("pfnCreateObject error!\n");
        return FALSE;
    }

    pscreen->Init(width, height);
}

void Start() { pscreen->Start(); }

void Update(char **ppData, int *psize) { pscreen->Update(ppData, psize); }

void Shutdown() { pscreen->Shutdown(); }