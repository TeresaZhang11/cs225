#include "Image.h"
#include "StickerSheet.h"
using namespace cs225;
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image mybase; 
  mybase.readFromFile("../mybase.png");
  Image mysticker1;    
  mysticker1.readFromFile("../mysticker1.png");
  Image mysticker2; 
  mysticker2.readFromFile("../mysticker2.png");
  StickerSheet myimage(mybase, 2);
  mysticker1.scale(0.7);
  mysticker2.scale(0.2);
  myimage.addSticker(mysticker1, 60, 90);
  myimage.addSticker(mysticker2, 55, 200);
  Image output = myimage.render();
  output.scale(2);
  output.writeToFile("../myImage.png");

  return 0;
}
