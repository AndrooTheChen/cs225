#include "StickerSheet.h"


void StickerSheet::copy_(const StickerSheet & other) {
    // clear stickers_
    delete background_;
    for (std::vector<Image *>::iterator it = stickers_.begin(); it != stickers_.end(); it++) {
        delete *it;
    }

    background_ = other.background_;
    size_ = other.size_;

    // copy other stickers_ into current stickers_
    for (unsigned ctr = 0; ctr < size_; ctr++) {
        stickers_.push_back(other.stickers_[ctr]);
    }
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    background_ = new Image();
    background_ = &picture;
    size_ = max;
}

StickerSheet::~StickerSheet() {
    delete background_;
    for (std::vector<Image *>::iterator it = stickers_.begin(); it != stickers_.end(); it++) {
        delete *it;
    }
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this != &other) { copy_(other); }
    return *this;
}

bool StickerSheet::operator==(const StickerSheet & other) const {
    if (background_ != other.background_) { return false; }
    if (size_ != other.size_) { return false; }
    for (unsigned ctr = 0; ctr < size_; ctr++) {
        Image & other_image = *(other.stickers_[ctr]);
        Image & this_image = *(stickers_[ctr]);
        if (other_image != this_image) { return false; }
    }
    return true;
}

bool StickerSheet::operator!=(const StickerSheet & other) const {
    return !(*this != other);
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max >= size_) { return; }
    int diff = size_-max;
    size_ = max;

    std::vector<Image *>::iterator sticker = stickers_.end();
    for (int ctr = 0; ctr < diff; ctr++) {
        delete *sticker;
        sticker--;

        xcoord_.pop_back();
        ycoord_.pop_back();
    }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    if (stickers_.size() == size_) { return -1; }

    xcoord_.push_back(x);
    ycoord_.push_back(y);
    Image * sticky = new Image();
    sticky = &sticker;
    stickers_.push_back(sticky);
    return stickers_.size()-1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= size_) { return false; }
    xcoord_[index] = x;
    ycoord_[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    xcoord_.erase(xcoord_.begin()+(index-1));
    ycoord_.erase(ycoord_.begin()+(index-1));
    delete stickers_[index];
    stickers_.erase(stickers_.begin()+(index-1));
}

Image * StickerSheet::getSticker(unsigned index) const {
    return stickers_[index];
}

Image StickerSheet::render() const {
    Image sticky, output;
    output = *background_;
    for (unsigned ctr = 0; ctr < stickers_.size(); ctr++) {
	      std::cout << "Copying sticker from sticker list" << std::endl;
        sticky = *getSticker(ctr);
	      std::cout << "Copied sticker from sticker list" << std::endl;
        int x_sticky = 0, y_sticky = 0;
        for (unsigned int y = ycoord_[ctr]; y < ycoord_[ctr]+sticky.height(); y++) {
            for (unsigned int x = xcoord_[ctr]; x < xcoord_[ctr]+sticky.width(); x++) {
                HSLAPixel & pic_pixel = output.getPixel(x, y);
                HSLAPixel & sticky_pixel = sticky.getPixel(x_sticky++, y_sticky);
                if (sticky_pixel.a == 0) { continue; }
                pic_pixel = sticky_pixel;
            }
            x_sticky = 0;
            y_sticky++;
        }
    }
    std::cout << "render() complete " << std::endl;
    return output;
}
