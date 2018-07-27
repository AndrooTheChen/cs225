#include "Image.h"

void Image::lighten() {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l > .9) {
                pixel.l = 1;
            } else {
                pixel.l += .1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l+amount > 1) {
                pixel.l = 1;
            } else {
                pixel.l += amount;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l < .1 ) {
                pixel.l = 0;
            } else {
                pixel.l -= .1;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.l-amount < 0) {
                pixel.l = 0;
            } else {
                pixel.l -= amount;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s > .9) {
                pixel.s = 1;
            } else {
                pixel.s += .1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s+amount > 1) {
                pixel.s = 1;
            } else {
                pixel.s += amount;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s < .1 ) {
                pixel.s = 0;
            } else {
                pixel.s -= .1;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.s-amount < 0) {
                pixel.s = 0;
            } else {
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned y = 0; y < this->height(); y++) {
        for (unsigned x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned y = 0; y < this->height(); y++) {
        for (unsigned x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.h = ((int)(degrees+pixel.h)) % 361;
        }
    }
}

void Image::illinify() {
    for (unsigned int y = 0; y < this->height(); y++) {
        for (unsigned int x = 0; x < this->width(); x++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.h >= 139 || pixel.h < 294) {
                pixel.h = 216;
            } else {
                pixel.h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    if (factor == 1.0) return;
    int currWidth = this->width();
    int currHeight = this->height();
    this->resize(factor*currWidth, factor*currHeight);
}

void Image::scale(unsigned w, unsigned h) {
    this->resize(w, h);
}