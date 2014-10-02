#ifndef LaserMaze_Bitmap_h
#define LaserMaze_Bitmap_h

struct RGBQUAD             /**** Colormap entry structure ****/
{
    int  rgbBlue;          /* Blue value */
    int  rgbGreen;         /* Green value */
    int  rgbRed;           /* Red value */
};

class Bitmap {
  public:
    int width;
    int height;
    RGBQUAD** pixels;

    Bitmap(const char* filename);
    ~Bitmap();
  private:
};

#endif
