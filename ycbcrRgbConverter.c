#include <stdio.h>
//based on https://en.wikipedia.org/wiki/YCbCr
struct YCrCbColor {
    double Y;
    double Cb;
    double Cr;
};

struct RGBColor {
    double r;
    double b;
    double g;
};

typedef struct YCrCbColor YCrCbColor;
typedef struct RGBColor RGBColor;

YCrCbColor rgbToYCbCr(RGBColor rgbColor) {
    double r = rgbColor.r;
    double b = rgbColor.b;
    double g = rgbColor.g;

    YCrCbColor color;
    color.Y  =  16 + ( 65.738 * r / 256) + (129.057 * g / 256) + ( 25.064 * b / 256);
    color.Cb = 128 - ( 37.945 * r / 256) - ( 74.494 * g / 256) + (112.439 * b / 256);
    color.Cr = 128 + (112.439 * r / 256) - ( 94.154 * g / 256) + ( 18.285 * b / 256);

    return color;
}

RGBColor YCbCrToRgb(YCrCbColor yCbCrColor) {
    double y = yCbCrColor.Y;
    double Cr = yCbCrColor.Cr;
    double Cb = yCbCrColor.Cb;

    RGBColor color;
    color.r = (298.082 * y / 256) + (408.583 * Cr / 256) - 222.921;
    color.g = (298.082 * y / 256) - (100.291 * Cb / 256) + 135.576;
    color.b = (298.082 * y / 256) + (516.412 * Cb / 256) - 276.836;

    return color;
}

void printRgb(RGBColor color) {
    printf("R: %x\n",(unsigned char) color.r);
    printf("G: %x\n",(unsigned char) color.g);
    printf("B: %x\n",(unsigned char) color.b);
}

void printYCrCb(YCrCbColor color) {
    printf("Y: %x\n",(unsigned char) color.Y);
    printf("Cr: %x\n",(unsigned char) color.Cr);
    printf("Cb: %x\n",(unsigned char) color.Cb);
}

int main() {
    RGBColor rgbColor;
    rgbColor.r = 23;
    rgbColor.g = 50;
    rgbColor.b = 54;
    printRgb(rgbColor);

    YCrCbColor ycc = rgbToYCbCr(rgbColor);
    printYCrCb(ycc);

    RGBColor newRgbColor = YCbCrToRgb(ycc);
    printRgb(rgbColor);
}
