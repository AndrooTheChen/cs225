#include "StickerSheet.h"


void StickerSheet::copy_(const StickerSheet & other) {
    delete [] stickers_;
    background_ = other.background_;
    size_ = other.size_;
    stickers_ = new Image[size_];
    for (int ctr = 0; ctr < size_; ctr++) {
        stickers_[ctr] = other.stickers_[ctr];
    }
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    background_ = picture;
    size_ = max;
    stickers_ = new Image[size_];
    for (int ctr = 0; ctr < size_; ctr++) {
        stickers_[ctr] = NULL;
    }
}

StickerSheet::~StickerSheet() {
    delete [] stickers_;
    stickers_ = NULL;
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    stickers_ = NULL;
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
        Image & other_image = other.stickers_[ctr];
        Image & this_image = stickers_[ctr];
        if (other_image != this_image) { return false; }
    }
}

bool StickerSheet::operator!=(const StickerSheet & other) const {
    return !(*this != other);
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max >= size_) { return; }
    size_ = max;

    Image * temp = stickers_;
    stickers_ = new Image[size_];
    for (int ctr = 0; ctr < size_; ctr++) {
        stickers_[ctr] = temp[ctr];
    }

    delete [] temp;
}