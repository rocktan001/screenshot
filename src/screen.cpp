#include <Windows.h>
#include<stdio.h>
#include "interface.h"
extern "C" {
    #include "screen.h"
}

IInterface* pscreen = NULL;
int dw,dh;

int Init(int width, int height) {
    HMODULE hModule = LoadLibrary("Screencapture.dll");
    if (NULL == hModule) {
        printf("load Screencapture.dll error!\n");
        return FALSE;
    }
    dw = width;
    dh = height;
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

void Update(char **ppData, int *psize, int *result) { 
    pscreen->Update(ppData, psize,result);
    //BGRA =>RGBA
      for (int h = 0; h < dh; h++) {
          for (int w = 0; w < dw; w++) {
              char* b = &((char*) *ppData)[h * dw * 4 + w * 4];
              char* r = &((char*) *ppData)[h * dw * 4 + w * 4 + 2];
              // BGRA==>RGBA
              char temp;
              temp = *b;
              *b   = *r;
              *r   = temp;
          }
      }
 }

void Shutdown() { pscreen->Shutdown(); }