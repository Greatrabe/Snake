#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "bitmap.h"

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
    int width, height;

 public:
  Xwindow(int width=800, int height=800);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  //  void drawSmallString(int x, int y, std::string msg, int colour=Black);
  //void drawLargeString(int x, int y, std::string msg, int colour=Black);
    
    // Draws a string
  //  void drawBigString(int x, int y, std::string msg, int colour=Black);
    
  //  void notify(int x, int y, int width, int height, Pieces *pieceOnIt, int colour=Black);
    
    void draw(int x, int y, Bitmap &bmp);
    void monodraw(int x, int y, Bitmap &bmp);
    void drawBlock(int x, int y, int colour);

};

#endif
