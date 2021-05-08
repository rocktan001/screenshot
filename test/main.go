package main

import (
	"fmt"
	"image/png"
	"os"

	"github.com/rocktan001/screenshot"
)

func main() {
	img, _ := screenshot.Capture(1920, 1080)
	fileName := fmt.Sprintf("%d.bmp", 1)
	file, _ := os.Create(fileName)
	defer file.Close()
	png.Encode(file, img)
}
