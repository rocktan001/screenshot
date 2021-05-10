#include "interface.h"

#include <screencapture/ScreenCapture.h>

#include <iostream>
using namespace std;

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")

static void frame_callback(sc::PixelBuffer& buf);
static sc::ScreenCapture capture(frame_callback);

class IInterfaceScreenCapture : public IInterface {
   public:
    virtual void Init(int width,int height);
    virtual void Update(char **ppData, int *psize,int *result);
    virtual void Shutdown();
};

void IInterfaceScreenCapture::Init(int width, int height) {

    std::vector<sc::Display*> displays;
    sc::Settings settings;

    if (0 != capture.init()) { exit(EXIT_FAILURE); }

    if (0 != capture.listDisplays()) { exit(EXIT_FAILURE); }

    if (0 != capture.getDisplays(displays)) { exit(EXIT_FAILURE); }

    if (0 != capture.listPixelFormats()) { exit(EXIT_FAILURE); }

    settings.pixel_format  = SC_BGRA;
    settings.display       = 0;
    settings.output_width  = width;
    settings.output_height = height;

    if (0 != capture.configure(settings)) { exit(EXIT_FAILURE); }

    if (0 != capture.start()) { exit(EXIT_FAILURE); }
}
void IInterfaceScreenCapture::Shutdown() { capture.shutdown(); }


void IInterfaceScreenCapture::Update(char **ppData, int *psize,int *result) {
 capture.updateV2((uint8_t**)ppData,psize,(bool*)result); 
}

static void frame_callback(sc::PixelBuffer& buf) {

}
//导出接口
extern "C" {
__declspec(dllexport) void* CreateObject() { return new IInterfaceScreenCapture(); }
}