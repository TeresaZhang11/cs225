#include "StickerSheet.h"
namespace cs225{
    StickerSheet::StickerSheet(const Image &picture, unsigned max){
        base_ = picture;
        max_ = max;
        picture_ = new Image*[max];
        xC = new unsigned[max];
        yC = new unsigned[max];
        for (unsigned i = 0; i < max_; i++) {
            picture_[i] = nullptr;
        }
    }
    StickerSheet::~StickerSheet(){
        // delete everything in pic, use a loop
        //also delete xC and yC;
        delete[] picture_;
        picture_ = nullptr;
        delete[] xC;
        xC = nullptr;
        delete[] yC;
        yC = nullptr;
    }
    StickerSheet::StickerSheet (const StickerSheet &other){
        base_ = other.base_;
        max_ = other.max_;
        xC = new unsigned[other.max_];
        yC = new unsigned[other.max_];
        picture_ = new Image*[other.max_];
        // copy picture_
        for (unsigned j = 0; j < other.max_; j++) {
            picture_[j] = nullptr;
        }
        for (unsigned i = 0; i < other.max_; i++) {
            if (other.picture_[i] != nullptr) {
                picture_[i] = other.picture_[i];
                xC[i] = other.xC[i];
                yC[i] = other.yC[i];
            }
        }
    }
    const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
        delete[] picture_;
        picture_ = nullptr;
        delete[] xC;
        xC = nullptr;
        delete[] yC;
        yC = nullptr;
        base_ = other.base_;
        max_ = other.max_;
        picture_ = new Image*[max_];
        xC = new unsigned[max_];
        yC = new unsigned[max_];
        // copy picture_
        for (unsigned j = 0; j < max_; j++) {
            picture_[j] = nullptr;
        }
        for (unsigned i = 0; i < max_; i++) {
            picture_[i] = other.picture_[i];
            xC[i] = other.xC[i];
            yC[i] = other.yC[i];
        }
        return *this;
    }
    void StickerSheet::changeMaxStickers(unsigned max){
        // add more stickers
        if (max != max_) {
        
            Image ** stickersNew = new Image*[max];
            unsigned * xNew = new unsigned[max];
            unsigned * yNew = new unsigned[max];
            for (unsigned i = 0; i < max; i++) {
                stickersNew[i] = nullptr;
            }
            if (max > max_) {
            //has nullptr
                for (unsigned j = 0; j < max_; j++) {
                    stickersNew[j] = picture_[j];
                    xNew[j] = xC[j];
                    yNew[j] = yC[j];
                }
            } else if (max < max_){
            // lost pointers
                for (unsigned i = 0; i < max; i++) {
                    stickersNew[i] = picture_[i];
                    xNew[i] = xC[i];
                    yNew[i] = yC[i];
                }
            
            }
            delete[] picture_;
            picture_ = nullptr;
            picture_ = stickersNew;
            max_ = max;
            delete[] xC;
            xC = nullptr;
            xC = xNew;
            delete[] yC;
            yC = nullptr;
            yC = yNew;
        }
    }
    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        for (unsigned i = 0; i < max_; i++) {
            if (picture_[i] == nullptr) {
                xC[i] = x;
                yC[i] = y;
                picture_[i] = &sticker;
                return i;
            }
        }
        return -1;
    }
    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
        
        if (index >= 0 && index < max_ && picture_[index] != nullptr) { 
            xC[index] = x;
            yC[index] = y;
            return true;
        }
        return false;
    }

    void StickerSheet::removeSticker(unsigned index){
        picture_[index] = nullptr;
    }
    Image* StickerSheet::getSticker(unsigned index){
        if (index < 0 || index > max_ || picture_[index] == nullptr) {
            return nullptr;
        }
        return picture_[index];
    }
    Image StickerSheet::render() const{
        // view stickers as points, loacation(x, y)
        // check if the radiu of the points exceeds the base, sticker.width() + x 
        // if exceeds, resize the pic
        Image newI = base_;
        unsigned newHeight = base_.height();
        unsigned newWidth = base_.width();
        for (unsigned int i = 0; i < max_; i++) {
            if (picture_[i] != nullptr) {
                if (xC[i] + picture_[i]->width() > base_.width()) {
                    newWidth = xC[i] + picture_[i]->width();
                }
                if (yC[i] + picture_[i]->height() > base_.height()){
                    newHeight = yC[i] + picture_[i]->height();
                }
            }

        }
        newI.resize(newWidth, newHeight);

        // now add it to the base;
        for (unsigned j = 0; j < max_; j++) {
            if (picture_[j] != nullptr) {
                for (unsigned k = xC[j]; k < (xC[j] + picture_[j] -> width()); k++) {
                    for (unsigned z = yC[j]; z < (yC[j] + picture_[j] -> height()); z++) {
                        // check every pixel.a
                        if (picture_[j]->getPixel(k - xC[j],z - yC[j]).a != 0) {
                            newI.getPixel(k,z) = picture_[j]->getPixel(k - xC[j],z - yC[j]);
                        }
                    }
                }
            } 
            
        }
        return newI;
    }

}