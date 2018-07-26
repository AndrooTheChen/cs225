#include "Image.h"

void Image::lighten() {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l > .9) {
                continue;
            } else {
                pixel.l += .1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = getPixel(x, y);
            if (pixel.l+amount > 1) {
                pixel.l = 1;
            } else {
                pixel.l += amount;
            }
        }
    }
}
