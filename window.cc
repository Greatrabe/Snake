#include <iomanip>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include "window.h"
#include "bitmap.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
 // XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
 // XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawBlock(int x, int y, int colour)
{
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x*10, y*10, 10, 10);
}

void Xwindow::draw(int x, int y, Bitmap &bmp) {
    int pieceColor = 1, sum, sum2, wid, red, green, blue, cyan, magenta, yellow;

    for (int i = bmp.height - 1; i >= 0; i--) {
        for (int j = 0; j < bmp.width; j++) {
            wid = 0;
            red = bmp.pixels[i][j].rgbRed;
            green = bmp.pixels[i][j].rgbGreen;
            blue = bmp.pixels[i][j].rgbBlue;
            sum = (red << 16) + (green << 8) + blue;
	    //cout << i << " " << j << endl;;
            XSetForeground(d, gc, sum);
            do{
                wid++;
                red = bmp.pixels[i][j+wid].rgbRed;
                green = bmp.pixels[i][j+wid].rgbGreen;
                blue = bmp.pixels[i][j+wid].rgbBlue;
                sum2 = (red << 16) + (green << 8) + blue;
            }
            while (sum2 == sum && j + wid  + 1 < bmp.width);
            
            //XDrawPoint(d, w, gc, x+j, y+(bmp.height-i));
            XFillRectangle(d, w, gc, x+j, y+(bmp.height-i), wid, 1);    
            j = j + wid - 1;
        }
    }
}

void Xwindow::monodraw(int x, int y, Bitmap &bmp) {
    int pieceColor = 1, sum;

    XSetForeground(d, gc, colours[0]);
    XFillRectangle(d, w, gc, 0, 0, bmp.width, bmp.height);
    XSetForeground(d, gc, colours[1]);
    for (int i = bmp.height - 1; i >= 0; i--) {
        for (int j = 0; j < bmp.width; j++) {
            sum = bmp.pixels[i][j].rgbRed + bmp.pixels[i][j].rgbGreen + bmp.pixels[i][j].rgbBlue;
            if (sum < 300)
            {
                XDrawPoint(d, w, gc, x+j, y+(bmp.height-i));    
            }
        }
    }
}

/*void Xwindow::drawSmallString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    Font f = XLoadFont(d, "6x13");
    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f;
    XDrawText(d, w, gc, x, y, &ti, 1);
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);
}*/

/*void Xwindow::drawLargeString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    //    XChangeGC(d, gc, 500, GCLineWidth);
    //    XSetLineAttributes(d, gc, 10000, LineSolid, CapNotLast, JoinMiter);
    
    XFontStruct *fontInfo;
    char *fontName = (char *)"*-times-medium-r-*-50-*";
    fontInfo = XLoadQueryFont(d, fontName);
    if (fontInfo) {
        XSetFont(d, gc, fontInfo->fid);
    } else {
        cerr << "ERROR: Failed to load the requested font." << endl;
    }
    
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);
}*/

/*void Xwindow::drawBigString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
    ostringstream name;
    name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";
    
    XFontStruct * f = XLoadQueryFont(d, name.str().c_str());
    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f->fid;
    XDrawText(d, w, gc, x, y, &ti, 1);
    XSetForeground(d, gc, colours[Black]);
    XFlush(d);

}*/


/*void Xwindow::notify(int x, int y, int width, int height, Pieces *pieceOnIt, int color) {
    fillRectangle(x, y+14, width, height-14, color); // undraw the cell
    if (pieceOnIt == NULL) {
        return;
    }
    string pieceColor = pieceOnIt->getColor();
    if (pieceOnIt) {
        if (pieceOnIt->getName() == "king") {
            draw(x, y, width, height, "king.txt", color, pieceColor);
        } else if (pieceOnIt->getName() == "queen") {
            draw(x, y, width, height, "queen.txt", color, pieceColor);
        } else if (pieceOnIt->getName() == "bishop") {
            draw(x, y, width, height, "bishop.txt", color, pieceColor);
        } else if (pieceOnIt->getName() == "knight") {
            draw(x, y, width, height, "knight.txt", color, pieceColor);
        } else if (pieceOnIt->getName() == "rook") {
            draw(x, y, width, height, "rook.txt", color, pieceColor);
        } else if (pieceOnIt->getName() == "pawn") {
            draw(x, y, width, height, "pawn.txt", color, pieceColor);
        }
    }
}*/



/*if (pieceOnIt->getColor() == "white") {
 string temp = "p";
 temp[0] = pieceOnIt->getName()[0]-'a'+'A';
 drawBigString(x + 40, y + 60, temp, Xwindow::White);
 } else if (pieceOnIt->getColor() == "black") {
 string temp = "p";
 temp[0] = pieceOnIt->getName()[0];
 drawBigString(x + 40, y + 60, temp, Xwindow::Black);
 }*/









