/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include "Image.h"
#include <iostream>

using namespace cs225;

class StickerSheet {
public:
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    bool operator==(const StickerSheet & other) const;
    bool operator!=(const StickerSheet & other) const;
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    Image render() const;

private:
    Image background_;
    unsigned size_;
    Image * stickers_;
    void copy_(const StickerSheet & other);
};


#endif
 