#include <screencapture/ScreenCapture.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")

static void frame_callback(sc::PixelBuffer& buf);

static int count = 0;
static time_t c_start, c_end;
int main() {
    printf("\n\ntest_api\n\n");
    sc::ScreenCapture capture(frame_callback);
    std::vector<sc::Display*> displays;
    sc::Settings settings;

    if (0 != capture.init()) { exit(EXIT_FAILURE); }

    if (0 != capture.listDisplays()) { exit(EXIT_FAILURE); }

    if (0 != capture.getDisplays(displays)) { exit(EXIT_FAILURE); }

    if (0 != capture.listPixelFormats()) { exit(EXIT_FAILURE); }

    settings.pixel_format  = SC_BGRA;
    settings.display       = 0;
    settings.output_width  = 1920;
    settings.output_height = 1080;

    if (0 != capture.configure(settings)) { exit(EXIT_FAILURE); }

    if (0 != capture.start()) { exit(EXIT_FAILURE); }

    uint8_t* data = NULL;
    int size      = 0;
    bool result;

    c_start       = clock();
    // for (int i = 0; i < 1000000; i++) {
    while(true){
        // capture.update();
        capture.updateV2(&data, &size,&result);
        printf("get size %d\n",size);
    }
    c_end = clock();
    printf("The pause used %f ms by clock()\n", difftime(c_end, c_start));
    capture.shutdown();

    return 0;
}

static void frame_callback(sc::PixelBuffer& buf) {
    // printf("- PixelBuffer.\n");
    count += 1;

    if (count == 1) {
        c_start = clock();
    } else if (count == 100) {
        c_end = clock();
        printf("The pause used %f ms by clock()\n", difftime(c_end, c_start));
        exit(EXIT_FAILURE);
    }
}
