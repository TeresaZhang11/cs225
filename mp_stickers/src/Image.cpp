#include "Image.h"
#include <math.h>
namespace cs225 {
    void Image::lighten(){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.l += 0.1;
                if (p.l > 1){
                    p.l = 1;
                }
            }
        }
    }
    void Image::lighten(double amount){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++){
                HSLAPixel & p = getPixel(i,j);
                p.l += amount;
                if (p.l > 1){
                    p.l = 1;
                }
            }
        }
    }
    void Image::darken(){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.l -= 0.1;
                if (p.l < 0){
                    p.l = 0;
                }
            }
        }
    }
    void Image::darken(double amount){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.l -= amount;
                if (p.l < 0){
                    p.l = 0;
                }
            }
        }
    }
    void Image::saturate(){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.s += 0.1;
                if (p.s > 1){
                    p.s = 1;
                }
            }
        }
    }
    void Image::saturate(double amount){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.s += amount;
                if (p.s > 1){
                    p.s = 1;
                }
            }
        }
    }
    void Image::desaturate(){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.s -= 0.1;
                if (p.s < 0){
                    p.s = 0;
                }
            }
        }
    }
    void Image::desaturate(double amount){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.s -= amount;
                if (p.s < 0){
                    p.s = 0;
                }
            }
        }
    }
    void Image::grayscale(){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.s = 0;
            }
        }
    }
    void Image::rotateColor(double degrees){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                p.h += degrees;
                if (p.h > 360) {
                    p.h -= 360;
                } else if (p.h < 0) {
                    p.h = 360 + p.h;
                }
            }
        }
    }
    void Image::illinify(){
        for (unsigned i = 0; i < width(); i++){
            for (unsigned j = 0; j < height(); j++) {
                HSLAPixel & p = getPixel(i,j);
                double diffOrange = abs(p.h - 11);
                double diffBlue = abs(p.h - 216);
                if (diffOrange <= diffBlue) {
                    p.h = 11;
                } else {
                    p.h = 216;
                }
            }
        }
    }
    void Image::scale(double factor){
        PNG * old = new PNG(*this);
        resize(width()* factor, height() * factor);
        for (unsigned i = 0; i < width(); i++) {
            for (unsigned j = 0; j < height(); j++) {
                getPixel(i,j).s = old->getPixel(i/factor,j/factor).s;
                getPixel(i,j).h = old->getPixel(i/factor,j/factor).h;
                getPixel(i,j).l = old->getPixel(i/factor,j/factor).l;
                getPixel(i,j).a = old->getPixel(i/factor,j/factor).a;
                /*
                if (factor < 1) {
                    getPixel(i,j).s = old->getPixel(i/factor,j/factor).s;
                    getPixel(i,j).h = old->getPixel(i/factor,j/factor).h;
                    getPixel(i,j).l = old->getPixel(i/factor,j/factor).l;
                    getPixel(i,j).a = old->getPixel(i/factor,j/factor).a;
                } else if (factor > 1) {
                    getPixel(i,j).s = old->getPixel(i/factor,j/factor).s;
                    getPixel(i,j).h = old->getPixel(i/factor,j/factor).h;
                    getPixel(i,j).l = old->getPixel(i/factor,j/factor).l;
                    getPixel(i,j).a = old->getPixel(i/factor,j/factor).a;
                }
                */
            }
        }
        delete old;    
    }
    void Image::scale(unsigned w, unsigned h){
        //缩小 10，5 -- 5，3 =》 5/10 * 5 = 2.5 
        //放大 10，5 -- 20，30 =》 20/10 * 5 = 10
        double factorW = double(w) / width();
         double factorH =  double(h) / height();
        if (factorW* height() <= h){
            scale(factorW);
        } else{
            scale(factorH);
        }
    }
    

}