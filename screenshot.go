package screenshot

//#cgo CXXFLAGS: -I/usr/lib/
//#cgo CFLAGS: -I${SRCDIR}/include
//#cgo CXXFLAGS: -I${SRCDIR}/include
//#cgo windows,amd64 LDFLAGS: ${SRCDIR}/lib/libscreen.a -lstdc++
// #include "screen.h"
/*
struct Frame {
    char* pFrame;
    int pSize;
    int result;
};
*/
import "C"
import (
	"image"
	"reflect"
	"unsafe"

	"github.com/kbinani/screenshot"
)

func init() {
	bounds := screenshot.GetDisplayBounds(0)
	C.Init(C.int(bounds.Dx()), C.int(bounds.Dy()))
}

func Capture(width, height int) (*image.RGBA, error) {
	f := &C.struct_Frame{}
	rect := image.Rect(0, 0, width, height)
	img := image.NewRGBA(rect)

	for {

		C.Update(&f.pFrame, &f.pSize, &f.result)
		if f.result == 1 {
			break
		}
	}
	var buf []byte
	hdr := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	hdr.Data = uintptr(unsafe.Pointer(f.pFrame))
	hdr.Len = int(f.pSize)
	hdr.Cap = int(f.pSize)
	copy(img.Pix, buf)
	return img, nil
}

func Shutdown() {
	C.Shutdown()
}
