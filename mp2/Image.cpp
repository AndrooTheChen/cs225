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
    // else if (factor < 1.0) {
    //     PNG * copy = new PNG(*this);
    //     unsigned int oldWidth = factor*this->width();
    //     unsigned int oldHeight = factor*this->height();
        
    //     this->resize(factor*oldWidth, factor*oldHeight);

    //     int scale = 1/factor, newX = 0, newY = 0;
    //     for (unsigned int oldY = 0; oldY < oldHeight; oldY+=scale) {
    //         for (unsigned int oldX = 0; oldX < oldWidth; oldX+=scale) {
    //             HSLAPixel & oldPixel = copy->getPixel(oldX, oldY);
    //             HSLAPixel & newPixel = this->getPixel(newX, newY);

    //             newPixel.h = oldPixel.h;
    //             newPixel.l = oldPixel.l;
    //             newPixel.s = oldPixel.s;

    //             newX++;
    //         }
    //         newX = 0;
    //         newY++;
    //     }
    //     delete copy;
    // } else {
    //     PNG * copy = new PNG(*this);
    //     unsigned int oldWidth = factor*this->width();
    //     unsigned int oldHeight = factor*this->height();
        
    //     this->resize(factor*oldWidth, factor*oldHeight);

    //     int scale = factor, oldX = 0, oldY = 0;
    //     for (int newY = 0; newY < this->height(); newY+= scale) {
    //         for (int newX = 0; newX < this->width(); newX+= scale) {
    //             HSLAPixel & oldPixel = copy->getPixel(oldX, oldY);
    //             HSLAPixel & newPixel = this->getPixel(newX, newY);

    //             newPixel.h = oldPixel.h;
    //             newPixel.l = oldPixel.l;
    //             newPixel.s = oldPixel.s;

    //             oldX++;
    //         }
    //         oldX = 0;
    //         oldY++;
    //     }

    //     for (int newY = 1; newY < this->height(); newY+=scale) {
    //         for (int newX = 1; newX < this->width(); newX+=scale) {
    //             HSLAPixel & newPixel = this->getPixel(newX, newY);
    //             if (newX > 0 && newX < this->width()-2 && newY > 0 && newY < this->height()-2) {
    //                 HSLAPixel & lpixel = this->getPixel(newX-1, newY);
    //                 HSLAPixel & rpixel = this->getPixel(newX+1, newY);
    //                 HSLAPixel & upixel = this->getPixel(newX, newY-1);
    //                 HSLAPixel & dpixel = this->getPixel(newX, newY+1);

    //                 newPixel.h = (lpixel.h+rpixel.h+upixel.h+dpixel.h)/4;
    //                 newPixel.l = (lpixel.l+rpixel.l+upixel.l+dpixel.l)/4;
    //                 newPixel.s = (lpixel.s+rpixel.s+upixel.s+dpixel.s)/4;
    //             } else if (newX < this->width()-2 && newY > 0 && newY < this->height()-2) {
    //                 HSLAPixel & rpixel = this->getPixel(newX+1, newY);
    //                 HSLAPixel & upixel = this->getPixel(newX, newY-1);
    //                 HSLAPixel & dpixel = this->getPixel(newX, newY+1);

    //                 newPixel.h = (rpixel.h+upixel.h+dpixel.h)/3;
    //                 newPixel.l = (rpixel.l+upixel.l+dpixel.l)/3;
    //                 newPixel.s = (rpixel.s+upixel.s+dpixel.s)/3;
    //             } else if (newX > 0 && newY > 0 && newY < this->height()-2) {
    //                 HSLAPixel & lpixel = this->getPixel(newX-1, newY);
    //                 HSLAPixel & upixel = this->getPixel(newX, newY-1);
    //                 HSLAPixel & dpixel = this->getPixel(newX, newY+1);

    //                 newPixel.h = (lpixel.h+upixel.h+dpixel.h)/3;
    //                 newPixel.l = (lpixel.l+upixel.l+dpixel.l)/3;
    //                 newPixel.s = (lpixel.s+upixel.s+dpixel.s)/3;
    //             } else if (newX > 0 && newX < this->width()-2 && newY < this->height()-2) {
    //                 HSLAPixel & lpixel = this->getPixel(newX-1, newY);
    //                 HSLAPixel & rpixel = this->getPixel(newX+1, newY);     
    //                 HSLAPixel & dpixel = this->getPixel(newX, newY+1);

    //                 newPixel.h = (lpixel.h+rpixel.h+dpixel.h)/3;
    //                 newPixel.l = (lpixel.l+rpixel.l+dpixel.l)/3;
    //                 newPixel.s = (lpixel.s+rpixel.s+dpixel.s)/3;
    //             } else if (newX > 0 && newX < this->width()-2 && newY > 0) {
    //                 HSLAPixel & lpixel = this->getPixel(newX-1, newY);
    //                 HSLAPixel & rpixel = this->getPixel(newX+1, newY);
    //                 HSLAPixel & upixel = this->getPixel(newX, newY-1);

    //                 newPixel.h = (lpixel.h+rpixel.h+upixel.h)/3;
    //                 newPixel.l = (lpixel.l+rpixel.l+upixel.l)/3;
    //                 newPixel.s = (lpixel.s+rpixel.s+upixel.s)/3;
    //             } else if (newX < this->width() && newY < this->height()) {
    //                 HSLAPixel & rpixel = this->getPixel(newX+1, newY);
    //                 HSLAPixel & dpixel = this->getPixel(newX, newY+1);

    //                 newPixel.h = (rpixel.h+dpixel.h)/2;
    //                 newPixel.l = (rpixel.l+dpixel.l)/2;
    //                 newPixel.s = (rpixel.s+dpixel.s)/2;
    //             } else if (newX > 0 && newY < this->height()) {
    //                 HSLAPixel & lpixel = this->getPixel(newX-1, newY);
    //                 HSLAPixel & dpixel = this->getPixel(newX, newY+1);

    //                 newPixel.h = (lpixel.h+dpixel.h)/2;
    //                 newPixel.l = (lpixel.l+dpixel.l)/2;
    //                 newPixel.s = (lpixel.s+dpixel.s)/2;
    //             } else if (newX < this->width() && newY > 0) {
    //                 HSLAPixel & rpixel = this->getPixel(newX+1, newY);
    //                 HSLAPixel & upixel = this->getPixel(newX, newY-1);

    //                 newPixel.h = (rpixel.h+upixel.h)/2;
    //                 newPixel.l = (rpixel.l+upixel.l)/2;
    //                 newPixel.s = (rpixel.s+upixel.s)/2;
    //             } else if (newX > 0 && newY > 0) {
    //                 HSLAPixel & lpixel = this->getPixel(newX-1, newY);
    //                 HSLAPixel & upixel = this->getPixel(newX, newY-1);

    //                 newPixel.h = (lpixel.h+upixel.h)/2;
    //                 newPixel.l = (lpixel.l+upixel.l)/2;
    //                 newPixel.s = (lpixel.s+upixel.s)/2;
    //             }

    //         }
    //     }
    //}
    PNG * original = new PNG(*this);
    unsigned int oldWidth = this->width(), oldHeight = this->height();
    this->resize(factor*oldWidth, factor*oldHeight);

    unsigned int newX = 0, newY = 0;
    for (unsigned int y = 0; y < oldHeight; y++) {
        for (unsigned int x = 0; x < oldWidth; x++) {
            if (factor > 1.0) {
                int tempX = x*factor;
                while (tempX < factor*(x+1)) {
                    HSLAPixel & oldPixel = original->getPixel(x, y);
                    HSLAPixel & newPixel = this->getPixel(tempX++, y);

                    newPixel.h = oldPixel.h;
                    newPixel.s = oldPixel.s;
                    newPixel.l = oldPixel.l;
                }

                int tempY = y*factor;
                while (tempY < factor*(y+1)) {
                    HSLAPixel & oldPixel = original->getPixel(x, y);
                    HSLAPixel & newPixel = this->getPixel(x, tempY++);

                    newPixel.h = oldPixel.h;
                    newPixel.s = oldPixel.s;
                    newPixel.l = oldPixel.l;
                }
                newX++;
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