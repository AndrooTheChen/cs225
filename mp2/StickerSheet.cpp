#include "StickerSheet.h"


void StickerSheet::copy_(const StickerSheet & other) {
    // clear stickers_
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
    background_ = picture;
    size_ = max;
}

StickerSheet::~StickerSheet() {
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
    for (int ctr = 0; ctr < size_; ctr++) {
        Image & other_image = *(other.stickers_[ctr]);
        Image & this_image = *(stickers_[ctr]);
        if (other_image != this_image) { return false; }
    }
}

bool StickerSheet::operator!=(const StickerSheet & other) const {
    return !(*this != other);
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max >= size_) { return; }
    int diff = size_-max;
    size_ = max;

    std::vector<Image *>::iterator sticker = stickers_.end();
    for (unsigned ctr = 0; ctr < diff; ctr++) {
        delete *sticker;
        sticker--;

        xcoord_.pop_back();
        ycoord_.pop_back();
    }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    xcoord_.push_back(x);
    ycoord_.push_back(y);
    
    int capacity = stickers_.size();
    stickers_.push_back(&sticker);
    if (capacity != stickers_.size()) {
        return -1;
    } else {
        size_++;
        return stickers_.size()-1;
    }
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
    size_--;
}

Image * StickerSheet::getSticker(unsigned index) const {
    return stickers_[index];
}

Image StickerSheet::render() const {
    Image sticky, output = background_;
    for (int ctr = 0; ctr < size_; ctr++) {
        sticky = *getSticker(ctr);
        for (unsigned int y = 0; y < sticky.height(); y++) {
            for (unsigned int x = 0; x < sticky.width(); x++) {
                HSLAPixel & pic_pixel = output.getPixel(x, y);
                HSLAPixel & sticky_pixel = sticky.getPixel(x, y);
                pic_pixel = sticky_pixel;
            }
        }
    }

    return output;
}

