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
            //pixel.h = ((int)(degrees+pixel.h)) % 361;
            if (pixel.h+degrees > 360) {
                pixel.h = (pixel.h+degrees)-360;
            } else if (pixel.h+degrees < 0) {
                pixel.h = (pixel.h+degrees)+360;
            } else {
                pixel.h = pixel.h+degrees;
            }
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

    PNG * original = new PNG(*this);
    unsigned int oldWidth = this->width(), oldHeight = this->height();
    this->resize(factor*oldWidth, factor*oldHeight);

    unsigned int newX = 0, newY = 0;
    for (unsigned int y = 0; y < oldHeight; y++) {
        for (unsigned int x = 0; x < oldWidth; x++) {
            if (factor > 1.0) {
                for (unsigned int tempY = y*factor; tempY < (y+1)*factor; tempY++) {
                    for (unsigned int tempX = x*factor; tempX < (x+1)*factor; tempX++) {
                        HSLAPixel & oldPixel = original->getPixel(x, y);
                        HSLAPixel & newPixel = this->getPixel(tempX, tempY);

                        newPixel.h = oldPixel.h;
                        newPixel.s = oldPixel.s;
                        newPixel.l = oldPixel.l;
                    }
                }
            } else {
                while (x*factor == newX && x < oldWidth) { 
                    newX = x*factor;
                    HSLAPixel & oldPixel = original->getPixel(x, y);
                    HSLAPixel & newPixel = this->getPixel(newX, y);
                    newPixel.h = oldPixel.h;
                    newPixel.s = oldPixel.s;
                    newPixel.l = oldPixel.l;
                    x++; 
                }
                
                while (y*factor == newY && y < oldHeight) { 
                    newY = y*factor;
                    HSLAPixel & oldPixel = original->getPixel(x, y);
                    HSLAPixel & newPixel = this->getPixel(x, newY);
                    newPixel.h = oldPixel.h;
                    newPixel.s = oldPixel.s;
                    newPixel.l = oldPixel.l;
                    y++;
                }
            }
        }
        newX = 0;
        newY++;
    }
}

void Image::scale(unsigned w, unsigned h) {
    this->resize(w, h);
}