/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "cs225/PNG.h"
#include "Image.h"
#include <vector>
#pragma once
namespace cs225{
    class StickerSheet{
    public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet (const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    Image render() const;
    private:
    // an array of pointers but have to know the size to create array
    Image** picture_;
    unsigned max_;
    Image base_;
    unsigned * xC;
    unsigned * yC;
    };
}
#endif
